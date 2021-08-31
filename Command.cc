#include <cassert>
#include "Command.h"
#include "Type.h"

// Constructors and Destructors
Command::Command(): type{EMPTY}, secondArg{""}, multiplier{0} {}
Command::Command(Type t): type{t}, secondArg{""}, multiplier{0} {}
Command::~Command() {}

// Parse for any numbers at the beginning of a command
std::string Command::_parseInputNumber(std::string cmd) {
  int i = 0;
  multiplier = 0;
  for (; i < cmd.size(); i++) {
    if (isdigit(cmd[i])) {
      multiplier = multiplier*10 + (cmd[i] - '0');
    } else {
      break;
    }
  }
  if (i == 0) multiplier = 1;
  else cmd.erase(0, i);
  
  return cmd.empty() ? " " : cmd;

}

// Used to read in a command
std::istream& operator>>(std::istream &in, Command &c) {
  std::string cmd;
  std::string blocks = "IJLSZOT";
  in >> cmd;
  cmd = c._parseInputNumber(cmd);

  // check if each input can be identified as command 
  if (std::string("left").find(cmd, 0) == 0 && cmd.size() >= 3) {
    c.type = LEFT;
  } else if (std::string("right").find(cmd, 0) == 0 && cmd.size() >= 2) {
    c.type = RIGHT;
  } else if (std::string("down").find(cmd, 0) == 0 && cmd.size() >= 2) {
    c.type = DOWN;
  } else if (std::string("clockwise").find(cmd, 0) == 0 && cmd.size() >= 2) {
    c.type = CLOCKWISE;
  } else if (std::string("counterclockwise").find(cmd, 0) == 0 && cmd.size() >= 2) {
    c.type = COUNTERCLOCKWISE;
  } else if (std::string("drop").find(cmd, 0) == 0 && cmd.size() >= 2) {
    c.type = DROP;
  } else if (std::string("levelup").find(cmd, 0) == 0 && cmd.size() >= 6) {
    c.type = LEVELUP;
  } else if (std::string("leveldown").find(cmd, 0) == 0 && cmd.size() >= 6) {
    c.type = LEVELDOWN;
  } else if (std::string("norandom").find(cmd, 0) == 0) {
    c.type = NORANDOM;
    in >> c.secondArg;
  } else if (std::string("random").find(cmd, 0) == 0 && cmd.size() >= 2) {
    c.type = RANDOM;
  } else if (std::string("sequence").find(cmd, 0) == 0) {
    c.type = SEQUENCE;
    in >> c.secondArg;
  } else if (blocks.find(cmd) != std::string::npos && cmd.size() == 1) {
    c.type = BLOCK;
    c.secondArg = cmd;
  } else if (std::string("restart").find(cmd, 0) == 0 && cmd.size() >= 2) {
    c.type = RESTART;
  } else if (std::string("hint").find(cmd, 0) == 0) {
    c.type = HINT;
  }

  return in;
}