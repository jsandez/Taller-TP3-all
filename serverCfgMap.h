#ifndef _CFGMAP_H_
#define _CFGMAP_H_
#include <string>
#include <map>
#include <fstream>

/*
 * Clas que representa
 * al mapa que se creara
 * a partir del archivo de configuracion
 * ingresado por parametro.
 */
class serverCfgMap {
 private:
  std::map<std::string, std::string> map;
  std::ifstream& input_file_stream;
 public:
  serverCfgMap(std::ifstream& input_file_stream);
  std::string get(const std::string& key) const;
};

#endif
