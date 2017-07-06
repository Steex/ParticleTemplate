#include "head.h"

#include "processor_factory.h"



const static String errorProcessorTypeNotSet   = "The processor type is not specified in the XML node.";
const static String errorProcessorTypeExists   = "The processor type \"%1%\" already exists.";
const static String errorProcessorTypeNotFound = "The processor type \"%1%\" is not found.";



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



Particles::Processor* Particles::ProcessorFactory::create(iXml *_xml, ParamInfoHolder& _param_info)
{
    // Read the type of a processor to create.
    String processor_type = _xml->getAttribute("type");

    if (processor_type.empty())
    {
        throw Debug::Exception(String::format(errorProcessorTypeNotSet));
    }

    // Find the creator.
    CreatorCollection::const_iterator it_creator = inst()->creators.find(processor_type);

    if (it_creator == inst()->creators.end())
    {
        throw Debug::Exception(String::format(errorProcessorTypeNotFound, processor_type));
    }

    // Create the processor.
    return it_creator->second(_xml, _param_info);
}
