#ifndef _THREAD_H_
#define _THREAD_H_
#include <thread>

/*
 * Interfaz de thread que luego
 * utilizaran los hilos especificos
 */
class commonThread {
 private:
  std::thread thread;

 public:
  commonThread();
  void start();
  void join();
  virtual void run() = 0;
  virtual void stop() = 0;
  virtual bool isAlive() = 0;
  virtual ~commonThread();
  commonThread(const commonThread &) = delete;
  commonThread &operator=(const commonThread &) = delete;
  commonThread(commonThread &&other);
  commonThread &operator=(commonThread &&other);
};

#endif
