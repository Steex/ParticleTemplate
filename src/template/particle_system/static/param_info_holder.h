#ifndef _PSYS_STATIC_PARAM_INFO_HOLDER_INCLUDED_
#define _PSYS_STATIC_PARAM_INFO_HOLDER_INCLUDED_


namespace ParticlesStatic
{
    class ParamInfoHolder
    {
    public:

        ParamInfoHolder();
        ~ParamInfoHolder() {}

        template<typename P>
        inline USize registerParam(const String& _name) { return registerParam(_name, sizeof(P), typeid(P)); }
        USize createParamCopy(const String& _orig_name, const String& _copy_name);
        USize getParamOffset(const String& _name) const;
        USize getParamSize(const String& _name) const;
        USize getTotalSize() const { return total_size; }

        void enableParamRestoring(const String& _name);
        std::vector<String> getStoredValues() const;

    private:
        
        struct Param
        {
            String           name;
            USize            offset;
            USize            size;
            Bool             restore_every_tick;
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


#endif // _PSYS_STATIC_PARAM_INFO_HOLDER_INCLUDED_
