#ifndef _PSYS_PROCESSOR_ACCELERATION_INCLUDED_
#define _PSYS_PROCESSOR_ACCELERATION_INCLUDED_


#include "processor.h"
#include "param_accessor.h"


namespace Particles
{
    class ParamInfoHolder;


    class ProcessorAcceleration: public Processor
    {
    public:

        ProcessorAcceleration(ParamInfoHolder& _param_info);
        virtual ~ProcessorAcceleration();

        virtual void load();
        virtual void initParticles(Byte *_start, USize _stride, USize _count);
        virtual void updateParticles(Byte *_start, USize _stride, USize _count, Float _tick);

    private:

        Byte *current_particle;
        ParamAccessor<Vector2> position;
        ParamAccessor<Vector2> velocity;

        Vector2 accel;
    };
}


#endif // _PSYS_PROCESSOR_ACCELERATION_INCLUDED_
