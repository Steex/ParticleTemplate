#ifndef _PSYS_PROCESSOR_ACCELERATION_INCLUDED_
#define _PSYS_PROCESSOR_ACCELERATION_INCLUDED_


#include "../processor.h"
#include "../param_accessor.h"


namespace Particles
{
    class ParamInfoHolder;


    class Processor_Acceleration: public Processor
    {
    public:

        Processor_Acceleration(iXml *_xml, ParamInfoHolder& _param_info);
        virtual ~Processor_Acceleration();

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
