#ifndef _USERAUTHENTICATION_H_
#define _USERAUTHENTICATION_H_
#include <string>

/*
 * Clase que funciona como autenticador
 * del usuario, tambien guarada el user_name
 * en caso de ser necesario para realizar
 * la autenticacion. Tiene un enum con
 * los estados del usuario dependiendo el momento
 */
enum UserState {
  NOT_AUTHENTICATED = 0,
  LOGIN_PROVIDED = 1,
  AUTHENTICATED = 2
};

class serverUserAuthentication {
 private:
  UserState state;
  std::string user_name;

 public:
  serverUserAuthentication();
  void user(std::string user_name);
  void setState(UserState state);
  std::string getUser() const;
  bool checkState(UserState user_state);
};

#endif
