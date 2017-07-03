// Copyright (c) 2001-2017 Aliasworlds Entertainment
// file particle_control.h
// author: Sergey Sotnikov

#ifndef _PARTICLE_CONTROL_INCLUDED__
#define _PARTICLE_CONTROL_INCLUDED__


namespace Particles
{
    class ParticleSystem;
}

class ParticleRenderer;


class ParticleControl : public cControl
{
    typedef cControl PARENT_CLASS;
    FRIEND_CREATE_METHODS;

public:

    virtual void process();
    virtual void prepareDraw();
    virtual void draw();

protected:

    ParticleControl(cControl *_parent);

    virtual void onCreate();
    virtual void onDestroy();

private:

    Particles::ParticleSystem *m_system;
    ParticleRenderer          *m_renderer;
    iTexture                  *m_texture;
};


#endif // _PARTICLE_CONTROL_INCLUDED__
