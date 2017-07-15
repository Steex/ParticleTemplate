#include "head.h"

#include "processor_rotation.h"
#include "../param_info_holder.h"
#include "../processor_factory.h"



static const ParticlesStatic::ProcessorRegistrator<ParticlesStatic::Processor_Rotation> registrator("rotation");



ParticlesStatic::Processor_Rotation::Processor_Rotation(iXml *_xml, ParamInfoHolder& _param_info)
    : Processor        (_xml)
    , current_particle (nullptr)
    , angle            (current_particle, _param_info.registerParam<Float>("angle"))
    , rot_speed        (current_particle, _param_info.registerParam<Float>("rot_speed"))
    , speed_range      (0.0f, 0.0f)
{
    speed_range << _xml->getAttribute("rotation_speed");
    speed_range.min *= Math::DEG_TO_RAD;
    speed_range.max *= Math::DEG_TO_RAD;
}



ParticlesStatic::Processor_Rotation::~Processor_Rotation()
{
}



void ParticlesStatic::Processor_Rotation::initParticles(Byte *_start, USize _stride, USize _count)
{
    for (USize i = 0; i < _count; ++i)
    {
        current_particle = _start + _stride * i;

        *rot_speed = Math::random(speed_range);
    }
}



void ParticlesStatic::Processor_Rotation::updateParticles(Byte *_start, USize _stride, USize _count, Float _tick)
{
    for (USize i = 0; i < _count; ++i)
    {
        current_particle = _start + _stride * i;

        *angle += *rot_speed * _tick;
    }
}
