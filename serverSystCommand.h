#ifndef _SYSTCOMMAND_H_
#define _SYSTCOMMAND_H_
#include "serverCommand.h"

/*
 * Comando para saber informacion del sistema
 */
class serverSystCommand : public serverCommand {
public:
    serverSystCommand(serverUserAuthentication &user_authentication, serverCfgMap &cfg_map);
    std::string execute() override;
};


#endif
