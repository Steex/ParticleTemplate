// Copyright (c) 2001-2011 Aliasworlds Entertainment
// file tag_manager.cpp
// author: Sergey Sotnikov

#include "head.h"
#include "tag_manager.h"

//-----------------------------------------------------------------------

template<class _Enum>
Utils::TagTable<_Enum> Tags<_Enum>::ms_tag_table;

template<class _Enum>
Utils::StaticInitializer Tags<_Enum>::ms_initializer(init, &(Tags<_Enum>::ms_tag_table));

//-----------------------------------------------------------------------

template<>
void Tags<eCursorMode>::init()
{
    ms_initializer = ms_initializer; // fake using the initializer

    ms_tag_table.registerTag(CUR_NORMAL, "normal");
}

//-----------------------------------------------------------------------
