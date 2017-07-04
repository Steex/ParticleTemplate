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

    m_renderer = new NormalParticleRenderer();
}

//-----------------------------------------------------------------------

void NormalParticleControl::onDestroy()
{
    PARENT_CLASS::onDestroy();
}

//-----------------------------------------------------------------------

void NormalParticleControl::loadIni(iIni *_ini, const String& _section)
{
    PARENT_CLASS::loadIni(_ini, _section);

    // Set the texture.
    String texture_name = _ini->get(_section, "picture");
    if (!texture_name.empty())
    {
        m_texture = iResourceManager::inst()->getTexture(texture_name);
    }

    // Destroy the existing system.
    delete m_system;
    m_system = NULL;

    // Create a new system.
    String system_data_file = _ini->get(_section, "system");
    if (!system_data_file.empty())
    {
        iXml *data_xml = iResourceManager::inst()->getXml(system_data_file);
        m_system = new Particles::ParticleSystem(data_xml);
    }

    // Reinitialize the renderer.
    m_renderer->init(m_system ? m_system->getMaxCount() : 0, m_texture);
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
