#ifndef _HELPCOMMAND_H_
#define _HELPCOMMAND_H_
#include "serverCommand.h"

/*
 * Comando Help
 */
class serverHelpCommand : public serverCommand{
public:
    serverHelpCommand(serverUserAuthentication& user_authentication, serverCfgMap& cfg_map);
    std::string execute() override ;
};


#endif
