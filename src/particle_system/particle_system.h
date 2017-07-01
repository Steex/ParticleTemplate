#ifndef _PARTICLE_PARAMS_INFO_INCLUDED_
#define _PARTICLE_PARAMS_INFO_INCLUDED_


#include "param_info_holder.h"

namespace Particles
{
    class Processor;


    class ParticleSystem
    {
    public:

        ParticleSystem();
        ~ParticleSystem();

        void load();
        void update(Float _tick);

    private:

        struct BaseParticleParams
        {
            Bool    dead;
            Vector2 position;
            Float   scale;
            Float   angle;
            Color   color;
        };

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


#endif // _PARTICLE_PARAMS_INFO_INCLUDED_
