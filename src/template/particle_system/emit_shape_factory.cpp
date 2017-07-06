#include "head.h"

#include "emit_shape_factory.h"



const static String errorEmitShapeTypeNotSet   = "The emit shape type is not specified in the XML node.";
const static String errorEmitShapeTypeExists   = "The emit shape type \"%1%\" already exists.";
const static String errorEmitShapeTypeNotFound = "The emit shape type \"%1%\" is not found.";



Particles::EmitShapeFactory::EmitShapeFactory()
    : creators ()
{
}



Particles::EmitShapeFactory* Particles::EmitShapeFactory::inst()
{
    static EmitShapeFactory *instance = new EmitShapeFactory();

    return instance;
}



void Particles::EmitShapeFactory::registerCreator(const String& _type, EmitShapeCreator _creator)
{
    if (!inst()->creators.insert(make_pair(_type, _creator)).second)
    {
        throw Debug::Exception(String::format(errorEmitShapeTypeExists, _type));
    }
}



Particles::EmitShape* Particles::EmitShapeFactory::create(iXml *_xml)
{
    // Read the type of a processor to create.
    String emit_shape_type = _xml->getAttribute("type");

    if (emit_shape_type.empty())
    {
        throw Debug::Exception(String::format(errorEmitShapeTypeNotSet));
    }

    // Find the creator.
    CreatorCollection::const_iterator it_creator = inst()->creators.find(emit_shape_type);

    if (it_creator == inst()->creators.end())
    {
        throw Debug::Exception(String::format(errorEmitShapeTypeNotFound, emit_shape_type));
    }

    // Create the emit shape.
    return it_creator->second(_xml);
}
