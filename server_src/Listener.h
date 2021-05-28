#ifndef _LISTENER_H_
#define _LISTENER_H_

#include "../common_src/Socket.h"
#include "Thread.h"
#include <atomic>

class Listener : public Thread {
	private:
		Socket listener;
		bool isRunning;

		Listener(const Listener &other) = delete;
		Listener& operator=(const Listener &other) = delete;
		void run() override;

	public:
		Listener(const char *service);
		Listener(const char *host, 
				 const char *service);
		Listener(Listener &&other);
		~Listener();
		Listener& operator=(Listener &&other);
		void stop();
};

#endif // _LISTENER_H_
