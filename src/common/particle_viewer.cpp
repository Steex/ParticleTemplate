// Copyright (c) 2001-2011 Aliasworlds Entertainment
// file particle_viewer.cpp
// author: Sergey Sotnikov

#include "head.h"
#include "particle_viewer.h"

//-----------------------------------------------------------------------

ParticleViewer::ParticleViewer(cControl *_parent)
: PARENT_CLASS (_parent)
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

    show();
    enable();
    activate();
}

//-----------------------------------------------------------------------

void ParticleViewer::onDestroy()
{
    PARENT_CLASS::onDestroy();
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
