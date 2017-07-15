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

    m_renderer = new GeneratedParticleRenderer();
}

//-----------------------------------------------------------------------

void GeneratedParticleControl::onDestroy()
{
    PARENT_CLASS::onDestroy();
}

//-----------------------------------------------------------------------

void GeneratedParticleControl::loadIni(iIni *_ini, const String& _section)
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
        m_system = new GeneratedParticles::TempSparkles(data_xml);
    }

    // Reinitialize the renderer.
    m_renderer->init(m_system ? m_system->getMaxCount() : 0, m_texture);

    // Start the system.
    m_system->start();
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
