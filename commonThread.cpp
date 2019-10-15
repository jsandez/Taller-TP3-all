#include "commonThread.h"

commonThread::commonThread() {}

commonThread::~commonThread() {
}

void commonThread::start() {
  thread = std::thread(&commonThread::run, this);
}

void commonThread::join() {
  thread.join();
}

commonThread::commonThread(commonThread &&other) {
  this->thread = std::move(other.thread);
}

commonThread &commonThread::operator=(commonThread &&other) {
  this->thread = std::move(other.thread);
  return *this;
}