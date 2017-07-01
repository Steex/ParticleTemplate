#ifndef _PSYS_EMITTER_RECT_INCLUDED_
#define _PSYS_EMITTER_RECT_INCLUDED_


#include "emitter.h"
#include "param_accessor.h"


namespace Particles
{
    class ParamInfoHolder;


    class EmitterRect: public Emitter
    {
    public:

        EmitterRect(ParamInfoHolder& _param_info);
        virtual ~EmitterRect() {}

        virtual void load();
        virtual void createParticle(Byte *_data);

    protected:

        struct EmitParams
        {
            Vector2 position;
            Vector2 velocity;
        };

        virtual EmitParams createEmitParams();

    protected:

        Rect emit_rect;

        Byte *current_particle;
        ParamAccessor<Vector2> position;
        ParamAccessor<Float> scale;
        ParamAccessor<Float> angle;
        ParamAccessor<Color> color;
    };
}


#endif // _PSYS_EMITTER_RECT_INCLUDED_
