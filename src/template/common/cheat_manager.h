// Copyright (c) 2001-2015 Aliasworlds Entertainment
// file cheat_manager.h
// author: Sergey Sotnikov

#ifndef RB_EXTENSIONS_CHEAT_MANAGER_INCLUDED
#define RB_EXTENSIONS_CHEAT_MANAGER_INCLUDED


class CheatManager : public Singleton<CheatManager>
{
public:

    typedef Event0<void> CheatEvent;

    CheatManager();
    virtual ~CheatManager();

    Bool isCheatsEnabled() const { return m_cheats_enabled; }
    void setCheatsEnabled(Bool _value);

    // Assigns a handing function to the action
    void add(const String& _name, CheatEvent::Delegate *_handler);
    // Clear the action handler
    void remove(const String& _name, CheatEvent::Delegate *_handler);
    // Clear all handlers
    void clear();

    // Gets the name of the currently called handler.
    const String& getCheatName() const;

private:

    struct CheatLess
    {
        Bool operator()(const String& _left, const String& _right) const
        {
            return
                _left.length() <  _right.length() ||
                (_left.length() == _right.length() && _left < _right);
        }
    };

    typedef std::map<String, CheatEvent*, CheatLess> EVENT_MAP;


    void toggleCheats();
    void checkCheats();

    void onKeyPress(eControl _key);
    void onChar(Char _char);


    Bool m_cheats_enabled;
    Bool m_play_beep;
    String m_cheat_string;

    EVENT_MAP m_event_map;
};


#endif // RB_EXTENSIONS_CHEAT_MANAGER_INCLUDED
