#ifndef _ACCEPTTHREAD_H_
#define _ACCEPTTHREAD_H_
#include <list>
#include "serverThread.h"
#include "serverCfgMap.h"
#include "serverMonitorDirectory.h"
#include "serverSocket.h"

/*
 * Thread aceptador de clientes.
 * Tambien es el encargado de cerrar las conexiones
 * de forma correcta cuando el servidor se apaga.
 */
class serverAcceptThread : public serverThread {
 private:
  /*
   * Tiene una referencia al archivo de configuracion
   * para ejecutar comandos ya que esto
   * necesitan los threads clientes.
   * Tambien un monitor del directorio para controlar
   * races conditions.
   * La lista de threads es donde se iran ubicando
   * cada uno de los clientes.
   * Por ultimo, el socket que sirve como aceptador.
   */
  serverSocket &socket_server;
  serverCfgMap &cfg_map;
  serverMonitorDirectory &monitor_directory;
  std::list<serverThread *> ths;

 public:
  serverAcceptThread(serverSocket &socket_server, serverCfgMap &cfg_map, serverMonitorDirectory &directory);
  virtual void run() override;
  virtual void stop() override;
  virtual bool isAlive() override;
  ~serverAcceptThread();
};

#endif
