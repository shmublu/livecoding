#ifndef SHELL_COMMANDS_H
#define SHELL_COMMANDS_H

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <sstream>
#include <iostream>
#include <any>

using CommandKey = std::pair<std::string, int>;

struct Command {
    std::string name;
    int numArgs;
    std::function<void(std::vector<std::string>)> func;
    std::string helpText;
};



// Splits a string by a delimiter and returns a vector of tokens
inline std::vector<std::string> split(const std::string& str, char delim) {
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> tokens;
    while (std::getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

// Executes a command based on the input string and a map of commands
void executeCommand(const std::string& input, const std::map<CommandKey, Command>& commands);
void executeCreateRhythm(const std::vector<std::string>& stringArgs);
void executeCreateInstrument(const std::vector<std::string>& stringArgs);
void executeDeleteInstrument(const std::vector<std::string>& stringArgs);
void executeChangePitch(const std::vector<std::string>& stringArgs);
void greet(std::vector<std::string> args);
void showHelp(std::vector<std::string> args, const std::map<CommandKey, Command>& commands);

#endif // SHELL_COMMANDS_H