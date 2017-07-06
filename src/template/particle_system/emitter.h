#ifndef _PSYS_EMITTER_INCLUDED_
#define _PSYS_EMITTER_INCLUDED_


#include "fetcher.h"
#include "param_accessor.h"


namespace Particles
{
    class EmitShape;
    class ParamInfoHolder;


    class Emitter
    {
    public:

        Emitter(iXml *_xml, ParamInfoHolder& _param_info);
        ~Emitter();

        void createParticle(Byte *_data, Float _norm_emit_time);

    private:

        Byte *current_particle;
        ParamAccessor<Vector2> position;
        ParamAccessor<Vector2> velocity;
        ParamAccessor<Float> scale;
        ParamAccessor<Float> angle;
        ParamAccessor<Color> color;

        Fetcher<Float> *speed_fetcher;
        Fetcher<Float> *scale_fetcher;
        Fetcher<Float> *angle_fetcher;
        Fetcher<Color> *color_fetcher;

        EmitShape *emit_shape;
    };
}


#endif // _PSYS_EMITTER_INCLUDED_
