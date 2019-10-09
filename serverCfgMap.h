#ifndef _CFGMAP_H_
#define _CFGMAP_H_
#include <string>
#include <map>
#include "serverInputFileStream.h"

/*
 * Clas que representa
 * al mapa que se creara
 * a partir del archivo de configuracion
 * ingresado por parametro.
 */
class serverCfgMap {
 private:
  std::map<std::string, std::string> map;
  serverInputFileStream input_file_stream;
 public:
  serverCfgMap(std::string file_name);
  std::string get(std::string key);
  ~serverCfgMap();
};

#endif
