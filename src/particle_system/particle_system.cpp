#include "head.h"

#include "particle_system.h"
#include "base_params.h"
#include "renderer.h"
#include "processor_rotation.h"
#include "processor_acceleration.h"



Particles::ParticleSystem::ParticleSystem()
    : param_info     ()
    , processors     ()
    , max_particles  (0)
    , particle_count (0)
    , particle_size  (0)
    , particle_data  (nullptr)
    , create_acc     (0.0f)
{
}



Particles::ParticleSystem::~ParticleSystem()
{
    delete[] particle_data;
}



void Particles::ParticleSystem::load()
{
    // Prepare standard data.
    param_info.registerParam<Bool>("dead");
    param_info.registerParam<Vector2>("position");
    param_info.registerParam<Float>("scale");
    param_info.registerParam<Float>("angle");
    param_info.registerParam<Color>("color");

    // Create processing blocks.
    ProcessorRotation *rotation = new ProcessorRotation(param_info);
    rotation->load();
    processors.push_back(rotation);

    ProcessorAcceleration *gravity = new ProcessorAcceleration(param_info);
    gravity->load();
    processors.push_back(gravity);

    // Allocate particles.
    max_particles = 100;
    particle_size = param_info.getTotalSize();
    particle_data = new Byte[particle_size * max_particles];
}



void Particles::ParticleSystem::update(Float _tick)
{
    // Process existing particles.
    if (particle_count > 0)
    {
        // Update particles.
        for (ProcessorList::iterator proc = processors.begin(); proc != processors.end(); ++proc)
        {
            (*proc)->updateParticles(particle_data, particle_size, particle_count, _tick);
        }

        // Clean dead particles.
        Byte *dest_particle = particle_data;

        for (USize i = 0; i < particle_count; ++i)
        {
            BaseParticleParams *current_particle = (BaseParticleParams*)(particle_data + particle_size * i);
            if (current_particle->dead)
            {
                memmove(dest_particle, current_particle, particle_size);
                dest_particle += particle_size;
            }
        }
    }

    // Emit new particles.
    Float particle_per_second = 10;
    create_acc += _tick * particle_per_second;
    USize create_amount = (USize)create_acc;
    if (create_amount > 1)
    {
        create_acc -= create_amount;
        create_amount = min(create_amount, max_particles - particle_count);
        for (USize i = 0; i < create_amount; ++i)
        {
            BaseParticleParams *current_particle = (BaseParticleParams*)(particle_data + particle_size * (particle_count + i));
            current_particle->dead = false;
            current_particle->position = Vector2(Math::random(-100.f, 100.0f), Math::random(-100.f, 100.0f));
            current_particle->angle = 0.0f; //Math::random(Math::TWO_PI);
            current_particle->scale = 1.0f; //Math::random(0.8, 1.2);
            current_particle->color = Colors::White;
        }

        for (ProcessorList::iterator proc = processors.begin(); proc != processors.end(); ++proc)
        {
            (*proc)->initParticles(particle_data + particle_size * particle_count, particle_size, create_amount);
        }

        particle_count += create_amount;
    }
}



void Particles::ParticleSystem::render(Renderer *_renderer)
{
    _renderer->renderParticles(particle_data, particle_size, particle_count);
}
