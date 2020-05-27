#ifndef TABLE_H
#define TABLE_H

#include "LinkedList.h"
#include "Vector.h"
#include "Types.h"
#include "SetupManager.h"

class Table {

public:

    Table(int seed, int boardId);

    ~Table();

    LinkedList* getTileBag();

    LinkedList* getBoxLid();

    Factory* getFactories();

    Vector* getCenter();
    
    int getSeedNumber();

    void setSeedNumber(int seedNumber);

    bool isFactoryEmpty(int& pos);

    bool isAllFactoriesEmpty();

    bool isCenterEmpty();

    bool findColourInFactory(int& pos,char& colourChoice);

    bool findColourInCenter(char& colourChoice);

    void setupGame();

    void refillTable();

    void populateChosenFactory(int& pos);

    void clearChosenFactory();

    Tile* getChosenFactory();

    void removeFactory(int& pos);

private:

    LinkedList* tileBag;

    LinkedList* boxLid;

    Factory factories[NUMBER_OF_FACTORY];

    Tile chosenFactory[FACTORY_SIZE];

    Vector* centerOfTable;
    
    int seedNumber;
    
    SetupManager* sm;
  
};

#endif // TABLE_H