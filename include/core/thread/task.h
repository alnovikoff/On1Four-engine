#ifndef TASK_H
#define TASK_H

#include <core/thread/task_func.h>
#include <core/thread/task_data.h>

namespace O1F4Engine
{
	namespace O1F4Thread
	{
		class Task
		{
		public:
			Task(TaskFunc task, TaskData* data) 
			{
				m_task = task;
				m_data = data;
			}
			Task(const Task&) {}
			Task& operator = (const Task&){}
			~Task()
			{
				if(m_data != NULL)
					delete m_data;
				
				m_data = NULL;
				//m_task = NULL;
			}

			TaskFunc	GetTask()	{ return m_task; }
			TaskData*	GetData()	{ return m_data; }
		private:
			TaskFunc m_task;
			TaskData* m_data;
		};
	}
}

//typedef void (*TaskFunc)(Task*);

#endif // TASK_H