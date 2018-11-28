#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <string>

//Stcructure shuldn't be in main??????
struct NPC
{
	std::string name;
	int height, width, weight, race, age, positionX, positionY;

};

//testing function (my favourite)
void testing() {
	system("cls");
	
	
	
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
	player.positionX = 1;
	player.positionY = 1;
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

//Here should be main loop of the game, but insted I created butload of code typing words. (for later use mabye)
//*************************************************************************************************************************************************************************
void game_start() {
	system("cls");
	struct NPC player;

	//Just text shit for fun. I'm going to replace this.
	std::cout << "<Lady> Hello participants." << std::endl; Sleep(3000);
	std::cout << "<Lady> Time have come for another of you to join oure &%$^&#322" << std::endl; Sleep(5000);
	std::cout << "<Lady> Ok, you are next to see prof. OAK. Please tell us youre name" << std::endl;
	std::cout << "<YOU>"; std::cin >> player.name;
	std::cin.get(); system("cls");
	std::cout << "<Prof. OAK> Ohhh.... "; Sleep(2000); std::cout << player.name << " was it?"; Sleep(2000); std::cout <<" Yes, now I remember." << std::endl; std::cin.get();
	std::cout << "<Prof. OAK> WAIT!!!!"; Sleep(1000); std::cout << "\n\n ^ The hell is this!? \n | \n" << std::endl; Sleep(2000); std::cout << "SOMEONE IS GOING TO LOSE HIS HEAD. MY NAME IS JOHN !!!!" << std::endl; std::cin.get();
	system("cls");
	std::cout << "<JOHN> FINALY! \n<JOHN> All right I'm here to introduce you to all of the mechanics in this $#522$#%#"; std::cin.get();
	system("cls"); std::cout << "INTRODUCING 0%"; Sleep(2000);
	system("cls"); std::cout << "INTRODUCING 20%"; Sleep(2000);
	system("cls"); std::cout << "INTRODUCING 40%"; Sleep(2000);
	system("cls"); std::cout << "INTRODUCING 60%"; Sleep(2000);
	system("cls"); std::cout << "INTRODUCING 80%"; Sleep(2000);
	system("cls"); std::cout << "INTRODUCING 81%"; Sleep(2000);
	system("cls"); std::cout << "INTRODUCING 82%"; Sleep(2000);
	system("cls"); std::cout << "INTRODUCING 83%"; Sleep(2000);
	system("cls"); std::cout << "INTRODUCING 83% (Becouse of windows :P)"; Sleep(2000);
	system("cls"); std::cout << "INTRODUCING 90%"; Sleep(2000);
	system("cls"); std::cout << "INTRODUCING 99%"; Sleep(2000);
	system("cls"); std::cout << "INTRODUCING NAN%"; Sleep(5000);
	system("cls"); std::cout << "Ok. Just kidding. Go play game :P";
}
//*************************************************************************************************************************************************************************

void main()
{
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
	case 2: std::cout << "Still working on it" <<std::endl;
		break;
	case 3: std::cout << "Still working on it" << std::endl;
		break;
	case 4: std::cout << "Bye." << std::endl;
		break;
	case 666: testing();
		break;
	default: std::cout << "Beeep.... "; Sleep(900); std::cout << "beep...."; Sleep(900); std::cout <<" boop...." << std::endl; Sleep(2000); std::cout << "Shuting down" << std::endl;
		break;
	}
}