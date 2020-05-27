#ifndef TILELIST_H
#define TILELIST_H

class TileList {

public:

    TileList(char colour);

    ~TileList();

    void updateNumberOfTiles(int offSet);

    int getNumberOfTiles();

    char getColour();

private:
    char colour;

    int numberOfTiles;
};

#endif // TILELIST_H