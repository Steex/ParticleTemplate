#ifndef _PSYS_STATIC_PROCESSOR_SCALE_OVER_LIFETIME_INCLUDED_
#define _PSYS_STATIC_PROCESSOR_SCALE_OVER_LIFETIME_INCLUDED_


#include "../processor.h"
#include "../param_accessor.h"
#include "../fetcher.h"


namespace ParticlesStatic
{
    class ParamInfoHolder;


    class Processor_ScaleOverLifetime: public Processor
    {
    public:

        Processor_ScaleOverLifetime(iXml *_xml, ParamInfoHolder& _param_info);
        virtual ~Processor_ScaleOverLifetime();

        virtual void initParticles(Byte *_start, USize _stride, USize _count);
        virtual void updateParticles(Byte *_start, USize _stride, USize _count, Float _tick);

    private:

        Byte *current_particle;
        ParamAccessor<Float> age;
        ParamAccessor<Float> lifetime;
        ParamAccessor<Float> scale;

        Fetcher<Float> *scale_fetcher;
    };
}


#endif // _PSYS_STATIC_PROCESSOR_SCALE_OVER_LIFETIME_INCLUDED_
