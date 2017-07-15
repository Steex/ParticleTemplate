#ifndef _PSYS_STATIC_INSPECTOR_INCLUDED_
#define _PSYS_STATIC_INSPECTOR_INCLUDED_


namespace ParticlesStatic
{
    class Inspector
    {
    public:

        virtual void inspect(const Byte *_start, USize _stride, USize _count) = 0;

    };
}


#endif // _PSYS_STATIC_INSPECTOR_INCLUDED_
