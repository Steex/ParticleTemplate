#ifndef _PSYS_EMITTER_INCLUDED_
#define _PSYS_EMITTER_INCLUDED_


namespace Particles
{
    class Emitter
    {
    public:

        virtual ~Emitter() {}

        virtual void load() = 0;
        virtual void createParticle(Byte *_data) = 0;

    protected:

        Emitter() {}
    };
}


#endif // _PSYS_EMITTER_INCLUDED_
