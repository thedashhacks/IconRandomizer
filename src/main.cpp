/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>
/**
 * Required to modify the MenuLayer class
 */
#include <Geode/modify/MenuLayer.hpp>

/**
 * Brings cocos2d and all Geode namespaces 
 * to the current scope.
 */
using namespace geode::prelude;

/**
 * `$modify` lets you extend and modify GD's 
 * classes; to hook a function in Geode, 
 * simply $modify the class and write a new 
 * function definition with the signature of 
 * the one you want to hook.
 */
class $modify(MenuLayer) {
	/**
	 * MenuLayer::onMoreGames is a GD function, 
	 * so we hook it by simply writing its name 
	 * inside a $modified MenuLayer class.
	 * 
	 * Note that for all hooks, your signature 
	 * has to match exactly - `bool onMoreGames` 
	 * would not place a hook!
	 */
	void onMoreGames(CCObject*) {
		FLAlertLayer::create("Geode", "Hello from my custom mod!", "OK")->show(); 
	} 
	#include "HackAPI.h"
#include <iostream>

DWORD MAX_VAL[11] = { 108, 35, 29, 28, 23, 17, 10, 41, 41, 7, 13 };	//Max values for every icon set

BOOL WriteIcon(HackIH &hProc, PointerIH hPointer, DWORD Value);
int main(){

	srand(GetTickCount());	//Randomize this a little more
	SetConsoleTitleA("Dashhacks Icon Set Randomizer - 2.1");
	HackIH GD(0, "GeometryDash.exe", "Geometry Dash");	//Initialize game handler

	std::cout << "Waiting for process..." << std::endl;

	while (!GD.GetPid()){
		Sleep(250);
	}

	system("cls");

	PointerIH BasePointer = GD.GetModuleAddress(0);		//Gets GeometryDash.exe address in memory
	BasePointer += 0x303118;
	BasePointer << 0x1E8;	//First offset, got with Cheat Engine
	GD.SolvePointer(BasePointer);	//Now BasePointer is resolved, you can sum and substract this to obtain the final address

	std::cout << "Program running. View DashHacks on GitHub" << std::endl;
	ShellExecuteA(0, "open", "https://github.com/thedashhacks", 0, 0, 5);

	while (1){
		for (int i = 0; i < 10; i++){
			if (!WriteIcon(GD, BasePointer + (i * 0x0C), rand() % MAX_VAL[i] + 1))	//Uses the layout of the GD Icon sets in order to improve efficiency (Every offset is +0xC apart)
				break;
		}
		if (GD.GetLastError()) break;
		Sleep(500);	//A little delay for not stressing out the computer
	}

	system("cls");
	std::cout << "Program terminated. Error: " << GD.GetLastError() << std::endl;	//Actually get what went wrong, the number is an msdn error code

	system("PAUSE>NUL");
}

BOOL WriteIcon(HackIH &hProc, PointerIH hPointer, DWORD Value){		//Uses HAPIH in order to read and write the values needed.

	hProc.WriteDW(hPointer, Value);
	hProc.WriteDW(hPointer - 8, hProc.ReadDW(hPointer-4) + Value );	//Bypass the anticheat protection (Very simple, but needed)

	if (hProc.GetLastError()){
		return 0;
	}
	return 1;
}
};
