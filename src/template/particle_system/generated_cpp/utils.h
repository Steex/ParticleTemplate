#ifndef _PSYS_GENCPP_UTILS_INCLUDED_
#define _PSYS_GENCPP_UTILS_INCLUDED_


namespace ParticlesGenCpp
{
    template<typename T>
    T fetchCurve(Float _arg, const T *_table, USize _table_size);
}


template<typename T>
T ParticlesGenCpp::fetchCurve(Float _arg, const T *_table, USize _table_size)
{
    if (_arg <= 0.0f)
    {
        return _table[0];
    }
    else if (_arg >= 1.0f)
    {
        return _table[_table_size - 1];
    }
    else
    {
        Float soft_index = _arg * (_table_size - 1);
        USize i = (USize)Math::floor(soft_index);
        USize j = (USize)Math::ceil(soft_index);
        Float lerp_coeff = (soft_index - (Float)i);
        return Math::lerp(_table[i], _table[j], lerp_coeff);
    }
}


#endif // _PSYS_GENCPP_UTILS_INCLUDED_
