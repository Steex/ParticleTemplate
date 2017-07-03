// Copyright (c) 2001-2011 Aliasworlds Entertainment
// file general_loop.cpp
// author: Sergey Sotnikov

#ifndef _GENERAL_LOOP_INCLUDED__
#define _GENERAL_LOOP_INCLUDED__

class ParticleViewer;
class CheatManager;


class GeneralLoop
    : public cControl
    , public Singleton<GeneralLoop>
{
    typedef cControl PARENT_CLASS;
    FRIEND_CREATE_METHODS;

public:

    static GeneralLoop* Create();
    static void Destroy();

    virtual void process();

    void onClose();

protected:

    GeneralLoop();
    virtual ~GeneralLoop();

    virtual void onCreate();
    virtual void onDestroy();

    virtual void onEnable();
    virtual void onDisable();

private:

    void onPageUp();
    void onPageDown();
    void onHome();


    ParticleViewer *m_particle_viewer;

    CheatManager   *m_cheat_manager;
    Bool            m_cheat_pause;
};


#endif // _GENERAL_LOOP_INCLUDED__
