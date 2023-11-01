#include <core/event/event_system.h>

EventSystem* EventSystem::instance()
{
	static EventSystem::instance();
	return &instance;
}

void register_client(EVENT_ID event, Listener* client)
{
	// https://www.youtube.com/watch?v=2E98LkckmYk 	23:09

}

void unregister_client(EVENT_ID event, Listener* client)
{
	
}

void unregister_all(Listener* client)
{
	
}

void send_event(EVENT_ID event_id, void* data = 0)
{
	
}

void process_events()
{
	
}

void clear_events()
{
	
}

void shutdown()
{
	
}