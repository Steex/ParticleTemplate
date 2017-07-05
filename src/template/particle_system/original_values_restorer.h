#ifndef _PSYS_ORIGINAL_VALUES_RESTORER_INCLUDED_
#define _PSYS_ORIGINAL_VALUES_RESTORER_INCLUDED_


namespace Particles
{
    class ParamInfoHolder;


    class OriginalValuesRestorer
    {
    public:

        OriginalValuesRestorer(ParamInfoHolder& _param_info);
        virtual ~OriginalValuesRestorer();

        virtual void storeValues(Byte *_start, USize _stride, USize _count);
        virtual void restoreValues(Byte *_start, USize _stride, USize _count);

    private:

        struct ValueCopyInfo
        {
            USize value_size;
            USize value_offset;
            USize copy_offset;
        };

        typedef std::vector<ValueCopyInfo> ValueInfoList;


        ValueInfoList value_info_list;
    };
}


#endif // _PSYS_ORIGINAL_VALUES_RESTORER_INCLUDED_
