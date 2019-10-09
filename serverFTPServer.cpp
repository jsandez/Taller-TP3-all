#include <iostream>
#include "serverFTPServer.h"
#include "serverCommand.h"

serverFTPServer::serverFTPServer(serverCfgMap &cfg_map, serverMonitorDirectory &directory)
    : cfg_map(cfg_map), directory(directory) {}

void serverFTPServer::executeCommand(std::string msg, std::string &response) {
  serverCommand *command = serverCommand::getCommand(msg, this->user_authentication,
                                                     this->cfg_map, this->directory);
  response = std::move(command->execute());
  delete command;
}
