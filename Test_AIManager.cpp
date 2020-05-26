#include "AIManager.h"
#include "GameManager.h"
#include "Utility.h"

int main(void) {
    AIManager* ai = new AIManager();
    GameManager* gm = new GameManager("Alice","Bob",5);
    Table* table = gm->getTable();
    table->setupGame();
    printFactoryToFile(std::cout, table->getFactories());
    std::cout << std::endl;
    printCenterToFile(std::cout, table->getCenter());
    ai->generatePossibleTurn(table);
    std::vector<AITurn*> listTurn = ai->getListOfTurn();
    for(unsigned int i = 0; i != listTurn.size(); i++) {
        std::cout << listTurn.at(i)->toString() << std::endl;
    }

}