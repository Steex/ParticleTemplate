#ifndef _PSYS_PARTICLE_PARAMS_INFO_INCLUDED_
#define _PSYS_PARTICLE_PARAMS_INFO_INCLUDED_


#include "param_info_holder.h"


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

        void update(Float _tick);
        void inspect(Inspector *_inspector) const;

        USize getMaxCount() const { return max_particles; }

    private:

        typedef std::vector<Processor*> ProcessorList;


        ParamInfoHolder param_info;
        Emitter *emitter;
        ProcessorList processors;
        OriginalValuesRestorer *values_restorer;
        USize max_particles;
        USize particle_count;
        USize particle_size;
        Byte *particle_data;
        Float create_acc;
    };
}


#endif // _PSYS_PARTICLE_PARAMS_INFO_INCLUDED_
