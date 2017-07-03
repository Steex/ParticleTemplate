// Copyright (c) 2001-2011 Aliasworlds Entertainment
// file periodic_event.h
// author: Sergey Sotnikov

#ifndef _PERIODIC_EVENT_INCLUDED__
#define _PERIODIC_EVENT_INCLUDED__


enum ePeriodicEventFlags
{
    // The timer never stops by itself (otherwise it'll stop when the given number of events are raised).
    PEF_ENDLESS         = 1 << 0,
    // An event will be raised immediately at activate (otherwise after the period time)
    PEF_IMMEDIATE_EVENT = 1 << 1,
    // Use the menu timer (otherwise use the game timer).
    PEF_MENU_TIMER      = 1 << 2,
    // Destroy the event object after finish.
    PEF_AUTO_DESTROY    = 1 << 3,
};


class cPeriodicEvent: public cControl
{
    typedef cControl PARENT_CLASS;
    FRIEND_CREATE_METHODS;

public:

    Event0<void> OnTick;
    Event0<void> OnFinish;

    virtual void process();

    Bool isFinished() const { return m_finished; }

    void stop();
    void reset();

protected:

    cPeriodicEvent(cControl *_parent, Float _period, UInt _count, UInt _flags = PEF_AUTO_DESTROY);
    virtual ~cPeriodicEvent();

    virtual void onActivate();

private:

    typedef Float (cPeriodicEvent::*fGetTickTime)() const;

    Bool getFlag(ePeriodicEventFlags _flag) const { return (m_flags & (UInt)_flag) != 0; }
    void raiseEvent();

    Bool m_finished;

    UInt m_flags;
    UInt m_count;
    Float m_period;
    Float m_time;

    fGetTickTime mf_get_tick_time;
};


#endif // _PERIODIC_EVENT_INCLUDED__