#include <stdio.h> // for fprintf
#include <stdlib.h> // for malloc and free
#include <iostream>
using namespace std;

/*
// datatype declaration 
typedef struct{
    int *array;
    int capacity;
    int size;
} Stack;

// functions declarations/prototypes
void init(Stack *stack, int capacity);
bool push(Stack *stack, int value);
void release(Stack *stack);

// main
int main(){
    Stack s;
    init(&s, 4);
    push(&s, 10);
    release(&s);

    return 0;
}

// define functions
void init(Stack *stack, int capacity){
    int *array = (int*) malloc(capacity * sizeof(int)); // allocate space for the stack of 4 ints
    fprintf(stderr, "STACK ALLOCATION\n");
    stack->array = array;
    stack->capacity = capacity;
    stack->size = 0;
}

bool push(Stack *stack, int value){
    fprintf(stderr, "STACK PUSH\n");
    stack->array[stack->size]  = value;
    if(stack->size < stack->capacity){
        stack->size++;
        return true;
    } else {
        return false;
    }
}

void release(Stack *stack){
    fprintf(stderr, "STACK DEALOCATION\n");
    free(stack->array);
}

*/

// class declaration/protoype
class Stack{
    public:
        Stack(); // constructor
        Stack(int capacity); // constructor with argument
        ~Stack(); // destructor
        bool push(int value); // member function to push a value onto the stack
    private:
        int *array;
        int capacity;
        int size;
};

// main
int main(){
    Stack *s = new Stack(4);
    s->push(10);
    delete(s);
    return 0;
}

// class member function definitions
Stack::Stack(int capacity){
    cerr << "CAPACITY CONSTRUCTOR" << endl;
    int *array = (int*) malloc(capacity * sizeof(int));
    this->array = array;
    this->capacity = capacity;
    this->size = 0;
}

Stack::~Stack(){
    cerr << "DESTROYING STACK" << endl;
    free(this->array);
}

bool Stack::push(int value){
    cerr << "STACK PUSH" << endl;
    this->array[this->size] = value;
    if(this->size < this->capacity){
        this->size++;
        return true;
    } else {
        return false;
    }
}