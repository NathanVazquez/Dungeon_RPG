/*
 * CSCI235 Fall 2023
 * Project 5 - Testing
 * Tor Sdayur
 * November 2023
 * main.cpp tests all relevant methods of QuestList class, along with its constructors.
 */

#include "QuestList.hpp"

//Tests the Parameterized constructor
void testQuestListConstructor()
{
	QuestList my_quest = QuestList("debug.csv");
	Node<Quest*>* node_curr_ptr = my_quest.getHeadNode();
	while (node_curr_ptr != nullptr)
	{
		std::cout << "Quest Title: " << node_curr_ptr->getItem()->title_ << std::endl; 
		std::cout << "Quest Description: " << node_curr_ptr->getItem()->description_ << std::endl; 
		std::cout << "Quest Completed: " << node_curr_ptr->getItem()->completed_ << std::endl; 
		std::cout << "Quest Experience: " << node_curr_ptr->getItem()->experience_points_ << std::endl; 
		if (node_curr_ptr->getItem()->dependencies_.size() != 0)
		{
			std::cout << "Quest Dependencies: " << std::endl << std::endl;
			for (auto& dependency : node_curr_ptr->getItem()->dependencies_)
			{
				std::cout << "Quest Title: " << dependency->title_ << std::endl; 
				std::cout << "Quest Description: " << dependency->description_ << std::endl; 
				std::cout << "Quest Completed: " << dependency->completed_ << std::endl; 
				std::cout << "Quest Experience: " << dependency->experience_points_ << std::endl; 
			}
		}
		if (node_curr_ptr->getItem()->subquests_.size() != 0)
		{
			std::cout << "Quest Subquests: " << std::endl << std::endl;
			for (auto& subquest : node_curr_ptr->getItem()->subquests_)
			{
				std::cout << "Quest Title: " << subquest->title_ << std::endl; 
				std::cout << "Quest Description: " << subquest->description_ << std::endl; 
				std::cout << "Quest Completed: " << subquest->completed_ << std::endl; 
				std::cout << "Quest Experience: " << subquest->experience_points_ << std::endl; 
			}
		}
		node_curr_ptr = node_curr_ptr->getNext();
		std::cout << std::endl << std::endl << std::endl << std::endl;
	}	
}

//Tests trivial method getPosOf and contains.
void testSimpleMethods()
{
	QuestList my_quest = QuestList("debug.csv");
	std::cout << my_quest.getPosOf("Quest 6") << std::endl;
	std::cout << my_quest.getPosOf("Quest 10") << std::endl;
	std::cout << my_quest.contains("Quest 6") << std::endl;
	std::cout << my_quest.contains("Quest 10") << std::endl;
}

//tests questHistory
void testQuestHistory()
{
	QuestList my_quest = QuestList("debug.csv");
	//my_quest.questHistory("COMPLETE");
	//my_quest.questHistory("INCOMPLETE");
	my_quest.questHistory("AVAILABLE");
}

//tests questDetails
void testPrintQuestDetails()
{
	QuestList my_quest = QuestList("debug.csv");
	Node<Quest*>* node_curr_ptr = my_quest.getHeadNode();

	std::cout << "Testing printQuestDetails:" << std::endl << std::endl;
	while (node_curr_ptr != nullptr)
	{
		my_quest.printQuestDetails(node_curr_ptr->getItem());
		node_curr_ptr = node_curr_ptr->getNext();
		std::cout << std::endl;
	}
}

//tests questQuery
void testQuestQuery()
{
	QuestList my_quest = QuestList("debug.csv");
	Node<Quest*>* node_curr_ptr = my_quest.getHeadNode();

	std::cout << "Testing questQuery:" << std::endl << std::endl;
	while (node_curr_ptr != nullptr)
	{
		my_quest.questQuery(node_curr_ptr->getItem()->title_);
		std::cout << std::endl;
		node_curr_ptr = node_curr_ptr->getNext();
	}

	my_quest.questQuery("Quest 12");
	std::cout << std::endl;

}

//tests calculatePathwayExperience
void testCalculatePathwayExperience()
{
	QuestList my_quest = QuestList("debug.csv");
	Node<Quest*>* node_curr_ptr = my_quest.getHeadNode();
	while (node_curr_ptr != nullptr)
	{
		std::cout << my_quest.calculatePathwayExperience(node_curr_ptr->getItem()) << std::endl;
		node_curr_ptr = node_curr_ptr->getNext();
	}
}
	
//tests calculateProjectedExperience
void testCalculateProjectedExperience()
{
	QuestList my_quest = QuestList("debug.csv");
	Node<Quest*>* node_curr_ptr = my_quest.getHeadNode();
	while (node_curr_ptr != nullptr)
	{
		std::cout << my_quest.calculateProjectedExperience(node_curr_ptr->getItem()) << std::endl;
		node_curr_ptr = node_curr_ptr->getNext();
	}
}

int main()
{
	//testQuestListConstructor();
	//testSimpleMethods();
	//testQuestHistory();
	//testPrintQuestDetails();
	//testQuestQuery();
	//testCalculatePathwayExperience();
	//testCalculateProjectedExperience();
}
