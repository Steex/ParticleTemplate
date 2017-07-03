// Copyright (c) 2001-2017 Aliasworlds Entertainment
// file normal_particle_control.cpp
// author: Sergey Sotnikov

#include "head.h"
#include "normal_particle_control.h"
#include "normal_particle_renderer.h"
#include "../particle_system/particle_system.h"

//-----------------------------------------------------------------------

NormalParticleControl::NormalParticleControl(cControl *_parent)
: PARENT_CLASS (_parent)
, m_system     (NULL)
, m_renderer   (NULL)
, m_texture    (NULL)
{
}

//-----------------------------------------------------------------------

void NormalParticleControl::onCreate()
{
    PARENT_CLASS::onCreate();

    m_system = new Particles::ParticleSystem();
    m_system->load();

    m_texture = iResourceManager::inst()->getTexture("particles/smoke.png");

    m_renderer = new NormalParticleRenderer();
    m_renderer->init(m_system->getMaxCount(), m_texture);
}

//-----------------------------------------------------------------------

void NormalParticleControl::onDestroy()
{
    PARENT_CLASS::onDestroy();
}

//-----------------------------------------------------------------------

void NormalParticleControl::process()
{
    PARENT_CLASS::process();

    m_system->update(getTickTimeGame());
}

//-----------------------------------------------------------------------

void NormalParticleControl::prepareDraw()
{
    PARENT_CLASS::prepareDraw();

    m_renderer->setParentTransform(getCombinedTransform());
    m_renderer->setParentColor(getCombinedColor());
    m_system->inspect(m_renderer);
}

//-----------------------------------------------------------------------

void NormalParticleControl::draw()
{
    PARENT_CLASS::draw();

    m_renderer->drawParticles();
}

//-----------------------------------------------------------------------
