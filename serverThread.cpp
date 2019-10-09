#include "serverThread.h"

serverThread::serverThread() {}

serverThread::~serverThread() {
}

void serverThread::start() {
  thread = std::thread(&serverThread::run, this);
}

void serverThread::join() {
  thread.join();
}

serverThread::serverThread(serverThread &&other) {
  this->thread = std::move(other.thread);
}

serverThread &serverThread::operator=(serverThread &&other) {
  this->thread = std::move(other.thread);
  return *this;
}