// Copyright (c) 2001-2011 Aliasworlds Entertainment
// file loop.h
// author: Roman Mikhayloff

#ifndef _LOOP_INTERFACE_INCLUDED_
#define _LOOP_INTERFACE_INCLUDED_



class iLoop
{
public:

    iLoop() : m_result(0), m_finished(false) {}
    virtual ~iLoop() {}

    virtual Bool isIdle() const = 0;
    virtual Bool isFinished() const { return m_finished; }
    virtual Int  getResult() const  { return m_result; }

protected:

    virtual void setResult(Int _value)    { m_result = _value; }
    virtual void setFinished(Bool _value) { m_finished = _value; }

private:

    Int  m_result;
    Bool m_finished;
};

#endif //_LOOP_INTERFACE_INCLUDED_
