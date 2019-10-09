#include "serverInputFileStream.h"
#include "serverInputFileException.h"

serverInputFileStream::serverInputFileStream(std::string name_file) : ifstream(name_file) {
    if (this->ifstream.fail()) {
        this->ifstream.close();
        throw serverInputFileException("FALLO AL ABRIR EL ARCHIVO");
    }
}

int serverInputFileStream::getLine(std::string &line) {
    if (!std::getline(this->ifstream, line)) {
        return -1;
    }
    return 0;
}

serverInputFileStream::~serverInputFileStream() {
    this->ifstream.close();
}
