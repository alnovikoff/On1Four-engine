#ifndef EVENT_H
#define EVENT_H

#include <of_pch.h>

#define EVENT_ID std::string


class Event
{
public:
	//Constructor
	Event(EVENT_ID _event_id, void* _parameter = 0)
	{
		this->event_id = _event_id;
		this->parameter = _parameter;
	}

	// Destructor
	~Event() {}

	// Accessors
	inline EVENT_ID event_id_func() const { return event_id; };
	inline void* parameter_func() const { return parameter; };

private:
	// Members
	EVENT_ID  event_id;
	void* parameter;
};

#endif // EVENT_H