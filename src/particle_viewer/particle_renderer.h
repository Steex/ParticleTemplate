// Copyright (c) 2001-2017 Aliasworlds Entertainment
// file particle_renderer.h
// author: Sergey Sotnikov

#ifndef _PARTICLE_RENDERER_INCLUDED__
#define _PARTICLE_RENDERER_INCLUDED__


#include "../particle_system/renderer.h"


class ParticleRenderer : public Particles::Renderer
{
public:

    ParticleRenderer();
    virtual ~ParticleRenderer();

    void init(USize _particle_count, iTexture *_texture);
    void setTexture(iTexture *_texture);
    void setParentTransform(const Matrix3& _transform);
    void setParentColor(const Color& _color);
    void drawParticles();
    virtual void renderParticles(Byte *_start, USize _stride, USize _count);

private:

    struct Particle
    {
        iGraphics::DrawParams draw_params;
        iGraphics::Sprite     sprite;
        Matrix3               transform;
    };

    typedef std::vector<Particle> ParticleList;

    iTexture    *m_texture;
    Matrix3      m_parent_transform;
    Color        m_parent_color;
    UInt         m_render_flags;
    ParticleList m_particles;
    USize        m_draw_count;
};


#endif // _PARTICLE_RENDERER_INCLUDED__
