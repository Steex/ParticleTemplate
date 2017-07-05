#include "head.h"

#include "original_values_restorer.h"
#include "param_info_holder.h"



Particles::OriginalValuesRestorer::OriginalValuesRestorer(ParamInfoHolder& _param_info)
    : value_info_list ()
{
    std::vector<String> restorable_param_names = _param_info.getStoredValues();
    FOREACH (std::vector<String>::const_iterator, param_name, restorable_param_names)
    {
        ValueCopyInfo copy_info;
        copy_info.value_size = _param_info.getParamSize(*param_name);
        copy_info.value_offset = _param_info.getParamOffset(*param_name);
        copy_info.copy_offset = _param_info.createParamCopy(*param_name, *param_name + "::orig");

        value_info_list.push_back(copy_info);
    }
}



Particles::OriginalValuesRestorer::~OriginalValuesRestorer()
{
}



void Particles::OriginalValuesRestorer::storeValues(Byte *_start, USize _stride, USize _count)
{
    for (Byte *particle = _start, *last_particle = _start + _stride * (_count - 1); particle <= last_particle; particle += _stride)
    {
        FOREACH (ValueInfoList::const_iterator, value, value_info_list)
        {
            memcpy(particle + value->copy_offset, particle + value->value_offset, value->value_size);
        }
    }
}



void Particles::OriginalValuesRestorer::restoreValues(Byte *_start, USize _stride, USize _count)
{
    for (Byte *particle = _start, *last_particle = _start + _stride * (_count - 1); particle <= last_particle; particle += _stride)
    {
        FOREACH (ValueInfoList::const_iterator, value, value_info_list)
        {
            memcpy(particle + value->value_offset, particle + value->copy_offset, value->value_size);
        }
    }
}
