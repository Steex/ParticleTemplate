#ifndef _PSYS_PROCESSOR_FACTORY_INCLUDED_
#define _PSYS_PROCESSOR_FACTORY_INCLUDED_


namespace Particles
{
    class Processor;
    class ParamInfoHolder;


    class ProcessorFactory
    {
    public:

        typedef Processor* (*ProcessorCreator)(ParamInfoHolder&);

        static void registerCreator(const String& _name, ProcessorCreator _creator);
        static Processor* create(const String& _name, ParamInfoHolder& _params);

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
        ProcessorRegistrator(const String& _name)
        {
            ProcessorFactory::registerCreator(_name, &ProcessorRegistrator<P>::createProcessor);
        }

    private:
        static Processor* createProcessor(ParamInfoHolder& _params)
        {
            return new P(_params);
        }
    };
}


#endif // _PSYS_PROCESSOR_FACTORY_INCLUDED_
