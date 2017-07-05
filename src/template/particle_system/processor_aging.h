#ifndef _PSYS_PROCESSOR_AGING_INCLUDED_
#define _PSYS_PROCESSOR_AGING_INCLUDED_


#include "processor.h"
#include "param_accessor.h"


namespace Particles
{
    class ParamInfoHolder;


    class ProcessorAging: public Processor
    {
    public:

        ProcessorAging(iXml *_xml, ParamInfoHolder& _param_info);
        virtual ~ProcessorAging();

        virtual void initParticles(Byte *_start, USize _stride, USize _count);
        virtual void updateParticles(Byte *_start, USize _stride, USize _count, Float _tick);

    private:

        Range<Float> lifetime_range;

        Byte *current_particle;
        ParamAccessor<Float> age;
        ParamAccessor<Float> lifetime;
        ParamAccessor<Bool>  dead;
    };
}


#endif // _PSYS_PROCESSOR_AGING_INCLUDED_
