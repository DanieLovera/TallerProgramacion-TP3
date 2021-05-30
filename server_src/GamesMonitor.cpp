#include "GamesMonitor.h"
#include "Tateti.h"
#include <string>
#include <map>
#include <utility>

GamesMonitor::GamesMonitor() { }

GamesMonitor::~GamesMonitor() { }

void GamesMonitor::putIfAbsent(std::string &&key, Tateti &tateti) {
	std::lock_guard<std::mutex> lock(mutex);
	std::map<std::string, Tateti*>::iterator it = games.find(key);
	if(it == games.end()) {
		games[std::move(key)] = &tateti;
	}
}

/*void GamesMonitor::removeIfPresent(const std::string &key) {
	std::lock_guard<std::mutex> lock(mutex);
	std::map<std::string, Tateti*>::iterator it = games.find(key);
	if (it != games.end()) {
		games.erase(key);
	}
}*/

Tateti& GamesMonitor::operator[](const std::string &key) {
	return *(games.at(key));
}

std::string GamesMonitor::toString() {
	std::lock_guard<std::mutex> lock(mutex);
	std::string str;
	str += "Partidas:\n";
	for (auto &pair : games) {
		str += " - ";
		str += pair.first;
		str += "\n";
	}
	return str;
}
