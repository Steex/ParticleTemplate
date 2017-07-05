#ifndef _PSYS_FETCHER_FACTORY_INCLUDED_
#define _PSYS_FETCHER_FACTORY_INCLUDED_



#include "fetcher.h"



namespace Particles
{
    class FetcherFactory
    {
    public:

        template<typename T>
        static Fetcher<T>* create(iXml *_xml);

    private:

        const static String errorUnknownType;
    };



    template<typename T>
    static Fetcher<T>* Particles::FetcherFactory::create(iXml *_xml)
    {
        String type = _xml->getAttribute("type");
        if (type == "const")
        {
            return new FetcherConst<T>(_xml);
        }
        else if (type == "lerp")
        {
            return new FetcherLerp<T>(_xml);
        }
        else if (type == "curve")
        {
            return new FetcherCurve<T>(_xml);
        }
        else
        {
            throw Debug::Exception(String::format(errorUnknownType, type));
        }
    }
}


#endif // _PSYS_FETCHER_FACTORY_INCLUDED_
