// Copyright (c) 2001-2017 Aliasworlds Entertainment
// file generated_particle_control.h
// author: Sergey Sotnikov

#ifndef _GENERATED_PARTICLE_CONTROL_INCLUDED__
#define _GENERATED_PARTICLE_CONTROL_INCLUDED__


namespace GeneratedParticles
{
    class IParticleSystem;
}

class GeneratedParticleRenderer;


class GeneratedParticleControl : public cControl
{
    typedef cControl PARENT_CLASS;
    FRIEND_CREATE_METHODS;

public:

    virtual void process();
    virtual void prepareDraw();
    virtual void draw();

protected:

    GeneratedParticleControl(cControl *_parent);

    virtual void onCreate();
    virtual void onDestroy();

private:

    GeneratedParticles::IParticleSystem *m_system;
    GeneratedParticleRenderer *m_renderer;
    iTexture                  *m_texture;
};


#endif // _GENERATED_PARTICLE_CONTROL_INCLUDED__
