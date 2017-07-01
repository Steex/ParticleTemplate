#ifndef _PSYS_PARAM_ACCESSOR_INCLUDED_
#define _PSYS_PARAM_ACCESSOR_INCLUDED_


namespace Particles
{
    template<typename T>
    class ParamAccessor
    {
    public:
        ParamAccessor(Byte*& _chunk_ptr, USize _offset)
            : chunk_ptr(_chunk_ptr), offset(_offset)
        {}

        inline const T& operator*() const { return *(T*)(chunk_ptr + offset); }
        inline T& operator*() { return *(T*)(chunk_ptr + offset); }
        inline const T* operator->() const { return (T*)(chunk_ptr + offset); }
        inline T* operator->() { return (T*)(chunk_ptr + offset); }

    private:
        Byte*& chunk_ptr;
        USize  offset;
    };
}


#endif // _PSYS_PARAM_ACCESSOR_INCLUDED_
