#ifndef _PSYS_CURVE_INCLUDED_
#define _PSYS_CURVE_INCLUDED_


namespace Particles
{
    template<typename T>
    struct CurveDataItem
    {
        Float arg;
        T     value;
    };


    template<typename T>
    class Curve
    {
    public:

        Curve(std::vector<T> _data, USize _table_size = 64);
        T operator()(Float _arg);

    private:

        USize table_size;
        std::vector<T> fetch_table;
    };

    template<typename T>
    Particles::Curve<T>::Curve(std::vector<T> _data, USize _table_size = 64)
        : table_size  (_table_size)
        , fetch_table (_table_size)
    {
        for (USize i = 0; i < _table_size; ++i)
        {
            fetch_table[i] = (1.0f / (_table_size - 1)) * i;
        }
    }

    template<typename T>
    T Particles::Curve<T>::operator()(Float _arg)
    {
        if (_arg <= 0.0f)
        {
            return fetch_table.front();
        }
        else if (_arg >= 1.0f)
        {
            return fetch_table.back();
        }
        else
        {
            Float soft_index = _arg / table_size;
            USize i = (USize)Math::floor(soft_index);
            USize j = (USize)Math::ceil(soft_index);
            Float lerp_coeff = (soft_index - (Float)i) * table_size;
            return Math::lerp(fetch_table[i], fetch_table[j], lerp_coeff);
        }
    }
}


#endif // _PSYS_CURVE_INCLUDED_
