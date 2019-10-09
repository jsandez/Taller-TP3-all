#ifndef _INPUTFILESTREAM_H_
#define _INPUTFILESTREAM_H_
#include <fstream>

/*
 * Clase que encapsula
 * el manejo del archivo de entrada
 */
class serverInputFileStream {
 private:
  std::ifstream ifstream;
 public:
  serverInputFileStream(std::string name_file);
  int getLine(std::string& line);
  ~serverInputFileStream();
};

#endif
