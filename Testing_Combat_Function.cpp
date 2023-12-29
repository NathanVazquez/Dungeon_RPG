/*
 * CSCI235 Fall 2023
 * Project 6 - Testing
 * Tor Sdayur
 * November 2023
 * main.cpp tests all relevant methods of Tavern class to Project 6.
 */

#include "Tavern.hpp"

//tests createCombatQueue and printCombatQueue
void testCreateAndPrintCombatQueue()
{
	Tavern my_tavern = Tavern("enemies.csv");

	my_tavern.createCombatQueue();
	//my_tavern.createCombatQueue("LVLASC");
	//my_tavern.createCombatQueue("LVLDES");
	//my_tavern.createCombatQueue("HPASC");
	//my_tavern.createCombatQueue("HPDES");


	my_tavern.printCombatQueue();
}

//test actionSelection
void testActionSelection()
{
	Tavern my_tavern = Tavern("enemies.csv");
	my_tavern.createCombatQueue();
	my_tavern.setMainCharacter(my_tavern.getTarget());
	my_tavern.actionSelection();

	std::cout << std::endl;
	while (!my_tavern.getMainCharacter()->getActionQueue().empty())
	{
		std::cout << "Action: " << my_tavern.getMainCharacter()->getActionQueue().front() << std::endl;
		my_tavern.getMainCharacter()->getActionQueue().pop();
	}
}

//tests turnResolution
void testTurnResolution()
{
	Character* joe = new Character("JOE", "HUMAN", 10, 10, 10, false);

	Tavern my_tavern = Tavern("enemies.csv");
	my_tavern.createCombatQueue();
	my_tavern.setMainCharacter(joe);
	for (int i = 0; i < 10; i++)
	{
		my_tavern.actionSelection();
		my_tavern.turnResolution();
	}
}

//tests enemyTurn
void testEnemyTurn()
{
	Character* joe = new Character("JOE", "HUMAN", 10, 0, 10, false);

	Tavern my_tavern = Tavern("enemies.csv");
	my_tavern.createCombatQueue();
	my_tavern.setMainCharacter(joe);
	for (int i = 0; i < 10; i++)
	{
		my_tavern.enemyTurn(my_tavern.getTarget());
	}
}

//tests combat()
void testCombat()
{
	Character* joe = new Character("JOE", "HUMAN", 1, 0, 1, false);

	Tavern my_tavern = Tavern("enemies.csv");
	my_tavern.createCombatQueue();
	my_tavern.setMainCharacter(joe);

	my_tavern.combat();
}

int main()
{
	//testCreateAndPrintCombatQueue();
	//testActionSelection();
	//testTurnResolution();
	//testEnemyTurn();
	//testCombat();
}
