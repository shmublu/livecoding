#include "shell.h"
#include "music.h"
#include <bitset>

enum class ArgType { INT, FLOAT, STRING };
struct TypedArg {
    ArgType type;
    std::string value;
};


void executeCommand(const std::string& input, const std::map<CommandKey, Command>& commands) {
    auto tokens = split(input, ' ');
    if (tokens.empty()) return; // No input

    std::string cmdName = tokens[0];
    int argCount = tokens.size() - 1; // Number of arguments

    auto it = commands.find({cmdName, argCount});
    if (it == commands.end()) {
        // Try finding a command with variable arguments (-1)
        it = commands.find({cmdName, -1});
    }

    if (it != commands.end()) {
        tokens.erase(tokens.begin()); // Remove command name from the list of arguments
        it->second.func(tokens); // Execute the command
    } else {
        std::cout << "Error: Unknown command or incorrect number of arguments '" << cmdName << "'\n";
    }
}

//Commands:


void executeChangeRhythmPattern(const std::vector<std::string>& stringArgs) {
    if (stringArgs.size() != 2) {
        std::cout << "Error: Incorrect number of arguments for change_rhythm_pattern\n";
        return;
    }

    try {
        // Assuming the first argument is a binary string representation of the pattern
        char pattern = static_cast<char>(std::bitset<8>(stringArgs[0]).to_ulong());
        std::string rhythm_name = stringArgs[1];
        
        change_rhythm_pattern(pattern, rhythm_name);
        std::cout << "Rhythm pattern changed successfully for rhythm '" << rhythm_name << "'\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}
void executeListInstruments(const std::vector<std::string>& stringArgs) {
    if (stringArgs.size() != 0) {
        std::cout << "Error: Incorrect number of arguments for list_instrument\n";
        return;
    }
    try {
        listInstruments();
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        return;
    }
}

void executeListRhythms(const std::vector<std::string>& stringArgs) {
    if (stringArgs.size() != 0) {
        std::cout << "Error: Incorrect number of arguments for list_rhythms\n";
        return;
    }
    try {
        listRhythms();
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        return;
    }
}
void executeCreateInstrument(const std::vector<std::string>& stringArgs) {
    if (stringArgs.size() != 4) {
        std::cout << "Error: Incorrect number of arguments for create_instrument\n";
        return;
    }
    try {
        create_instrument(
            "./samples/" + stringArgs[0],
            stringArgs[1],
            stringArgs[2],
            std::stoi(stringArgs[3])
        );
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        return;
    }
}

void executeChangePitch(const std::vector<std::string>& stringArgs) {
    if (stringArgs.size() != 2) {
        std::cout << "Error: Incorrect number of arguments for change_pitch\n";
        return;
    }
    try {
        change_instrument_pitch(
            std::stof(stringArgs[0]),
            stringArgs[1]
        );
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}


void executeCreateRhythm(const std::vector<std::string>& stringArgs) {
    if (stringArgs.size() != 2) {
        std::cout << "Error: Incorrect number of arguments for create_rhythm\n";
        return;
    }
    try {
        create_rhythm(
            stringArgs[0],
            stringArgs[1]
        );
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void executeDeleteInstrument(const std::vector<std::string>& stringArgs) {
    if (stringArgs.size() != 1) {
        std::cout << "Error: Incorrect number of arguments for delete_instrument\n";
        return;
    }
    try {
        delete_instrument(
            stringArgs[0]
        );
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}



void showHelp(std::vector<std::string> args, const std::map<CommandKey, Command>& commands) {
    for (const auto& cmd : commands) {
        std::cout << cmd.first.first << " - " << cmd.second.helpText << "\n";
    }
}

