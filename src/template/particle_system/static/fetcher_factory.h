#ifndef _PSYS_STATIC_FETCHER_FACTORY_INCLUDED_
#define _PSYS_STATIC_FETCHER_FACTORY_INCLUDED_



#include "fetcher.h"



namespace ParticlesStatic
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
    static Fetcher<T>* ParticlesStatic::FetcherFactory::create(iXml *_xml)
    {
        String type = _xml->getAttribute("type");
        if (type == "const")
        {
            return new Fetcher_Const<T>(_xml);
        }
        else if (type == "lerp")
        {
            return new Fetcher_Lerp<T>(_xml);
        }
        else if (type == "random")
        {
            return new Fetcher_Random<T>(_xml);
        }
        else if (type == "curve")
        {
            return new Fetcher_Curve<T>(_xml);
        }
        else
        {
            throw Debug::Exception(String::format(errorUnknownType, type));
        }
    }
}


#endif // _PSYS_STATIC_FETCHER_FACTORY_INCLUDED_
