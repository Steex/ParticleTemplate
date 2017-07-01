// Copyright (c) 2001-2011 Aliasworlds Entertainment
// file general_loop.cpp
// author: Sergey Sotnikov

#include "head.h"
#include "general_loop.h"
#include "cheat_manager.h"
#include "particle_viewer/particle_viewer.h"

//-----------------------------------------------------------------------

GeneralLoop::GeneralLoop()
: PARENT_CLASS      (NULL)
, m_particle_viewer (NULL)
, m_cheat_manager   (NULL)
, m_cheat_pause     (false)
{
}

//-----------------------------------------------------------------------

GeneralLoop::~GeneralLoop()
{
    delete m_cheat_manager;
}

//-----------------------------------------------------------------------

GeneralLoop* GeneralLoop::Create()
{
    GeneralLoop *loop = new GeneralLoop();
    loop->onCreate();
    return loop;
}

//-----------------------------------------------------------------------

void GeneralLoop::Destroy()
{
    GeneralLoop *loop = GeneralLoop::getInstance();
    UI::Destroy(loop);
}

//-----------------------------------------------------------------------

void GeneralLoop::onCreate()
{
    //UI::cUIManager::setPlayUISoundFunc(playInterfaceSound);

    // Load all assets.
    LOG_NOTE("game", "Load assets");
    STRING_LIST resources;
    iFileManager::inst()->getFileList(resources, "", true);
    FOREACH (STRING_LIST::iterator, resource, resources)
    {
        iResourceManager::inst()->loadFile(*resource);
    }

    // Create the particle viewer.
    LOG_NOTE("game", "Create the particle viewer");
    m_particle_viewer = UI::Create<ParticleViewer>(this);

    // Create a cheat manager.
    LOG_NOTE("game", "Create a cheat manager");
    m_cheat_manager = new CheatManager();

    // Activate the loop.
    show();
    enable();
    activate();
}

//-----------------------------------------------------------------------

void GeneralLoop::onDestroy()
{
    PARENT_CLASS::onDestroy();
}

//-----------------------------------------------------------------------

void GeneralLoop::process()
{
    PARENT_CLASS::process();
}

//-----------------------------------------------------------------------

void GeneralLoop::onEnable()
{
    PARENT_CLASS::onEnable();

    if (m_cheat_manager->isCheatsEnabled())
    {
        bind(KEY_PGUP_DOWN,   MakeDelegate(this, &GeneralLoop::onPageUp));
        bind(KEY_PGDOWN_DOWN, MakeDelegate(this, &GeneralLoop::onPageDown));
        bind(KEY_HOME_DOWN,   MakeDelegate(this, &GeneralLoop::onHome));
    }
}

//-----------------------------------------------------------------------

void GeneralLoop::onDisable()
{
    if (m_cheat_manager->isCheatsEnabled())
    {
        unbind(KEY_PGUP_DOWN,   MakeDelegate(this, &GeneralLoop::onPageUp));
        unbind(KEY_PGDOWN_DOWN, MakeDelegate(this, &GeneralLoop::onPageDown));
        unbind(KEY_HOME_DOWN,   MakeDelegate(this, &GeneralLoop::onHome));
    }

    PARENT_CLASS::onDisable();
}

//-----------------------------------------------------------------------

void GeneralLoop::onPageUp()
{
    if (iTime::getInstance()->getTimeSpeedGame() != 0.1f)
    {
        iTime::getInstance()->setTimeSpeedGame(0.1f);
    }
    else
    {
        iTime::getInstance()->setTimeSpeedGame(1.0f);
    }
}

//-----------------------------------------------------------------------

void GeneralLoop::onPageDown()
{
    if (iTime::getInstance()->getTimeSpeedGame() != 10.0f)
    {
        iTime::getInstance()->setTimeSpeedGame(10.0f);
    }
    else
    {
        iTime::getInstance()->setTimeSpeedGame(1.0f);
    }
}

//-----------------------------------------------------------------------

void GeneralLoop::onHome()
{
    m_cheat_pause = !m_cheat_pause;
}

//-----------------------------------------------------------------------

void GeneralLoop::onClose()
{
    iPlatform::getInstance()->exit();
}

//-----------------------------------------------------------------------
