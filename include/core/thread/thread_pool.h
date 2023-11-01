#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <of_pch.h>
#include <core/thread/task.h>

namespace O1F4Engine
{
	namespace O1F4Thread
	{
		class ThreadPool
		{
		public:
			ThreadPool(size_t size);
			~ThreadPool();

			void add_task(Task task);
			void wait();
			void stop();
			int get_num_threads();
			bool is_stoped();
			bool is_empty();

		private:
			std::vector<std::thread> m_threads;
			std::queue<Task> m_tasks;
			std::mutex m_mutex;
			std::condition_variable m_condition_variable;
			bool m_stopped;
		};
	}
}

#endif // THREAD_POOL_H