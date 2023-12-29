/*
 * CSCI235 Fall 2023
 * Project 5 - QuestList Class
 * Tor Sdayur
 * November 2023
 * QuestList.hpp implements QuestList class along with its members.
 */

#include "QuestList.hpp"

/** Default Constructor */
QuestList::QuestList() : DoublyLinkedList<Quest*>()
{
}

/** Parameterized Constructor
 * @param: a reference to string name of an input file
 * @pre: Formatting of the csv file is as follows:
 * 		Title: A string
 * 		Description: A string
 * 		Completion Status: 0 (False) or 1 (True)
 * 		Experience Points: a non-negative integer
 * 		Dependencies: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is seperated by a semicolon. The value may be NONE.
 * 		Subquests: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is seperated by a semicolon. The value may be NONE.
 * Notes:
 * 		- The first line of the input file is a header, and should be ignored.
 * 		- The dependencies and subquests are separated by a semicolon and may be NONE.
 * 		- The dependencies and subquests may be in any order.
 * 		- If any of the dependencies or subquests are not in the list, they should be created as new quests with the following information:
 * 			- Title: The title of the quest
 * 			- Description: "NOT DISCOVERED"
 * 			- Completion Status: False
 * 			- Experience Points: 0
 * 			- Subquests: An empty vector
 * 		- However, if you eventually encounter a quest that matches one of the "NOT DISCOVERED" quests while parsing the file, you should update all the quest details.
 *
 *
 * @post: Each line of the input file corresponds to a quest to be added to the list. No duplicates are allowed.
 */
QuestList::QuestList(const std::string& in_file) : DoublyLinkedList<Quest*>() {
	std::ifstream file_stream;
	file_stream.open(in_file);

	//parameters to initialize character derived objects
	std::string title;
	std::string description;
	std::string str_completed;
	std::string str_experience_points;
	std::string str_dependencies;
	std::string str_subquests;

	//converted bool/int parameters for the data read in its respective string parameters.
	bool completed;
	int experience_points;

	
	if(file_stream.is_open())
	{
		//to skip first line in CSV file.
		std::string line;
		std::getline(file_stream, line);

		while(std::getline(file_stream, line))
		{
			std::vector<Quest*> dependencies; 
			std::vector<Quest*> subquests; 


			std::istringstream line_stream(line);

			std::getline(line_stream, title, ',');
			std::getline(line_stream, description, ',');
			std::getline(line_stream, str_completed, ',');
			std::getline(line_stream, str_experience_points, ',');
			std::getline(line_stream, str_dependencies, ',');
			std::getline(line_stream, str_subquests, '\r');

			completed = std::stoi(str_completed);
			experience_points = std::stoi(str_experience_points);

			//Adding quest dependencies
			if (str_dependencies != "NONE")
			{
				std::vector<Quest*> no_quests;

				int start_pos = 0;
				int end_pos = str_dependencies.find(';', start_pos);

				//There is only one dependency
				if (end_pos == -1)
				{
					Quest* dependency_ptr = new Quest(str_dependencies, "NOT DISCOVERED", false, 0, no_quests, no_quests);
					dependencies.push_back(dependency_ptr);
				}
				//There is more than one dependency
				else
				{
					std::string dependency;
					while (str_dependencies.find(';', start_pos) != -1)
					{
						end_pos = str_dependencies.find(';', start_pos);
						std::istringstream dependency_stream(str_dependencies.substr(start_pos, end_pos - start_pos));
						std::getline(dependency_stream, dependency, ';');

						Quest* dependency_ptr = new Quest(dependency, "NOT DISCOVERED", false, 0, no_quests, no_quests);
						dependencies.push_back(dependency_ptr);

						start_pos = end_pos + 1;
					}

					//Adding the last dependency.
					std::istringstream dependency_stream(str_dependencies.substr(start_pos));
					std::getline(dependency_stream, dependency);

					Quest* dependency_ptr = new Quest(dependency, "NOT DISCOVERED", false, 0, no_quests, no_quests);
					dependencies.push_back(dependency_ptr);
				}
			}
			//Adding quest subquests
			if (str_subquests != "NONE")
			{
				std::vector<Quest*> no_quests;

				int start_pos = 0;
				int end_pos = str_subquests.find(';', start_pos);

				//There is only one subquest
				if (end_pos == -1)
				{
					Quest* subquest_ptr = new Quest(str_subquests, "NOT DISCOVERED", false, 0, no_quests, no_quests);
					subquests.push_back(subquest_ptr);
				}
				//There is more than one subquest
				else
				{
					std::string subquest;
					while (str_subquests.find(';', start_pos) != -1)
					{
						end_pos = str_subquests.find(';', start_pos);
						std::istringstream subquest_stream(str_subquests.substr(start_pos, end_pos - start_pos));
						std::getline(subquest_stream, subquest, ';');

						Quest* subquest_ptr = new Quest(subquest, "NOT DISCOVERED", false, 0, no_quests, no_quests);
						subquests.push_back(subquest_ptr);

						start_pos = end_pos + 1;
					}

					//Adding the last subquest.
					std::istringstream subquest_stream(str_subquests.substr(start_pos));
					std::getline(subquest_stream, subquest);

					Quest* subquest_ptr = new Quest(subquest, "NOT DISCOVERED", false, 0, no_quests, no_quests);
					subquests.push_back(subquest_ptr);
				}
			}
			addQuest(title, description, completed, experience_points, dependencies, subquests);
		}
	}
}

/**
 * @param: A string reference to a quest title
 * @return: The integer position of the given quest if it is in the QuestList, -1 if not found.
 */
int QuestList::getPosOf(const std::string& title) const {
	
	bool is_found = false;
	int pos = 0;
	int found_pos = -1;

	Node<Quest*>* curr_quest_ptr = first_;

	while (!is_found && pos < item_count_)
	{
		if ( curr_quest_ptr->getItem()->title_ == title )
		{
			is_found = true;
			found_pos = pos;
		}
		pos++;
		curr_quest_ptr = curr_quest_ptr->getNext();
	}
	return found_pos;
}

/**
 * @param: A string reference to a quest title
 * @return: True if the quest with the given title is already in the QuestList
 */
bool QuestList::contains(const std::string& title) const {
	return (getPosOf(title) != -1);
}

/**
 * @pre: The given quest is not already in the QuestList
 * @param: A pointer to a Quest object
 * @post: Inserts the given quest pointer into the QuestList. Each of its dependencies and subquests are also added to the QuestList IF not already in the list.
 *      If the quest is already in the list but is marked as "NOT DISCOVERED", update its details. (This happens when a quest has been added to the list through a dependency or subquest list)
 * @return: True if the quest was added successfully, False otherwise
 */
bool QuestList::addQuest(Quest* quest_ptr) {
	int pos = getPosOf(quest_ptr->title_);

	//already in the list
	if (pos > -1)
	{
		Node<Quest*>* node_quest_ptr = getPointerTo(pos);
		//the quest of the same title of quest_ptr is in the list, but its details are empty.
		if (node_quest_ptr->getItem()->description_ == "NOT DISCOVERED")
		{
			node_quest_ptr->getItem()->description_ = quest_ptr->description_;
			node_quest_ptr->getItem()->experience_points_ = quest_ptr->experience_points_;
			node_quest_ptr->getItem()->completed_ = quest_ptr->completed_;
			node_quest_ptr->getItem()->subquests_ = quest_ptr->subquests_;
			node_quest_ptr->getItem()->dependencies_ = quest_ptr->dependencies_;
		}
		//update dependencies and subquests of each relevant item in the list.
		updateDependenciesAndSubquests(quest_ptr);
		return true;
	}
	//not in the list
	else if (pos == -1)
	{
		for (auto& dependency : quest_ptr->dependencies_)
		{
			if (getPosOf(dependency->title_) == -1)
			{
				addQuest(dependency);
			}
		}
		for (auto& subquest : quest_ptr->subquests_)
		{
			if (getPosOf(subquest->title_) == -1)
			{
				addQuest(subquest);
			}
		}
		//update dependencies and subquests of each relevant item in the list.
		updateDependenciesAndSubquests(quest_ptr);
		insert(item_count_, quest_ptr);
		return true;
	}
	return false;
}

/**
 * @param: A reference to string representing the quest title
 * @param: A reference to string representing the quest description
 * @param: A reference to boolean representing if the quest is completed
 * @param: A reference to int representing experience_pointserience points the quest rewards upon completion
 * @param: A reference to vector of Quest pointers representing the quest's dependencies
 * @param: A reference to vector of Quest pointers representing the quest's subquests
 * @post: Creates a new Quest object and inserts a pointer to it into the QuestList.
 *      If the quest is already in the list but is marked as "NOT DISCOVERED", update its details. (This happens when a quest has been added to the list through a dependency or subquest list)
 * 	    Each of its dependencies and subquests are also added to the QuestList IF not already in the list.
 * @return: True if the quest was added successfully
 */
bool QuestList::addQuest(const std::string& title, const std::string& description, const bool& completed, const int& experience_points, const std::vector<Quest*>& dependencies, const std::vector<Quest*>& subquests) {
	Quest* new_quest_ptr = new Quest(title, description, completed, experience_points, dependencies, subquests);
	bool success = addQuest(new_quest_ptr);
	return success;
}

/**
 * @param: A Quest pointer
 * @return: A boolean indicating if all the given quest's dependencies are completed
 */
bool QuestList::dependenciesComplete(Quest* quest_ptr) const {
	for (int i = 0; i < quest_ptr->dependencies_.size(); i++)
	{
		if (!quest_ptr->dependencies_[i]->completed_)
		{
			return false;
		}
	}
	return true;
}

/**
 * @param: A Quest pointer
 * @return: A boolean if the given quest is available.
 * Note: For a quest to be available, it must not be completed, and its dependencies must be complete.
 */
bool QuestList::questAvailable(Quest* quest_ptr) const {

	if (!quest_ptr->completed_ && dependenciesComplete(quest_ptr))
	{
		return true;
	}
	return false;
}

/**
 * @param: A Quest pointer
 * @post: Prints the quest title and completion status
 * The output should be of the form:
 * [Quest Title]: [Complete / Not Complete]
 * [Quest Description]\n\n
 */
void QuestList::printQuest(Quest* quest_ptr) const {
	std::cout << quest_ptr->title_ << ": ";
	if (quest_ptr->completed_)
	{
		std::cout << "Complete";
	}
	else
	{
		std::cout << "Not Complete";
	}
	std::cout << std::endl;
	std::cout << quest_ptr->description_ << std::endl << std::endl;
}

/**
 * @param: A string reference to a quest title
 * @post: Prints a list of quests that must to be completed before the given quest can be started (incomplete dependencies).
 *        If any of the quest's incomplete dependencies have an incomplete dependency, recursively print the quests that need to be done in order, indenting incomplete quests.
 * 		  The indentation for incomplete quests is 2 spaces: "  "
 * 		  The format of the list should be of the following forms for each different case:
 *
 *
  		  Query: [Quest Title]
 * 		  No such quest.
 *
 * 		  Query: [Quest Title]
 * 		  Quest Complete
 *
 * 		  Query: [Quest Title]
 * 		  Ready: [Quest Title]
 *
 * 		  Query: [Quest Title]
 * 		  Ready: [Dependency0]
 * 			[Quest Title]
 *
 * 		  Query: [Quest Title]
 * 		  Ready: [Dependency0]
 * 		  Ready: [Dependency1]
 * 			[Quest Title]
 *
 * 		  Query: [Quest Title]
 * 		  Ready: [Dependency0]
 * 		  Ready: [Dependency1]
 * 			[Dependency2]
 * 			[Quest Title]
 *
 * If the given quest title is not found in the list, print "No such quest."
 */
void QuestList::questQuery(const std::string& title) const {
	int pos = getPosOf(title);
	std::cout << "Query: " << title << std::endl;

	if (pos == -1)
	{
		std::cout << "No such quest." << std::endl;
	}
	else
	{
		Node<Quest*>* quest_ptr = getPointerTo(pos);

		if (quest_ptr->getItem()->completed_)
		{
			std::cout << "Quest Complete" << std::endl;
		}
		else if (!quest_ptr->getItem()->completed_ && dependenciesComplete(quest_ptr->getItem()))
		{
			std::cout << "Ready: " << quest_ptr->getItem()->title_ << std::endl;
		}
		else
		{
			for (auto& dependency : quest_ptr->getItem()->dependencies_)
			{
				if (!dependency->completed_ && dependenciesComplete(dependency))
				{
					std::cout << "Ready: " << dependency->title_ << std::endl;
				}
				else if (!dependency->completed_ && !dependenciesComplete(dependency))
				{
					dependencyQuery(dependency);
					std::cout << "  " << dependency->title_ << std::endl;
				}
			}
			std::cout << "  " << quest_ptr->getItem()->title_ << std::endl;
		}
	}
}

/**
 * @return: An integer sum of all the experience gained
 * Note: This should only include exerience from completed quests
 */
int QuestList::calculateGainedExperience() const {
	int total_experience_points = 0;
	Node<Quest*>* curr_quest_ptr = first_;

	while (curr_quest_ptr != nullptr)
	{
		if (curr_quest_ptr->getItem()->completed_)
		{
			total_experience_points += curr_quest_ptr->getItem()->experience_points_;
		}
		curr_quest_ptr = curr_quest_ptr->getNext();
	}
	return total_experience_points;
}

/**
 * @param: A quest pointer to a main quest
 * @return: An integer sum of all the experience that can be gained from completing the main quest AND all its subquests.
 * Note: Also consider the potential experience if a subquest itself has subquests.
 */
int QuestList::calculateProjectedExperience(Quest* quest_ptr) const {
	std::vector<Quest*> subquests_factored;
	return calculateIfCompletedSubquests(quest_ptr, subquests_factored);
}

/**
 * @param: A quest pointer to a main quest
 * @return: An integer sum of all the experience that has already been gained by completing the given quest's subquests.
 * Note: Also consider the experience gained if a completed subquest itself has subquests.
 */
int QuestList::calculatePathwayExperience(Quest* quest_ptr) const {
	std::vector<Quest*> subquests_factored;
	return calculateCompletedSubquests(quest_ptr, subquests_factored);
}

/**
 * @param: A string reference to a filter with a default value of "NONE".
 * @post: With default filter "NONE": Print out every quest in the list.
 * 		With filter "COMPLETE":		Only print out the completed quests in the list.
 * 		With filter "INCOMPLETE": 	Only print out the incomplete quests in the list.
 * 		With filter "AVAILABLE": 	Only print out the available quests in the list.
 * 		If an invalid filter is passed, print "Invalid Filter\n"
 * Printing quests should be of the form:
 * [Quest title]: [Complete / Not Complete]
 * [Quest description]\n
 */
void QuestList::questHistory(const std::string& filter) const {
	if (filter != "COMPLETE" && filter != "INCOMPLETE" && filter != "AVAILABLE" && filter != "NONE")
	{
		std::cout << "Invalid Filter" << std::endl;
	}
	else {
		Node<Quest*>* curr_quest_ptr = first_;

		if (filter == "COMPLETE")
		{
			while (curr_quest_ptr != nullptr)
			{
				if (curr_quest_ptr->getItem()->completed_)
				{
					printQuest(curr_quest_ptr->getItem());
				}
				curr_quest_ptr = curr_quest_ptr->getNext();
			}
		}
		else if (filter == "INCOMPLETE")
		{
			while (curr_quest_ptr != nullptr)
			{
				if (!curr_quest_ptr->getItem()->completed_)
				{
					printQuest(curr_quest_ptr->getItem());
				}
				curr_quest_ptr = curr_quest_ptr->getNext();
			}
		}
		else if (filter == "AVAILABLE")
		{
			while (curr_quest_ptr != nullptr)
			{
				if (questAvailable(curr_quest_ptr->getItem()))
				{
					printQuest(curr_quest_ptr->getItem());
				}
				curr_quest_ptr = curr_quest_ptr->getNext();
			}
		}
		else
		{
			while (curr_quest_ptr != nullptr)
			{
				printQuest(curr_quest_ptr->getItem());
				curr_quest_ptr = curr_quest_ptr->getNext();
			}
		}
	}
}

/**
 * @param: A quest pointer to a main quest
 * @post:  Outputs subquest pathway. Print quest names with two spaces ("  ") of indentation for each subquest, recursively.
 * 		  Also print the percentage of experience_points gained in this pathway, rounded down to the lower integer.
 * The format should be of the form:
 * [Main Quest] ([Pathway XP] / [Projected XP]% Complete)
 * 		[Subquest0]: [Complete / Not Complete]
 * 			[Sub-Subquest01]: [Complete / Not Complete]
 * 				[Sub-Subquest011]: [Complete / Not Complete]
 * 			[Subquest02]: [Complete / Not Complete]
 */
void QuestList::printQuestDetails(Quest* quest_ptr) const {
	int percentage = static_cast<int>(100 * (calculatePathwayExperience(quest_ptr) * 1.0 / calculateProjectedExperience(quest_ptr)));
	if (quest_ptr->completed_)
	{
		percentage = 100;
	}
	std::cout << quest_ptr->title_ << " (" << percentage << "% Complete)" << std::endl;

	for (auto& subquest : quest_ptr->subquests_)
	{
		printSubquestsCompleted(subquest, 0);
	}
}

/**
 * Helper function for questQuery; this function handles incomplete dependencies.
 * @param: A quest pointer to a dependency.
 * @post: Outputs completed dependencies, and recursively goes through incomplete dependencies, until all incomplete dependencies have been printed.
 */
void QuestList::dependencyQuery(Quest* dependency_ptr) const {
	if (dependency_ptr->dependencies_.size() != 0)
	{
		for (auto& dep : dependency_ptr->dependencies_)
		{
			if (!dependenciesComplete(dep))
			{
				dependencyQuery(dep);
				std::cout << "  " << dep->title_ << std::endl;
			}
			else
			{
				std::cout << "Ready: " << dep->title_ << std::endl;
			}
		}
	}
}

/**
 * Helper function for questHistory; this function handles printing of in/complete subquests, until all subquests have been printed.
 * @param: A quest pointer to a subquest
 * @param: an integer representing the number of "  " should be used.
 * @post: Recursively outputs subquests, detailing if they have been completed or not.
 */
void QuestList::printSubquestsCompleted(Quest* subquest_ptr, int tabs) const {
	//accounting for indentation.
	for (int i = 0; i < tabs + 1; i++)
	{
		std::cout << "  ";
	}

	std::cout << subquest_ptr->title_;

	if (subquest_ptr->completed_)
	{
		std::cout << ": Complete" << std::endl;
	}
	else
	{
		std::cout << ": Not Complete" << std::endl;
	}

	tabs++;

	//handle subquests of subquest_ptr
	if (subquest_ptr->subquests_.size() != 0)
	{
		for (auto& sub : subquest_ptr->subquests_)
		{
			printSubquestsCompleted(sub, tabs);
		}
	}
}

/**
 * Helper funciton for addQuest
 * @param: The quest pointer used to update all depenencies and subquests of the same title.
 * @pre: A list of quests with certain dependencies and subquests which are not yet discovered.
 * @post: Updates the dependencies and subquests of each quest present in the list for each dependency or subquest of an item whose description is currently labeled as not discovered, yet has a quest with its complete information in the list.
 */
void QuestList::updateDependenciesAndSubquests(Quest* quest_ptr) {
	Node<Quest*>* node_curr_ptr = getHeadNode();
	while (node_curr_ptr != nullptr)
	{
		if (node_curr_ptr->getItem()->dependencies_.size() != 0)
		{
			for (auto& dependency : node_curr_ptr->getItem()->dependencies_)
			{
				if (dependency->description_ == "NOT DISCOVERED")
				{
					int pos = getPosOf(dependency->title_);
					//i.e. the quest to update the dependency is in the list.
					if (pos != -1)
					{
						Node<Quest*>* node_with_quest_ptr = getPointerTo(pos);
						dependency->description_ = node_with_quest_ptr->getItem()->description_;
						dependency->experience_points_ = node_with_quest_ptr->getItem()->experience_points_;
						dependency->completed_ = node_with_quest_ptr->getItem()->completed_;
						dependency->subquests_ = node_with_quest_ptr->getItem()->subquests_;
						dependency->dependencies_ = node_with_quest_ptr->getItem()->dependencies_;
					}
				}
			}
		}
		if (node_curr_ptr->getItem()->subquests_.size() != 0)
		{
			for (auto& subquest : node_curr_ptr->getItem()->subquests_)
			{
				if (subquest->description_ == "NOT DISCOVERED")
				{
					int pos = getPosOf(subquest->title_);
					//i.e. the quest to update the subquest is in the list.
					if (pos != -1)
					{
						Node<Quest*>* node_with_quest_ptr = getPointerTo(pos);
						subquest->description_ = node_with_quest_ptr->getItem()->description_;
						subquest->experience_points_ = node_with_quest_ptr->getItem()->experience_points_;
						subquest->completed_ = node_with_quest_ptr->getItem()->completed_;
						subquest->subquests_ = node_with_quest_ptr->getItem()->subquests_;
						subquest->dependencies_ = node_with_quest_ptr->getItem()->dependencies_;
					}
				}
			}
		}
		node_curr_ptr = node_curr_ptr->getNext();
	}
}	

/**
 * Helper function for calculateProjectedExperience
 * @param: a pointer to a quest.
 * @param: A vector of quest pointers containing subquests already factored into the total amount of experience points a quest along with its subquests can yield.
 * 		 : i.e. If one of the subquests considered was accounted for, if another subquest has that same subquest, it will not be accounted for again.
 * @return: an integer value representing the total experience points which can be earned by completed a quest, along with all of its subquests recursively.
 */
int QuestList::calculateIfCompletedSubquests(Quest* quest_ptr, std::vector<Quest*>& subquests_factored) const {
	int total_experience_points = 0;
	total_experience_points += quest_ptr->experience_points_;

	if (quest_ptr->subquests_.size() != 0)
	{
		for (auto& subquest : quest_ptr->subquests_)
		{
			//subquest has only been accounted for once, when accounting for the exp of this particular quest.
			if (auto it = std::find_if(subquests_factored.begin(), subquests_factored.end(), [subquest](const Quest* a) {return a->title_ == subquest->title_;}); it == subquests_factored.end()){
				subquests_factored.push_back(subquest);
				total_experience_points += calculateIfCompletedSubquests(subquest, subquests_factored);
			}
		}
	}
	return total_experience_points;
}

/**
 * Helper function for calculatePathwayExperience
 * @param: a pointer to a quest.
 * @param: A vector of quest pointers containing subquests already factored into the total amount of experience points a quest along with its subquests can yield.
 * 		 : i.e. If one of the subquests considered was accounted for, if another subquest has that same subquest, it will not be accounted for again.
 * @return: an integer value representing the total experience points which have already been earned by its currently completed subquests, which are considered recursively.
 */
int QuestList::calculateCompletedSubquests(Quest* quest_ptr, std::vector<Quest*>& subquests_factored) const {
	int total_experience_points = 0;

	if (quest_ptr->subquests_.size() != 0)
	{
		for (auto& subquest : quest_ptr->subquests_)
		{
			if (subquest->completed_)
			{
				//subquest has only been accounted for once, when accounting for the exp of this particular quest.
				if (auto it = std::find_if(subquests_factored.begin(), subquests_factored.end(), [subquest](const Quest* a) {return a->title_ == subquest->title_;}); it == subquests_factored.end()){
					subquests_factored.push_back(subquest);
					total_experience_points += subquest->experience_points_;
					total_experience_points += calculateCompletedSubquests(subquest, subquests_factored);
				}
			}
		}
	}
	return total_experience_points;
}

