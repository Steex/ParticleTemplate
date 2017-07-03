#ifndef _PSYS_BASE_PARAMS_INCLUDED_
#define _PSYS_BASE_PARAMS_INCLUDED_


namespace Particles
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


#endif // _PSYS_BASE_PARAMS_INCLUDED_
