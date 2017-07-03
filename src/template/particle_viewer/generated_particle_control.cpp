// Copyright (c) 2001-2017 Aliasworlds Entertainment
// file generated_particle_control.cpp
// author: Sergey Sotnikov

#include "head.h"
#include "generated_particle_control.h"
#include "generated_particle_renderer.h"
#include "../tmp_particle_system.h"

//-----------------------------------------------------------------------

GeneratedParticleControl::GeneratedParticleControl(cControl *_parent)
: PARENT_CLASS (_parent)
, m_system     (NULL)
, m_renderer   (NULL)
, m_texture    (NULL)
{
}

//-----------------------------------------------------------------------

void GeneratedParticleControl::onCreate()
{
    PARENT_CLASS::onCreate();

    m_system = new GeneratedParticles::TempSparkles();

    m_texture = iResourceManager::inst()->getTexture("particles/smoke.png");

    m_renderer = new GeneratedParticleRenderer();
    m_renderer->init(m_system->getMaxCount(), m_texture);
}

//-----------------------------------------------------------------------

void GeneratedParticleControl::onDestroy()
{
    PARENT_CLASS::onDestroy();
}

//-----------------------------------------------------------------------

void GeneratedParticleControl::process()
{
    PARENT_CLASS::process();

    m_system->update(getTickTimeGame());
}

//-----------------------------------------------------------------------

void GeneratedParticleControl::prepareDraw()
{
    PARENT_CLASS::prepareDraw();

    m_renderer->setParentTransform(getCombinedTransform());
    m_renderer->setParentColor(getCombinedColor());
    m_system->render(m_renderer);
}

//-----------------------------------------------------------------------

void GeneratedParticleControl::draw()
{
    PARENT_CLASS::draw();

    m_renderer->drawParticles();
}

//-----------------------------------------------------------------------
