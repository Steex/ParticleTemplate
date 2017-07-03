#include "head.h"

#include "emitter_rect.h"
#include "param_info_holder.h"



Particles::EmitterRect::EmitterRect(ParamInfoHolder& _param_info)
    : emit_rect        (-100.0f, -100.0f, 100.0f, 100.0f)
    , current_particle (nullptr)
    , position         (current_particle, _param_info.registerParam<Vector2>("position"))
    , scale            (current_particle, _param_info.registerParam<Float>("scale"))
    , angle            (current_particle, _param_info.registerParam<Float>("angle"))
    , color            (current_particle, _param_info.registerParam<Color>("color"))
{

}



void Particles::EmitterRect::load()
{

}



void Particles::EmitterRect::createParticle(Byte *_data)
{
    current_particle = _data;
    EmitParams emit_params = createEmitParams();

    *position = createEmitParams().position;
    *scale = Math::random(0.8f, 1.2f);
    *angle = Math::random(Math::TWO_PI);
    *color = Color(Math::random(), Math::random(), Math::random());
}



Particles::EmitterRect::EmitParams Particles::EmitterRect::createEmitParams()
{
    EmitParams params;
    params.position = emit_rect.getRandomPoint();

    return params;
}
