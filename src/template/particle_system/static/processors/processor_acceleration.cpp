#include "head.h"

#include "processor_acceleration.h"
#include "../param_info_holder.h"
#include "../processor_factory.h"



static const ParticlesStatic::ProcessorRegistrator<ParticlesStatic::Processor_Acceleration> registrator("acceleration");



ParticlesStatic::Processor_Acceleration::Processor_Acceleration(iXml *_xml, ParamInfoHolder& _param_info)
    : Processor        (_xml)
    , current_particle (nullptr)
    , position         (current_particle, _param_info.registerParam<Vector2>("position"))
    , velocity         (current_particle, _param_info.registerParam<Vector2>("velocity"))
    , accel            (0.0f, 0.0f)
{
    accel << _xml->getAttribute("acceleration");
}



ParticlesStatic::Processor_Acceleration::~Processor_Acceleration()
{
}



void ParticlesStatic::Processor_Acceleration::initParticles(Byte *_start, USize _stride, USize _count)
{
}



void ParticlesStatic::Processor_Acceleration::updateParticles(Byte *_start, USize _stride, USize _count, Float _tick)
{
    for (USize i = 0; i < _count; ++i)
    {
        current_particle = _start + _stride * i;

        *position += *velocity * _tick;
        *velocity += accel * _tick;
    }
}
