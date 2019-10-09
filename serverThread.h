#ifndef _THREAD_H_
#define _THREAD_H_
#include <thread>

/*
 * Interfaz de thread que luego
 * utilizaran los hilos especificos
 */
class serverThread {
 private:
  std::thread thread;

 public:
  serverThread();
  void start();
  void join();
  virtual void run() = 0;
  virtual void stop() = 0;
  virtual bool isAlive() = 0;
  virtual ~serverThread();
  serverThread(const serverThread &) = delete;
  serverThread &operator=(const serverThread &) = delete;
  serverThread(serverThread &&other);
  serverThread &operator=(serverThread &&other);
};

#endif
