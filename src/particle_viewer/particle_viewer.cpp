// Copyright (c) 2001-2011 Aliasworlds Entertainment
// file particle_viewer.cpp
// author: Sergey Sotnikov

#include "head.h"

#include "particle_viewer.h"
#include "particle_control.h"

//-----------------------------------------------------------------------

ParticleViewer::ParticleViewer(cControl *_parent)
: PARENT_CLASS (_parent)
, m_particles  (NULL)
{
}

//-----------------------------------------------------------------------

ParticleViewer::~ParticleViewer()
{
}

//-----------------------------------------------------------------------

void ParticleViewer::onCreate()
{
    PARENT_CLASS::onCreate();

    loadIni(iResourceManager::inst()->getIni("particles/viewer.ini"));
}

//-----------------------------------------------------------------------

void ParticleViewer::onDestroy()
{
    PARENT_CLASS::onDestroy();
}

//-----------------------------------------------------------------------

void ParticleViewer::loadIni(iIni *_ini)
{
    PARENT_CLASS::loadIni(_ini, "COMMON");

    UI::IniLoader ui(this, _ini);

    m_particles = ui.get<ParticleControl>("PARTICLES");
}

//-----------------------------------------------------------------------

void ParticleViewer::process()
{
    PARENT_CLASS::process();
}

//-----------------------------------------------------------------------

void ParticleViewer::onEnable()
{
    PARENT_CLASS::onEnable();
}

//-----------------------------------------------------------------------

void ParticleViewer::onDisable()
{
    PARENT_CLASS::onDisable();
}

//-----------------------------------------------------------------------
