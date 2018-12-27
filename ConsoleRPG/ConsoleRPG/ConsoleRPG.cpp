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
-Change some struckts to classes (not sure which ones)

-Loot system
-Fight system
-Cave generating system
-Proper inputter
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

class ENEMY
{
public:
	int ID, positionX, positionY, drop_table_id, health;
	int inventory[10];
};

//****************************************************************************************************************************
//Spawning and killing functions
int spawn(int map_with_ids[23][79], std::stack<ENEMY> &stack_of_enemies, int x, int y) {
	ENEMY enemy;
	std::stack <ENEMY> temporary_stack;

	//cheacks if enemy egzists in location
	while (stack_of_enemies.size() > 0)
	{
		if (stack_of_enemies.top().positionX == x && stack_of_enemies.top().positionY == y)
		{
			std::cout << "Here alredy is an enemy." << std::endl;
			while (temporary_stack.size() > 0)
			{
				stack_of_enemies.push(temporary_stack.top());
				temporary_stack.pop();
			}
			system("pause");
			return 0;
		}
		temporary_stack.push(stack_of_enemies.top());
		stack_of_enemies.pop();
	}
	//bringing back all enemies form temporary stack
	while (temporary_stack.size() > 0)
	{
		stack_of_enemies.push(temporary_stack.top());
		temporary_stack.pop();
	}

	stack_of_enemies.push(enemy);
	stack_of_enemies.top().positionX = x;
	stack_of_enemies.top().positionY = y;
	stack_of_enemies.top().ID = stack_of_enemies.size();

	map_with_ids[y][x] = 2;
	return 0;
}

//Handling dev command
int spawn_command(int map_with_ids[23][79], std::stack<ENEMY> &stack_of_enemies) {
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
	return 0;
}

//Reassigning ID for enemies. NEEDED WHEN YOU KILL ENEMY!!!!
void reassigning_of_ID(std::stack<ENEMY> &stack_of_enemies) {
	std::stack <ENEMY> temporary_stack;

	while (stack_of_enemies.size() > 0)
	{
		stack_of_enemies.top().ID = stack_of_enemies.size();
		temporary_stack.push(stack_of_enemies.top());
		stack_of_enemies.pop();
	}

	while (temporary_stack.size() > 0)
	{
		stack_of_enemies.push(temporary_stack.top());
		temporary_stack.pop();
	}
}

//Prepared to fetch by ID enemy you want to kill (helpfull after fight)
void kill(int map_with_ids[23][79], std::stack<ENEMY> &stack_of_enemies, int ID) {
	std::stack <ENEMY> temporary_stack;
	int temporary_x, temporary_y;

	//Search for Enemy with ID
	while (stack_of_enemies.top().ID != ID)
	{
		temporary_stack.push(stack_of_enemies.top());
		stack_of_enemies.pop();
	}
	temporary_x = stack_of_enemies.top().positionX;
	temporary_y = stack_of_enemies.top().positionY;

	//the killing part
	stack_of_enemies.pop();
	map_with_ids[temporary_y][temporary_x] = 0;

	while (temporary_stack.size() > 0)
	{
		stack_of_enemies.push(temporary_stack.top());
		temporary_stack.pop();
	}
}

//Handling dev command
int kill_command(int map_with_ids[23][79], std::stack<ENEMY> &stack_of_enemies) {
	int ID;

	std::cout << "What ID: " << std::endl;
	std::cin >> ID;

	//Very crucial, becouse othewise whole game gonna expolde XD
	if (ID == 0)
	{
		return 0;
	}
	else if (ID > stack_of_enemies.size())
	{
		std::cout << " Oop... Out of range. Try showID :) " << std::endl; Sleep(2000);
		kill_command(map_with_ids, stack_of_enemies);
	}

	kill(map_with_ids, stack_of_enemies, ID);
	return 0;
}

void kill_all(int map_with_ids[23][79], std::stack<ENEMY> &stack_of_enemies) {
	while (stack_of_enemies.size() > 0)
	{
		kill(map_with_ids, stack_of_enemies, stack_of_enemies.size());
	}
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

//Returns the ID of enemy for drawer
int enemy_ID(std::stack<ENEMY> &stack_of_enemies, int x, int y) {
	std::stack <ENEMY> temporary_stack;
	int temporary_ID;

	//searching for enemy ID
	while (stack_of_enemies.top().positionX != x && stack_of_enemies.top().positionY != y)
	{
		temporary_stack.push(stack_of_enemies.top());
		stack_of_enemies.pop();
	}

	temporary_ID = stack_of_enemies.top().ID;

	//putting back together stack
	while (temporary_stack.size() > 0)
	{
		stack_of_enemies.push(temporary_stack.top());
		temporary_stack.pop();
	}

	return temporary_ID;
}

//Function that is drawing table
void map_drawer(int map_with_ids[23][79], std::stack<ENEMY> &stack_of_enemies, bool show_enemies_id) {
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
				if (show_enemies_id == false)
				{
					std::cout << (char)2;
				}
				else
				{
					std::cout << enemy_ID(stack_of_enemies , x, y);
				}
			}
		}
		std::cout << std::endl;
	}
}
//****************************************************************************************************************************

//testing function (my favourite)
void testing() {
	system("cls");



	system("pause");
}

//****************************************************************************************************************************
//Main loop
void Game_loop() {
	system("cls");

	//Prepering variables, structures, map and stack
	std::string what_to_do;
	bool exit = true;
	bool show_enemies_id = false;
	NPC player;
	int map_with_ids[23][79];
	std::stack <ENEMY> stack_of_enemies;


	player.positionX = 39;
	player.positionY = 10;

	map_creator(map_with_ids);

	do{
		//Placing player on his position
		map_with_ids[player.positionY][player.positionX] = 1;
		//Drawing map
		map_drawer(map_with_ids, stack_of_enemies, show_enemies_id);
		//What player is going to do
		std::cout << "What do you want to do?" << std::endl;
		std::cin >> what_to_do;
		//Replacing old player location
		map_with_ids[player.positionY][player.positionX] = 0;

		//Commands
		//For player

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
				std::cout << "showID" << std::endl;
				std::cout << "kill" << std::endl;
				std::cout << "killall" << std::endl;
				std::cout << std::endl;
				system("pause");
			}

			//exiting
			else if (what_to_do == "exit")
			{
				exit = false;
			}

			//For Dev

			else if(what_to_do == "spawn")
			{
				spawn_command(map_with_ids, stack_of_enemies);
			}
			//Shows ID of enemy insted of it's icon
			else if(what_to_do == "showID")
			{
				if (show_enemies_id == true)
				{
					show_enemies_id = false;
				}
				else
				{
					show_enemies_id = true;
				}
			}

			else if (what_to_do == "kill") {
				kill_command(map_with_ids, stack_of_enemies);
				reassigning_of_ID(stack_of_enemies);
			}

			else if (what_to_do == "killall") {
				kill_all(map_with_ids, stack_of_enemies);
			}

			else if (what_to_do == "testing") {
				testing();
			}

			//only if game doesn't support command
			else
			{
				map_drawer(map_with_ids, stack_of_enemies, show_enemies_id);
				std::cout << "Sorry we do not support this command. Pleas try out help :)";
				Sleep(2000);
			}
	} while (exit);
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
	case 666: //testing();
		break;
	default: std::cout << "Beeep.... "; Sleep(900); std::cout << "beep...."; Sleep(900); std::cout <<" boop...." << std::endl; Sleep(2000); std::cout << "Shuting down" << std::endl;
		break;
	}
	return 0;
}