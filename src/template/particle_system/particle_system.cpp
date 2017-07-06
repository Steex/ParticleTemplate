#include "head.h"

#include "particle_system.h"
#include "base_params.h"
#include "emitter.h"
#include "processor.h"
#include "processor_factory.h"
#include "original_values_restorer.h"
#include "inspector.h"



Particles::ParticleSystem::ParticleSystem(iXml *_xml)
    : param_info      ()
    , processors      ()
    , values_restorer (nullptr)
    , max_particles   (0)
    , particle_count  (0)
    , particle_size   (0)
    , particle_data   (nullptr)
    , time            (0.0f)
    , create_acc      (0.0f)
{
    // Prepare standard data.
    param_info.registerParam<Bool>("dead");
    param_info.registerParam<Vector2>("position");
    param_info.registerParam<Float>("scale");
    param_info.registerParam<Float>("angle");
    param_info.registerParam<Color>("color");

    // Create an emitter.
    emitter = new Emitter(_xml->getChild("emitter"), param_info);

    // Create processing blocks.
    if (iXml *processor_list_node = _xml->getChild("processors"))
    {
        iXml::TAG_LIST processor_nodes;
        processor_list_node->getChildren("processor", processor_nodes);

        FOREACH (iXml::TAG_LIST::const_iterator, processor_node, processor_nodes)
        {
            String processor_type = (*processor_node)->getAttribute("type");
            Processor *processor = ProcessorFactory::create(processor_type, *processor_node, param_info);
            processors.push_back(processor);
        }
    }

    if (!param_info.getStoredValues().empty())
    {
        values_restorer = new OriginalValuesRestorer(param_info);
    }

    // Allocate particles.
    max_particles << _xml->getAttribute("max_particles");
    particle_size = param_info.getTotalSize();
    particle_data = new Byte[particle_size * max_particles];
}



Particles::ParticleSystem::~ParticleSystem()
{
    delete[] particle_data;
}



void Particles::ParticleSystem::update(Float _tick)
{
    // Process existing particles.
    if (particle_count > 0)
    {
        // Restore values.
        if (values_restorer)
        {
            values_restorer->restoreValues(particle_data, particle_size, particle_count);
        }

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
    time += _tick;
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
            emitter->createParticle(particle_data + particle_size * (particle_count + i), Math::fmod(time, 1.0f));
        }

        FOREACH (ProcessorList::iterator, processor, processors)
        {
            (*processor)->initParticles(particle_data + particle_size * particle_count, particle_size, create_amount);
        }

        // Store values.
        if (values_restorer)
        {
            values_restorer->storeValues(particle_data + particle_size * particle_count, particle_size, create_amount);
        }

        // Apply the logic.
        FOREACH (ProcessorList::iterator, processor, processors)
        {
            (*processor)->updateParticles(particle_data + particle_size * particle_count, particle_size, create_amount, 0.0f);
        }

        // Update the particle count.
        particle_count += create_amount;
    }
}



void Particles::ParticleSystem::inspect(Inspector *_inspector) const
{
    _inspector->inspect(particle_data, particle_size, particle_count);
}
