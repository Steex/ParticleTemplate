// Copyright (c) 2001-2011 Aliasworlds Entertainment
// file particle_viewer.cpp
// author: Sergey Sotnikov

#ifndef _PARTICLE_VIEWER_INCLUDED__
#define _PARTICLE_VIEWER_INCLUDED__


//class ParticleControl;


class ParticleViewer : public cControl
{
    typedef cControl PARENT_CLASS;
    FRIEND_CREATE_METHODS;

public:

    virtual void process();

protected:

    ParticleViewer(cControl *_parent);
    virtual ~ParticleViewer();

    virtual void onCreate();
    virtual void onDestroy();

    virtual void onEnable();
    virtual void onDisable();

private:

    void loadIni(iIni *_ini);

    //ParticleControl *m_particles;
};


#endif // _PARTICLE_VIEWER_INCLUDED__
