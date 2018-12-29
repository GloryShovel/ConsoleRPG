#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <cstdio>

/*
TODO:
-Recreat map with vectors / pointers.
-Change some struckts to classes (not sure which ones)
-Create better UI modules
-Enchence egzisting UIs

-Loot system
-Fight system
-Cave generating system
-Proper inputter
*/

//********************************************************************************************************************************************************************************************************
//																																																CLASSES
//standard NPC
class NPC
{
public:
	std::string name;
	int ID, height, width, weight, race, age, positionX, positionY, drop_table_id, health, base_damage;
	int inventory[10];
};

//Standard enemy
class ENEMY
{
public:
	int ID, positionX, positionY, drop_table_id, health;
	int inventory[10];
};

//																																																CLASSES
//********************************************************************************************************************************************************************************************************
//																																														 USEFULL FUNCTIONS
//Converting int to vector of chars
std::vector <char> int_to_char(int i) {
	std::vector <char> tab;
	std::vector <char> tab_revers;
	bool a = false;

	if (i < 0)
	{
		a = true;
		i *= -1;
	}

	do
	{
		tab.push_back(i % 10 + 48);
		i /= 10;
	} while (i > 0);

	if (a) {
		tab.push_back(45);
	}

	while (tab.size() > 0)
	{
		tab_revers.push_back(tab.back());
		tab.pop_back();
	}

	return tab_revers;
}

//Returns the ID of enemy by giving him pozition
int enemy_ID_finder(std::stack<ENEMY> &stack_of_enemies, int x, int y) {
	std::stack <ENEMY> temporary_stack;
	int ID_holder;

	//Searching for enemy ID
	while (stack_of_enemies.top().positionX != x && stack_of_enemies.top().positionY != y)
	{
		temporary_stack.push(stack_of_enemies.top());
		stack_of_enemies.pop();
	}

	ID_holder = stack_of_enemies.top().ID;

	//Putting back together the stack
	while (temporary_stack.size() > 0)
	{
		stack_of_enemies.push(temporary_stack.top());
		temporary_stack.pop();
	}

	return ID_holder;
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

//																																													 USEFULL FUNCTIONS
//********************************************************************************************************************************************************************************************************
//																																													 SPAWNING AND KILLING
//Spawning without command
int spawn(int map_with_ids[23][79], std::stack<ENEMY> &stack_of_enemies, int x, int y, ENEMY enemy) {
	std::stack <ENEMY> temporary_stack;

	//Cheacks if enemy egzists in location
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
	//Bringing back all enemies form temporary stack
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

//Handling dev spawn command (remember about reassigning_of_ID(stack_of_enemies); )
int spawn_command(int map_with_ids[23][79], std::stack<ENEMY> &stack_of_enemies, ENEMY enemy) {
	int x, y;

	std::cout << "Where X: "; std::cin >> x;
	if (x <= 0 || x > 78)
	{
		std::cout << "You got wrong x (range betwin 1 and 78)";
		spawn_command(map_with_ids, stack_of_enemies, enemy);
	}

	std::cout << " Y: "; std::cin >> y;
	if (y <= 0 || y > 22)
	{
		std::cout << "You got wrong y (range betwin 1 and 22)";
		spawn_command(map_with_ids, stack_of_enemies, enemy);
	}
	spawn(map_with_ids, stack_of_enemies, x, y, enemy);
	return 0;
}

//Prepared to fetch by ID enemy you want to kill ( you always have to write reassigning_of_ID(stack_of_enemies); after killing)
void kill(int map_with_ids[23][79], std::stack<ENEMY> &stack_of_enemies, int ID, int *actual_pozition_ID) {
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
	//map_with_ids[temporary_y][temporary_x] = 0;
	*actual_pozition_ID = 0;

	while (temporary_stack.size() > 0)
	{
		stack_of_enemies.push(temporary_stack.top());
		temporary_stack.pop();
	}
}

//Handling dev  kill command
int kill_command(int map_with_ids[23][79], std::stack<ENEMY> &stack_of_enemies, int *actual_pozition_ID) {
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
		kill_command(map_with_ids, stack_of_enemies, actual_pozition_ID);
	}

	kill(map_with_ids, stack_of_enemies, ID, actual_pozition_ID);
	return 0;
}

//Handling dev killall command
void kill_all(int map_with_ids[23][79], std::stack<ENEMY> &stack_of_enemies, int *actual_pozition_ID) {
	while (stack_of_enemies.size() > 0)
	{
		kill(map_with_ids, stack_of_enemies, stack_of_enemies.size(), actual_pozition_ID);
	}
}

//																																												 SPAWNING AND KILLING
//********************************************************************************************************************************************************************************************************
//																																														DROP FUNCTIONS
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

//																																															DROP FUNCTIONS
//********************************************************************************************************************************************************************************************************
//																																							(NOTE: will add something better)		UIs
void fighting_UI(char fighting_UI_table[23][79]) {
	char text_fight[7] = { '1','.','F','i','g','h','t' };
	char text_magic[7] = { '2','.','M','a','g','i','c' };
	char text_items[7] = { '3','.','I','t','e','m','s' };
	char text_run[5] = { '4','.','R','u','n' };
	char text_player[6] = {'P','l','a','y','e','r'};
	char text_enemy[5] = {'E','n','e','m','y'};
	char text_health[7] = { 'H','e','a','l','t','h',':' };

	for (int y = 0; y < 23; y++) {
		for (int x = 0; x < 79; x++) {
			//Corners
			if (y == 0 && x == 0)
			{
				fighting_UI_table[y][x] = (char)218;
			}
			else if (y == 0 && x == 78)
			{
				fighting_UI_table[y][x] = (char)191;
			}
			else if (y == 22 && x == 0)
			{
				fighting_UI_table[y][x] = (char)192;
			}
			else if (y == 22 && x == 78)
			{
				fighting_UI_table[y][x] = (char)217;
			}
			//Middle line attachments
			else if (y == 16 && x == 0)
			{
				fighting_UI_table[y][x] = (char)195;
			}
			else if (y == 16 && x == 78)
			{
				fighting_UI_table[y][x] = (char)180;
			}
			//Border roof, floor and lines
			else if (y == 0 || y == 22 || y == 16)
			{
				fighting_UI_table[y][x] = (char)196;
			}
			//Border walls
			else if (x == 0 || x == 78)
			{
				fighting_UI_table[y][x] = (char)179;
			}
			//Empty spaces
			else
			{
				fighting_UI_table[y][x] = (char)000;
			}
		}
	}

	//Adding what you can do
	for (int i = 0; i < 7; i++)
	{
		fighting_UI_table[17][i+1] = text_fight[i];
	}
	for (int i = 0; i < 7; i++)
	{
		fighting_UI_table[18][i+1] = text_magic[i];
	}
	for (int i = 0; i < 7; i++)
	{
		fighting_UI_table[19][i+1] = text_items[i];
	}
	for (int i = 0; i < 5; i++)
	{
		fighting_UI_table[20][i+1] = text_run[i];
	}
	//Adding player text
	for (int i = 0; i < 6; i++)
	{
		fighting_UI_table[17][i + 25] = text_player[i];
	}
	//Adding enemy text
	for (int i = 0; i < 5; i++)
	{
		fighting_UI_table[17][i + 50] = text_enemy[i];
	}
	for (int i = 0; i < 7; i++)
	{
		fighting_UI_table[18][i + 25] = text_health[i];
		fighting_UI_table[18][i + 50] = text_health[i];
	}
}

//Displaying UI on console
void UI_displayer(char table[23][79]) {
	for (int y = 0; y < 23; y++) {
		for (int x = 0; x < 79; x++) {
			std::cout << table[y][x];
		}
		std::cout << std::endl;
	}
}

//																																																	UIs
//********************************************************************************************************************************************************************************************************
//																																															MAP FUNCTIONS
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

//Function that is drawing table with map
void map_drawer(int map_with_ids[23][79], std::stack<ENEMY> &stack_of_enemies, bool show_enemies_id) {
	/* What ID is what
	//Map
	-1 - unwalkable
	0 - walkable
	1 - palyer
	2 - enemy
	*/
	system("cls");

	for (int y = 0; y < 23; y++) {
		for (int x = 0; x < 79; x++) {
			if (map_with_ids[y][x] == (-1)) {
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
					std::cout << enemy_ID_finder(stack_of_enemies, x, y);
				}
			}
		}
		std::cout << std::endl;
	}
}

//																																															MAP FUNCTIONS
//********************************************************************************************************************************************************************************************************
//																																																FIGHTING
//Checks youre position for fight 
bool fight_checker(int map_with_ids[23][79], NPC player) {
	if (map_with_ids[player.positionY][player.positionX] == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Fighting loop
void fight(int map_with_ids[23][79], std::stack<ENEMY> &stack_of_enemies, NPC player, char fighting_UI_table[23][79], int *actual_pozition_ID) {

	//(BUT) BEFORE FIGHT (YOU NEED TO GATHER THE PARTY)

	std::stack <ENEMY> temporary_stack;
	std::string action;
	std::vector <char> player_health;
	std::vector <char> enemy_health;
	int enemy_ID = enemy_ID_finder(stack_of_enemies, player.positionX, player.positionY);
	bool didnt_run = true;

	//"Opens" stack in proper enemy
	while (stack_of_enemies.top().ID != enemy_ID)
	{
		temporary_stack.push(stack_of_enemies.top());
		stack_of_enemies.pop();
	}

	//Actiual fight part
	while (true) 
	{
		//Updating healths
		player_health = int_to_char(player.health);
		enemy_health = int_to_char(stack_of_enemies.top().health);
		for (int i = 0; i < player_health.size(); i++)
		{

			fighting_UI_table[18][i + 32] = player_health.at(i);
		}
		for (int i = 0; i < enemy_health.size(); i++)
		{
			fighting_UI_table[18][i + 57] = enemy_health.at(i);
		}

		//Draw fighting scene
		UI_displayer(fighting_UI_table);

		//Clearing space for next health update
		for (int i = 0; i < player_health.size(); i++)
		{
			fighting_UI_table[18][i + 32] = (char)000;
		}
		for (int i = 0; i < enemy_health.size(); i++)
		{
			fighting_UI_table[18][i + 57] = (char)000;
		}

		std::cout << "What you want to do?" << std::endl;
		std::cin >> action;

		//Fight logic
		if (action == "fight")
		{
			stack_of_enemies.top().health -= player.base_damage;
		}
		else if (action == "magic")
		{
			std::cout << "I'm lazy and I didn't done it" << std::endl; Sleep(2000);
		}
		else if (action == "items")
		{
			std::cout << "Nope you still don't have inventory (but it exgzists :) )" << std::endl; Sleep(2000);
		}
		else if (action == "run")
		{
			std::cout << "Really you want to run????" << std::endl; Sleep(1000);
			std::cout << "OK then" << std::endl; Sleep(1000);
			didnt_run = false;
		}
		else if (action == "help")
		{
			std::cout << "You got everything on screen why are you typing help?" << std::endl; Sleep(2000);
		}
		else
		{
			std::cout << "There is not such a thing as: " << action << ". Maby try: help." << std::endl;
		}

		//Ends loop when someone dies
		if (player.health <= 0 || stack_of_enemies.top().health <= 0 || didnt_run == false)
		{
			break;
		}
	}

	//AFTER FIGHT PART

	//Killing enemy after fight (if didn't run away)
	if (didnt_run) {
		kill(map_with_ids, stack_of_enemies, enemy_ID, actual_pozition_ID);
	}

	//"Closes" stack after killing
	while (temporary_stack.size() > 0)
	{
		stack_of_enemies.push(temporary_stack.top());
		temporary_stack.pop();
	}
	
	//Needed becouse whole stack of enemies gonna exploade
	reassigning_of_ID(stack_of_enemies);

}

//																																																FIGHTING
//********************************************************************************************************************************************************************************************************
//																																										TESTING FUNCTION (my favourite)
void testing(char fighting_UI_table[23][79]) {
	system("cls");



	system("pause");
}

//																																										TESTING FUNCTION (my favourite)
//********************************************************************************************************************************************************************************************************
//																																													MAIN LOOP OF GAME
void Game_loop() {
	system("cls");

	//PREPARING TO STAART
	//Variables
	int player_last_pozition_ID;
	int player_actual_pozition_ID = 0;
	int *actual_pozition_ID = &player_actual_pozition_ID;
	bool exit = true;
	bool show_enemies_id = false;
	std::string what_to_do;

	//Tables
	int map_with_ids[23][79];
	char fighting_UI_table[23][79];

	//Vectors

	//Stacks
	std::stack <ENEMY> stack_of_enemies;

	//Classes
	NPC player;
	player.health = 100;
	player.positionX = 2;
	player.positionY = 1;
	player.base_damage = 10;

	ENEMY enemy;
	enemy.health = 100;

	map_creator(map_with_ids);
	fighting_UI(fighting_UI_table);

	do{
		//Placing player on his position
		map_with_ids[player.positionY][player.positionX] = 1;
		//Drawing map
		map_drawer(map_with_ids, stack_of_enemies, show_enemies_id);
		//Actual pozition gives ID to last pozition
		player_last_pozition_ID = player_actual_pozition_ID;
		//Replacing old player location
		map_with_ids[player.positionY][player.positionX] = player_last_pozition_ID;

		//What player is going to do
		std::cout << "What do you want to do?" << std::endl;
		std::cin >> what_to_do;

		//Commands
		//For player

			//walking
			if (what_to_do == "up" && map_with_ids[player.positionY - 1][player.positionX] >= 0)
			{
				player.positionY--;
				player_actual_pozition_ID = map_with_ids[player.positionY][player.positionX];
				if (fight_checker(map_with_ids, player)) {
					fight(map_with_ids, stack_of_enemies, player, fighting_UI_table, actual_pozition_ID);
				}
			}
			else if (what_to_do == "down" && map_with_ids[player.positionY + 1][player.positionX] >= 0)
			{
				player.positionY++;
				player_actual_pozition_ID = map_with_ids[player.positionY][player.positionX];
				if (fight_checker(map_with_ids, player)) {
					fight(map_with_ids, stack_of_enemies, player, fighting_UI_table, actual_pozition_ID);
				}
			}
			else if (what_to_do == "left" && map_with_ids[player.positionY][player.positionX - 1] >= 0)
			{
				player.positionX--;
				player_actual_pozition_ID = map_with_ids[player.positionY][player.positionX];
				if (fight_checker(map_with_ids, player)) {
					fight(map_with_ids, stack_of_enemies, player, fighting_UI_table, actual_pozition_ID);
				}
			}
			else if (what_to_do == "right" && map_with_ids[player.positionY][player.positionX + 1] >= 0)
			{
				player.positionX++;
				player_actual_pozition_ID = map_with_ids[player.positionY][player.positionX];
				if (fight_checker(map_with_ids, player)) {
					fight(map_with_ids, stack_of_enemies, player, fighting_UI_table, actual_pozition_ID);
				}
			}

			//Help comand
			else if(what_to_do == "help")
			{
				system("cls");
				std::cout << "Walking directions: up, down, left, right" << std::endl;
				std::cout << "exit - exits the game" << std::endl << std::endl << std::endl;
				std::cout << "Debbuging comands (cheats XD)" << std::endl;
				std::cout << "WARNING: If you use them not properly even I will not be able to help you!!!" << std::endl;
				std::cout << "spawn - spawns enemy on given location" << std::endl;
				std::cout << "showID - showis IDs of enemies on the map" << std::endl;
				std::cout << "kill - kills an enemy based on his ID (to get the ID try showID)" << std::endl;
				std::cout << "killall - kills aaaaaaall of the enemies" << std::endl;
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
				spawn_command(map_with_ids, stack_of_enemies, enemy);
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
				kill_command(map_with_ids, stack_of_enemies, actual_pozition_ID);
				reassigning_of_ID(stack_of_enemies);
			}

			else if (what_to_do == "killall") {
				kill_all(map_with_ids, stack_of_enemies, actual_pozition_ID);
			}

			else if (what_to_do == "testing") {
				testing(fighting_UI_table);
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