/*
URGENT_WASH(Item, After_Item)
SOAK_CHUNK(Start_Item, End_Item)
Task: Given the initial line of dishes and a sequence of these interruptions, determine the exact order you will end up washing the dishes.
​Connection to std::list: You need to grab chunks from the middle and move them to the end without physically sliding every single other dish on the counter.
*/




#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <iterator>
using namespace std;


class DishSanitizer {
private:
    list<string> dishQueue;
    unordered_map<string, list<string>::iterator> positionMap;

public:
    DishSanitizer() {
        int initialCount;
       cout << "Enter the total number of dishes: ";
        if (!(cin >> initialCount) || initialCount <= 0) return;

        cout << "Enter the names of the dishes in their initial order:\n";
        for (int i = 0; i < initialCount; ++i) {
           string dishName;
           cin >> dishName;
            dishQueue.push_back(dishName);
            positionMap[dishName] = prev(dishQueue.end());
        }

        int commandCount;
        cout << "\nEnter the number of interruptions/commands: ";
        if (!(cin >> commandCount) || commandCount <= 0) return;
        cout << "Enter commands (URGENT_WASH Item After_Item) or (SOAK_CHUNK Start_Item End_Item):\n";
        for (int i = 0; i < commandCount; ++i) {
            string commandType;
            cin >> commandType;

            if (commandType == "URGENT_WASH") {
                string item, afterItem;
                cin >> item >> afterItem;
                executeUrgentWash(item, afterItem);
            }
            else if (commandType == "SOAK_CHUNK") {
               string startItem, endItem;
               cin >> startItem >> endItem;
                executeSoakChunk(startItem, endItem);
            }
        }
    }
    void executeUrgentWash(const string& item, const string& afterItem) {
        if (positionMap.find(item) == positionMap.end() || positionMap.find(afterItem) == positionMap.end()) return;

        auto itItem = positionMap[item];
        auto itAfter = positionMap[afterItem];
        auto targetPos =next(itAfter);
        dishQueue.splice(targetPos, dishQueue, itItem);
    }
        void executeSoakChunk(const string& startItem, const string& endItem) {
        if (positionMap.find(startItem) == positionMap.end() || positionMap.find(endItem) == positionMap.end()) return;

        auto itStart = positionMap[startItem];
        auto itEnd = positionMap[endItem];
        auto rangeEnd = next(itEnd);

        dishQueue.splice(dishQueue.end(), dishQueue, itStart, rangeEnd);
    }
    void displayFinalOrder() const {
        cout << "\n=== Exact Final Washing Order ===\n";
        for (auto it = dishQueue.begin(); it != dishQueue.end(); ++it) {
          cout << *it;
            if (next(it) != dishQueue.end()) {
              cout << " -> ";
            }
        }
       cout << "\n=================================\n";
    }
};
int main() {
    DishSanitizer manager;
    manager.displayFinalOrder();

    return 0;
}
