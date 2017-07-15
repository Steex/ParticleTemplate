#ifndef _PSYS_STATIC_PROCESSOR_ROTATION_INCLUDED_
#define _PSYS_STATIC_PROCESSOR_ROTATION_INCLUDED_


#include "../processor.h"
#include "../param_accessor.h"


namespace ParticlesStatic
{
    class ParamInfoHolder;


    class Processor_Rotation: public Processor
    {
    public:

        Processor_Rotation(iXml *_xml, ParamInfoHolder& _param_info);
        virtual ~Processor_Rotation();

        virtual void initParticles(Byte *_start, USize _stride, USize _count);
        virtual void updateParticles(Byte *_start, USize _stride, USize _count, Float _tick);

    private:

        Byte *current_particle;
        ParamAccessor<Float> angle;
        ParamAccessor<Float> rot_speed;

        Range<Float> speed_range;
    };
}


#endif // _PSYS_STATIC_PROCESSOR_ROTATION_INCLUDED_
