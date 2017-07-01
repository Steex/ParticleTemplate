// Copyright (c) 2001-2011 Aliasworlds Entertainment
// file game_api.cpp
// author: Gennady Filazopovich


#include "head.h"
#include "common/general_loop.h"
#include <metrics.h>


const char* GameApi::pack_key = "VeryStrongPackKey";


//------------------------------------------------------------------------------------

void GameApi::initApp()
{
    UI::init();

    UI::Create<GeneralLoop>();
    UI::cUIManager::setRoot(GeneralLoop::inst());
}

//------------------------------------------------------------------------------------

void GameApi::clearApp()
{
    UI::Destroy(GeneralLoop::inst());
    UI::cUIManager::setRoot(NULL);
}

//------------------------------------------------------------------------------------

void GameApi::onClose()
{
    if (GeneralLoop::inst())
    {
        GeneralLoop::inst()->onClose();
    }
}

//------------------------------------------------------------------------------------

void GameApi::draw()
{
    UI::draw();
}

//------------------------------------------------------------------------------------

void GameApi::tick()
{
    UI::process();
}

//------------------------------------------------------------------------------------

void GameApi::registerUsedFeatures(Features& _features)
{
    // Setup the assets list.
    if(Device::inst()->getOS() == Device::OS_ANDROID && Device::inst()->getOS(true) == Device::OS_WINDOWS)
    {
        _features.assetsDir("assets-droid");
    }
    else if (Device::inst()->getType() == Device::DEVICE_PC)
    {
        _features.assetsDir("assets,assets-pc");
    }
    else if (Device::inst()->getOS() == Device::OS_IOS)
    {
        _features.assetsDir("assets,assets-mobile");
    }


    // Setup the custom tags.
    STRING_VECTOR custom_tags;

#ifdef EXTERNAL_VERSION
    custom_tags.push_back("external");
#elif defined(AMAZON)
    custom_tags.push_back("amazon");
#elif defined(GOOGLE)
    custom_tags.push_back("google");
#endif

#ifdef PAID_VERSION
    custom_tags.push_back("full");
#else
    custom_tags.push_back("free");
#endif

    _features.tags(Utils::serializeList(custom_tags, ","));

}

//------------------------------------------------------------------------------------
