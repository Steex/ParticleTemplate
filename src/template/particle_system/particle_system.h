#ifndef _PSYS_PARTICLE_PARAMS_INFO_INCLUDED_
#define _PSYS_PARTICLE_PARAMS_INFO_INCLUDED_


#include "param_info_holder.h"
#include "fetcher.h"


namespace Particles
{
    class Emitter;
    class Processor;
    class OriginalValuesRestorer;
    class Inspector;


    class ParticleSystem
    {
    public:

        ParticleSystem(iXml *_xml);
        ~ParticleSystem();

        Bool isActive() const { return emit_active; }
        void start();
        void pause();
        void resume();

        void update(Float _tick);
        void inspect(Inspector *_inspector) const;

        USize getMaxCount() const { return max_particles; }

    private:

        typedef std::vector<Processor*> ProcessorList;


        USize processEmission(Float _tick);


        ParamInfoHolder param_info;
        Emitter *emitter;
        ProcessorList processors;
        OriginalValuesRestorer *values_restorer;
        USize max_particles;
        USize particle_count;
        USize particle_size;
        Byte *particle_data;

        Bool emit_active;
        Bool emit_looped;
        Fetcher<Float> *emit_density_fetcher;
        Float emit_duration;
        Float emit_time;
        Float emit_last_time;
        std::vector<Float> emit_times; // wrapped by the emit_duration
    };
}


#endif // _PSYS_PARTICLE_PARAMS_INFO_INCLUDED_
