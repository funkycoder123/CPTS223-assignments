#include <iostream>
#include <map>
#include <vector>
#include "generateUsers.hpp"

// Function to build a map using userName as the key...
std::map<std::string, User> buildMapByUserName(const std::vector<User> &users)
{
    std::map<std::string, User> mapByUserName;
    for (const auto &user : users)
    {
        mapByUserName[user.userName] = user;
    }
    return mapByUserName;
}

// Function to print the map using an iterator...
void printMap(const std::map<std::string, User> &mapByUserName)
{
    for (const auto &pair : mapByUserName)
    {
        std::cout << pair.first << ": " << pair.second.firstName << " " << pair.second.lastName
                  << ", " << pair.second.email << ", " << pair.second.numPosts
                  << " posts, Most Viewed: " << pair.second.mostViewedCategory << std::endl;
    }
}

// Function to search by key....
bool testSearchByKey(const std::map<std::string, User> &mapByUserName, const std::string &key)
{
    return mapByUserName.find(key) != mapByUserName.end();
}

// Function to delete an element by key....
bool testDeleteByKey(std::map<std::string, User> &mapByUserName, const std::string &key)
{
    return mapByUserName.erase(key) > 0;
}

// Function to check if the map is sorted...
bool isMapSorted(const std::map<std::string, User> &mapByUserName)
{
    if (mapByUserName.empty())
        return true;
    auto it = mapByUserName.begin();
    auto prev = it++;
    for (; it != mapByUserName.end(); ++it, ++prev)
    {
        if (prev->first > it->first)
            return false;
    }
    return true;
}

// Function to print users with more than 800 tweets....
void printActiveUsers(const std::map<std::string, User> &mapByUserName)
{
    for (const auto &pair : mapByUserName)
    {
        if (pair.second.numPosts > 800)
        {
            std::cout << pair.first << ": " << pair.second.numPosts << " posts" << std::endl;
        }
    }
}

// Function to print the most popular category....
void printMostPopularCategory(const std::map<std::string, User> &mapByUserName)
{
    std::map<std::string, int> categoryCount;
    for (const auto &pair : mapByUserName)
    {
        categoryCount[pair.second.mostViewedCategory]++;
    }
    std::string mostPopular;
    int maxCount = 0;
    for (const auto &category : categoryCount)
    {
        if (category.second > maxCount)
        {
            maxCount = category.second;
            mostPopular = category.first;
        }
    }
    std::cout << "Most popular category: " << mostPopular << " with " << maxCount << " users" << std::endl;
}

// Function to build a map using email as the key...
std::map<std::string, User> buildMapByEmail(const std::vector<User> &users)
{
    std::map<std::string, User> mapByEmail;
    for (const auto &user : users)
    {
        mapByEmail[user.email] = user;
    }
    return mapByEmail;
}

int main()
{
    std::vector<User> users = generateUsers(10); // Generate 10 users...

    // Scenario 1: Map by userName...
    std::map<std::string, User> mapByUserName = buildMapByUserName(users);
    printMap(mapByUserName);
    std::cout << "Search for smith55: " << (testSearchByKey(mapByUserName, "smith55") ? "Found" : "Not found") << std::endl;
    std::cout << "Delete smith55: " << (testDeleteByKey(mapByUserName, "smith55") ? "Deleted" : "Not found") << std::endl;
    std::cout << "Is map sorted? " << (isMapSorted(mapByUserName) ? "Yes" : "No") << std::endl;
    printActiveUsers(mapByUserName);
    printMostPopularCategory(mapByUserName);

    // Scenario 2: Map by email...
    std::map<std::string, User> mapByEmail = buildMapByEmail(users);
    std::cout << "Search for kat@gmail.com: " << (testSearchByKey(mapByEmail, "kat@gmail.com") ? "Found" : "Not found") << std::endl;
    std::cout << "Delete kat@gmail.com: " << (testDeleteByKey(mapByEmail, "kat@gmail.com") ? "Deleted" : "Not found") << std::endl;

    return 0;
}
