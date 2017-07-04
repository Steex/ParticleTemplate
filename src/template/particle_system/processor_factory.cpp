#include "head.h"

#include "processor_factory.h"



const static String errorProcessorNameExists = "The processor name \"%1%\" already exists.";
const static String errorProcessorNameNotFound = "The processor name \"%1%\" is not found.";



Particles::ProcessorFactory::ProcessorFactory()
    : creators ()
{

}



Particles::ProcessorFactory* Particles::ProcessorFactory::inst()
{
    static ProcessorFactory *instance = new ProcessorFactory();

    return instance;
}



void Particles::ProcessorFactory::registerCreator(const String& _name, ProcessorCreator _creator)
{
    if (!inst()->creators.insert(make_pair(_name, _creator)).second)
    {
        throw Debug::Exception(String::format(errorProcessorNameExists, _name));
    }
}



Particles::Processor* Particles::ProcessorFactory::create(const String& _name, ParamInfoHolder& _params)
{
    CreatorCollection::const_iterator it_creator = inst()->creators.find(_name);

    if (it_creator == inst()->creators.end())
    {
        throw Debug::Exception(String::format(errorProcessorNameNotFound, _name));
    }

    return it_creator->second(_params);
}
