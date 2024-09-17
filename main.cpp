
#include <iostream>
#include "linkedlist.h"
#include "functions.h"

using namespace std;

/*
 * ADVANTAGES/DISADVANTAGES LINKED LIST:
 *
 * A linked list allows dynamic memory allocation and easy insertion or deletion of commands
 * without needing to reallocate or resize memory. This is beneficial in terms of this PA
 * because commands can be added or removed frequently, and a linked list can handle it efficiently......
 *
 * A disadvantage of linked lists is that access to an element is slower compared to arrays since
 * each node must be traversed from the head of the list. In this pa, if we want to find a specific command,
 * we have to traverse the list, which can take longer if the list becomes large.....
 *
 * ADVANTAGES/DISADVANTAGES ARRAY:
 *
 * Arrays provides fast access to elements via indexing, which makes operations
 * like accessing or changing a user's profile by their index very efficient. In this PA, this is useful
 * because profiles can be accessed directly by index without needing to traverse through each element, providing
 * a quick lookup.
 *
 * A disadvantage of arrays is that they have a fixed size except `std::vector`....
 * This can lead to wasted memory if the array is much larger than necessary,
 * or it may require costly reallocation if the array runs out of space. In this PA, using arrays might lead
 * to inefficient memory usage if the number of profiles changes frequently.......
 */

int main()
{
    LinkedList<string, string> commandList;
    vector<pair<string, int>> profiles; // player profiles..

    loadCommands(commandList);
    loadProfiles(profiles);

    int choice;
    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Game Rules: Match Linux commands with their descriptions to earn points." << endl;
            break;
        case 2:
            playGame(commandList, profiles);
            break;
        case 3:
            loadPreviousGame(commandList, profiles);
            break;
        case 4:
            addCommand(commandList);
            break;
        case 5:
            removeCommand(commandList);
            break;
        case 6:
            saveCommands(commandList);
            saveProfiles(profiles);
            cout << "Exiting game..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
