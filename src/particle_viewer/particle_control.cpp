// Copyright (c) 2001-2017 Aliasworlds Entertainment
// file particle_control.cpp
// author: Sergey Sotnikov

#include "head.h"
#include "particle_control.h"
#include "particle_renderer.h"
#include "../particle_system/particle_system.h"

//-----------------------------------------------------------------------

ParticleControl::ParticleControl(cControl *_parent)
: PARENT_CLASS (_parent)
, m_system     (NULL)
, m_renderer   (NULL)
, m_texture    (NULL)
{
}

//-----------------------------------------------------------------------

void ParticleControl::onCreate()
{
    PARENT_CLASS::onCreate();

    m_system = new Particles::ParticleSystem();
    m_system->load();

    m_texture = iResourceManager::inst()->getTexture("particles/smoke.png");

    m_renderer = new ParticleRenderer();
    m_renderer->init(m_system->getMaxCount(), m_texture);
}

//-----------------------------------------------------------------------

void ParticleControl::onDestroy()
{
    PARENT_CLASS::onDestroy();
}

//-----------------------------------------------------------------------

void ParticleControl::process()
{
    PARENT_CLASS::process();

    m_system->update(getTickTimeGame());
}

//-----------------------------------------------------------------------

void ParticleControl::prepareDraw()
{
    PARENT_CLASS::prepareDraw();

    m_renderer->setParentTransform(getCombinedTransform());
    m_renderer->setParentColor(getCombinedColor());
    m_system->render(m_renderer);
}

//-----------------------------------------------------------------------

void ParticleControl::draw()
{
    PARENT_CLASS::draw();

    m_renderer->drawParticles();
}

//-----------------------------------------------------------------------
