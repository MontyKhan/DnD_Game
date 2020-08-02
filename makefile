dnd_helper: main.cpp combatant.cpp csv_reader.cpp tools.cpp
	g++ -std=c++11 -o output/dnd_helper.exe combatant.cpp csv_reader.cpp tools.cpp load_file.cpp weapon_type.cpp roll.cpp pathfinding.cpp player.cpp main.cpp
