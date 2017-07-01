// Copyright (c) 2001-2013 Aliasworlds Entertainment
// file cheat_manager.cpp
// author: Sergey Sotnikov

#include "head.h"
#include "cheat_manager.h"

//--------------------------------------------------------------------------------------

CheatManager::CheatManager()
: m_cheats_enabled (false)
, m_play_beep      (!iPlatform::inst()->isKeyDefined("-no-cheat-beep"))
, m_cheat_string   ()
, m_event_map      ()
{
#ifdef _DEBUG
    m_cheats_enabled  = true;
#else
    if (iPlatform::inst()->isKeyDefined("-use-cheats"))
    {
        m_cheats_enabled = true;
    }
    else
    {
        m_cheats_enabled << iSettings::inst()->getProperty("Debug", "debug_cheats");
    }
#endif

    iInput::inst()->bindKeyboard(MakeDelegate(this, &CheatManager::onKeyPress));
    iInput::inst()->bindChar(MakeDelegate(this, &CheatManager::onChar), false);
}

//-----------------------------------------------------------------------

CheatManager::~CheatManager()
{
    iInput::inst()->unbindKeyboard(MakeDelegate(this, &CheatManager::onKeyPress));
    iInput::inst()->unbindChar(MakeDelegate(this, &CheatManager::onChar), false);

    clear();
}

//-----------------------------------------------------------------------

void CheatManager::add(const String& _name, CheatEvent::Delegate *_handler)
{
    if (!_name.empty())
    {
        EVENT_MAP::iterator it_cheat = m_event_map.find(_name.toUpper());
        if (it_cheat != m_event_map.end())
        {
            // Add the handler to an existing event.
            *it_cheat->second += _handler;
        }
        else
        {
            // Create a new event.
            CheatEvent *new_event = new CheatEvent;
            *new_event += _handler;
            m_event_map[_name.toUpper()] = new_event;
        }
    }
    else
    {
        assert(!"The cheat name must not be empty.");
    }
}

//-----------------------------------------------------------------------

void CheatManager::remove(const String& _name, CheatEvent::Delegate *_handler)
{
    if (!_name.empty())
    {
        EVENT_MAP::iterator it_cheat = m_event_map.find(_name.toUpper());
        if (it_cheat != m_event_map.end())
        {
            // Remove the handler from the event.
            *it_cheat->second -= _handler;
        }
    }
    else
    {
        assert(!"The cheat name must not be empty.");
    }
}

//-----------------------------------------------------------------------

void CheatManager::clear()
{
    FOREACH (EVENT_MAP::iterator, it, m_event_map)
    {
        delete it->second;
    }

    m_event_map.clear();
}

//-----------------------------------------------------------------------

void CheatManager::setCheatsEnabled(Bool _value)
{
    m_cheats_enabled = _value;
    ///SoundPlayer::inst()->play("CHEAT");
}

//-----------------------------------------------------------------------

void CheatManager::toggleCheats()
{
    Bool enable_debug_features = false;
    enable_debug_features << iSettings::inst()->getProperty("Debug", "enable_debug_features");

    if (enable_debug_features)
    {
        m_cheats_enabled = !m_cheats_enabled;
        ///SoundPlayer::inst()->play("CHEAT");
    }
}

//-----------------------------------------------------------------------

void CheatManager::checkCheats()
{
    if (!m_cheats_enabled)
    {
        return;
    }

    // Flag for cheats begin with entered string.
    Bool partial_match = false;

    // Test all cheats.
    for (EVENT_MAP::const_iterator it = m_event_map.begin(); it != m_event_map.end(); ++it)
    {
        // Skip empty cheats.
        if (it->second->empty())
        {
            continue;
        }

        // Cheat name.
        const String& cheat_name = it->first;

        // If there's a cheat with entered name
        if (cheat_name == m_cheat_string)
        {
            // Play cheat beep.
            if (m_play_beep)
            {
                ///SoundPlayer::inst()->play("CHEAT");
            }

            // Call the cheat event.
            (*it->second)();

            // Clear string.
            m_cheat_string.clear();

            return;        
        }

        // Set the flag if there's a cheat whose name begins with entered string.
        if (cheat_name.startsWith(m_cheat_string))
        {
            partial_match = true;
        }
    }

    // If no cheats begins with entered string
    if (!partial_match)
    {
        // If the string has several chars, test the last char alone.
        if (m_cheat_string.length() >= 2)
        {
            m_cheat_string.erase(0, m_cheat_string.length() - 1);
            checkCheats();
        }
        else
        {
            m_cheat_string.clear();
        }
    }
}

//-----------------------------------------------------------------------

void CheatManager::onKeyPress(eControl _key)
{
#ifdef PLATFORM_MAC
    if (_key == KEY_F10_DOWN)
#else
    if (_key == KEY_F11_DOWN)
#endif
    {
        toggleCheats();
    }
}

//-----------------------------------------------------------------------

void CheatManager::onChar(Char _char)
{
    if (!iInput::inst()->isTyping())
    {
        m_cheat_string += toupper(_char);
        checkCheats();
    }
}

//-----------------------------------------------------------------------

const String& CheatManager::getCheatName() const
{
    return m_cheat_string;
}

//-----------------------------------------------------------------------
