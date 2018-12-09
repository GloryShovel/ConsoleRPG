#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>

struct NPC
{
	std::string name;
	int height, width, weight, race, age, positionX, positionY;
	int inventory[10];
	bool is_enemy;

};

struct Item
{
	std::string name;
	int ID;
};

//testing function (my favourite)
void testing() {
	system("cls");

}

//It's returning name of item
std::string	getting_name_by_id(){
	//opening file with item name
	std::string file_name = "Drop_Name_By_ID.txt";
	std::fstream file;
	file.open(file_name.c_str());

	//here logic (TO DO!!!!!!) (becouse I need enemy first)
	return 0;
}

//droping function
void drop() {


}

//Working pattern for creating 23x79 plane to walk on.
void map_creator(bool map_to_walk_on[23][79], char map_drawing[23][79]) {
	for (int y = 0; y < 23; y++) {
		for (int x = 0; x < 79; x++) {
			if (y == 0 || y == 22 || x == 0 || x == 78)
			{
				map_to_walk_on[y][x] = false;
				map_drawing[y][x] = (char)219;
			}
			else{
				map_to_walk_on[y][x] = true;
				map_drawing[y][x] = ' ';
			}
		}
	}
}

//Function that is drawing table
void map_drawer(bool map_to_walk_on[23][79], char map_drawing[23][79]) {
	system("cls");

	for (int y = 0; y < 23; y++) {
		for (int x = 0; x < 79; x++) {
			std::cout << map_drawing[y][x];
		}
		std::cout << std::endl;
	}
}

//New main loop
void Game_loop(bool map_to_walk_on[23][79], char map_drawing[23][79]) {
	system("cls");

	//Prepering variables, structures and map
	std::string what_you_are_going_to_do;
	bool exit = true;
	struct NPC player;
	player.positionX = 39;
	player.positionY = 10;
	map_creator(map_to_walk_on, map_drawing);

	do{
		//Placing player on his position
		map_drawing[player.positionY][player.positionX] = (char)1;
		//Drawing map
		map_drawer(map_to_walk_on, map_drawing);
		//What player is going to do
		std::cout << "What do you want to do?" << std::endl;
		std::cin >> what_you_are_going_to_do;
		//Replacing old player location
		map_drawing[player.positionY][player.positionX] = ' ';

		//walking
		if (what_you_are_going_to_do == "up" && map_to_walk_on[player.positionY - 1][player.positionX] == true)
		{
			player.positionY--;
		}
		else if (what_you_are_going_to_do == "down" && map_to_walk_on[player.positionY + 1][player.positionX] == true)
		{
			player.positionY++;
		}
		else if (what_you_are_going_to_do == "left" && map_to_walk_on[player.positionY][player.positionX - 1] == true)
		{
			player.positionX--;
		}
		else if (what_you_are_going_to_do == "right" && map_to_walk_on[player.positionY][player.positionX + 1] == true)
		{
			player.positionX++;
		}

		//exiting
		if (what_you_are_going_to_do == "exit")
		{
			exit = false;
		}
	} while (exit);
}

int main()
{
	system("cls");
	int choise;
	bool map_to_walk_on[23][79];
	char map_drawing[23][79];

    std::cout << "\n\n\n\n\n\n\n\n\n\n\n                            Welcome in ConsoleRPG"; 
	std::cin.get(); system("cls");
	std::cout << "1.New Game \n2.Load Game \n3.Options \n4.Exit";
	std::cin >> choise;

	switch (choise)
	{
	case 1: Game_loop(map_to_walk_on, map_drawing);
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