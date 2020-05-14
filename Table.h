#ifndef TABLE_H
#define TABLE_H

#include "LinkedList.h"
#include "Vector.h"
#include "Types.h"

class Table {

public:

    Table();

    ~Table();

    LinkedList* getTileBag();

    LinkedList* getBoxLid();

    Factory* getFactories();

    Vector* getCenter();
    
    int getSeedNumber();

    void setSeedNumber(int seedNumber);

    void addFactory(int row, int col, char value);


private:

    LinkedList* tileBag;

    LinkedList* boxLid;

    Factory factories[NUMBER_OF_FACTORY];

    Vector* centerOfTable;
    
    int seedNumber;
  
};

#endif // TABLE_H