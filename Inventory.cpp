/*
Author: Nathan Vazquez
Title: Project 7 
Contribution: Implementation for all Inventory functions
Date: 12/2023
*/

#include "Inventory.hpp"

/**
 * @param : A Pointer to the Item object to be added to the inventory.
 * @post  : The Item is added to the inventory, preserving the BST structure. The BST property is based on (ascending) alphabetical order of the item's name.
 *          If the item is type UNKNOWN, WEAPON, or ARMOR and is already in the inventory, it is not added.
      However, if another instance of an Item of type CONSUMABLE is being added (an item with the same name), its quantity is updated to the sum of the quantities of the two objects, and the time_picked_up_ variable is updated to that of the latest instance of the item being added.
 * @return true if the item was added to the inventory or updated, false otherwise.
 */

bool Inventory::addItem(Item* name) 
{ 
    // BST property is based on the ascending alphabetical order of the item's name
    // if the BST contains the item and its item type is UNKNOWN, WEAPON or ARMOR then do nothing
    // if the BST contains the item and its type is CONSUMABLE, then add adjust the item to be 
    // the sum of the current quantity plus what will be added to the BST
    if (contains(name)&&(name->getType()=="CONSUMABLE")){
        //quant is the sum of the quantity of the item in the BST and the one that the user wants to add
        int quant = name->getQuantity() + getPointerTo(name)->getItem()->getQuantity();
        // next we access the item in the BST using the name of the item given to us
        // then save the new quantity to that value
        getPointerTo(name)->getItem()->setQuantity(quant);
        using namespace std::chrono;
        //getting the current time in milliseconds to replace the time picked up variable for our item
        getPointerTo(name)->getItem()->setTimePickedUp(duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count());
        // return true since the operation was successful
        return true;
    }else{
        // else, the item is not contained in the BST so we add the whole item
        add(name); 
        return true; 
    }
    return false;
}

/**
 * @param   : A reference to string name of the item to be found.
 * @return  : An Item pointer to the found item, or nullptr if the item is not in the inventory.
 */

Item* Inventory::findItem(const std::string& name)
{   
    //creating a new Item pointer
    Item* temp = new Item;
    //setting the Item pointer name equal to the name we are given in the parameter
    temp->setName(name);
    // this allows us to use the contains function on the Item* named temp
    if (contains(temp)){
        //if the item name is contained in the BST we will return the pointer to that Item
        return (getPointerTo(temp)->getItem());
    }else{
        //else we return nullptr
        return nullptr;
    }

}

/**
 * @param   : A reference to string name of the item to be removed from the inventory.
 * @return  : True if the item was found and removed or updated successfully, false otherwise.
 * @post    : If the item is found in the inventory, it is removed while preserving the BST structure.
              If a CONSUMABLE is removed, its quantity is decremented by one, but its time_picked_up_ remains the same. However, if it is the last item (it's quantity is 1 and is being removed), the item should be removed. Non-CONSUMABLE items should always be removed when they are found.
 */

bool Inventory::removeItem(const std::string& name)
{   
    // first we need to test if the item is inside the BST, if not then we return false
    //the first case is whether the item is a consumable & included in the BST
    if((findItem(name)!=nullptr)&&findItem(name)->getType() == "CONSUMABLE"){
        //item in BST, consumable
        //Next we are going to test if the quantity is 1, if true we will remove the item
        if(findItem(name)->getQuantity() == 1){
            remove(findItem(name));
        }else{
            //else the quantity is greater than 1, therefore we only subtract one from the item quantity
            //get the quantity of the Item
            int quant = findItem(name)->getQuantity() - 1;
            // replace the Items quantity with the value of quant
            findItem(name)->setQuantity(quant);
        }
        // lastly, return true since we have successfully updated/removed the item 
        return true;
    }else if((findItem(name)!=nullptr)){
        // Item in BST, not consumable
        //remove Item
        remove(findItem(name));
        //return true since we have removed the item from the BST
        return true;
    }else{
        //not in BST
        return false;
    }
}

/**
 * @param   : The current node we are going view
 * @return  : Returns the total gold value
 * @post    : the function will recursively do an inorder traversal of all nodes in the tree and continously sum up the gold value of each item.
 */

int Inventory::getTotalGoldValueHelperFunction(std::shared_ptr<BinaryNode<Item*>> curr_node) const
{   
    //return 0 when we find a nullptr
    if(curr_node==nullptr){
        return 0;
    }
    //creating a temporary item to store the value of the item inside the current node
    Item* curr_item = new Item();
    curr_item = (curr_node->getItem());
    // if the current item is a consumable we want to multiply the quantity with the gold value of the item 
    if (curr_item->getType()=="CONSUMABLE"){
        //to make sure we recursively go through all items we will call the helper function on the left and right node
        return (curr_item->getGoldValue() * curr_item->getQuantity()) + getTotalGoldValueHelperFunction(curr_node->getLeftChildPtr()) + getTotalGoldValueHelperFunction(curr_node->getRightChildPtr());
    }else{
        //to make sure we recursively go through all items we will call the helper function on the left and right node
        return curr_item->getGoldValue() + getTotalGoldValueHelperFunction(curr_node->getLeftChildPtr()) + getTotalGoldValueHelperFunction(curr_node->getRightChildPtr());
    }
    
}

/**
 * @return    : The total sum of gold values of all items in the inventory.
                Note: consumable items may have quantity >1 and gold value must be
                      added for each item
 */

int Inventory::getTotalGoldValue() const{
    //testing if the tree we are traversing is empty
    if (getRoot() == nullptr){
        return 0;
    }else{
        //if it is not empty we will call our helper function to get the value of every item in the tree
        return getTotalGoldValueHelperFunction(getRoot());
    }
}

/**
 * @param   : The current node we are going view
 * @post    : Print the Name, Type, Level Value of all items. It will only print the Quantity of consumables
 */

void Inventory::printInventoryInOrderHelperFunction(std::shared_ptr<BinaryNode<Item*>> curr_node)
{
    //base case is the current node is a nullptr
    if(curr_node==nullptr){
        return;
    }
    //if the base case is not true we will perform inorder traversal on all items in the tree
    //for in order traversal we will go through the left tree first, then the root, then the right tree
    printInventoryInOrderHelperFunction(curr_node->getLeftChildPtr());
    //when we get to the root of a sub tree with left children we will print out the details below root node of the sub tree
    //creating a temp Item to store the value of the Item in our current node
    Item* curr_item = new Item();
    curr_item = (curr_node->getItem());
    std::cout<< curr_item->getName()<<" ("<<curr_item->getType()<<")"<<"\n";
    std::cout<< "Level: "<< curr_item->getLevel()<<"\n";
    std::cout<< "Value: "<< curr_item->getGoldValue()<<"\n";
    if(curr_item->getType()=="CONSUMABLE"){
        //if the Item is a consumable then print the quantity
        std::cout<< "Quantity: "<< curr_item->getQuantity()<<"\n";
    }
    std::cout<<"\n";
    //lastly traverse the right subtree
    printInventoryInOrderHelperFunction(curr_node->getRightChildPtr());

}

/**
 * @post    : The names of all items in the Inventory are printed in ascending order.
 *            This function performs an in-order traversal of the binary search tree and prints the details of each item in the following format. 
        NOTE: QUANTITY ONLY NEEDS TO BE DISPLAYED FOR CONSUMABLE ITEMS.

 *            [NAME] ([TYPE])
              Level: [LEVEL]
              Value: [VALUE]
              Quantity: [QUANTITY]
   
              Example:
              TIRED GAUNTLETS (ARMOR)
              Level: 3
              Value: 25
        
              SMALL HEALTH POTION (CONSUMABLE)
              Level: 1
              Value: 10
              Quantity: 2
 * 
 */

void Inventory::printInventoryInOrder()
{   
    //if the root is a null pointer we will exit the function since it has no nodes
    if (getRoot() == nullptr){
        return;
    }else{
        //else we will traverse the tree starting at the node
        printInventoryInOrderHelperFunction(getRoot());
    }
}

/**
 * @param   : The current node we are going view, and a pass by reference to the vector we are editing
 * @post    : the function will recursively do an inorder traversal of all nodes in the tree and continously push back each item to a vector so we can easily mutate the values of the BST
 */

void Inventory::printInventoryTotalHelperFunction(std::shared_ptr<BinaryNode<Item*>> curr_node, std::vector<Item*>& all_items)
{
    //if the current node is not a pointer we want to add its Item into the vector
    if(curr_node!=nullptr){
    //creating a temporary item to store the value of the pointer that is inside the current node
    Item* curr_item = new Item();
    curr_item = (curr_node->getItem());
    // doing inorder traversal of the BST
    //recursively call the function on the subtree of the right child node
    printInventoryTotalHelperFunction(curr_node->getLeftChildPtr() ,all_items);
    //push the root node to the tree if it doesn't have left children 
    all_items.push_back(curr_item); 
    //recursively call the function on the subtree of the right child node
    printInventoryTotalHelperFunction(curr_node->getRightChildPtr(),all_items);
    }
}

/**
 * @param   : a reference to bool if the items are to be printed in ascending order. 
 * @param   : a reference to string attribute which defines the order by which the items are to be printed. You may assume that the given parameter will be in one of the following forms: ["NAME"/"TYPE"/"LEVEL"/"VALUE"/"TIME"]
 * @post    : All items in the Inventory are printed in the order specified by the parameter.
 *          Example usage: inventory.printInventory(false, "LEVEL");
            NOTE: QUANTITY ONLY NEEDS TO BE DISPLAYED FOR CONSUMABLE ITEMS:

            FEATHER DUSTER (WEAPON)
            Level: 5
            Value: 100

            TIRED GAUNTLETS (ARMOR)
            Level: 3
            Value: 50

            SMALL HEALTH POTION (CONSUMABLE)
            Level: 1
            Value: 10
            Quantity: 2

            NOODLES (CONSUMABLE)
            Level: 0
            Value: 120
            Quantity: 5
 */

void Inventory::printInventory(const bool& ASC, const std::string& filter)
{   
    //creating a vector of called all_items
    std::vector<Item*> all_items;
    //calling the helper function to create a vector of Items that from the current BST
    printInventoryTotalHelperFunction(getRoot(), all_items);
    // using the insertion sort implementation from https://www.geeksforgeeks.org/insertion-sort/
    int i, j;
    // int i and j will keep track of where we are in our vector
    Item* key = new Item();
    // key will be the Item we use to compare the value of our current place in the vector
    //for all items inside the vector
    for (i = 1; i < all_items.size(); i++) {
        key = all_items[i];
        //j = i-1 becuase we don't have to sort the last item in the vector
        j = i - 1;

        // depending on the filter given, we will run a while loop that will compare either the NAME, TYPE, VALUE, LEVEL, or TIME of 2 items
        // the while loop will loop until j is greater than or equal to 0 and the current item in all_items is greater then our key
        if(filter == "NAME"){
            while (j >= 0 && all_items[j]->getName() > key->getName()) {
                all_items[j + 1] = all_items[j];
                j = j - 1;
            }
        }else if(filter == "TYPE"){
            while (j >= 0 && all_items[j]->getType() > key->getType()) {
                all_items[j + 1] = all_items[j];
                j = j - 1;
            }
        }else if(filter == "LEVEL"){
            while (j >= 0 && all_items[j]->getLevel() > key->getLevel()) {
                all_items[j + 1] = all_items[j];
                j = j - 1;
            }
        }else if(filter == "VALUE"){
            while (j >= 0 && all_items[j]->getGoldValue() > key->getGoldValue()) {
                all_items[j + 1] = all_items[j];
                j = j - 1;
            }
        }else{
            // the last filter is time
            while (j >= 0 && all_items[j]->getTimePickedUp() > key->getTimePickedUp()) {
                all_items[j + 1] = all_items[j];
                j = j - 1;
            }
        }

        all_items[j + 1] = key;
    }
    //if the bool for Ascending is not true then we need to reverse the order of the vector so that the vector will be in ascending order
    if(!ASC){
        //creating a new vector that gets the value of the sorted vector
        std::vector<Item*> smeti_lla = all_items;
        //int j will keep track of the position all_items vector and keep increasing it so it will go to the next item
        int j = 0;
        // the for loop will loop through the new vector in reverse
        for (int i = all_items.size() -1; i>=0;i--){
            all_items[j]=smeti_lla[i];
            j++;

        }
    }
    //for all items in the all_items vector, print out the value of the item
    for (int i =0 ; i< all_items.size();i++){

    std::cout<< all_items[i]->getName()<<" ("<<all_items[i]->getType()<<")"<<"\n";
    std::cout<< "Level: "<< all_items[i]->getLevel()<<"\n";
    std::cout<< "Value: "<< all_items[i]->getGoldValue()<<"\n";
    if(all_items[i]->getType()=="CONSUMABLE"){
        std::cout<< "Quantity: "<< all_items[i]->getQuantity()<<"\n";
    }
    std::cout<<"\n";
    }
    
}


