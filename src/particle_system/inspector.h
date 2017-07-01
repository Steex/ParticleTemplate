#ifndef _PSYS_INSPECTOR_INCLUDED_
#define _PSYS_INSPECTOR_INCLUDED_


namespace Particles
{
    class Inspector
    {
    public:

        virtual void inspect(const Byte *_start, USize _stride, USize _count) = 0;

    };
}


#endif // _PSYS_INSPECTOR_INCLUDED_
