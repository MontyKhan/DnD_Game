dnd_game: main.cpp combatant.cpp csv_reader.cpp tools.cpp
	g++-8 -lstdc++fs -std=c++17 -c combatant.cpp csv_reader.cpp tools.cpp load_file.cpp weapon_type.cpp roll.cpp pathfinding.cpp player.cpp tile.cpp object.cpp display.cpp main.cpp -lstdc++fs;
	g++-8 -lstdc++fs combatant.o csv_reader.o tools.o load_file.o weapon_type.o roll.o pathfinding.o player.o tile.o object.o display.o main.o -o ./output/dnd_game.exe -lsfml-graphics -lsfml-window -lsfml-system -lstdc++fs
