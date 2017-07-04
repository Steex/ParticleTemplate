// Copyright (c) 2001-2017 Aliasworlds Entertainment
// file normal_particle_control.h
// author: Sergey Sotnikov

#ifndef _NORMAL_PARTICLE_CONTROL_INCLUDED__
#define _NORMAL_PARTICLE_CONTROL_INCLUDED__


namespace Particles
{
    class ParticleSystem;
}

class NormalParticleRenderer;


class NormalParticleControl : public cControl
{
    typedef cControl PARENT_CLASS;
    FRIEND_CREATE_METHODS;

public:

    virtual void loadIni(iIni *_ini, const String& _section);

    virtual void process();
    virtual void prepareDraw();
    virtual void draw();

protected:

    NormalParticleControl(cControl *_parent);

    virtual void onCreate();
    virtual void onDestroy();

private:

    Particles::ParticleSystem *m_system;
    NormalParticleRenderer    *m_renderer;
    iTexture                  *m_texture;
};


#endif // _NORMAL_PARTICLE_CONTROL_INCLUDED__
