#include "head.h"

#include "processor_scale_over_lifetime.h"
#include "param_info_holder.h"
#include "processor_factory.h"
#include "fetcher_factory.h"



static const Particles::ProcessorRegistrator<Particles::ProcessorScaleOverLifetime> registrator("scale_over_lifetime");



Particles::ProcessorScaleOverLifetime::ProcessorScaleOverLifetime(iXml *_xml, ParamInfoHolder& _param_info)
    : Processor        (_xml)
    , current_particle (nullptr)
    , age              (current_particle, _param_info.registerParam<Float>("age"))
    , lifetime         (current_particle, _param_info.registerParam<Float>("lifetime"))
    , scale            (current_particle, _param_info.registerParam<Float>("scale"))
    , scale_fetcher    (FetcherFactory::create<Float>(_xml->getChild("fetcher_scale")))
{
    _param_info.enableParamRestoring("scale");
}



Particles::ProcessorScaleOverLifetime::~ProcessorScaleOverLifetime()
{
}



void Particles::ProcessorScaleOverLifetime::initParticles(Byte *_start, USize _stride, USize _count)
{
}



void Particles::ProcessorScaleOverLifetime::updateParticles(Byte *_start, USize _stride, USize _count, Float _tick)
{
    for (USize i = 0; i < _count; ++i)
    {
        current_particle = _start + _stride * i;

        *scale *= scale_fetcher->fetch(*age / *lifetime);
    }
}
