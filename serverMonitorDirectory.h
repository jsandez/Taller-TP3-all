#ifndef _MONITORDIRECTORY_H_
#define _MONITORDIRECTORY_H_
#include <mutex>
#include "serverDirectory.h"
#include "serverCfgMap.h"

/*
 * Clase monitor para controlar
 * el acceso de los threas al
 * directorio, sea para consultas
 * creacion o eliminacion de los archivos
 */
class serverMonitorDirectory {
 private:
  serverDirectory &directory;
  serverCfgMap &cfg_map;
  std::mutex m;
 public:
  serverMonitorDirectory(serverDirectory &directory, serverCfgMap &cfg_map);
  std::string addUniq(std::string dir_name);
  std::string removeUniq(std::string dir_name);
  std::string getDirectory(std::string format);
  ~serverMonitorDirectory();
};

#endif
