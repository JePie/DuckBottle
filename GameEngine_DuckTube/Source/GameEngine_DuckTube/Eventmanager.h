#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <typeindex>
#include"Event.h"


class HandlerFunctionBase
{
public:
	virtual ~HandlerFunctionBase() {};
	void exec(const Event* event) { call(event); }

private:
	virtual void call(const Event*) = 0;
};


template < class T, class EventT >
class MemberFunctionHandler : public HandlerFunctionBase
{
public:
	typedef void (T::*MemberFunc)(EventT*);
	MemberFunctionHandler(T* instance, MemberFunc memFn) : _instance(instance), _function(memFn) {};

	void call(const Event* event)
	{
		(_instance->*_function)(static_cast<EventT*>(event));
	}

private:
	T * _instance;
	MemberFunc _function;
};


class EventHandler
{
public:
	void handleEvent(const Event* event)
	{
		Handlers::iterator it = _handlers.find(std::type_index(typeid(*event)));
		if (it != _handlers.end())
		{
			it->second->exec(event);
		}
	}

	~EventHandler()
	{
		Handlers::iterator it = _handlers.begin();
		while (it != _handlers.end())
		{
			delete it->second;
			++it;
		}
		_handlers.clear();
	}

	template < class T, class EventT >
	void registerEventFunc(T*, void (T::*memFn)(EventT*));

private:
	typedef std::map<std::type_index, HandlerFunctionBase* > Handlers;
	Handlers _handlers;
};


template < class T, class EventT >
void EventHandler::registerEventFunc(T* obj, void (T::*memFn)(EventT*))
{
	_handlers[std::type_index(typeid(EventT))] =
		new MemberFunctionHandler< T, EventT >(obj, memFn);
}


class EventClass_LMouse_Clicked : public Event
{
public:
	EventClass_LMouse_Clicked() : m_eventName("default") {};
	EventClass_LMouse_Clicked(std::string eventName) : m_eventName("Event_LeftMouse_Clicked") {};
	std::string getEventName() const { return m_eventName; }
private:
	std::string m_eventName{ " defaultName " };
};