#ifndef _PSYS_PARTICLE_PARAMS_INFO_INCLUDED_
#define _PSYS_PARTICLE_PARAMS_INFO_INCLUDED_


#include "param_info_holder.h"


namespace Particles
{
    class Processor;
    class Inspector;


    class ParticleSystem
    {
    public:

        ParticleSystem();
        ~ParticleSystem();

        void load();
        void update(Float _tick);
        void inspect(Inspector *_inspector) const;

        USize getMaxCount() const { return max_particles; }

    private:

        typedef std::vector<Processor*> ProcessorList;


        ParamInfoHolder param_info;
        ProcessorList processors;
        USize max_particles;
        USize particle_count;
        USize particle_size;
        Byte *particle_data;
        Float create_acc;
    };
}


#endif // _PSYS_PARTICLE_PARAMS_INFO_INCLUDED_
