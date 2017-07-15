#include "head.h"

#include "param_info_holder.h"


static const String errorParamNameExists  = "Particle param \"%1%\" already exists.";
static const String errorParamAnotherType = "Particle param \"%1%\" already exists and have another type.";
static const String errorParamNotFound    = "Particle param \"%1%\" is not found.";



ParticlesStatic::ParamInfoHolder::ParamInfoHolder()
    : params        ()
    , param_indices ()
    , total_size    (0)
{
}



USize ParticlesStatic::ParamInfoHolder::registerParam(const String& _name, USize _size, const type_info& _info)
{
    // If the name already defined, make sure the type is the same and return the parameter's offset.
    ParamIndexMap::const_iterator it_index = param_indices.find(_name);
    if (it_index != param_indices.end())
    {
        Param& param_info = params[it_index->second];

        if (*param_info.info != _info)
        {
            throw Debug::Exception(String::format(errorParamAnotherType, _name));
        }
        else
        {
            return params[it_index->second].offset;
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
    param_info.restore_every_tick = false;

    params.push_back(param_info);

    // Update the total size.
    total_size += param_info.size;

    // Return an offset of the parameter.
    return param_info.offset;
}



USize ParticlesStatic::ParamInfoHolder::createParamCopy(const String& _orig_name, const String& _copy_name)
{
    // Make sure the copy name is not used yet.
    if (param_indices.find(_copy_name) != param_indices.end())
    {
        throw Debug::Exception(String::format(errorParamNameExists, _copy_name));
    }

    // Search for the original info.
    ParamIndexMap::const_iterator it_index = param_indices.find(_orig_name);
    if (it_index == param_indices.end())
    {
        throw Debug::Exception(String::format(errorParamNotFound, _orig_name));
    }

    const Param& orig_param = params[it_index->second];

    // Register the name.
    param_indices[_copy_name] = params.size();

    // Add an info copy.
    Param param_info;
    param_info.name = _copy_name;
    param_info.offset = total_size;
    param_info.size = orig_param.size;
    param_info.info = orig_param.info;
    param_info.restore_every_tick = false;

    params.push_back(param_info);

    // Update the total size.
    total_size += param_info.size;

    // Return an offset of the copy.
    return param_info.offset;
}



USize ParticlesStatic::ParamInfoHolder::getParamOffset(const String& _name) const
{
    ParamIndexMap::const_iterator it_index = param_indices.find(_name);

    if (it_index != param_indices.end())
    {
        return params[it_index->second].offset;
    }
    else
    {
        throw Debug::Exception(String::format(errorParamNotFound, _name));
    }
}



USize ParticlesStatic::ParamInfoHolder::getParamSize(const String& _name) const
{
    ParamIndexMap::const_iterator it_index = param_indices.find(_name);

    if (it_index != param_indices.end())
    {
        return params[it_index->second].size;
    }
    else
    {
        throw Debug::Exception(String::format(errorParamNotFound, _name));
    }
}



void ParticlesStatic::ParamInfoHolder::enableParamRestoring(const String& _name)
{
    ParamIndexMap::const_iterator it_index = param_indices.find(_name);

    if (it_index != param_indices.end())
    {
        params[it_index->second].restore_every_tick = true;
    }
    else
    {
        throw Debug::Exception(String::format(errorParamNotFound, _name));
    }
}



std::vector<String> ParticlesStatic::ParamInfoHolder::getStoredValues() const
{
    std::vector<String> names;

    FOREACH (ParamList::const_iterator, param, params)
    {
        if (param->restore_every_tick)
        {
            names.push_back(param->name);
        }
    }

    return names;
}
