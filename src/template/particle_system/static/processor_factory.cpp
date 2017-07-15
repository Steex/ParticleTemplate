#include "head.h"

#include "processor_factory.h"



const static String errorProcessorTypeNotSet   = "The processor type is not specified in the XML node.";
const static String errorProcessorTypeExists   = "The processor type \"%1%\" already exists.";
const static String errorProcessorTypeNotFound = "The processor type \"%1%\" is not found.";



ParticlesStatic::ProcessorFactory::ProcessorFactory()
    : creators ()
{
}



ParticlesStatic::ProcessorFactory* ParticlesStatic::ProcessorFactory::inst()
{
    static ProcessorFactory *instance = new ProcessorFactory();

    return instance;
}



void ParticlesStatic::ProcessorFactory::registerCreator(const String& _type, ProcessorCreator _creator)
{
    if (!inst()->creators.insert(make_pair(_type, _creator)).second)
    {
        throw Debug::Exception(String::format(errorProcessorTypeExists, _type));
    }
}



ParticlesStatic::Processor* ParticlesStatic::ProcessorFactory::create(iXml *_xml, ParamInfoHolder& _param_info)
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
