#ifndef _PSYS_PROCESSOR_INCLUDED_
#define _PSYS_PROCESSOR_INCLUDED_


namespace Particles
{
    class Processor
    {
    public:

        virtual ~Processor() {}

        virtual void load() = 0;
        virtual void initParticles(Byte *_start, USize _stride, USize _count) = 0;
        virtual void updateParticles(Byte *_start, USize _stride, USize _count, Float _tick) = 0;

    protected:

        Processor() {}
    };
}


#endif // _PSYS_PROCESSOR_INCLUDED_