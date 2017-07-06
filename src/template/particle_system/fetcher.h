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
    class Fetcher_Const: public Fetcher<T>
    {
    public:

        Fetcher_Const(const T& _value): value(_value) {}
        Fetcher_Const(iXml *_xml): value(parse<T>(_xml->getAttribute("value"))) {}
        virtual ~Fetcher_Const() {}

        virtual T fetch(Float _arg) { return value; }

    private:

        T value;
    };


    template<typename T>
    class Fetcher_Lerp: public Fetcher<T>
    {
    public:

        Fetcher_Lerp(const Range<T>& _range): value_range(_range) {}
        Fetcher_Lerp(const T& _min, const T& _max): value_range(_min, _max) {}
        Fetcher_Lerp(iXml *_xml): value_range(parse<T>(_xml->getAttribute("min")), parse<T>(_xml->getAttribute("max"))) {}
        virtual ~Fetcher_Lerp() {}

        virtual T fetch(Float _arg) { return Math::lerpStrict(value_range, _arg); }

    private:

        Range<T> value_range;
    };


    template<typename T>
    class Fetcher_Random: public Fetcher<T>
    {
    public:

        Fetcher_Random(const Range<T>& _range): value_range(_range) {}
        Fetcher_Random(const T& _min, const T& _max): value_range(_min, _max) {}
        Fetcher_Random(iXml *_xml): value_range(parse<T>(_xml->getAttribute("min")), parse<T>(_xml->getAttribute("max"))) {}
        virtual ~Fetcher_Random() {}

        virtual T fetch(Float _arg) { return Math::random(value_range); }

    private:

        Range<T> value_range;
    };


    template<typename T>
    class Fetcher_Curve: public Fetcher<T>
    {
    public:

        Fetcher_Curve(const Curve<T>& _curve): curve(_curve) {}
        Fetcher_Curve(iXml *_xml): curve(_xml) {}
        virtual ~Fetcher_Curve() {}

        virtual T fetch(Float _arg) { return curve(_arg); }

    private:

        Curve<T> curve;
    };
}


#endif // _PSYS_FETCHER_INCLUDED_
