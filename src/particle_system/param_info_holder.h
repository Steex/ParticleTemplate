#ifndef _PARAM_INFO_HOLDER_INCLUDED_
#define _PARAM_INFO_HOLDER_INCLUDED_


namespace Particles
{
    class ParamInfoHolder
    {
    public:

        ParamInfoHolder();
        ~ParamInfoHolder() {}

        template<typename P>
        inline USize registerParam(const String& _name) { return registerParam(_name, sizeof(P), typeid(P)); }
        USize getParamOffset(const String& _name) const;
        USize getTotalSize() const { return total_size; }

    private:
        
        struct Param
        {
            String           name;
            USize            offset;
            USize            size;
            const type_info *info;
        };

        typedef std::vector<Param> ParamList;
        typedef std::map<String, USize> ParamIndexMap;

        USize registerParam(const String& _name, USize _size, const type_info& _info);

        ParamList     params;
        ParamIndexMap param_indices;
        USize         total_size;
    };
}


#endif // _PARAM_INFO_HOLDER_INCLUDED_
