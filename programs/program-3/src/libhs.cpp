#include "../include/hashset.hpp"
#include <iostream>

// Initialize an empty hash set, where size is the number of buckets in the array
HashSet::HashSet(size_t size){
    this->size = size; // assserting size of the hashset
    this->array = (LinkedList**) malloc(size * sizeof(LinkedList*)); // allocating memory for new list using malloc with the inputted size
    //this->array = new LinkedList*[size];
    for(unsigned int i = 0; i < size; i++){ // initalizing the LL in the hashset
        LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
        initList(list);
        array[i] = list; // creating new LL for each index of array
    }

}

// Free all memory allocated by the hash set
HashSet::~HashSet(){
    for(unsigned int i = 0; i < size; i++){ // iterating through each LinkedList in the array
        Node* temp = array[i]->head;
        while(temp != nullptr){
            Node* next = temp->next;
            //free(temp->item);
            free(temp); // delete the temp node itself
            // dont need to free uop next because if temp->next == nullptr then there is nothing at the address anyway
            // so all frees are covered
            temp = next;
        }
        free(array[i]); // delete the LinkedList at i index
    }
    free(array); // clearing the whole array of LinkedLists
}

// Hash an unsigned long into an index that fits into a hash set
unsigned long HashSet::hash(int item){
    unsigned long hash = prehash(item);

    return hash;
}

// Insert item in the set. Return true if the item was inserted, false if it wasn't (i.e. it was already in the set)
// Recalculate the load factor after each successful insert (round to nearest whole number).
// If the load factor exceeds 70 after insert, resize the table to hold twice the number of buckets.
bool HashSet::insert(int item){
    int index = hash(item) % size; // getting index from hashing
    LinkedList* list = array[index]; // simplifying my code to zoom in on the LinkedList I am accessing

    int* newItem = new int(item); // allocating memory for newItem

    // checking if the item is in the LL
    if(containsItem(list, newItem)){
        return false;
    }

    // if the item is not in the set
    Node* newNode = createNode(newItem); // creating new node

    if(list->head == nullptr){ // the list is empty so set the new Node to head/tail
        list->head = newNode;
        list->tail = newNode;
    } else { // add the new node at the end of the list
        list->tail->next = newNode; 
        list->tail = newNode;
    }

    size_t items = len(); // numItems in the list
    size_t loadFactor = items / size; // calculating loadFactor of the list (doesn't need to be very precise)
    //std::cout << "Loadfactor: " << loadFactor << std::endl;

    return true;
}

// Remove an item from the set. Return true if it was removed, false if it wasn't (i.e. it wasn't in the set to begin with)
bool HashSet::remove(int item){
    for(unsigned int i = 0; i < size; i++){ // iterating through each LL in array
            LinkedList* list = array[i]; // setting LL to array index
            Node* temp = list->head; // setting temp Node for iterating
            Node* prev = nullptr; // setting temp Node for iterating
            while(temp != nullptr){ // continue iterating while temp isnt a NULL ptr
                if(*(int*)temp->item == item){ // if temp equals the item then return true
                    if(temp == list->head && temp == list->tail){ // if temp is both the head and the tail 
                        list->head = nullptr; // setting list head/tail to nullptr
                        list->tail = nullptr;
                    }else if(temp == list->head){ // if temp is just the head
                        list->head = temp->next; // set the head to the node after temp
                    }else if(temp == list->tail){ // if temp is just the tail
                        list->tail = prev; // setting tail to prev
                        prev->next = nullptr; // setting node after the tail to node
                    } else {
                        prev->next = temp->next; // if none of those cases, then link the nodes on either side of temp before deletion 
                    }

                    delete temp; // deallocating memory for temp
                    
                    return true;
                }
                prev = temp; // set prev to the temp element before it moves to the next Node
                temp = temp->next; // otherwise, go to next element
            }
        }

    return false;
}

// Return true if the item exists in the set, false otherwise
bool HashSet::contains(int item){
    for(unsigned int i = 0; i < size; i++){ // iterating through each LL in array
            LinkedList* list = array[i]; // setting LL to array index
            if(containsItem(list, &item)){ // checking if the list contains the item
                return true;
            }
        }

    return false;
}

// Returns the number of items in the hash set
size_t HashSet::len(){
    size_t items = 0;
    for(unsigned int i = 0; i < size; i++){ // iterating through each LL
        LinkedList* list = array[i]; // setting the particular LL
        Node* temp = list->head; // setting temp Node for iterating
        while(temp != nullptr){ // iterating until get to nullptr
            items++; // iterating items
            temp = temp->next; // going to next Node
        }
    }
    return items;
}

// Returns the number of empty buckets that can be filled before reallocating
size_t HashSet::capacity(){
    size_t capacity = 0;
    for(unsigned int i = 0; i < size; i++){ // iterating through the array of LL
        if(array[i]->head == nullptr){ // if the LL is empty
            capacity++; // iterate capacity
        }
    }
    return capacity;
}

// Print Table. You can do this in a way that helps you implement your hash set.
void HashSet::print(){
    std::cout << "Size of array: " << size << std::endl;
    for(unsigned int i = 0; i < size; i++){ // iterating through each LL
        std::cout<<"\tArray " << i << std::endl; // printing the specific array index
        LinkedList* list = array[i]; // setting the particular LL
        Node* temp = list->head; // setting temp Node for iterating
        int index = 0; // keeping track of index for each item
        while(temp != nullptr){ // iterating until get to nullptr
            std::cout << "\t\tItem at Node index " << index << ": " << *(int*)temp->item << 
                                            " with address: " << temp << std::endl; // printing item at index
            index++; // iterating index
            temp = temp->next; // going to next Node
        }
    }
}

// Modify this prehash function to work with a template type T instead of a char*
unsigned long HashSet::prehash(int item) {
    unsigned long h = 5381;
	h = ((h << 5) + h) + item;

    return h;
}
