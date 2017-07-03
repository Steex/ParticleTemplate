#include "head.h"

#include "processor_acceleration.h"
#include "param_info_holder.h"



Particles::ProcessorAcceleration::ProcessorAcceleration(ParamInfoHolder& _param_info)
    : current_particle (nullptr)
    , position         (current_particle, _param_info.registerParam<Vector2>("position"))
    , velocity         (current_particle, _param_info.registerParam<Vector2>("velocity"))
    , accel            (0.0f, 100.0f)
{

}



Particles::ProcessorAcceleration::~ProcessorAcceleration()
{
}



void Particles::ProcessorAcceleration::load()
{

}



void Particles::ProcessorAcceleration::initParticles(Byte *_start, USize _stride, USize _count)
{
    for (USize i = 0; i < _count; ++i)
    {
        current_particle = _start + _stride * i;

        Float angle = -Math::HALF_PI + Math::random(-Math::PI * 0.2f, Math::PI * 0.2f);
        Float speed = Math::random(100.0f, 200.0f);
        velocity->x = Math::cos(angle) * speed;
        velocity->y = Math::sin(angle) * speed;
    }
}



void Particles::ProcessorAcceleration::updateParticles(Byte *_start, USize _stride, USize _count, Float _tick)
{
    for (USize i = 0; i < _count; ++i)
    {
        current_particle = _start + _stride * i;

        *position += *velocity * _tick;
        *velocity += accel * _tick;
    }
}