#include "serverCfgMap.h"
#include "serverInputFileException.h"

/*
 * Tener en cuenta que si una linea del
 * archivo de configuracion no posee el caracter =
 * entonces se tomara como archivo invalido.
 */
serverCfgMap::serverCfgMap(std::string file_name) : input_file_stream(file_name) {
  std::string line;
  while (this->input_file_stream.getLine(line) != -1) {
    size_t found = line.find('=');
    if (found == std::string::npos) {
      throw serverInputFileException("INCORRECT ENTRY IN CFG FILE");
    }
    this->map[line.substr(0, found)] = line.substr(found + 1);
    line.clear();
  }
}

std::string serverCfgMap::get(std::string key) {
  return map[key];
}

serverCfgMap::~serverCfgMap() {}