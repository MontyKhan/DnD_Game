dnd_game: main.cpp combatant.cpp csv_reader.cpp tools.cpp
	g++ -std=c++11 -c combatant.cpp csv_reader.cpp tools.cpp load_file.cpp weapon_type.cpp roll.cpp pathfinding.cpp player.cpp main.cpp;
	g++ combatant.o csv_reader.o tools.o load_file.o weapon_type.o roll.o pathfinding.o player.o main.o -o ./output/dnd_game.exe -lsfml-graphics -lsfml-window -lsfml-system
