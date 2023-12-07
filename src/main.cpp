#include <SFML/Audio.hpp>
#include <iostream>
#include "music.h"
#include <sstream>
#include <algorithm>
#include "shell.h"


int main() {
    // test
    start_music_thread();
    std::map<CommandKey, Command> commands;

    // Registering commands
    commands[{"ci", 4}] = Command{"create_instrument", 4, executeCreateInstrument, "Create an instrument. Usage: ci <file_name> <rhythm_id> <instrument_id> <pitchVal>"};
    commands[{"cp", 2}] = Command{"change_pitch", 2, executeChangePitch, "Change an instrument's pitch. Usage: cp <pitchVal> <instrument_id>"};
    commands[{"cr", 2}] = Command{"create_rhythm", 2, executeCreateRhythm, "Create a rhythm. Usage: cr <rhythm_pattern> <rhythm_id>"};
    commands[{"di", 1}] = Command{"delete_instrument", 1, executeDeleteInstrument, "Delete an instrument. Usage: di <instrument_id>"};
    commands[{"greet", 1}] = Command{"greet", 1, greet, "Greet a user by name"};
    commands[{"help", 0}] = Command{"help", 0, [commands](auto args){ showHelp(args, commands); }, "Show help text"};
    
    while (true) {
        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);

        executeCommand(input, commands);
    }
}

