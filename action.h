#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <time.h>	// For generating random seed
#include <vector>	// For results of multiple rolls

#define NAME_VAR 	0
#define HP_VAR		1
#define AC_VAR		2
#define SPD_VAR		3
#define INIT_VAR	4
#define ATTACK_VAR	5
#define DAM_VAR		6

void print_vector(std::vector <int> input);
int roll_dice(int num, int dice, int mod);
int take_action(std::vector<std::string> creature);
int * read_dam(std::string input);
