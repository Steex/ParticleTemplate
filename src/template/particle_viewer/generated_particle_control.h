// Copyright (c) 2001-2017 Aliasworlds Entertainment
// file generated_particle_control.h
// author: Sergey Sotnikov

#ifndef _GENERATED_PARTICLE_CONTROL_INCLUDED__
#define _GENERATED_PARTICLE_CONTROL_INCLUDED__


namespace ParticlesGenCpp
{
    class IParticleSystem;
}

class GeneratedParticleRenderer;


class GeneratedParticleControl : public cControl
{
    typedef cControl PARENT_CLASS;
    FRIEND_CREATE_METHODS;

public:

    virtual void loadIni(iIni *_ini, const String& _section);

    virtual void process();
    virtual void prepareDraw();
    virtual void draw();

protected:

    GeneratedParticleControl(cControl *_parent);

    virtual void onCreate();
    virtual void onDestroy();

private:

    ParticlesGenCpp::IParticleSystem *m_system;
    GeneratedParticleRenderer *m_renderer;
    iTexture                  *m_texture;
};


#endif // _GENERATED_PARTICLE_CONTROL_INCLUDED__
