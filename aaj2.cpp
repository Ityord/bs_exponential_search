#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

// Node structure for the circular linked list
struct Node {
    string data;
    Node* next;
    Node(const string &d) : data(d), next(nullptr) {}
};

// CircularLinkedList class with methods for appending, displaying,
// finding the forward distance, and getting the total length.
class CircularLinkedList {
private:
    Node* head;
public:
    CircularLinkedList() : head(nullptr) {}

    // Append a new node to the list
    void append(const string &data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = newNode;
            newNode->next = head;
        } else {
            Node* temp = head;
            while (temp->next != head)
                temp = temp->next;
            temp->next = newNode;
            newNode->next = head;
        }
    }

    // Display the circular linked list
    void display() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = head;
        do {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != head);
        cout << "(back to head)" << endl;
    }

    // Get the total number of nodes in the list
    int getLength() {
        if (!head) return 0;
        int count = 1;
        Node* temp = head->next;
        while (temp != head) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // Find the forward distance from 'start' to 'end'
    // Returns -1 if either element is not found.
    int findDistance(const string &start, const string &end, string &errorMessage) {
        if (!head) {
            errorMessage = "The list is empty.";
            return -1;
        }
        Node* current = head;
        bool foundStart = false;
        // Search for the start node in the circular list
        do {
            if (current->data == start) {
                foundStart = true;
                break;
            }
            current = current->next;
        } while (current != head);
        if (!foundStart) {
            errorMessage = "Start element '" + start + "' not found in the list.";
            return -1;
        }
        // Traverse starting from the found start node until the end element is encountered.
        int distance = 0;
        Node* startNode = current;
        do {
            if (current->data == end) {
                return distance;
            }
            current = current->next;
            distance++;
        } while (current != startNode);
        // If the loop completes, the end element was not found.
        errorMessage = "End element '" + end + "' not found in the list.";
        return -1;
    }

    // Destructor to free memory allocated for nodes
    ~CircularLinkedList() {
        if (!head) return;
        Node* current = head->next;
        while (current != head) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        delete head;
    }
};

int main() {
    CircularLinkedList cll;
    cout << "Enter elements for the circular linked list separated by spaces:" << endl;
    
    // Read a full line of input and extract tokens.
    string line;
    getline(cin, line);
    istringstream iss(line);
    string token;
    while (iss >> token) {
        cll.append(token);
    }

    cout << "\nThe circular linked list is:" << endl;
    cll.display();

    // Get the start and end elements from the user.
    string startVal, endVal;
    cout << "\nEnter the start element: ";
    cin >> startVal;
    cout << "Enter the end element: ";
    cin >> endVal;

    // Find the forward distance and handle any potential errors.
    string errorMsg;
    int forwardDistance = cll.findDistance(startVal, endVal, errorMsg);
    if (forwardDistance == -1) {
        cout << "\nError: " << errorMsg << endl;
    } else {
        int totalLength = cll.getLength();
        int reverseDistance = totalLength - forwardDistance;
        int shortest = min(forwardDistance, reverseDistance);
        cout << "\nDistance from '" << startVal << "' to '" << endVal << "':" << endl;
        cout << "Forward distance: " << forwardDistance << endl;
        cout << "Reverse distance: " << reverseDistance << endl;
        cout << "Minimum (shortest) distance: " << shortest << endl;
    }

    return 0;
}
