#ifndef _PSYS_GENCPP_SYSTEM_FACTORY_INCLUDED_
#define _PSYS_GENCPP_SYSTEM_FACTORY_INCLUDED_


namespace ParticlesGenCpp
{
    class IParticleSystem;


    class SystemFactory
    {
    public:

        typedef IParticleSystem* (*SystemCreator)(iXml*);

        static void registerCreator(const String& _type, SystemCreator _creator);
        static IParticleSystem* create(const String& _type, iXml *_xml);

    private:

        typedef std::map<String, SystemCreator> CreatorCollection;

        SystemFactory();
        static SystemFactory* inst();

        CreatorCollection creators;
    };


    template<typename S>
    class SystemRegistrator
    {
    public:
        SystemRegistrator(const String& _type)
        {
            SystemFactory::registerCreator(_type, &SystemRegistrator<S>::createSystem);
        }

    private:
        static IParticleSystem* createSystem(iXml *_xml)
        {
            return new S(_xml);
        }
    };
}


#endif // _PSYS_GENCPP_SYSTEM_FACTORY_INCLUDED_
