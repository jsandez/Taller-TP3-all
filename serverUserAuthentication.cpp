#include "serverUserAuthentication.h"

serverUserAuthentication::serverUserAuthentication() {
  this->state = NOT_AUTHENTICATED;
}

void serverUserAuthentication::user(std::string user_name) {
  this->user_name = user_name;
}

void serverUserAuthentication::setState(UserState state) {
  this->state = state;
}

std::string serverUserAuthentication::getUser() const {
  return this->user_name;
}

bool serverUserAuthentication::checkState(UserState user_state) {
  return (this->state == user_state);
}

serverUserAuthentication::~serverUserAuthentication() {}