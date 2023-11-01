#ifndef LOCK_H
#define LOCK_H

namespace O1F4Engine
{
	namespace O1F4Thread
	{
		class Lock
		{
		private:
			//CRITICAL_SECTION m_critsec;
		public:
			Lock();
			~Lock();

			void lock();
			void unlock();
		};
	}
}

#endif // LOCK_H