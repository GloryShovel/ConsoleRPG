#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <stack>

/*
TODO: 
-Recreat map with vectors / pointers.
-Recreate table of enemies
-Enchence spawning
-Change some struckts to classes (not sure which ones)

-Loot system
-Fight system
-Cave generating system
*/

//****************************************************************************************************************************
//Class
class NPC
{
public:
	std::string name;
	int ID, height, width, weight, race, age, positionX, positionY, drop_table_id, health;
	int inventory[10];
};

//****************************************************************************************************************************
//Spawning and killing functions
void spawn(int map_with_ids[23][79], std::stack<NPC> stack_of_enemies, int x, int y) {
	struct NPC enemy;

	stack_of_enemies.push(enemy);
	stack_of_enemies.top().positionX = x;
	stack_of_enemies.top().positionY = y;
	
	map_with_ids[y][x] = 2;
}

void spawn_command(int map_with_ids[23][79], std::stack<NPC> stack_of_enemies) {
	int x, y;
	std::cout << "Where X: "; std::cin >> x;
	if (x <= 0 || x > 78)
	{
		std::cout << "You got wrong x (range betwin 1 and 78)";
		spawn_command(map_with_ids, stack_of_enemies);
	}
	std::cout << " Y: "; std::cin >> y;
	if (y <= 0 || y > 22)
	{
		std::cout << "You got wrong y (range betwin 1 and 22)";
		spawn_command(map_with_ids, stack_of_enemies);
	}

	spawn(map_with_ids, stack_of_enemies, x, y);
}

void kill(int map_with_ids[23][79], std::stack<NPC> stack_of_enemies) {

}

void kill_command() {

	
}

void kill_all() {

}

//****************************************************************************************************************************
//Drop functions
//It's returning name of item
std::string	getting_name_by_id(){
	//opening file with items names
	std::string file_name = "Drop_Name_By_ID.txt";
	std::fstream file;
	file.open(file_name.c_str());

	//here logic (TO DO!!!!!!) (becouse I need enemy first)
	return 0;
}

//droping function
void drop() {


}

//****************************************************************************************************************************
//Map functions
//Working pattern for creating 23x79 plane to walk on.
void map_creator(int map_with_ids[23][79]) {
	for (int y = 0; y < 23; y++) {
		for (int x = 0; x < 79; x++) {
			if (y == 0 || y == 22 || x == 0 || x == 78)
			{
				map_with_ids[y][x] = -1;
			}
			else{
				map_with_ids[y][x] = 0;
			}
		}
	}
}

//Function that is drawing table
void map_drawer(int map_with_ids[23][79]) {
	/* What ID is what
	<0 - unwalkable
	0 - walkable
	1 - palyer
	2 - enemy
	*/
	system("cls");

	for (int y = 0; y < 23; y++) {
		for (int x = 0; x < 79; x++) {
			if (map_with_ids[y][x] < 0) {
				std::cout << (char)219;
			}
			if (map_with_ids[y][x] == 0) {
				std::cout << " ";
			}
			if (map_with_ids[y][x] == 1) {
				std::cout << (char)1;
			}
			if (map_with_ids[y][x] == 2) {
				std::cout << (char)2;
			}
		}
		std::cout << std::endl;
	}
}
//****************************************************************************************************************************

//Main loop
void Game_loop() {
	system("cls");

	//Prepering variables, structures, map and stack
	std::string what_to_do;
	bool exit = true;
	NPC player;
	int map_with_ids[23][79];
	std::stack <NPC> stack_of_enemies;

	player.positionX = 39;
	player.positionY = 10;

	map_creator(map_with_ids);

	do{
		//Placing player on his position
		map_with_ids[player.positionY][player.positionX] = 1;
		//Drawing map
		map_drawer(map_with_ids);
		//What player is going to do
		std::cout << "What do you want to do?" << std::endl;
		std::cin >> what_to_do;
		//Replacing old player location
		map_with_ids[player.positionY][player.positionX] = 0;

		//commends

		//walking
		if (what_to_do == "up" && map_with_ids[player.positionY - 1][player.positionX] >= 0)
		{
			player.positionY--;
		}
		else if (what_to_do == "down" && map_with_ids[player.positionY + 1][player.positionX] >= 0)
		{
			player.positionY++;
		}
		else if (what_to_do == "left" && map_with_ids[player.positionY][player.positionX - 1] >= 0)
		{
			player.positionX--;
		}
		else if (what_to_do == "right" && map_with_ids[player.positionY][player.positionX + 1] >= 0)
		{
			player.positionX++;
		}

		else if(what_to_do == "help")
		{
			system("cls");
			std::cout << "up" << std::endl;
			std::cout << "down" << std::endl;
			std::cout << "left" << std::endl;
			std::cout << "right" << std::endl;
			std::cout << "exit" << std::endl << std::endl;
			std::cout << "Debbuging comands (cheats XD)" << std::endl;
			std::cout << "WARNING: If you use them not properly even I will not be able help you!!!" << std::endl;
			std::cout << "spawn" << std::endl;
			std::cout << std::endl;
			system("pause");
		}

		//exiting
		else if (what_to_do == "exit")
		{
			exit = false;
		}
		else if(what_to_do == "spawn")
		{
			spawn_command(map_with_ids, stack_of_enemies);
		}

		//only if game doesn't support command
		else
		{
			map_drawer(map_with_ids);
			std::cout << "Sorry we do not support this command. Pleas try out help :)";
			Sleep(2000);
		}
	} while (exit);
}

//testing function (my favourite)
void testing() {

}

//Just regular main
int main()
{
	system("cls");
	int choise;

    std::cout << "\n\n\n\n\n\n\n\n\n\n\n                            Welcome in ConsoleRPG"; 
	std::cin.get(); system("cls");
	std::cout << "1.New Game \n2.Load Game \n3.Options \n4.Exit";
	std::cin >> choise;

	switch (choise)
	{
	case 1: Game_loop();
		break;
	case 2: std::cout << "Still working on it" << std::endl; Sleep(1000); main();
		break;
	case 3: std::cout << "Still working on it" << std::endl; Sleep(1000); main();
		break;
	case 4: std::cout << "Bye." << std::endl;
		break;
	case 666: testing();
		break;
	default: std::cout << "Beeep.... "; Sleep(900); std::cout << "beep...."; Sleep(900); std::cout <<" boop...." << std::endl; Sleep(2000); std::cout << "Shuting down" << std::endl;
		break;
	}
	return 0;
}