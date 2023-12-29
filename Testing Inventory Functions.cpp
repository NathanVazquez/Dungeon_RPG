#include "Inventory.hpp"
#include "Item.hpp"
//#include "Inventory.cpp"
#include <chrono>

void testAddItem(){
    std::cout<<"inside function \n";
    Item* item1 = new Item;
    ItemType WEAP = WEAPON;
    item1->setType(WEAP);

    Inventory* bag = new Inventory;
    (bag->addItem(item1) == 1) ? std::cout<<"True item":std::cout<<" false item not";
    std::cout<< " added to inventory \n \n";
    //std::cout << "number of nodes in tree: "<< bag->getNumberOfNodes();
}

void testAddRemoveItem(){
    Item* item1 = new Item;
    ItemType WEAP = WEAPON;
    ItemType CONSUM = CONSUMABLE;
    ItemType UNKN = UNKNOWN;
    ItemType ARM = ARMOR;
    item1->setType(WEAP);
    item1->setName("KNIFE");
    ////////////////////////
    Item* item2 = new Item;
    
    item2->setType(ARM);
    item2->setName("CHESTPLATE");
    ///////////////////////////
    Item* item3 = new Item;
    
    item3->setType(CONSUM);
    item3->setName("HEALTHPOTION");
    item3->setQuantity(1);
    ////////////////////////////
    Item* item4 = new Item;
    
    item4->setType(CONSUM);
    item4->setName("HEALTHPOTION");
    item4->setQuantity(1);

    Inventory* bag = new Inventory;

    (bag->addItem(item1) == 1) ? std::cout<<"True item ":std::cout<<"False item not ";
    std::cout<< " added to inventory";
    std::cout<<  bag->findItem("KNIFE")->getName()<< " was added \n \n";

    (bag->addItem(item2) == 1) ? std::cout<<"True item ":std::cout<<"False item not ";
    std::cout<< " added to inventory";
    std::cout<<  bag->findItem("CHESTPLATE")->getName()<< " was added \n \n";


    (bag->addItem(item3) == 1) ? std::cout<<"True item ":std::cout<<"False item not ";
    std::cout<< " added to inventory";
    std::cout<<  bag->findItem("HEALTHPOTION")->getName()<< " was added.  "<<bag->findItem("HEALTHPOTION")->getQuantity()<<"\n \n";



    (bag->addItem(item4) == 1) ? std::cout<<"True item ":std::cout<<"False item not ";
    std::cout<< " added to inventory";
    std::cout<<  bag->findItem("HEALTHPOTION")->getName()<< " was added.  "<<bag->findItem("HEALTHPOTION")->getQuantity()<<"\n \n";


    /////////////////////////////
    std::cout << bag->findItem("KNIFE")->getName();
    (bag->removeItem("KNIFE") == 1) ? std::cout<<" has":std::cout<<" has not";
    std::cout<< " been removed from inventory \n \n";

    std::cout << bag->findItem("CHESTPLATE")->getName();
    (bag->removeItem("CHESTPLATE") == 1) ? std::cout<<"True item has":std::cout<<" false item has not";
    std::cout<< " been removed from inventory \n \n";

    std::cout << bag->findItem("HEALTHPOTION")->getName();
    (bag->removeItem("HEALTHPOTION") == 1) ? std::cout<<"True item has":std::cout<<" false item has not";
    std::cout<< " been removed from inventory \n";
    std::cout << " Quantity of this consumable is: " <<bag->findItem("HEALTHPOTION")->getQuantity()<<"\n \n";
    

    std::cout << bag->findItem("HEALTHPOTION")->getName();
    (bag->removeItem("HEALTHPOTION") == 1) ? std::cout<<"True item has":std::cout<<" false item has not";
    std::cout<< " been removed from inventory \n";
    //std::cout << " Quantity of this consumable is: " <<bag->findItem("HEALTHPOTION")->getQuantity()<<"\n \n";


    //std::cout << "number of nodes in tree: "<< bag->getNumberOfNodes();
}
void testFindItem(){
    std::cout<<"inside function \n";
    Item* item1 = new Item;
    ItemType WEAP = WEAPON;
    item1->setType(WEAP);
    item1->setName("KNIFE");

    Inventory* bag = new Inventory;
    (bag->addItem(item1) == 1) ? std::cout<<"True item":std::cout<<" false item not";
    std::cout<< " added to inventory \n \n";

    Item* item2 = new Item;
    
    item2 = bag->findItem("KNIFE");
    std::cout << "found item with name: " << item2->getName() << "\n its type is: "<< item2->getType() <<"\n"; 
    //std::cout << "number of nodes in tree: "<< bag->getNumberOfNodes();
}
void testPrintInventoryInOrder(){
    Item* item1 = new Item;
    ItemType WEAP = WEAPON;
    ItemType CONSUM = CONSUMABLE;
    ItemType UNKN = UNKNOWN;
    ItemType ARM = ARMOR;
    item1->setType(WEAP);
    item1->setName("KNIFE");
    ////////////////////////
    Item* item2 = new Item;
    
    item2->setType(ARM);
    item2->setName("CHESTPLATE");
    ///////////////////////////
    Item* item3 = new Item;
    
    item3->setType(CONSUM);
    item3->setName("HEALTHPOTION");
    item3->setQuantity(4);
    ////////////////////////////
    Item* item4 = new Item;
    
    item4->setType(CONSUM);
    item4->setName("HEALTHPOTION");
    item4->setQuantity(4);

    Inventory* bag = new Inventory;

    (bag->addItem(item1) == 1) ? std::cout<<"True item ":std::cout<<"False item not ";
    std::cout<< " added to inventory";
    std::cout<<  bag->findItem("KNIFE")->getName()<< " was added \n \n";

    (bag->addItem(item2) == 1) ? std::cout<<"True item ":std::cout<<"False item not ";
    std::cout<< " added to inventory";
    std::cout<<  bag->findItem("CHESTPLATE")->getName()<< " was added \n \n";


    (bag->addItem(item3) == 1) ? std::cout<<"True item ":std::cout<<"False item not ";
    std::cout<< " added to inventory";
    std::cout<<  bag->findItem("HEALTHPOTION")->getName()<< " was added.  "<<bag->findItem("HEALTHPOTION")->getQuantity()<<"\n \n";


    (bag->addItem(item4) == 1) ? std::cout<<"True item ":std::cout<<"False item not ";
    std::cout<< " added to inventory";
    std::cout<<  bag->findItem("HEALTHPOTION")->getName()<< " was added.  "<<bag->findItem("HEALTHPOTION")->getQuantity()<<"\n \n";

    bag->printInventoryInOrder();

}
void testGetGoldValue(){
    
    Item* item1 = new Item;
    ItemType WEAP = WEAPON;
    ItemType CONSUM = CONSUMABLE;
    ItemType UNKN = UNKNOWN;
    ItemType ARM = ARMOR;
    item1->setType(WEAP);
    item1->setName("KNIFE");
    item1->setGoldValue(5);
    ////////////////////////
    Item* item2 = new Item;
    
    item2->setType(ARM);
    item2->setName("CHESTPLATE");
    item2->setGoldValue(5);

    ///////////////////////////
    Item* item3 = new Item;
    
    item3->setType(CONSUM);
    item3->setName("HEALTHPOTION");
    item3->setQuantity(4);
    item3->setGoldValue(5);

    ////////////////////////////
    Item* item4 = new Item;
    
    item4->setType(CONSUM);
    item4->setName("HEALTHPOTION");
    item4->setQuantity(4);

    Inventory* bag = new Inventory;

    (bag->addItem(item1) == 1) ? std::cout<<"True item ":std::cout<<"False item not ";
    std::cout<< " added to inventory";
    std::cout<<  bag->findItem("KNIFE")->getName()<< " was added \n \n";

    (bag->addItem(item2) == 1) ? std::cout<<"True item ":std::cout<<"False item not ";
    std::cout<< " added to inventory";
    std::cout<<  bag->findItem("CHESTPLATE")->getName()<< " was added \n \n";


    (bag->addItem(item3) == 1) ? std::cout<<"True item ":std::cout<<"False item not ";
    std::cout<< " added to inventory";
    std::cout<<  bag->findItem("HEALTHPOTION")->getName()<< " was added.  "<<bag->findItem("HEALTHPOTION")->getQuantity()<<"\n \n";


    (bag->addItem(item4) == 1) ? std::cout<<"True item ":std::cout<<"False item not ";
    std::cout<< " added to inventory";
    std::cout<<  bag->findItem("HEALTHPOTION")->getName()<< " was added.  "<<bag->findItem("HEALTHPOTION")->getQuantity()<<"\n \n";


    //std::cout <<"callign func";
    std::cout << bag->getTotalGoldValue();
}

void testPrintInventoryTotal(){
     
    Item* item1 = new Item;
    ItemType WEAP = WEAPON;
    ItemType CONSUM = CONSUMABLE;
    ItemType UNKN = UNKNOWN;
    ItemType ARM = ARMOR;
    item1->setType(WEAP);
    item1->setName("FEATHER DUSTER");
    item1->setGoldValue(100);
    item1->setLevel(5);
    ////////////////////////
    Item* item2 = new Item;
    
    item2->setType(ARM);
    item2->setName("TIRED GUANTLETS");
    item2->setGoldValue(50);
    item2->setLevel(3);

    ///////////////////////////
    Item* item3 = new Item;
    
    item3->setType(CONSUM);
    item3->setName("HEALTH POTION");
    item3->setQuantity(2);
    item3->setGoldValue(10);
    item3->setLevel(2);

    ////////////////////////////
    Item* item4 = new Item;
    
    item4->setType(CONSUM);
    item4->setName("NOODLES");
    item4->setQuantity(5);
    item4->setGoldValue(120);
    item4->setLevel(0);

    Inventory* bag = new Inventory;

    (bag->addItem(item1) == 1) ? std::cout<<"True item ":std::cout<<"False item not ";
    std::cout<< " added to inventory";
    std::cout<<  bag->findItem("FEATHER DUSTER")->getName()<< " was added \n \n";

    (bag->addItem(item2) == 1) ? std::cout<<"True item ":std::cout<<"False item not ";
    std::cout<< " added to inventory";
    std::cout<<  bag->findItem("TIRED GUANTLETS")->getName()<< " was added \n \n";


    (bag->addItem(item3) == 1) ? std::cout<<"True item ":std::cout<<"False item not ";
    std::cout<< " added to inventory";
    std::cout<<  bag->findItem("HEALTH POTION")->getName()<< " was added.  "<<bag->findItem("HEALTH POTION")->getQuantity()<<"\n \n";


    (bag->addItem(item4) == 1) ? std::cout<<"True item ":std::cout<<"False item not ";
    std::cout<< " added to inventory";
    std::cout<<  bag->findItem("NOODLES")->getName()<< " was added.  "<<bag->findItem("NOODLES")->getQuantity()<<"\n \n";


    //std::cout <<"callign func";

    bag->printInventory(false,"LEVEL");
}
int main(){
    //testAddItem();
    //testFindItem();
    //testAddRemoveItem();
    //testPrintInventoryInOrder();
    //testGetGoldValue();
    //testPrintInventoryTotal();
  

    return 0;
}