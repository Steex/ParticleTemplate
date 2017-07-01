// Copyright (c) 2001-2011 Aliasworlds Entertainment
// file tag_manager.h
// author: Sergey Sotnikov

#ifndef _TAG_MANAGER_INCLUDED__
#define _TAG_MANAGER_INCLUDED__


template<class _Enum>
class Tags
{
public:

    static const String& getTag(_Enum _value) { return ms_tag_table.getTag(_value); }
    static _Enum parse(const String& _name) { return ms_tag_table.parse(_name); }

private:

    static void init();

    static Utils::TagTable<_Enum> ms_tag_table;
    static Utils::StaticInitializer ms_initializer;
};


#endif // _TAG_MANAGER_INCLUDED__
