#pragma once

class RemoveFromGameEvent : public fw::Event
{
public:
    RemoveFromGameEvent(fw::GameObject* pObject)
    {
        m_pObject = pObject;
    }
    virtual ~RemoveFromGameEvent() {}

    static const char* GetStaticEventType() { return "RemoveFromGameEvent"; }
    virtual const char* GetType() override { return GetStaticEventType(); }

    fw::GameObject* GetGameObject() { return m_pObject; }

protected:
    fw::GameObject* m_pObject;
};

class AddFromGameEvent : public fw::Event
{
public:
    AddFromGameEvent()
    {
    }
    virtual ~AddFromGameEvent() {}

    static const char* GetStaticEventType() { return "AddFromGameEvent"; }
    virtual const char* GetType() override { return GetStaticEventType(); }


protected:

};