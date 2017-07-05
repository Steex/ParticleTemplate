#include "head.h"

#include "processor_aging.h"
#include "param_info_holder.h"
#include "processor_factory.h"



static const Particles::ProcessorRegistrator<Particles::ProcessorAging> registrator("aging");



Particles::ProcessorAging::ProcessorAging(iXml *_xml, ParamInfoHolder& _param_info)
    : lifetime_range   (1.0f, 1.0f)
    , current_particle (nullptr)
    , age              (current_particle, _param_info.registerParam<Float>("age"))
    , lifetime         (current_particle, _param_info.registerParam<Float>("lifetime"))
    , dead             (current_particle, _param_info.registerParam<Bool>("dead"))
{
    lifetime_range << _xml->getAttribute("lifetime");
}



Particles::ProcessorAging::~ProcessorAging()
{
}



void Particles::ProcessorAging::initParticles(Byte *_start, USize _stride, USize _count)
{
    for (USize i = 0; i < _count; ++i)
    {
        current_particle = _start + _stride * i;

        *age      = 0.0f;
        *lifetime = Math::random(lifetime_range);
    }
}



void Particles::ProcessorAging::updateParticles(Byte *_start, USize _stride, USize _count, Float _tick)
{
    for (USize i = 0; i < _count; ++i)
    {
        current_particle = _start + _stride * i;

        *age += _tick;
        *dead = *dead || *age >= *lifetime;
    }
}
