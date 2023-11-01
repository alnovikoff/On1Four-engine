#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <core/event/event.h>
#include <core/event/event_listener.h>

class EventSystem
{
	public:
	static EventSystem* Instance();

	void register_client(EVENT_ID event, Listener* client);

	void unregister_client(EVENT_ID event, Listener* client);

	void unregister_all(Listener* client);

	void send_event(EVENT_ID event_id, void* data = 0);

	void process_events();

	void clear_events();

	void shutdown();

	private:
	// Singleton, deny access to construct/destruct
	EventSystem() {};
	~EventSystem() {};
	EventSystem(const EventSystem& rhs) {};
	EventSystem& operator=(const EventSystem& rhs) {};

	std::multimap<EVENT_ID, EventListener*> database;
	std::list<Event> currentEvents;
};

#endif // EVENT_SYSTEM_H