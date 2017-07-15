#ifndef _PSYS_STATIC_PROCESSOR_AGING_INCLUDED_
#define _PSYS_STATIC_PROCESSOR_AGING_INCLUDED_


#include "../processor.h"
#include "../param_accessor.h"


namespace ParticlesStatic
{
    class ParamInfoHolder;


    class Processor_Aging: public Processor
    {
    public:

        Processor_Aging(iXml *_xml, ParamInfoHolder& _param_info);
        virtual ~Processor_Aging();

        virtual void initParticles(Byte *_start, USize _stride, USize _count);
        virtual void updateParticles(Byte *_start, USize _stride, USize _count, Float _tick);

    private:

        Byte *current_particle;
        ParamAccessor<Float> age;
        ParamAccessor<Float> lifetime;
        ParamAccessor<Bool>  dead;

        Range<Float> lifetime_range;
    };
}


#endif // _PSYS_STATIC_PROCESSOR_AGING_INCLUDED_
