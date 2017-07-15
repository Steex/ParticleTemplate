#ifndef _PSYS_GENCPP_INTERFACES_INCLUDED_
#define _PSYS_GENCPP_INTERFACES_INCLUDED_


namespace ParticlesGenCpp
{
    struct BaseParticleParams
    {
        Bool    dead;
        Vector2 position;
        Float   scale;
        Float   angle;
        Color   color;
    };


    class IRenderer
    {
    public:
        virtual void iterate(const Byte *_start, USize _stride, USize _count) = 0;
    };


    class IParticleSystem
    {
    public:
        virtual ~IParticleSystem() {}

        virtual Bool isActive() const = 0;
        virtual void start() = 0;
        virtual void pause() = 0;
        virtual void resume() = 0;

        virtual void update(Float _tick) = 0;
        virtual void render(IRenderer *_renderer) const = 0;

        virtual USize getMaxCount() const = 0;
    };
}


#endif // _PSYS_GENCPP_INTERFACES_INCLUDED_
