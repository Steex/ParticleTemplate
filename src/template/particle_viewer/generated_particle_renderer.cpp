// Copyright (c) 2001-2017 Aliasworlds Entertainment
// file generated_particle_renderer.cpp
// author: Sergey Sotnikov

#include "head.h"
#include "generated_particle_renderer.h"
#include "../particle_system/base_params.h"

//-----------------------------------------------------------------------

GeneratedParticleRenderer::GeneratedParticleRenderer()
: m_texture          (NULL)
, m_parent_transform (Matrix3::IDENTITY)
, m_parent_color     (Colors::White)
, m_render_flags     (0)
, m_particles        ()
, m_draw_count       (0)
{

}

//-----------------------------------------------------------------------

GeneratedParticleRenderer::~GeneratedParticleRenderer()
{
}

//-----------------------------------------------------------------------

void GeneratedParticleRenderer::init(USize _particle_count, iTexture *_texture)
{
    // Remember the texture.
    m_texture = _texture;
    Rect texture_rect(Vector2(0.0f, 0.0f), (Vector2)_texture->getImageSize());

    // Prepare params.
    m_particles.resize(_particle_count);

    FOREACH (ParticleList::iterator, particle, m_particles)
    {
        particle->draw_params.m_texture       = _texture;
        particle->draw_params.m_texture_map_u = iGraphics::TMM_CLAMP;
        particle->draw_params.m_texture_map_v = iGraphics::TMM_CLAMP;
        particle->draw_params.m_render_flags  = m_render_flags;

        particle->sprite.m_texture_rect = texture_rect;
        particle->sprite.m_transform    = &particle->transform;
        particle->sprite.m_color        = Colors::White;

        particle->transform = Matrix3::IDENTITY;
    }

    // Reset the draw count.
    m_draw_count = 0;
}

//-----------------------------------------------------------------------

void GeneratedParticleRenderer::setTexture(iTexture *_texture)
{
    // Remember the texture.
    m_texture = _texture;
    Rect texture_rect(Vector2(0.0f, 0.0f), (Vector2)_texture->getImageSize());

    // Update params.
    FOREACH (ParticleList::iterator, particle, m_particles)
    {
        particle->draw_params.m_texture = _texture;
        particle->sprite.m_texture_rect = texture_rect;
    }
}

//-----------------------------------------------------------------------

void GeneratedParticleRenderer::setParentTransform(const Matrix3& _transform)
{
    m_parent_transform = _transform;
}

//-----------------------------------------------------------------------

void GeneratedParticleRenderer::setParentColor(const Color& _color)
{
    m_parent_color = _color;
}

//-----------------------------------------------------------------------

void GeneratedParticleRenderer::iterate(const Byte *_start, USize _stride, USize _count)
{
    for (USize i = 0; i < _count; ++i)
    {
        const GeneratedParticles::BaseParticleParams *params = (const GeneratedParticles::BaseParticleParams*)(_start + _stride * i);
        Particle& particle = m_particles[i];

        // Update particle transform.
        particle.transform.makeTransform(params->position, Vector2(params->scale, params->scale), params->angle);
        particle.transform *= m_parent_transform;

        // Update particle color.
        particle.sprite.m_color = params->color * m_parent_color;
    }

    m_draw_count = _count;
}

//-----------------------------------------------------------------------

void GeneratedParticleRenderer::drawParticles()
{
    iGraphics *graphics = iGraphics::inst();

    for (USize i = 0; i < m_draw_count; ++i)
    {
        graphics->drawSprite2D(m_particles[i].draw_params, m_particles[i].sprite);
    }
}

//-----------------------------------------------------------------------
