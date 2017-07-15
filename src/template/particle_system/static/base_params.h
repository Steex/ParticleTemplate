#ifndef _PSYS_STATIC_BASE_PARAMS_INCLUDED_
#define _PSYS_STATIC_BASE_PARAMS_INCLUDED_


namespace ParticlesStatic
{
    struct BaseParticleParams
    {
        Bool    dead;
        Vector2 position;
        Float   scale;
        Float   angle;
        Color   color;
    };
}


#endif // _PSYS_STATIC_BASE_PARAMS_INCLUDED_
