#include "head.h"

#include "processor_rotation.h"
#include "param_info_holder.h"
#include "processor_factory.h"



static const Particles::ProcessorRegistrator<Particles::ProcessorRotation> registrator("rotation");



Particles::ProcessorRotation::ProcessorRotation(ParamInfoHolder& _param_info)
    : current_particle (nullptr)
    , angle            (current_particle, _param_info.registerParam<Float>("angle"))
    , rot_speed        (current_particle, _param_info.registerParam<Float>("rot_speed"))
{

}



Particles::ProcessorRotation::~ProcessorRotation()
{
}



void Particles::ProcessorRotation::load()
{

}



void Particles::ProcessorRotation::initParticles(Byte *_start, USize _stride, USize _count)
{
    for (USize i = 0; i < _count; ++i)
    {
        current_particle = _start + _stride * i;

        *rot_speed = Math::random(-Math::PI, Math::PI);
    }
}



void Particles::ProcessorRotation::updateParticles(Byte *_start, USize _stride, USize _count, Float _tick)
{
    for (USize i = 0; i < _count; ++i)
    {
        current_particle = _start + _stride * i;

        *angle += *rot_speed * _tick;
    }
}
