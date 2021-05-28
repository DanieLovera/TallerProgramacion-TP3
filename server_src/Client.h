#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "CommunicationProtocol.h"
#include "Thread.h"
#include <atomic>

class Client : public Thread {
	private:
		Socket peer;
		bool keepTalking;
		bool isRunning;

		Client(const Client &other) = delete;
		Client& operator=(const Client &other) = delete;
		void run() override;

	public:
		Client(Socket &&peer);
		Client(Client &&other);
		~Client();
		Client& operator=(Client &&other);

		void stop();
		bool isDead() const;
};

#endif // _CLIENT_H_
