#include "Thread.h"
#include <utility>
#include <iostream>

Thread::Thread() : thread {} { }
	
Thread::Thread(Thread &&other) : thread {std::move(other.thread)} { }

Thread::~Thread() { }

Thread& Thread::operator=(Thread &&other) {
	if (this == &other) return *this;
	thread = std::move(other.thread);
	return *this;
}

void Thread::start() {
	thread = std::move(std::thread(&Thread::run, this));
}

void Thread::join() {
	thread.join();
}
