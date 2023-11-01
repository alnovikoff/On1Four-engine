#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include <core/event/event.h>

class EventListener
{
private:
	EventListener() {}
	virtual ~EventListener() {}
	virtual void handle_event(Event* event) = 0;
public:
};

#endif // EVENT_LISTENER_H