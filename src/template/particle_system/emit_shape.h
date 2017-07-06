#ifndef _PSYS_EMIT_SHAPE_INCLUDED_
#define _PSYS_EMIT_SHAPE_INCLUDED_


#include "emitter.h"
#include "param_accessor.h"


namespace Particles
{
    class ParamInfoHolder;


    class EmitShape
    {
    public:

        struct Placement
        {
            Vector2 position;
            Vector2 direction;
        };


        virtual ~EmitShape() {}

        virtual Placement create(Float _norm_emit_time) = 0;

    protected:

        EmitShape() {}
    };
}


#endif // _PSYS_EMIT_SHAPE_INCLUDED_
