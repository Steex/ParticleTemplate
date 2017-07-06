#include "head.h"

#include "particle_system.h"
#include "base_params.h"
#include "emitter.h"
#include "processor.h"
#include "processor_factory.h"
#include "fetcher_factory.h"
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
    , emit_active     (false)
    , emit_looped     (false)
    , emit_density_fetcher (nullptr)
    , emit_duration   (1.0f)
    , emit_time       (0.0f)
    , emit_last_time  (0.0f)
    , emit_times      ()
{
    // Load parameters.
    emit_looped    << _xml->getAttribute("looped");
    emit_duration  << _xml->getAttribute("duration");
    emit_density_fetcher = FetcherFactory::create<Float>(_xml->getChild("fetcher_density"));

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
            Processor *processor = ProcessorFactory::create(*processor_node, param_info);
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



void Particles::ParticleSystem::start()
{
    emit_time = 0.0f;
    emit_last_time = 0.0f;
    emit_active = true;
}



void Particles::ParticleSystem::pause()
{
    emit_active = false;
}



void Particles::ParticleSystem::resume()
{
    emit_active = true;
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
    if (emit_active)
    {
        USize emit_count = processEmission(_tick);
        if (emit_count > 0)
        {
            // Zero the particles data (including the 'dead' field).
            memset(particle_data + particle_size * particle_count, 0, particle_size * emit_count);

            // Init new particles.
            for (USize i = 0; i < emit_count; ++i)
            {
                emitter->createParticle(particle_data + particle_size * (particle_count + i), emit_times[i] / emit_duration);
            }

            FOREACH (ProcessorList::iterator, processor, processors)
            {
                (*processor)->initParticles(particle_data + particle_size * particle_count, particle_size, emit_count);
            }

            // Store values.
            if (values_restorer)
            {
                values_restorer->storeValues(particle_data + particle_size * particle_count, particle_size, emit_count);
            }

            // Apply the logic.
            FOREACH (ProcessorList::iterator, processor, processors)
            {
                (*processor)->updateParticles(particle_data + particle_size * particle_count, particle_size, emit_count, 0.0f);
            }

            // Update the particle count.
            particle_count += emit_count;
        }
    }
}



USize Particles::ParticleSystem::processEmission(Float _tick)
{
    if (!emit_active)
    {
        return 0;
    }

    Float next_time = emit_time + _tick;
    if (!emit_looped && next_time >= emit_duration)
    {
        next_time = emit_duration;
        emit_active = false;
    }

    Float emit_dencity = emit_density_fetcher->fetch(Math::fmod(emit_time, emit_duration) / emit_duration);
    Float emit_interval = 1.0f / emit_dencity;
    USize emit_count = (USize)((next_time - emit_last_time) / emit_interval);

    if (emit_count > 0)
    {
        if (emit_times.size() < emit_count)
        {
            emit_times.resize(emit_count + 4); // add some extra space to minimize potential reallocations
        }

        if (emit_looped)
        {
            for (USize i = 0; i < emit_count; ++i)
            {
                emit_times[i] = Math::fmod(emit_last_time + emit_interval * (i + 1), emit_duration);
            }
        }
        else
        {
            for (USize i = 0; i < emit_count; ++i)
            {
                emit_times[i] = emit_last_time + emit_interval * i;
            }
        }

        emit_last_time += emit_interval * emit_count;
    }

    emit_time = next_time;

    return emit_count;
}



void Particles::ParticleSystem::inspect(Inspector *_inspector) const
{
    _inspector->inspect(particle_data, particle_size, particle_count);
}
