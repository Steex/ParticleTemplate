#include "head.h"

#include "particle_system.h"
#include "base_params.h"
#include "emitter.h"
#include "processor.h"
#include "inspector.h"

#include "emitter_rect.h"
#include "processor_aging.h"
#include "processor_rotation.h"
#include "processor_acceleration.h"
#include "processor_scale_over_lifetime.h"



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


    // Create an emitter.
    emitter = new EmitterRect(param_info);
    emitter->load();

    // Create processing blocks.
    ProcessorAging *aging = new ProcessorAging(param_info);
    aging->load();
    processors.push_back(aging);

    ProcessorRotation *rotation = new ProcessorRotation(param_info);
    rotation->load();
    processors.push_back(rotation);

    ProcessorAcceleration *gravity = new ProcessorAcceleration(param_info);
    gravity->load();
    processors.push_back(gravity);

    ProcessorScaleOverLifetime *scale = new ProcessorScaleOverLifetime(param_info);
    scale->load();
    processors.push_back(scale);

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
        FOREACH (ProcessorList::iterator, processor, processors)
        {
            (*processor)->updateParticles(particle_data, particle_size, particle_count, _tick);
        }

        // Clean dead particles.
        Byte *dest_particle = particle_data;

        for (USize i = 0; i < particle_count; ++i)
        {
            BaseParticleParams *current_particle = (BaseParticleParams*)(particle_data + particle_size * i);
            if (!current_particle->dead)
            {
                memcpy(dest_particle, current_particle, particle_size);
                dest_particle += particle_size;
            }
        }

        // Update the particle count.
        particle_count = (dest_particle - particle_data) / particle_size;
    }

    // Emit new particles.
    Float particle_per_second = 10;
    create_acc += _tick * particle_per_second;
    USize create_amount = (USize)create_acc;
    if (create_amount > 1)
    {
        create_acc -= create_amount;
        create_amount = min(create_amount, max_particles - particle_count);

        // Zero the particles data (including the 'dead' field).
        memset(particle_data + particle_size * particle_count, 0, particle_size * create_amount);

        // Init new particles.
        for (USize i = 0; i < create_amount; ++i)
        {
            emitter->createParticle(particle_data + particle_size * (particle_count + i));
        }

        FOREACH (ProcessorList::iterator, processor, processors)
        {
            (*processor)->initParticles(particle_data + particle_size * particle_count, particle_size, create_amount);
        }

        // Update the particle count.
        particle_count += create_amount;
    }
}



void Particles::ParticleSystem::inspect(Inspector *_inspector) const
{
    _inspector->inspect(particle_data, particle_size, particle_count);
}
