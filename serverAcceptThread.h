#ifndef _ACCEPTTHREAD_H_
#define _ACCEPTTHREAD_H_
#include <list>
#include "commonThread.h"
#include "serverCfgMap.h"
#include "serverMonitorDirectory.h"
#include "commonSocket.h"

/*
 * Thread aceptador de clientes.
 * Tambien es el encargado de cerrar las conexiones
 * de forma correcta cuando el servidor se apaga.
 */
class serverAcceptThread : public commonThread {
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
  commonSocket &socket_server;
  serverCfgMap &cfg_map;
  serverMonitorDirectory &monitor_directory;
  std::list<commonThread *> ths;

 public:
  serverAcceptThread(commonSocket &socket_server, serverCfgMap &cfg_map, serverMonitorDirectory &directory);
  virtual void run() override;
  virtual void stop() override;
  virtual bool isAlive() override;
};

#endif
