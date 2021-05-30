#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "CommunicationProtocol.h"
#include "Thread.h"
#include <atomic>
class GamesMonitor;

class Client : public Thread {
	private:
		Socket peer;
		GamesMonitor &gamesMonitor;
		bool isRunning;

		Client(const Client &other) = delete;
		Client& operator=(const Client &other) = delete;
		Client& operator=(Client &&other) = delete;
		void run() override;

	public:
		Client(Socket &&peer, GamesMonitor &gamesMonitor);
		Client(Client &&other);
		~Client();

		void stop();
		bool isDead() const;
};

#endif // _CLIENT_H_
