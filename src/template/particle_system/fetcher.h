#ifndef _PSYS_FETCHER_INCLUDED_
#define _PSYS_FETCHER_INCLUDED_


#include "curve.h"


namespace Particles
{
    template<typename T>
    class Fetcher
    {
    public:

        virtual ~Fetcher() {}

        virtual T fetch(Float _arg) = 0;

    protected:

        Fetcher() {}
    };


    template<typename T>
    class FetcherConst: public Fetcher<T>
    {
    public:

        FetcherConst(const T& _value): value(_value) {}
        FetcherConst(iXml *_xml): value(parse<T>(_xml->getAttribute("value"))) {}
        virtual ~FetcherConst() {}

        virtual T fetch(Float _arg) { return value; }

    private:

        T value;
    };


    template<typename T>
    class FetcherLerp: public Fetcher<T>
    {
    public:

        FetcherLerp(const Range<T>& _range): value_range(_range) {}
        FetcherLerp(const T& _min, const T& _max): value_range(_min, _max) {}
        FetcherLerp(iXml *_xml): value_range(parse<Range<T> >(_xml->getAttribute("value_range"))) {}
        virtual ~FetcherLerp() {}

        virtual T fetch(Float _arg) { return Math::lerpStrict(value_range, _arg); }

    private:

        Range<T> value_range;
    };


    template<typename T>
    class FetcherCurve: public Fetcher<T>
    {
    public:

        FetcherCurve(const Curve<T>& _curve): curve(_curve) {}
        FetcherCurve(iXml *_xml): curve(_xml) {}
        virtual ~FetcherCurve() {}

        virtual T fetch(Float _arg) { return curve(_arg); }

    private:

        Curve<T> curve;
    };
}


#endif // _PSYS_FETCHER_INCLUDED_
