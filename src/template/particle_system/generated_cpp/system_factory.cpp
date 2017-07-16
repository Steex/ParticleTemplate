#include "head.h"

#include "system_factory.h"



const static String errorSystemTypeNotSet   = "The particle system type is not specified in the XML node.";
const static String errorSystemTypeExists   = "The particle system type \"%1%\" already exists.";
const static String errorSystemTypeNotFound = "The particle system type \"%1%\" is not found.";



ParticlesGenCpp::SystemFactory::SystemFactory()
    : creators ()
{
}



ParticlesGenCpp::SystemFactory* ParticlesGenCpp::SystemFactory::inst()
{
    static SystemFactory *instance = new SystemFactory();

    return instance;
}



void ParticlesGenCpp::SystemFactory::registerCreator(const String& _type, SystemCreator _creator)
{
    if (!inst()->creators.insert(make_pair(_type, _creator)).second)
    {
        throw Debug::Exception(String::format(errorSystemTypeExists, _type));
    }
}



ParticlesGenCpp::IParticleSystem* ParticlesGenCpp::SystemFactory::create(const String& _type, iXml *_xml)
{
    // Read the type of a particle system to create.
    //String system_type = _xml->getAttribute("type");

    if (_type.empty())
    {
        throw Debug::Exception(String::format(errorSystemTypeNotSet));
    }

    // Find the creator.
    CreatorCollection::const_iterator it_creator = inst()->creators.find(_type);

    if (it_creator == inst()->creators.end())
    {
        throw Debug::Exception(String::format(errorSystemTypeNotFound, _type));
    }

    // Create the particle system.
    return it_creator->second(_xml);
}
