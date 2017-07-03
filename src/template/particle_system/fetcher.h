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

        virtual T fetch(Float _arg, Float _lerp_coeff) = 0;

    protected:

        Fetcher() {}
    };


    template<typename T>
    class FetcherConst: public Fetcher<T>
    {
    public:

        FetcherConst(const T& _value): value(_value) {}
        virtual ~FetcherConst() {}

        virtual T fetch(Float _arg, Float _lerp_coeff) { return value; }

    private:

        T value;
    };


    template<typename T>
    class FetcherLerp: public Fetcher<T>
    {
    public:

        FetcherLerp(const Range<T>& _range): value_range(_range) {}
        FetcherLerp(const T& _min, const T& _max): value_range(_min, _max) {}
        virtual ~FetcherLerp() {}

        virtual T fetch(Float _arg, Float _lerp_coeff) { return Math::lerpStrict(value_range, _lerp_coeff); }

    private:

        Range<T> value_range;
    };


    template<typename T>
    class FetcherTransition: public Fetcher<T>
    {
    public:

        FetcherTransition(const Range<T>& _range): value_range(_range) {}
        FetcherTransition(const T& _min, const T& _max): value_range(_min, _max) {}
        virtual ~FetcherTransition() {}

        virtual T fetch(Float _arg, Float _lerp_coeff) { return Math::lerpStrict(value_range, _arg); }

    private:

        Range<T> value_range;
    };


    template<typename T>
    class FetcherCurve: public Fetcher<T>
    {
    public:

        FetcherCurve(const Curve<T>& _curve): curve(_curve) {}
        virtual ~FetcherCurve() {}

        virtual T fetch(Float _arg, Float _lerp_coeff) { return curve(_arg); }

    private:

        Curve<T> curve;
    };


    template<typename T>
    class FetcherCurveLerp: public Fetcher<T>
    {
    public:

        FetcherCurveLerp(const Curve<T>& _curve1, const Curve<T>& _curve2): curve1(_curve1), curve2(_curve2) {}
        virtual ~FetcherCurveLerp() {}

        virtual T fetch(Float _arg, Float _lerp_coeff) { return Math::lerpStrict(curve1(_arg), curve2(arg), _lerp_coeff); }

    private:

        Curve<T> curve1;
        Curve<T> curve2;
    };
}


#endif // _PSYS_FETCHER_INCLUDED_
