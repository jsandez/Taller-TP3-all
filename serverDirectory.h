#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_
#include <set>
#include <string>

/*
 * Directorio de archivos.
 * En este caso solamente es un set de
 * String que debe ser controlado
 * por un monitor
 */
class serverDirectory {
 private:
  std::set<std::string> set_files;
 public:
  serverDirectory();
  void addFile(std::string name);
  void deleteFile(std::string name);
  bool isFile(std::string name);
  std::string getDirectory(std::string format);
};

#endif
