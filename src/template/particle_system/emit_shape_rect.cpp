#include "head.h"

#include "emit_shape_rect.h"
#include "param_info_holder.h"
#include "fetcher_factory.h"
#include "emit_shape_factory.h"



static const Particles::EmitShapeRegistrator<Particles::EmitShape_Rect> registrator("rectangle");



Particles::EmitShape_Rect::EmitShape_Rect(iXml *_xml)
    : emit_rect         (parse<Rect>(_xml->getAttribute("emit_rect")))
    , fly_angle_fetcher (nullptr)
{
    if (iXml *fetcher_node = _xml->getChild("fetcher_fly_angle"))
    {
        fly_angle_fetcher = FetcherFactory::create<Float>(fetcher_node);
    }
}



Particles::EmitShape::Placement Particles::EmitShape_Rect::create(Float _norm_emit_time)
{
    Placement placement;

    placement.position = emit_rect.getRandomPoint();

    if (fly_angle_fetcher)
    {
        Float angle = fly_angle_fetcher->fetch(_norm_emit_time) * Math::DEG_TO_RAD;
        placement.direction = Vector2(Math::cos(angle), Math::sin(angle));
    }
    else
    {
        placement.direction = placement.position.getSafeNormalized();
    }

    return placement;
}
