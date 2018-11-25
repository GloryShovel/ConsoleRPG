#include "pch.h"
#include <iostream>
#include <Windows.h>

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
	default: std::cout << "Beeep.... beep.... boop...." << std::endl; Sleep(300); std::cout << "Shuting down" << std::endl;
		break;
	}
}