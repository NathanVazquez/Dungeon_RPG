/*
CSCI235 Fall 2023
Project 3 - Tavern Class
Georgina Woo
June 20 2023
Tavern.cpp declares the Tavern class along with its private and public members

--------------------------------------------------------------------------------------------------------

CSCI235 Fall 2023
Project 4
Contributing author: Nathan Vazquez
10-2023
Implemented the parameterized tavern constructor, displayRace(), displayCharacters, and the taintedStew() functions.
*/



#include "Tavern.hpp"

/** Default Constructor **/
Tavern::Tavern() : ArrayBag<Character*>(), level_sum_{0}, num_enemies_{0}
{
}

/**
    @param: the name of an input file
    @pre: Formatting of the csv file is as follows (each numbered item appears separated by comma, only one value for each numbered item):
1. Name: An uppercase string
2. Race: An uppercase string [HUMAN, ELF, DWARF, LIZARD, UNDEAD]
3. Subclass: An uppercase string [BARBARIAN, MAGE, SCOUNDREL, RANGER]
4. Level/Vitality/Armor: A positive integer
5. Enemy: 0 (False) or 1 (True)
6. Main: Uppercase string or strings representing the main weapon (Barbarian and Mage), Dagger type (Scoundrel), or arrows (Ranger). A ranger's arrows are of the form [TYPE] [QUANTITY];[TYPE] [QUANTITY], where each arrow type is separated by a semicolon, and the type and its quantity are separated with a space.
7. Offhand: An uppercase string that is only applicable to Barbarians, and may be NONE if the Barbarian does not have an offhand weapon, or if the character is of a different subclass.
8. School/Faction: Uppercase strings that represent a Mage's school of magic: [ELEMENTAL, NECROMANCY, ILLUSION] or a Scoundrel's faction: [CUTPURSE, SHADOWBLADE, SILVERTONGUE], and NONE where not applicable
9. Summoning: 0 (False) or 1 (True), only applicable to Mages (summoning an Incarnate) and Rangers (Having an Animal Companion)
10. Affinity: Only applicable to Rangers. Affinities are of the form [AFFINITY1];[AFFINITY2] where multiple affinities are separated by a semicolon. Th value may be NONE for a Ranger with no affinities, or characters of other subclasses.
11. Disguise: 0 (False) or 1 (True), only applicable to Scoundrels, representing if they have a disguise.
12. Enraged: 0 (False) or 1 (True), only applicable to Barbarians, representing if they are enraged.
    @post: Each line of the input file corresponds to a Character subclass and dynamically allocates Character derived objects, adding them to the Tavern.
*/

Tavern::Tavern(std::string filename):ArrayBag<Character*>()
{
    
    std::ifstream fin; //create input stream object
    fin.open(filename.c_str()); // open filename

    //variables for all the character classes
    std::string name,race,subclass, main, offhand, schoolfaction, affinities,tempString,string_enemy; 
    int level, vitality, armor,temp_bool;
    bool enemy,summoning,disguise,enraged;
    char comma, semicolon, endline;

    //ignores the header of the csv file
    std::string line = "";
    getline(fin,line);
  
    while(getline(fin,line)) //loop while there are lines to read in csv
    {   
        std::istringstream inputString(line); //create a new string stream object
        // input the values from csv into variables created outside while loop
        getline(inputString, name, ',');
        getline(inputString, race, ',');
        getline(inputString, subclass, ',');
        getline(inputString, tempString, ',');

        level = std::stoi(tempString);
        //tempString = "";

        getline(inputString, tempString, ',');
        vitality = std::stoi(tempString);
        //tempString = "";

        getline(inputString, tempString, ',');
        armor = std::stoi(tempString);
        //tempString = "";

        getline(inputString, string_enemy, ',');
        enemy = std::stoi(string_enemy);

        //tempString = "";
        getline(inputString, main, ',');
        getline(inputString, offhand, ',');
        getline(inputString, schoolfaction, ',');
        getline(inputString, tempString, ',');
        summoning = std::stoi(tempString);
        //tempString = "";
        getline(inputString, affinities, ',');

        getline(inputString, tempString, ',');
        disguise = std::stoi(tempString);
        //tempString = "";

        getline(inputString, tempString);
        enraged = std::stoi(tempString);
        //tempString = "";
        
        //create characters, based on the subclass of each row
        // test which subclass row belongs to
          if(subclass == "BARBARIAN"){
            //creatw barbarian pointer
            Barbarian *BarbarianPtr = new Barbarian(name,race,vitality,armor,level,enemy,main,offhand,enraged);
            enterTavern(BarbarianPtr);

          }else if (subclass =="MAGE"){
            //create Mage character pointer
            Mage *MagePtr =  new Mage(name,race,vitality,armor,level,enemy,schoolfaction,main,summoning);
            enterTavern(MagePtr);

          }else if (subclass == "SCOUNDREL"){
            //create Scoundrel character pointer
            Scoundrel *ScoundrelPtr = new Scoundrel(name,race,vitality,armor,level,enemy,main,schoolfaction,disguise);
            enterTavern(ScoundrelPtr);

          }else if(subclass == "RANGER"){

            std::vector<Arrows> allArrows;
            Arrows arrow;
            //if main doesn't not equal none
            //test cases, one arrow, multiple arrows, no arrows
            if(main != "NONE"){

              int startPos=0;
              int endPos = affinities.find(";",startPos);
              std::string type;
              std::string quantity;

              if(endPos == -1){
                std::istringstream arrows_stream(main); // create a new stringstream to parse new variable
                std::getline(arrows_stream,type,' ');
                std::getline(arrows_stream,quantity);
                // save type and quantity into type and quantity variables, delimiter is empty char
                arrow.type_ = type;
                arrow.quantity_ = std::stoi(quantity);
                allArrows.push_back(arrow);
                }else{
                  //loop through all arrows in the arrow text and save their quantity and type into appropriate variables
                  while(main.find(';',startPos) != -1){
                    endPos = main.find(';', startPos);
                    std::istringstream arrows_stream(main.substr(startPos,endPos-startPos));
                    std::getline(arrows_stream,type,' ');
                    std::getline(arrows_stream,quantity,';');
                    arrow.type_ = type;
                    arrow.quantity_ = std::stoi(quantity);

                    allArrows.push_back(arrow);
                    startPos = endPos +1;
                  }

                  std::istringstream arrows_stream(main.substr(startPos));
                  std::getline(arrows_stream, type, ' ');
                  std::getline(arrows_stream, quantity);
                    
                  arrow.type_ = type;
                  arrow.quantity_ = std::stoi(quantity);
                  allArrows.push_back(arrow);
                }
              }

            std::vector<std::string> allAffinities;

            std::string delimiter = ";";
            std::string key;
            int i=affinities.size();
            //parse through affinity variable and seperate all affinities
            if(affinities != "NONE"){
              
              int startPos=0;
              int endPos = affinities.find(";",startPos);

              if(endPos == -1){
                allAffinities.push_back(affinities);
              }else{
                while(affinities.find(';',startPos) != -1){
                  endPos = affinities.find(';', startPos);
                  std::istringstream affin_stream(affinities.substr(startPos,endPos-startPos));
                  std::getline(affin_stream,key,';');
                  allAffinities.push_back(key);
                  startPos = endPos +1;
                }
                std::istringstream affin_stream(affinities.substr(startPos));
                std::getline(affin_stream, key);
                allAffinities.push_back(key);
              }

            }

          Ranger *rangerPtr = new Ranger(name,race,vitality,armor,level,enemy,allArrows,allAffinities,summoning);
          enterTavern(rangerPtr);
          }
                
      }

    fin.close();
}

/** 
    @param:   A reference to a Character entering the Tavern
    @return:  returns true if a Character was successfully added to items_, false otherwise
    @post:    adds Character to the Tavern and updates the level sum and the enemy count if the character is an enemy.
**/
bool Tavern::enterTavern(Character* a_character)
{
  if(add(a_character))
  {
    level_sum_ += a_character->getLevel();
    if(a_character->isEnemy())
      num_enemies_++;
     
    return true;
  }
  else
  {
    return false;
  }
}

/** @param:   A reference to a Character leaving the Tavern  
    @return:  returns true if a character was successfully removed from items_, false otherwise
    @post:    removes the character from the Tavern and updates the level sum and the enemy count if the character is an enemy.
**/
bool Tavern::exitTavern(Character* a_character)
{
  if(remove(a_character))
  {
    level_sum_ -= a_character->getLevel();
    if(a_character->isEnemy())
      num_enemies_--;
      
    return true;
  }
  return false;
}



/** 
    @return:  The integer level count of all the characters currently in the Tavern
    **/
    int Tavern::getLevelSum()
    {
      return level_sum_;
    }



/** 
    @return:  The average level of all the characters in the Tavern
    @post:    Considers every character currently in the Tavern, updates the average level of the Tavern rounded to the NEAREST integer, and returns the integer value.
**/
int Tavern::calculateAvgLevel()
{
   return (level_sum_>0) ? round(double(level_sum_) / item_count_) : 0.0;

}



/** 
    @return:  The integer enemy count of the Tavern
    **/
    int Tavern::getEnemyCount()
    {
      return num_enemies_;
    }



/** 
    @return:  The percentage (double) of all the enemy characters in the Tavern
    @post:    Considers every character currently in the Tavern, updates the enemy percentage of the Tavern rounded to 2 decimal places, and returns the double value.
**/
double Tavern::calculateEnemyPercentage()
{
  double enemy_percent = (num_enemies_>0) ?  (double(num_enemies_) / item_count_) * 100: 0.0;
  return std::ceil(enemy_percent*100.0) / 100.0; //round up to to decimal places
 
}


/** 
    @param:   A string reference to a race 
    @return:  An integer tally of the number of characters in the Tavern of the given race
**/
int Tavern::tallyRace(const std::string &race)
{
  int frequency = 0;
  int curr_index = 0;   
  while (curr_index < item_count_)
  {
    if (items_[curr_index]->getRace() == race)
    {
      frequency++;
    } 

    curr_index++; 
  }

  return frequency;
}


/**
  @post:    Outputs a report of the characters currently in the tavern in the form:
  "Humans: [x] \nElves: [x] \nDwarves: [x] \nLizards: [x] \nUndead: [x] \n\nThe average level is: [x] \n[x]% are enemies.\n\n"

  Example output: 
  Humans: 5
  Elves: 8
  Dwarves: 3
  Lizards: 7
  Undead: 2

  The average level is: 16
  24% are enemies.
*/
void Tavern::tavernReport()
{
  int humans = tallyRace("HUMAN");
  int elves = tallyRace("ELF");
  int dwarves = tallyRace("DWARF");
  int lizards = tallyRace("LIZARD");
  int undead = tallyRace("UNDEAD");
  
  std::cout << "Humans: " << humans << std::endl;
  std::cout << "Elves: " << elves << std::endl;
  std::cout << "Dwarves: " << dwarves << std::endl;
  std::cout << "Lizards: " << lizards << std::endl;
  std::cout << "Undead: " << undead << std::endl;
  std::cout << "\nThe average level is: " << calculateAvgLevel() << std::endl;
  std::cout << std::fixed << std::setprecision(2) << calculateEnemyPercentage() << "% are enemies.\n\n";
}

/**
    @post: For every character in the tavern, displays each character's information
*/

void Tavern::displayCharacters()
{
  int curr_index = 0;   //for all characters int he tavern, have them use display()
  while (curr_index < item_count_)
  {
    items_[curr_index]->display();
    curr_index++; 
  }
}

/**
    @param: a string reference to a race
    @post: For every character in the tavern of the given race (only exact matches to the input string), displays each character's information

*/

void Tavern::displayRace(const std::string &race)
{

  for(int i =0; i<item_count_;i++){ //loop through items in array, if the are the same race as the one int he parameter, run the display()
    if(items_[i]->getRace() == race){
      items_[i]->display();
    }
  }

}

/**
    @post: Every character in the tavern eats a tainted stew.
*/

void Tavern::taintedStew()
{
  int curr_index = 0;   
  while (curr_index < item_count_) // loop through all items in the items array and have them execute the function, eatTaintedStew()
  {
    items_[curr_index]->eatTaintedStew();
    curr_index++; 
  }

}