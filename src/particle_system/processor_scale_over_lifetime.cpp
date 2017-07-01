#include "head.h"

#include "processor_scale_over_lifetime.h"
#include "param_info_holder.h"



Particles::ProcessorScaleOverLifetime::ProcessorScaleOverLifetime(ParamInfoHolder& _param_info)
    : current_particle (nullptr)
    , age              (current_particle, _param_info.registerParam<Float>("age"))
    , lifetime         (current_particle, _param_info.registerParam<Float>("lifetime"))
    , scale            (current_particle, _param_info.registerParam<Float>("scale"))
    , scale_fetcher    (NULL)
{

}



Particles::ProcessorScaleOverLifetime::~ProcessorScaleOverLifetime()
{
}



void Particles::ProcessorScaleOverLifetime::load()
{
    //scale_fetcher = new FetcherTransition<Float>(0.5f, 1.5f);

    iCurve *rb_curve = iResourceManager::inst()->getCurve("particles/test.curve", "scale");
    scale_fetcher = new FetcherCurve<Float>(Curve<Float>(Range<Float>(0.0f, 1.0f), rb_curve));
}



void Particles::ProcessorScaleOverLifetime::initParticles(Byte *_start, USize _stride, USize _count)
{
    for (USize i = 0; i < _count; ++i)
    {
        current_particle = _start + _stride * i;

        *scale = scale_fetcher->fetch(0.0f, 0.0f);
    }
}



void Particles::ProcessorScaleOverLifetime::updateParticles(Byte *_start, USize _stride, USize _count, Float _tick)
{
    for (USize i = 0; i < _count; ++i)
    {
        current_particle = _start + _stride * i;

        *scale = scale_fetcher->fetch(*age / *lifetime, 0.0f);
    }
}
