#include "head.h"

#include "emitter.h"
#include "emit_shape.h"
#include "emit_shape_factory.h"
#include "param_info_holder.h"
#include "fetcher_factory.h"


Particles::Emitter::Emitter(iXml *_xml, ParamInfoHolder& _param_info)
    : current_particle (nullptr)
    , position         (current_particle, _param_info.registerParam<Vector2>("position"))
    , velocity         (current_particle, _param_info.registerParam<Vector2>("velocity"))
    , scale            (current_particle, _param_info.registerParam<Float>("scale"))
    , angle            (current_particle, _param_info.registerParam<Float>("angle"))
    , color            (current_particle, _param_info.registerParam<Color>("color"))
    , speed_fetcher    (nullptr)
    , scale_fetcher    (nullptr)
    , angle_fetcher    (nullptr)
    , color_fetcher    (nullptr)
{
    // Initialize fetchers.
    if (iXml *fetcher_node = _xml->getChild("fetcher_speed"))
    {
        speed_fetcher = FetcherFactory::create<Float>(fetcher_node);
    }

    if (iXml *fetcher_node = _xml->getChild("fetcher_scale"))
    {
        scale_fetcher = FetcherFactory::create<Float>(fetcher_node);
    }
    else
    {
        scale_fetcher = new Fetcher_Const<Float>(1.0f);
    }

    if (iXml *fetcher_node = _xml->getChild("fetcher_angle"))
    {
        angle_fetcher = FetcherFactory::create<Float>(fetcher_node);
    }
    else
    {
        angle_fetcher = new Fetcher_Const<Float>(0.0f);
    }

    if (iXml *fetcher_node = _xml->getChild("fetcher_color"))
    {
        color_fetcher = FetcherFactory::create<Color>(fetcher_node);
    }
    else
    {
        color_fetcher = new Fetcher_Const<Color>(Colors::White);
    }

    // Create an emit shape.
    if (iXml *shape_node = _xml->getChild("emit_shape"))
    {
        emit_shape = EmitShapeFactory::create(shape_node);
    }
}



Particles::Emitter::~Emitter()
{
}



void Particles::Emitter::createParticle(Byte *_data, Float _norm_emit_time)
{
    EmitShape::Placement placement = emit_shape ? emit_shape->create(_norm_emit_time) : EmitShape::Placement();

    current_particle = _data;

    *position = placement.position;
    if (speed_fetcher)
    {
        *velocity = placement.direction * speed_fetcher->fetch(_norm_emit_time);
    }
    *scale = scale_fetcher->fetch(_norm_emit_time);
    *angle = angle_fetcher->fetch(_norm_emit_time) * Math::DEG_TO_RAD;
    *color = color_fetcher->fetch(_norm_emit_time);
}
