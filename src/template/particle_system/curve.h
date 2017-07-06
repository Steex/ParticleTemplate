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
        Curve(const Range<T>& _value_range, iCurve *_smooth_curve, USize _table_size = 64);
        Curve(iXml *_xml);
        T operator()(Float _arg);

    private:

        USize table_size;
        std::vector<T> fetch_table;
    };

    template<typename T>
    Particles::Curve<T>::Curve(std::vector<T> _data, USize _table_size /*= 64*/)
        : table_size  (_table_size)
        , fetch_table (_table_size)
    {
        for (USize i = 0; i < _table_size; ++i)
        {
            fetch_table[i] = (1.0f / (_table_size - 1)) * i;
        }
    }


    template<typename T>
    Particles::Curve<T>::Curve(const Range<T>& _value_range, iCurve *_smooth_curve, USize _table_size /*= 64*/)
        : table_size  (_table_size)
        , fetch_table (_table_size)
    {
        Float max_arg = _smooth_curve->getMaxArgument();
        if (max_arg == 0)
        {
            max_arg = 1.0f;
        }

        for (USize i = 0; i < table_size; ++i)
        {
            Float lerp_coeff = _smooth_curve->getValue(((Float)i / (table_size - 1)) * max_arg) / 100.0f;
            fetch_table[i] = Math::lerpStrict(_value_range, lerp_coeff);
        }
    }


    template<typename T>
    Particles::Curve<T>::Curve(iXml *_xml)
        : table_size  (parse<USize>(_xml->getAttribute("table_size"), 64))
        , fetch_table (table_size)
    {
        Range<T> _value_range(parse<T>(_xml->getAttribute("min")), parse<T>(_xml->getAttribute("max")));
        String smooth_curve_file = _xml->getAttribute("curve_file");
        String smooth_curve_name = _xml->getAttribute("curve_name");
        iCurve *_smooth_curve = iResourceManager::inst()->getCurve(smooth_curve_file, smooth_curve_name);

        Float max_arg = _smooth_curve->getMaxArgument();
        if (max_arg == 0)
        {
            max_arg = 1.0f;
        }

        for (USize i = 0; i < table_size; ++i)
        {
            Float lerp_coeff = _smooth_curve->getValue(((Float)i / (table_size - 1)) * max_arg) / 100.0f;
            fetch_table[i] = Math::lerpStrict(_value_range, lerp_coeff);
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
            Float soft_index = _arg * (table_size - 1);
            USize i = (USize)Math::floor(soft_index);
            USize j = (USize)Math::ceil(soft_index);
            Float lerp_coeff = (soft_index - (Float)i);
            return Math::lerp(fetch_table[i], fetch_table[j], lerp_coeff);
        }
    }
}


#endif // _PSYS_CURVE_INCLUDED_
