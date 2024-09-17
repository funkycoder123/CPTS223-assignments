#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <string>
#include "linkedlist.h"

using namespace std;

// Function declarations
void displayMenu();
void loadCommands(LinkedList<string, string> &commandList);
void playGame(LinkedList<string, string> &commandList, vector<pair<string, int>> &profiles);
void addCommand(LinkedList<string, string> &commandList);
void removeCommand(LinkedList<string, string> &commandList);
void saveCommands(const LinkedList<string, string> &commandList);
void loadProfiles(vector<pair<string, int>> &profiles);
void saveProfiles(const vector<pair<string, int>> &profiles);
int findProfile(vector<pair<string, int>> &profiles, const string &name);
void loadPreviousGame(LinkedList<string, string> &commandList, vector<pair<string, int>> &profiles);

// Function to display the main menu
void displayMenu()
{
    cout << "\nMain Menu" << endl;
    cout << "1. Game Rules" << endl;
    cout << "2. Play Game" << endl;
    cout << "3. Load Previous Game" << endl;
    cout << "4. Add Command" << endl;
    cout << "5. Remove Command" << endl;
    cout << "6. Exit" << endl;
    cout << "Choose an option: ";
}

// Function to load commands from the CSV file into the linked list
void loadCommands(LinkedList<string, string> &commandList)
{
    ifstream file("commands.csv");
    string line, command, description;

    if (!file.is_open())
    {
        cerr << "Error opening commands.csv!" << endl;
        return;
    }

    while (getline(file, line))
    {
        size_t pos = line.find(",");
        if (pos != string::npos)
        {
            command = line.substr(0, pos);
            description = line.substr(pos + 1);
            commandList.insertAtFront(command, description);
        }
    }
    file.close();
}

// Function to load player profiles from profiles.csv
void loadProfiles(vector<pair<string, int>> &profiles)
{
    ifstream file("profiles.csv");
    string line, name;
    int points;

    if (!file.is_open())
    {
        cerr << "Error opening profiles.csv!" << endl;
        return;
    }

    while (getline(file, line))
    {
        size_t pos = line.find(",");
        if (pos != string::npos)
        {
            name = line.substr(0, pos);
            points = stoi(line.substr(pos + 1));
            profiles.push_back(make_pair(name, points));
        }
    }
    file.close();
}

// Function to save player profiles to profiles.csv
void saveProfiles(const vector<pair<string, int>> &profiles)
{
    ofstream file("profiles.csv");
    if (!file.is_open())
    {
        cerr << "Error opening profiles.csv for writing!" << endl;
        return;
    }

    for (const auto &profile : profiles)
    {
        file << profile.first << "," << profile.second << endl;
    }
    file.close();
}

// Function to find a player profile by name
int findProfile(vector<pair<string, int>> &profiles, const string &name)
{
    for (size_t i = 0; i < profiles.size(); ++i)
    {
        if (profiles[i].first == name)
        {
            return i; // Returning the index of the profile..
        }
    }
    return -1; // Profile not found...
}

// Function to handle game logic
void playGame(LinkedList<string, string> &commandList, vector<pair<string, int>> &profiles)
{
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;

    int profileIndex = findProfile(profiles, playerName);
    if (profileIndex == -1)
    {
        profiles.push_back(make_pair(playerName, 0)); // new player with 0 points
        profileIndex = profiles.size() - 1;
    }

    int numQuestions;
    cout << "How many questions would you like to play (between 5 and 30)? ";
    cin >> numQuestions;

    if (numQuestions < 5 || numQuestions > 30)
    {
        cout << "Invalid number of questions. Please enter a value between 5 and 30." << endl;
        return;
    }

    // all the  commands and descriptions from the linked list...
    vector<pair<string, string>> commands;
    auto *current = commandList.getHead(); // getter to access the head...
    while (current != nullptr)
    {
        commands.push_back(make_pair(current->command, current->description));
        current = current->next;
    }

    if (commands.size() < 3)
    {
        cout << "Not enough commands available to play the game!" << endl;
        return;
    }

    // random number generator for shuffling...
    random_device rd;
    mt19937 rng(rd());

    for (int i = 0; i < numQuestions; ++i)
    {
        int correctIndex = rand() % commands.size(); // a random command as the correct one...
        string correctCommand = commands[correctIndex].first;
        string correctDescription = commands[correctIndex].second;

        cout << "\nQuestion " << (i + 1) << ": Match the command: " << correctCommand << endl;

        // Select 2 other random descriptions....
        vector<string> options;
        options.push_back(correctDescription);
        while (options.size() < 3)
        {
            int randomIndex = rand() % commands.size();
            if (randomIndex != correctIndex)
            {
                options.push_back(commands[randomIndex].second);
            }
        }

        // Shuffle descriptions..
        shuffle(options.begin(), options.end(), rng);

        // Display the options...
        for (size_t j = 0; j < options.size(); ++j)
        {
            cout << (j + 1) << ": " << options[j] << endl;
        }

        // Get the player's answer...
        int playerChoice;
        cout << "Enter the number of the correct description: ";
        cin >> playerChoice;

        if (playerChoice < 1 || playerChoice > 3)
        {
            cout << "Invalid choice! You lose 1 point." << endl;
            profiles[profileIndex].second--; // Deduct a point for invalid choice
        }
        else if (options[playerChoice - 1] == correctDescription)
        {
            cout << "Correct! You've earned 1 point." << endl;
            profiles[profileIndex].second++; // Award a point for correct answer
        }
        else
        {
            cout << "Incorrect! You've lost 1 point." << endl;
            profiles[profileIndex].second--; // Deduct a point for incorrect answer
        }
    }

    cout << "\nGame over! Your final score is: " << profiles[profileIndex].second << endl;
}

// Function to save commands to the CSV file when exiting
void saveCommands(const LinkedList<string, string> &commandList)
{
    ofstream file("commands.csv");
    if (!file.is_open())
    {
        cerr << "Error opening commands.csv for writing!" << endl;
        return;
    }

    // Traverse the linked list and save each command-description pair....
    auto *current = commandList.getHead();
    while (current != nullptr)
    {
        file << current->command << "," << current->description << endl;
        current = current->next;
    }

    file.close();
    cout << "Commands saved to commands.csv." << endl;
}

void addCommand(LinkedList<std::string, std::string> &commandList)
{
    std::string command, description;
    std::cout << "Enter command to add: ";
    std::cin >> command;
    std::cin.ignore(); // remove any leftover newline characters...

    if (commandList.commandExists(command))
    {
        std::cout << "Command already exists. Cannot add duplicate." << std::endl;
        return;
    }

    std::cout << "Enter description for the command: ";
    std::getline(std::cin, description);

    commandList.insertAtFront(command, description);
    std::cout << "Command added successfully!" << std::endl;
}

void removeCommand(LinkedList<std::string, std::string> &commandList)
{
    std::string command;
    std::cout << "Enter command to remove: ";
    std::cin >> command;

    // Attempt to remove the command...
    if (commandList.removeNode(command))
    {
        std::cout << "Command removed successfully!" << std::endl;
    }
    else
    {
        std::cout << "Command not found. Cannot remove." << std::endl;
    }
}

void loadPreviousGame(LinkedList<string, string> &commandList, vector<pair<string, int>> &profiles)
{
    string playerName;
    cout << "Enter your name to load previous game: ";
    cin >> playerName;

    int profileIndex = findProfile(profiles, playerName);
    if (profileIndex == -1)
    {
        cout << "Profile not found. Please start a new game or check the name." << endl;
        return;
    }

    cout << "Welcome back, " << playerName << "! Your current score is: " << profiles[profileIndex].second << " points." << endl;

    int numQuestions;
    cout << "How many questions would you like to play (between 5 and 30)? ";
    cin >> numQuestions;

    if (numQuestions < 5 || numQuestions > 30)
    {
        cout << "Invalid number of questions. Please enter a value between 5 and 30." << endl;
        return;
    }

    playGame(commandList, profiles); // Continue with the game....
}
