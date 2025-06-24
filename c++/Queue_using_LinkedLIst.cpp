// Practice: Queue using Linked List
/*
Operations to support:
- Push(int x): Inserts an integer x into the queue
- Pop(): Removes the element at the front of the queue and returns it
- Front(): Returns the front element of the queue
- Size(): Returns the number of elements in the queue
*/

#include <iostream>     // for input/output
using namespace std;

// ----------- Node Class (Single Linked List Node) ------------
class LinkedList {
public:
    int val;             // Stores the data of the node
    LinkedList* next;    // Pointer to the next node

    // Constructor to initialize node with a value and null next pointer
    LinkedList(int data) {
        val = data;
        next = nullptr;
    }
};

// ----------- Queue Class Using Linked List ------------
class Queue {
private:
    LinkedList* frontNode;  // Points to the front (head) of the queue
    LinkedList* rearNode;   // Points to the rear (tail) of the queue
    int count;              // Tracks the size of the queue

public:
    // Constructor: Initializes an empty queue
    Queue() {
        frontNode = rearNode = nullptr;
        count = 0;
    }

    // Returns the element at the front of the queue
    int front() {
        if (frontNode == nullptr) {
            cout << "Queue is empty\n";
            return -1;
        }
        return frontNode->val;
    }

    // Returns the number of elements in the queue
    int size() {
        return count;
    }

    // Removes and returns the element at the front of the queue
    int pop() {
        if (frontNode == nullptr) {
            // If the queue is empty
            cout << "Queue is empty\n";
            return -1;
        } else {
            // Save current front node and its data
            LinkedList* temp = frontNode;
            int data = frontNode->val;

            // Move frontNode to the next element
            frontNode = frontNode->next;

            // If queue becomes empty after pop, rearNode should also be null
            if (frontNode == nullptr) {
                rearNode = nullptr;
            }

            // Free the memory of the removed node
            delete temp;
            count--;
            return data;
        }
    }

    // Adds an element to the rear of the queue
    void push(int data) {
        // Create a new node
        LinkedList* newNode = new LinkedList(data);

        // If queue is currently empty
        if (rearNode == nullptr) {
            frontNode = rearNode = newNode;
        } else {
            // Link new node to the end of the queue and update rearNode
            rearNode->next = newNode;
            rearNode = newNode;
        }

        count++;
    }

    // Destructor: Frees all memory used by the queue
    ~Queue() {
        while (frontNode != nullptr) {
            LinkedList* temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
        }
    }
};

// ----------- Main Function to Test the Queue ------------
int main() {
    Queue q;  // Create a new queue

    // Push elements into the queue
    q.push(10);
    q.push(20);
    q.push(30);

    // Print the front element and size
    cout << "Front: " << q.front() << endl;  // Should print 10
    cout << "Size: " << q.size() << endl;    // Should print 3

    // Pop an element and print updated front and size
    cout << "Pop: " << q.pop() << endl;      // Should print 10
    cout << "Front: " << q.front() << endl;  // Should print 20
    cout << "Size: " << q.size() << endl;    // Should print 2

    return 0;
}


