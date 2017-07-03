// Copyright (c) 2001-2011 Aliasworlds Entertainment
// file game_api.cpp
// author: Gennady Filazopovich

#include "head.h"
#include "common/general_loop.h"
#include "particle_viewer/normal_particle_control.h"
#include "particle_viewer/generated_particle_control.h"

const char* GameApi::pack_key = "VeryStrongPackKey";

//------------------------------------------------------------------------------------

void GameApi::initApp()
{
    UI::init();

    UI::IniLoader::registerStandardCreator<NormalParticleControl>("normal_particle_system");
    UI::IniLoader::registerStandardCreator<GeneratedParticleControl>("generated_particle_system");

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
}

//------------------------------------------------------------------------------------
