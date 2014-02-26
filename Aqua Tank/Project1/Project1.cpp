// Project1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
#include <ctime>
#include <vector>
#include <iostream>
#include <string>
#include <Windows.h>
#include "Entities.h"

using namespace std;

//generates random number
int myrandom(int rnd = 3)
{
	int x = rand() % rnd;
	return x;
}


class Overlord{
public:
	int fishFood;
	int savings;

	//default constructor, starts fishFoodUsed
	Overlord(){
		fishFood = 50;
		savings = 0;
	}
//
////Main Update
//
	void Update(vector<GameEntity_i*> _fishTank, GameEntity_d *_filter){

		Sleep(1000);
		bool fishOK = true;
		int fishTick = 0;
		
//if a fish is hungry then it has to be fed
		for each (GameEntity_i* var in _fishTank){
//checks how many fish are hungry
			if (var->health < var->health_MIN){
				fishOK = false;
				fishTick++;
			}
		}
//if fish are hungry and there isn't enough food
		if (fishOK == false && fishTick > fishFood){
			cout << "Gotta get food" << endl;
			savings -= 70;
			cout << "Fish food is expensive, I'm down to " << savings << " now." << endl << endl;
			fishFood += 50;
//the fish that are hungry now are fed
			for each (GameEntity_i* var in _fishTank){
				if (var->health < var->health_MIN){
					var->health = var->health_MAX;
					fishFood--;
				}
			}
			cout << "Fishies are fed now. There's " << fishFood << "pieces of food left" << endl << endl;
		}
//if fish are hungry and there is enough food
		else if (fishOK == false && fishTick < fishFood){
			for each (GameEntity_i* var in _fishTank){
				if (var->health < var->health_MIN){
					var->health = var->health_MAX;
					fishFood--;
				}
			}
			cout << "Fishies are fed now. There's " << fishFood << "pieces of food left" << endl << endl;
		}
//if filter is dirty then it is replaced
		else if (_filter->health < _filter->health_MIN){
			savings -= 100;
			cout << "Filter broke, now I'm down to" << savings << endl << endl;
			_filter->health = _filter->health_MAX;
		}
// if he doesn't have to feed the fish or get them a new filter he works
		else{
			cout << "Gonna trade stocks" << endl;
			savings += 1;
			cout << "Sweet, I have " << savings << " in savings now" << endl << endl;
		}
		
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	//randomizer
	srand(time(0));

	vector<GameEntity_i*> fishpointerTank;
	GameEntity_d filter(100, 100, 0, 0);
	Overlord overlord;

	for (int x = 0; x < 5; x++){
		GameEntity_i* fishie = new GameEntity_i(20, 20, 0, myrandom());
		fishpointerTank.push_back(fishie);
	}

	while (true){
		//slows down loop
		Sleep(1000);

		int workAround = 0;
		for each (GameEntity_i* var in fishpointerTank)
		{
			cout << "Fish hunger: " << var->health << endl;
			fishpointerTank[workAround]->Update();
			workAround++;
		}
		cout << "Filter health: " << filter.health << endl << endl;
		filter.Update();
		overlord.Update(fishpointerTank, &filter);


		
		if (overlord.fishFood < 0){
			char c;
			cout << "Type x and Enter to quit";
			cin >> c;
			if (c == 'x'){
				break;
			}
			else{
				overlord.fishFood = 0;
			}
		}
	}

	return 0;
}

