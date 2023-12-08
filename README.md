Live Coding with Seq++ Manual

DEMOS:

https://youtu.be/DZi7UhxmMEo

https://youtu.be/7PzMGss335g

https://youtu.be/VtUtDDlT8E8


Key Features

Live Coding: Modify and create music on the fly, with changes taking effect in real time.

Rhythmic Patterns: Utilize patterns as rhythms where every bit represents 1/8 of a second in a repeating cycle, allowing for intricate and varied rhythmic compositions.

Instrument Management: Create, modify, and delete instruments, providing a diverse palette of sounds for your compositions.

Dynamic Interaction: Change instrument pitches and rhythm patterns instantaneously, enabling a highly interactive and responsive music-making experience.

Sound files come from the samples folder, and more sound files can be added by the end user.

Shell Version Available Commands
1. Create Instrument (ci)
Usage: ci <file_name> <rhythm_id> <instrument_id> <pitchVal>
Function: Creates a new instrument with the specified file name, rhythm ID, instrument ID, and pitch value.
Example: ci guitar.wav rhythm1 guitar1 2
2. Change Instrument Pitch (cp)
Usage: cp <pitchVal> <instrument_id>
Function: Changes the pitch of an existing instrument.
Example: cp 8 guitar1
3. Create Rhythm (cr)
Usage: cr <rhythm_pattern> <rhythm_id>
Function: Creates a new rhythm with a specified pattern and rhythm ID. 
Example: cr 10001000 rhythm1
4. Delete Instrument (di)
Usage: di <instrument_id>
Function: Deletes an instrument from the system.
Example: di guitar1
5. Change Rhythm Pattern (crp)
Usage: crp <pattern> <rhythm_id>
Function: Changes the pattern of an existing rhythm.
Example: crp 00110011 rhythm1
6. List Instruments (li)
Usage: li
Function: Lists all instruments currently available in the system.
7. List Rhythms (lr)
Usage: lr
Function: Lists all rhythms currently available in the system.
8. Help (help)
Usage: help
Function: Displays help text with information about all available commands.
Additional Information
If an error occurs, the shell will provide an appropriate error message to guide you.



Cling Available Functions
1. listInstruments()
Purpose: Lists all available instruments in the system.
Usage: Simply call listInstruments(); in the Cling console.
Example: listInstruments();
2. listRhythms()
Purpose: Lists all rhythms currently available.
Usage: Use listRhythms(); to display all rhythms.
Example: listRhythms();
3. create_instrument(outputChannel, rhythm_name, instrument_name, pitchVal)
Purpose: Creates a new instrument.
Parameters:
outputChannel: The output channel number (type: uint32_t).
rhythm_name: Name of the rhythm (type: std::string).
instrument_name: Name for the new instrument (type: std::string).
pitchVal: The pitch value (type: int).
Usage: create_instrument(1, "rhythm1", "guitar", 440);
Example: create_instrument(2, "beat", "piano", 330);
4. create_rhythm(input, rhythm_name)
Purpose: Creates a new rhythm pattern.
Parameters:
input: string of numbers with length 8 representing the rhythm pattern (type: std::string). Numbers correspond to pitches in a key. Currently the key is hard coded as B flat minor.
rhythm_name: Name for the rhythm (type: std::string).
Usage: create_rhythm("12345671", "rhythm1");
Example: create_rhythm("00110011", "beat");
5. change_rhythm_pattern(pattern, rhythm_name)
Purpose: Changes the pattern of an existing rhythm.
Parameters:
pattern: New rhythm pattern (type: char).
rhythm_name: Name of the rhythm to change (type: std::string).
Usage: change_rhythm_pattern('A', "rhythm1");
Example: change_rhythm_pattern('B', "beat");
6. change_instrument_pitch(pitch, instrument_name)
Purpose: Changes the pitch of an existing instrument.
Parameters:
pitch: New pitch value (type: float).
instrument_name: Name of the instrument to modify (type: std::string).
Usage: change_instrument_pitch(440.0, "guitar");
Example: change_instrument_pitch(523.25, "piano");
7. delete_instrument(instrument_name)
Purpose: Deletes an existing instrument.
Parameters:
instrument_name: Name of the instrument to delete (type: std::string).
Usage: delete_instrument("guitar");
Example: delete_instrument("piano");
8. get_instrument_rhythm(instrument_name)
Purpose: Retrieves the rhythm pattern associated with an instrument.
Parameters:
instrument_name: Name of the instrument (type: std::string).
Usage: get_instrument_rhythm("guitar");
Example: char rhythm = get_instrument_rhythm("piano");


