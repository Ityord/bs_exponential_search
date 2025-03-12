#include <iostream>
using namespace std;

class CircularQueue {
private:
    int front, rear;
    int size;    // Maximum capacity of the queue
    int *arr;    // Dynamic array to store queue elements

public:
    // Constructor: Initialize the queue with given capacity
    CircularQueue(int s) {
        size = s;
        arr = new int[size];
        front = rear = -1;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return (front == -1);
    }

    // Check if the queue is full
    bool isFull() {
        return ((rear + 1) % size == front);
    }

    // Add an element to the queue
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is full. Cannot enqueue " << value << "." << endl;
            return;
        }
        // First element insertion
        if (isEmpty()) {
            front = rear = 0;
        } else {
            // Circular increment of rear
            rear = (rear + 1) % size;
        }
        arr[rear] = value;
        cout << "Enqueued: " << value << endl;
    }

    // Remove an element from the queue
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue." << endl;
            return;
        }
        int dequeuedValue = arr[front];
        // Only one element in the queue
        if (front == rear) {
            front = rear = -1;
        } else {
            // Circular increment of front
            front = (front + 1) % size;
        }
        cout << "Dequeued: " << dequeuedValue << endl;
    }

    // Display the elements of the queue
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Queue elements: ";
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear) {
                break;
            }
            i = (i + 1) % size;
        }
        cout << endl;
    }

    // Get the element at the front of the queue
    int frontElement() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return -1;  // Return -1 to indicate error
        }
        return arr[front];
    }

    // Destructor to free allocated memory
    ~CircularQueue() {
        delete[] arr;
    }
};

int main() {
    int capacity;
    cout << "Enter the capacity of the circular queue: ";
    cin >> capacity;
    
    CircularQueue cq(capacity);
    int choice;
    
    do {
        cout << "\n--- Circular Queue Menu ---" << endl;
        cout << "1. Enqueue" << endl;
        cout << "2. Dequeue" << endl;
        cout << "3. Display Queue" << endl;
        cout << "4. Show Front Element" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int value;
                cout << "Enter value to enqueue: ";
                cin >> value;
                cq.enqueue(value);
                break;
            }
            case 2: {
                cq.dequeue();
                break;
            }
            case 3: {
                cq.display();
                break;
            }
            case 4: {
                int frontVal = cq.frontElement();
                if (frontVal != -1) {
                    cout << "Front element: " << frontVal << endl;
                }
                break;
            }
            case 5: {
                cout << "Exiting program." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
