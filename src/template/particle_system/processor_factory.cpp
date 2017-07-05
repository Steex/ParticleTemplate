#include "head.h"

#include "processor_factory.h"



const static String errorProcessorTypeExists = "The processor name \"%1%\" already exists.";
const static String errorProcessorTypeNotFound = "The processor name \"%1%\" is not found.";



Particles::ProcessorFactory::ProcessorFactory()
    : creators ()
{

}



Particles::ProcessorFactory* Particles::ProcessorFactory::inst()
{
    static ProcessorFactory *instance = new ProcessorFactory();

    return instance;
}



void Particles::ProcessorFactory::registerCreator(const String& _type, ProcessorCreator _creator)
{
    if (!inst()->creators.insert(make_pair(_type, _creator)).second)
    {
        throw Debug::Exception(String::format(errorProcessorTypeExists, _type));
    }
}



Particles::Processor* Particles::ProcessorFactory::create(const String& _type, iXml *_xml, ParamInfoHolder& _param_info)
{
    CreatorCollection::const_iterator it_creator = inst()->creators.find(_type);

    if (it_creator == inst()->creators.end())
    {
        throw Debug::Exception(String::format(errorProcessorTypeNotFound, _type));
    }

    return it_creator->second(_xml, _param_info);
}
