#ifndef _RENDERER_INCLUDED_
#define _RENDERER_INCLUDED_


namespace Particles
{
    class Renderer
    {
    public:

        virtual ~Renderer() {}

        virtual void renderParticles(Byte *_start, USize _stride, USize _count) = 0;

    protected:

        Renderer() {}
    };
}


#endif // _RENDERER_INCLUDED_
