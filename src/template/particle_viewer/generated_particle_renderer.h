// Copyright (c) 2001-2017 Aliasworlds Entertainment
// file generated_particle_renderer.h
// author: Sergey Sotnikov

#ifndef _GENERATED_PARTICLE_RENDERER_INCLUDED__
#define _GENERATED_PARTICLE_RENDERER_INCLUDED__


#include "../particle_system/inspector.h"


class GeneratedParticleRenderer : public Particles::Inspector
{
public:

    GeneratedParticleRenderer();
    virtual ~GeneratedParticleRenderer();

    void init(USize _particle_count, iTexture *_texture);
    void setTexture(iTexture *_texture);
    void setParentTransform(const Matrix3& _transform);
    void setParentColor(const Color& _color);
    void drawParticles();
    virtual void inspect(const Byte *_start, USize _stride, USize _count);

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


#endif // _GENERATED_PARTICLE_RENDERER_INCLUDED__
