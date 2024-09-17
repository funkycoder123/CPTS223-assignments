#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T1, typename T2>
class LinkedList
{
private:
    // Node struct for storing command and description....
    struct Node
    {
        T1 command;     // Command .
        T2 description; // Description ..
        Node *next;     // Pointer to next node ...
        Node(const T1 &cmd, const T2 &desc) : command(cmd), description(desc), next(nullptr) {}
    };

    Node *head; // Head of the linked list

public:
    // Constructor
    LinkedList() : head(nullptr) {}

    // Destructor to deallocate memory
    ~LinkedList()
    {
        clear();
    }

    // Insert a node at the front of the list will use it for loading commands from commands.csv
    void insertAtFront(const T1 &command, const T2 &description);

    // Remove a node by command..
    bool removeNode(const T1 &command);

    // Clear the list..
    void clear();

    // Display all commands... might use to debug in the future..
    void display() const;

    Node *getHead() const
    {
        return head;
    }

    bool commandExists(const T1 &command) const
    {
        Node *current = head;
        while (current != nullptr)
        {
            if (current->command == command)
            {
                return true; // Command found
            }
            current = current->next;
        }
        return false; // Command not found
    }
};

// Insert node at front list..
template <typename T1, typename T2>
void LinkedList<T1, T2>::insertAtFront(const T1 &command, const T2 &description)
{
    Node *newNode = new Node(command, description);
    newNode->next = head;
    head = newNode;
}

// Remove a node by command
template <typename T1, typename T2>
bool LinkedList<T1, T2>::removeNode(const T1 &command)
{
    Node *current = head;
    Node *previous = nullptr;

    while (current != nullptr)
    {
        if (current->command == command)
        {
            if (previous == nullptr)
            {
                head = current->next; // remove head..
            }
            else
            {
                previous->next = current->next;
            }
            delete current;
            return true; // Node removed..
        }
        previous = current;
        current = current->next;
    }
    return false; // Node not found..
}

// Display the list..
template <typename T1, typename T2>
void LinkedList<T1, T2>::display() const
{
    Node *current = head;
    while (current != nullptr)
    {
        std::cout << "Command: " << current->command << " | Description: " << current->description << std::endl;
        current = current->next;
    }
}

// Clear the entire list and deallocate memory..

template <typename T1, typename T2>
void LinkedList<T1, T2>::clear()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

#endif
