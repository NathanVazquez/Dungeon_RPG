#include <iostream>
#include <vector>
#include <string>
#include <vector>

#include "Character.hpp"
#include "Barbarian.hpp"
#include "Mage.hpp"
#include "Character.cpp"
#include "Mage.cpp"
#include "Barbarian.cpp"
#include "Scoundrel.hpp"
#include "Scoundrel.cpp"
#include "Ranger.cpp"
#include "Ranger.hpp"
#include "Tavern.hpp"
#include "Tavern.cpp"
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

void testBarbarian()
{
    Barbarian obj1 ("Peanut","UNDEAD",77,22,2,false,"toad","gun",false);
    Barbarian *Peanut = &obj1;
    Peanut->display();
    Peanut->eatTaintedStew();
    Peanut->display();
}

void testMage()
{
    Mage Bella("Bella","ELF",77,3,4,false,"ELEMENTAL","WAND",false);
    Mage *Peanut = &Bella;
    Peanut->display();
    Peanut->eatTaintedStew();
    Peanut->display();
}

void testScoundrel()
{
    Scoundrel Snibbs("Peanut","ELF",8,22,23,false,"rune","SilverTongue",true);
    Scoundrel *Peanut = &Snibbs;
    Peanut->display();
    Peanut->eatTaintedStew();
    Peanut->display();
}

void testRanger()
{   
    std::vector<Arrows> bearsarrows = {{"Wood",2},{"FIRE",1}};
    std::vector<std::string> createdaffinities = {"FIRE", "blood"};
    Ranger Boobear("Boobear","ELF",77,7,7,false,bearsarrows, createdaffinities, true);
    Ranger *Peanut = &Boobear;
    Peanut->display();
    Peanut->eatTaintedStew();
    Peanut->display();
}

void testAccessingCSV(string filename){

  //std::cout << "Successful call to Tavern Parameterized Constructor"<<std::endl;
    Tavern Pub;
    std::ifstream fin;
    fin.open(filename.c_str());

    std::string name,race,subclass, main, offhand, schoolfaction, affinities,tempString;
    int level, vitality, armor,temp_bool;
    bool enemy,summoning,disguise,enraged;
    char comma, semicolon, endline;

    std::string line = "";
    getline(fin,line);
    while(getline(fin,line))
    {   
        //std::stringstream inputString(line);
        std::istringstream inputString(line);
        getline(inputString, name, ',');
        getline(inputString, race, ',');
        getline(inputString, subclass, ',');
        getline(inputString, tempString, ',');

        level = std::stoi(tempString);
        //level = atoi(tempString.c_str());
        tempString = "";

        getline(inputString, tempString, ',');
        //vitality= atoi(tempString.c_str());
        vitality = std::stoi(tempString);
        tempString = "";

        getline(inputString, tempString, ',');
        armor = std::stoi(tempString);
        //armor = atoi(tempString.c_str());
        tempString = "";

        getline(inputString, tempString, ',');
        enemy = std::stoi(tempString);
        //temp_bool = atoi(tempString.c_str());
        tempString = "";
        //(temp_bool == 0) ? enemy = false: enemy = true;

        getline(inputString, main, ',');
        getline(inputString, offhand, ',');
        getline(inputString, schoolfaction, ',');
        getline(inputString, tempString, ',');
        summoning = std::stoi(tempString);
        //temp_bool = atoi(tempString.c_str());
        tempString = "";
        //(temp_bool == 0) ? summoning = false: summoning = true;
        getline(inputString, affinities, ',');

        getline(inputString, tempString, ',');
        disguise = std::stoi(tempString);
        //temp_bool = atoi(tempString.c_str());
        tempString = "";
        //(temp_bool == 0) ? disguise = false: disguise = true;

        getline(inputString, tempString);// there is a problem in this line
        enraged = std::stoi(tempString);
        //temp_bool = atoi(tempString.c_str());
        tempString = "";
        //(temp_bool == 0) ? enraged = false: enraged = true;
        
        if(subclass == "BARBARIAN"){
          std::cout<< "This is  Barbarian"<< std::endl;

          Barbarian temp_barbarian(name,"BARBARIAN",vitality,armor,level,enemy,main,offhand,enraged);
          Pub.enterTavern(&temp_barbarian);

        }else if (subclass =="MAGE"){
          std::cout<< "This is  Mage"<< std::endl;
          Mage temp_Mage(name,"MAGE",vitality,armor,level,enemy,schoolfaction,main,summoning);
          Pub.enterTavern(&temp_Mage);

        }else if (subclass == "SCOUNDREL"){
          std::cout<< "This is  Scoundrel"<< std::endl;
          Scoundrel temp_Scoundrel(name,"SCOUNDREL",vitality,armor,level,enemy,main,schoolfaction,disguise);
          Pub.enterTavern(&temp_Scoundrel);

        }else if(subclass == "RANGER"){
            std::cout<< "This is  Ranger"<< std::endl;
            std::vector<Arrows> allArrows;
            Arrows arrow;

            if(main != "NONE"){

                int startPos=0;
                int endPos = affinities.find(";",startPos);
                std::string type;
                std::string quantity;

                if(endPos == -1){
                    std::istringstream arrows_stream(main);
                    std::getline(arrows_stream,type,' ');
                    std::getline(arrows_stream,quantity);
                    //allArrows.push_back();
                    arrow.type_ = type;
                    arrow.quantity_ = std::stoi(quantity);
                    allArrows.push_back(arrow);
                }else{
                    while(main.find(';',startPos) != -1){
                        endPos = main.find(';', startPos);
                        std::istringstream arrows_stream(main.substr(startPos,endPos-startPos));
                        std::getline(arrows_stream,type,' ');
                        std::getline(arrows_stream,quantity,';');
                        arrow.type_ = type;
                        arrow.quantity_ = std::stoi(quantity);

                        allArrows.push_back(arrow);
                        //std::cout<< "Pushed Back Arrows:  "<<type<<std::endl;
                        startPos = endPos +1;
                    }

                    std::istringstream arrows_stream(main.substr(startPos));
                    std::getline(arrows_stream, type, ' ');
                    std::getline(arrows_stream, quantity);
                    
                    arrow.type_ = type;
                    arrow.quantity_ = std::stoi(quantity);
                    allArrows.push_back(arrow);
                    //std::cout<< "Pushed Back arrow"<<quantity<<std::endl;
                }
            }
        



          ////////////
            std::vector<std::string> allAffinities;

            std::string delimiter = ";";
            std::string key;
            int i=affinities.size();
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
                        //std::cout<< "Pushed Back affinity11"<<key<<std::endl;
                        startPos = endPos +1;
                    }
                    std::istringstream affin_stream(affinities.substr(startPos));
                    std::getline(affin_stream, key);
                    allAffinities.push_back(key);
                    //std::cout<< "Pushed Back affinity"<<key<<std::endl;
                }

            }

        Ranger temp_ranger (name, race,vitality,armor,level,enemy,allArrows,allAffinities,summoning);
        Pub.enterTavern(&temp_ranger);
        }
        
        std::cout << "Name: " << name << "\n";
        std::cout << "Race: " << race << "\n";
        std::cout << "Subclass: " << subclass << "\n";
        std::cout << "Level: " << level << "\n";
        std::cout << "Vitality: " << vitality << "\n";
        std::cout << "Armor: " << armor << "\n";
        std::cout << "Enemy: " << enemy << "\n";
        std::cout << "Main: " << main << "\n";
        std::cout << "Offhand: " << offhand << "\n";
        std::cout << "School Faction: " << schoolfaction << "\n";
        std::cout << "Summoning: " << summoning << "\n";
        std::cout << "affinities: " << affinities << "\n";
        std::cout << "Disguise: " << disguise << "\n";
        std::cout << "Enraged: " << enraged << "\n";
        std::cout << std::endl;
        

        
        line = "";
    }
    

    fin.close();

}

void testTavernParamConstructor(std::string filename){
    Tavern Pub(filename);

}

void testAddingToTavern(){
    Tavern Pub;
    Scoundrel Snibbs("Peanut","ELF",8,22,23,false,"rune","SilverTongue",true);
    //Character Butter("Peanut","ELF",8,22,23,false);
    //Scoundrel *Peanut = &Snibbs;
    //Mage Bella("Bella","ELF",77,3,4,false,"ELEMENTAL","WAND",false);
    //Mage *Peanut = &Bella;
    Pub.enterTavern(&Snibbs);
    //Pub.enterTavern(Bella);
    std::cout << Pub.tallyRace("ELF") <<std::endl;
}
void testTavernDisplayCharacters(std::string filename){
    Tavern Pub(filename);
    Pub.displayCharacters();
}
void testTavernDisplayRace(std::string filename){
    Tavern Pub(filename);
    std::string race = "ELF";
    Pub.displayRace(race);
}

int main(){

    // testBarbarian();
    // testMage();
    // testScoundrel();
    // testRanger();
    //testAccessingCSV("characters.csv");
    //std::string filename = "characters.csv";
    //testTavernParamConstructor("characters.csv");
    //testAddingToTavern();
    //testTavernDisplayCharacters("characters.csv");
    testTavernDisplayRace("characters.csv");




    return 0;
}