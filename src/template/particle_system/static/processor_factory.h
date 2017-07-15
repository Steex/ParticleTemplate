#ifndef _PSYS_STATIC_PROCESSOR_FACTORY_INCLUDED_
#define _PSYS_STATIC_PROCESSOR_FACTORY_INCLUDED_


namespace ParticlesStatic
{
    class Processor;
    class ParamInfoHolder;


    class ProcessorFactory
    {
    public:

        typedef Processor* (*ProcessorCreator)(iXml*, ParamInfoHolder&);

        static void registerCreator(const String& _type, ProcessorCreator _creator);
        static Processor* create(iXml *_xml, ParamInfoHolder& _param_info);

    private:

        typedef std::map<String, ProcessorCreator> CreatorCollection;

        ProcessorFactory();
        static ProcessorFactory* inst();

        CreatorCollection creators;
    };


    template<typename P>
    class ProcessorRegistrator
    {
    public:
        ProcessorRegistrator(const String& _type)
        {
            ProcessorFactory::registerCreator(_type, &ProcessorRegistrator<P>::createProcessor);
        }

    private:
        static Processor* createProcessor(iXml *_xml, ParamInfoHolder& _param_info)
        {
            return new P(_xml, _param_info);
        }
    };
}


#endif // _PSYS_STATIC_PROCESSOR_FACTORY_INCLUDED_
