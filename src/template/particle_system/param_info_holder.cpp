#include "head.h"

#include "param_info_holder.h"


static const String errorParamAnotherType = "Particle param already exists and have another type: ";
static const String errorParamNotFound    = "Particle param is not found: ";



Particles::ParamInfoHolder::ParamInfoHolder()
    : params        ()
    , param_indices ()
    , total_size    (0)
{
}



USize Particles::ParamInfoHolder::registerParam(const String& _name, USize _size, const type_info& _info)
{
    // If the name already defined, make sure the type is the same and return the parameter's offset.
    ParamIndexMap::const_iterator it_index = param_indices.find(_name);
    if (it_index != param_indices.end())
    {
        if (*params[it_index->second].info == _info)
        {
            return params[it_index->second].offset;
        }
        else
        {
            throw Debug::Exception(errorParamAnotherType + _name);
        }
    }

    // Register the name.
    param_indices[_name] = params.size();

    // Add the info.
    Param param_info;
    param_info.name = _name;
    param_info.offset = total_size;
    param_info.size = Math::padSize(_size, 4);
    param_info.info = &_info;

    params.push_back(param_info);

    // Update the total size.
    total_size += param_info.size;

    // Return an offset of the parameter.
    return param_info.offset;
}



USize Particles::ParamInfoHolder::getParamOffset(const String& _name) const
{
    ParamIndexMap::const_iterator it_index = param_indices.find(_name);

    if (it_index != param_indices.end())
    {
        return params[it_index->second].offset;
    }
    else
    {
        throw Debug::Exception(errorParamNotFound + _name);
    }
}
