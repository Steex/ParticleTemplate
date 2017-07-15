#include "head.h"

#include "processor_aging.h"
#include "../param_info_holder.h"
#include "../processor_factory.h"



static const ParticlesStatic::ProcessorRegistrator<ParticlesStatic::Processor_Aging> registrator("aging");



ParticlesStatic::Processor_Aging::Processor_Aging(iXml *_xml, ParamInfoHolder& _param_info)
    : Processor        (_xml)
    , current_particle (nullptr)
    , age              (current_particle, _param_info.registerParam<Float>("age"))
    , lifetime         (current_particle, _param_info.registerParam<Float>("lifetime"))
    , dead             (current_particle, _param_info.registerParam<Bool>("dead"))
    , lifetime_range   (1.0f, 1.0f)
{
    lifetime_range << _xml->getAttribute("lifetime");
}



ParticlesStatic::Processor_Aging::~Processor_Aging()
{
}



void ParticlesStatic::Processor_Aging::initParticles(Byte *_start, USize _stride, USize _count)
{
    for (USize i = 0; i < _count; ++i)
    {
        current_particle = _start + _stride * i;

        *age      = 0.0f;
        *lifetime = Math::random(lifetime_range);
    }
}



void ParticlesStatic::Processor_Aging::updateParticles(Byte *_start, USize _stride, USize _count, Float _tick)
{
    for (USize i = 0; i < _count; ++i)
    {
        current_particle = _start + _stride * i;

        *age += _tick;
        *dead = *dead || *age >= *lifetime;
    }
}
