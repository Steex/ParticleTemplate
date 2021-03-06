#ifndef _PSYS_STATIC_EMIT_SHAPE_FACTORY_INCLUDED_
#define _PSYS_STATIC_EMIT_SHAPE_FACTORY_INCLUDED_


namespace ParticlesStatic
{
    class EmitShape;


    class EmitShapeFactory
    {
    public:

        typedef EmitShape* (*EmitShapeCreator)(iXml*);

        static void registerCreator(const String& _type, EmitShapeCreator _creator);
        static EmitShape* create(iXml *_xml);

    private:

        typedef std::map<String, EmitShapeCreator> CreatorCollection;

        EmitShapeFactory();
        static EmitShapeFactory* inst();

        CreatorCollection creators;
    };


    template<typename P>
    class EmitShapeRegistrator
    {
    public:
        EmitShapeRegistrator(const String& _type)
        {
            EmitShapeFactory::registerCreator(_type, &EmitShapeRegistrator<P>::createProcessor);
        }

    private:
        static EmitShape* createProcessor(iXml *_xml)
        {
            return new P(_xml);
        }
    };
}


#endif // _PSYS_STATIC_EMIT_SHAPE_FACTORY_INCLUDED_
