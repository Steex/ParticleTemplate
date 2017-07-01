// Copyright (c) 2001-2011 Aliasworlds Entertainment
// file periodic_event.cpp
// author: Sergey Sotnikov

#include "head.h"
#include "periodic_event.h"

//-----------------------------------------------------------------------

cPeriodicEvent::cPeriodicEvent(cControl *_parent, Float _period, UInt _count, UInt _flags /*= PEF_AUTO_DESTROY*/)
: PARENT_CLASS     (_parent)
, m_finished       (false)
, m_flags          (_flags)
, m_count          (_count)
, m_period         (_period)
, m_time           (getFlag(PEF_IMMEDIATE_EVENT) ? 0.0f : _period)
, mf_get_tick_time (getFlag(PEF_MENU_TIMER) ? &cPeriodicEvent::getTickTimeMenu : &cPeriodicEvent::getTickTimeGame)
{
    assert(_period > 0);
    assert(getFlag(PEF_ENDLESS) || _count > 0);
}

//-----------------------------------------------------------------------

cPeriodicEvent::~cPeriodicEvent()
{
}

//-----------------------------------------------------------------------

void cPeriodicEvent::process()
{
    PARENT_CLASS::process();

    if (!m_finished)
    {
        m_time += (this->*mf_get_tick_time)();
        if (m_time >= m_period)
        {
            raiseEvent();
            m_time -= m_period;
        }
    }
}

//-----------------------------------------------------------------------

void cPeriodicEvent::raiseEvent()
{
    OnTick();

    if (!getFlag(PEF_ENDLESS) &&
        (m_count == 0 || --m_count == 0))
    {
        stop();
    }
}

//-----------------------------------------------------------------------

void cPeriodicEvent::onActivate()
{
    PARENT_CLASS::onActivate();

    if (!m_finished && m_time >= m_period)
    {
        raiseEvent();
        m_time -= m_period;
    }
}

//-----------------------------------------------------------------------

void cPeriodicEvent::stop()
{
    m_finished = true;
    deactivate();

    OnFinish();

    if (getFlag(PEF_AUTO_DESTROY))
    {
        UI::Destroy(this);
    }
}

//-----------------------------------------------------------------------

void cPeriodicEvent::reset()
{
    m_time = getFlag(PEF_IMMEDIATE_EVENT) ? 0.0f : m_period;
    m_finished = false;
    deactivate();
}

//-----------------------------------------------------------------------
