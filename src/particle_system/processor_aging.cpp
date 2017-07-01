#include "head.h"

#include "processor_aging.h"
#include "param_info_holder.h"



Particles::ProcessorAging::ProcessorAging(ParamInfoHolder& _param_info)
    : current_particle (nullptr)
    , age              (current_particle, _param_info.registerParam<Float>("age"))
    , lifetime         (current_particle, _param_info.registerParam<Float>("lifetime"))
    , dead             (current_particle, _param_info.registerParam<Bool>("dead"))
{

}



Particles::ProcessorAging::~ProcessorAging()
{
}



void Particles::ProcessorAging::load()
{

}



void Particles::ProcessorAging::initParticles(Byte *_start, USize _stride, USize _count)
{
    for (USize i = 0; i < _count; ++i)
    {
        current_particle = _start + _stride * i;

        *age      = 0.0f;
        *lifetime = Math::random(1.0f, 2.0f);
    }
}



void Particles::ProcessorAging::updateParticles(Byte *_start, USize _stride, USize _count, Float _tick)
{
    for (USize i = 0; i < _count; ++i)
    {
        current_particle = _start + _stride * i;

        Bool deadv1 = *dead;

        *age += _tick;
        *dead = *dead || *age >= *lifetime;
        Bool deadv2 = *dead;
        int n = 0;
    }
}
