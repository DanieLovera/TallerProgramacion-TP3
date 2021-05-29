#ifndef _GAMES_MONITOR_H_
#define _GAMES_MONITOR_H_

#include <map>
#include <mutex>
#include <string>

class Tateti;

class GamesMonitor {
	private:
		std::map<std::string, Tateti> games;
		std::mutex mutex;

		GamesMonitor(const GamesMonitor &other) = delete;
		GamesMonitor(GamesMonitor &&other) = delete;
		GamesMonitor& operator=(const GamesMonitor &other) = delete;
		GamesMonitor& operator=(GamesMonitor &&other) = delete;

	public:
		GamesMonitor();
		~GamesMonitor();
		void putIfAbsent(std::string &&key, Tateti &&tateti);
		void removeIfPresent(const std::string &key);
		Tateti& operator[](const std::string key);
		std::string toString();
};

#endif // _GAMES_MONITOR_H_