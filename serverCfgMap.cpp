#include "serverCfgMap.h"
#include "serverInputFileException.h"

/*
 * Tener en cuenta que si una linea del
 * archivo de configuracion no posee el caracter =
 * entonces se tomara como archivo invalido.
 */
serverCfgMap::serverCfgMap(std::ifstream &input_file_stream) :
    input_file_stream(input_file_stream) {
  std::string line;
  while (std::getline(this->input_file_stream, line)) {
    size_t found = line.find('=');
    if (found == std::string::npos) {
      throw serverInputFileException("INCORRECT ENTRY IN CFG FILE");
    }
    this->map[line.substr(0, found)] = line.substr(found + 1);
    line.clear();
  }
}

std::string serverCfgMap::get(const std::string &key) const {
  try {
    return map.at(key);
  } catch (const std::out_of_range &e) {
    return "";
  }
}
