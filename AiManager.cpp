#include "AiManager.h"

AiManager::AiManager() {
    listTurn = {};
    this->cgs = new CurrentGameState();
    invalidTurn = {};
}

AiManager::~AiManager() {
    clearVector(listTurn);
    clearVector(invalidTurn);
    delete cgs;
}

void AiManager::clearVector(std::vector<AiTurn*> vector) {
    for(unsigned int i = 0; i != vector.size(); i++) {
        AiTurn* turn = vector.at(i);
        delete turn;
        turn = nullptr;
    }
    vector.clear();
}

bool AiManager::isValidTurn(Tile tile, int patternLinesChoice) {
    bool valid = true;
    unsigned int size = invalidTurn.size();
    if(size != 0) {
        for(unsigned int i = 0; i != size; i++) {
            AiTurn* turn = invalidTurn.at(i);
            if(turn->getTileChoice() == tile && turn->getPatternLinesChoice() == patternLinesChoice) {
                valid = false;
            }
        }
    }
    return valid;
}

void AiManager::generatePossibleTurn() {
    std::array<std::array<int, NUM_PLAYABLE_COLOURS>, WALL_DIM> factory = cgs->getFactoryState();

    for(int i = 0; i != WALL_DIM; i++) {
        for(int j = 0; j != NUM_PLAYABLE_COLOURS; j++) {
            int numTiles = factory[i][j];
            if(numTiles != 0) {
                Tile tile = cgs->getTile(j);
                for(int turnIndex = 0; turnIndex != (WALL_DIM+1); turnIndex++) {
                    if(isValidTurn(tile, turnIndex+1)) {
                        AiTurn* turn = new AiTurn(i+1, tile, turnIndex+1, true, numTiles);
                        listTurn.push_back(turn);
                    }
                }
            }
        }
    }
    for(int i = 0; i != NUM_PLAYABLE_COLOURS; i++) {
        Tile tile = cgs->getTile(i);
        for(int j = 0; j != (WALL_DIM+1); j++) {
            if(isValidTurn(tile, j+1)) {
                AiTurn* turn = new AiTurn(0, tile, j+1, false, 0);
                listTurn.push_back(turn);
            }
        }
    }
}

void AiManager::updateGameState(Factory* factory) {
    for(int i = 0; i != WALL_DIM; i++) {
        cgs->updateFactory(factory[i], i);
    }
}

void AiManager::updateByTurnFromFactory(Vector* center, int& factoryChoice, char& colourChoice) {
    cgs->updateCenter(center);
    std::array<int, NUM_PLAYABLE_COLOURS> centerState = cgs->getCenterState();
    for(unsigned int i = 0; i != listTurn.size(); i++) {

        AiTurn* turn = listTurn.at(i);
        int index = turn->getFactoryChoice();
        Tile tile = turn->getTileChoice();
        int numTilesTaken = centerState[cgs->getIndex(tile)];

        if(index == factoryChoice) {
            turn->setValid(false);
        } else if(index == 0 && numTilesTaken != 0) {
            turn->setNumTilesTaken(numTilesTaken);
            if(turn->isPatternLinesValid()) {
                turn->setValid(true); 
            }
        }
    }
    cgs->resetFactory(factoryChoice, colourChoice);
}

void AiManager::updateByTurnFromCenter(Vector* center) {
    cgs->updateCenter(center);
    cgs->printTableState();
    std::array<int, NUM_PLAYABLE_COLOURS> centerState = cgs->getCenterState();
    for(unsigned int i = 0; i != listTurn.size(); i++) {
        AiTurn* turn = listTurn.at(i);
        if(turn->getFactoryChoice() == 0) {
            int numTiles = centerState[cgs->getIndex(turn->getTileChoice())];
            turn->setNumTilesTaken(numTiles);
            if(numTiles == 0) {
                turn->setValid(false);
            } else {
                if(turn->isPatternLinesValid()) {
                    turn->setValid(true); 
                }
            }
        }
    }
    printTurn();
}

void AiManager::updateByAiTurn(int& factoryChoice, int& patternLinesChoice, char& colourChoice, int numTilesTaken) {
    int availableTiles = cgs->updatePatternLines(patternLinesChoice, numTilesTaken);
    for(unsigned int i = 0; i != listTurn.size(); i++) {
        AiTurn* turn = listTurn.at(i);
        if(turn->getPatternLinesChoice() == patternLinesChoice) {
            Tile tile = turn->getTileChoice();
            if(tile != colourChoice) {
                turn->setValid(false);
                turn->setPatternLines(false);
            } else if(availableTiles == 0 && tile == colourChoice) {
                turn->setValid(false);
                turn->setPatternLines(false);
            }
        }
    }
}

void AiManager::updateWall(int row, int col, Tile tile, Wall wall) {
    cgs->addTileAfterRound(tile, row, col);
    cgs->updateAdjacent(row, col);
    AiTurn* turn = new AiTurn(tile, row+1);
    invalidTurn.push_back(turn);
}

void AiManager::clearEndOfRound(AbstractBoard* board) {
    Tile** patternLines = board->getPatternLines();
    cgs->resetTable();
    cgs->resetBoard(patternLines);
    clearVector(listTurn);
    for(int i = 1; i != (WALL_DIM+1); i++) {
        if(!board->isPatternLinesEmpty(i)) {
            Tile tile = patternLines[i-1][0];
            for(int j = 0; j != NUM_PLAYABLE_COLOURS; j++) {
                if(j != cgs->getIndex(tile)) {
                    AiTurn* turn = new AiTurn(cgs->getTile(j), i);
                    invalidTurn.push_back(turn);
                }
            }
        }
    }
}

void AiManager::printTurn() {
    for(unsigned int i = 0; i != listTurn.size(); i++) {
        if(listTurn.at(i)->isValid()) {
            std::cout << listTurn.at(i)->toString() << " " 
                << listTurn.at(i)->getNumTilesTaken() << " " << std::endl;
        }
    }
}

AiTurn* AiManager::createPotentialTurn(Wall wall) {
    int mScore = -15;
    AiTurn* mTurn = nullptr;
    for(unsigned int index = 0; index != listTurn.size(); index++) {
        AiTurn* turn = listTurn.at(index);
        if(turn->isValid()) {
            int factoryChoice = turn->getFactoryChoice();
            Tile color = turn->getTileChoice();
            int patternLinesChoice = turn->getPatternLinesChoice();
            int numTilesTaken = turn->getNumTilesTaken();
            int score = cgs->calculateMove(wall, factoryChoice-1, color, patternLinesChoice-1, numTilesTaken);
            if(score > mScore) {
                mScore = score;
                mTurn = turn;
            }
        }
        
    }
    return mTurn;
}