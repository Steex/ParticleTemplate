#ifndef _PSYS_STATIC_EMIT_SHAPE_RECT_INCLUDED_
#define _PSYS_STATIC_EMIT_SHAPE_RECT_INCLUDED_


#include "../emit_shape.h"
#include "../fetcher.h"


namespace ParticlesStatic
{
    class ParamInfoHolder;


    class EmitShape_Rect: public EmitShape
    {
    public:

        EmitShape_Rect(iXml *_xml);
        virtual ~EmitShape_Rect() {}

        virtual Placement create(Float _norm_emit_time);

    private:

        Rect emit_rect;

        Fetcher<Float> *fly_angle_fetcher;
    };
}


#endif // _PSYS_STATIC_EMIT_SHAPE_RECT_INCLUDED_
