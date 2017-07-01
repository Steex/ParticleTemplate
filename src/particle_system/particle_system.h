#ifndef _PARTICLE_PARAMS_INFO_INCLUDED_
#define _PARTICLE_PARAMS_INFO_INCLUDED_


#include "param_info_holder.h"


namespace Particles
{
    class Processor;
    class Renderer;


    class ParticleSystem
    {
    public:

        ParticleSystem();
        ~ParticleSystem();

        void load();
        void update(Float _tick);
        void render(Renderer *_renderer);

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


#endif // _PARTICLE_PARAMS_INFO_INCLUDED_
