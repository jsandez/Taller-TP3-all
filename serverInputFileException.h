#ifndef _INPUTFILEEXCEPTION_H_
#define _INPUTFILEEXCEPTION_H_
#include <exception>
#include <stdexcept>
#include <string>

/*
 * Excepcion expecializada que se utilizara
 * cuando se abra un archivo en caso de ser necesario
 */
class serverInputFileException : public std::exception{
private:
    std::string msg;
    int __errno;
public:
    serverInputFileException(std::string msg) noexcept ;
    virtual const char* what() const noexcept ;
    ~serverInputFileException();
};

#endif
