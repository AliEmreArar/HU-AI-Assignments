#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 81  //TO DO: Define a maximum size for the stack to control memory usage considering the problem at hand

class Stack {
public:
    int top;                  // Index of the top element in the stack
    int data[MAX_SIZE]{};       // Static array to store provinces as integers (province IDs)

    Stack();                  // Constructor to initialize the stack

    // Adds a province to the top of the stack
    void push(int province);

    // Removes the top province from the stack
    int pop();

    // Returns the top province without removing it
    int peek() const;

    // Checks if the stack is empty
    bool isEmpty() const;

    // Returns the current size of the stack
    int getSize() const;  
};

#endif // STACK_H
