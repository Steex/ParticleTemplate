#ifndef _PSYS_PROCESSOR_ROTATION_INCLUDED_
#define _PSYS_PROCESSOR_ROTATION_INCLUDED_


#include "processor.h"
#include "param_accessor.h"


namespace Particles
{
    class ParamInfoHolder;


    class ProcessorRotation: public Processor
    {
    public:

        ProcessorRotation(iXml *_xml, ParamInfoHolder& _param_info);
        virtual ~ProcessorRotation();

        virtual void initParticles(Byte *_start, USize _stride, USize _count);
        virtual void updateParticles(Byte *_start, USize _stride, USize _count, Float _tick);

    private:

        Range<Float> speed_range;

        Byte *current_particle;
        ParamAccessor<Float> angle;
        ParamAccessor<Float> rot_speed;
    };
}


#endif // _PSYS_PROCESSOR_ROTATION_INCLUDED_
