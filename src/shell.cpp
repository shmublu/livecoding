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
        // Convert rhythm string to character representation
        std::string input = stringArgs[0];
        std::reverse(input.begin(), input.end());
        std::bitset<8> binaryRepresentation(input);
        unsigned char character = static_cast<unsigned char>(binaryRepresentation.to_ulong());

        create_rhythm(
            character,
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

void listFiles(std::vector<std::string> args) {
    // Implementation for listing files
    std::cout << "Listing files...\n";
}

void greet(std::vector<std::string> args) {
    if (!args.empty()) {
        std::cout << "Hello, " << args[0] << "!\n";
    }
}

void showHelp(std::vector<std::string> args, const std::map<CommandKey, Command>& commands) {
    for (const auto& cmd : commands) {
        std::cout << cmd.first.first << " - " << cmd.second.helpText << "\n";
    }
}

