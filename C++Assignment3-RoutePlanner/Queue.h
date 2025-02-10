#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE_SIZE 81  // // TO DO: Define a maximum size for the queue to control memory usage considering the problem at hand

class Queue {

public:
    int front, rear;          // Indices for the front and rear elements of the queue
    int data[MAX_QUEUE_SIZE]{}; // Static array to store provinces as integers (province IDs)
    
    Queue();                  // Constructor to initialize the queue

    // Adds a province to the end of the queue
    void enqueue(int province);

    // Removes and returns the front province from the queue
    int dequeue();

    // Returns the front province without removing it
    int peek() const;

    // Checks if the queue is empty
    bool isEmpty() const;

    // Add a priority province
    void enqueuePriority(int province);

    void printQueue() const;

    bool contains(int element) const;
};

#endif // QUEUE_H
