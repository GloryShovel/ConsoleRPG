#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <string>

struct NPC
{
	std::string name;
	int height, width, weight, race, age, positionX, posiotionY;

};

void Game_loop() {
	system("cls");
	struct NPC player;
	
	//something to think about
	//bool map[][];

}

//Here should be main loop of the game, but insted I created butload of code typing words.
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

int main()
{
	int choise;
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n                            Welcome in ConsoleRPG"; 
	std::cin.get(); system("cls");
	std::cout << "1.New Game \n2.Load Game \n3.Options \n4.Exit";
	std::cin >> choise;

	switch (choise)
	{
	case 1: 
		break;
	case 2: std::cout << "Still working on it" <<std::endl;
		break;
	case 3: std::cout << "Still working on it" << std::endl;
		break;
	case 4: std::cout << "Bye." << std::endl;
		break;
	default: std::cout << "Beeep.... "; Sleep(900); std::cout << "beep...."; Sleep(900); std::cout <<" boop...." << std::endl; Sleep(2000); std::cout << "Shuting down" << std::endl;
		break;
	}
}