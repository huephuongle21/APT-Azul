#include "AiManager.h"

AiManager::AiManager(int boardId) {
    listTurn = {};
    invalidTurn = {};
    startIndex = 0;
    if(boardId == ADVANCED_6TILE_BOARD) {
        this->boardSize = A_WALL_DIM;
    } else if(boardId == REGULAR_BOARD) {
        this->boardSize = WALL_DIM;
    }
    this->cgs = new CurrentGameState(boardSize);
    this->heuristic = new Heuristic(boardSize);
}

AiManager::~AiManager() {
    for(unsigned int i = 0; i != listTurn.size(); i++) {
        delete listTurn.at(i);
        listTurn.at(i) = nullptr;
    }
    listTurn.clear();
    for(unsigned int i = 0; i != invalidTurn.size(); i++) {
        delete invalidTurn.at(i);
        invalidTurn.at(i) = nullptr;
    }
    invalidTurn.clear();
    startIndex = 0;
    delete cgs;
    delete heuristic;
}

bool AiManager::isValidTurn(Tile tile, int patternLinesChoice) {
    bool valid = false;
    unsigned int size = invalidTurn.size();
    if(size != 0) {
        for(unsigned int i = 0; i != size; i++) {
            AiTurn* turn = invalidTurn.at(i);
            if(turn->isValid() && turn->isPatternLinesValid() 
                    && turn->getTileChoice() == tile 
                    && turn->getPatternLinesChoice() == patternLinesChoice) {
                valid = true;
            }
        }
    }
    return valid;
}

void AiManager::generatePossibleTurn() {
    int** factory = cgs->getFactoryState();

    for(int i = 0; i != WALL_DIM; i++) {
        for(int j = 0; j != boardSize; j++) {
            int numTiles = factory[i][j];
            if(numTiles != 0) {
                Tile tile = cgs->getTile(j);
                for(int turnIndex = 0; turnIndex != (boardSize+1); turnIndex++) {
                    if(isValidTurn(tile, turnIndex+1) || turnIndex == boardSize) {
                        AiTurn* turn = new AiTurn(i+1, tile, turnIndex+1, true, numTiles);
                        listTurn.push_back(turn);
                    }
                }
            }
        }
    }
    for(int i = 0; i != boardSize; i++) {
        Tile tile = cgs->getTile(i);
        for(int j = 0; j != (boardSize+1); j++) {
            if(isValidTurn(tile, j+1) || j == boardSize) {
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

void AiManager::updateByTurnFromFactory(Vector* center, 
        int& factoryChoice, char& colourChoice) {
    cgs->updateCenter(center);
    int* centerState = cgs->getCenterState();
    for(unsigned int i = startIndex; i != listTurn.size(); i++) {

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

void AiManager::setTurnByPatternLines(AbstractBoard* board) {
    for(int i = 0; i != boardSize; i++) {
        if(board->isPatternLinesFilled(i)) {
            for(unsigned int j = startIndex; j != listTurn.size(); j++) {
                AiTurn* turn = listTurn.at(j);
                if(turn->getPatternLinesChoice() == (i+1)) {
                    turn->setValid(false);
                }
            }
        }
    }    
}

void AiManager::setCenterTurnAndState(Vector* center, AbstractBoard* board) {
    cgs->updateCenter(center);
    int* centerState = cgs->getCenterState();
    for(unsigned int i = startIndex; i != listTurn.size(); i++) {
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
    setTurnByPatternLines(board);
}

void AiManager::updateByAiTurn(int& factoryChoice, int& patternLinesChoice, 
        char& colourChoice, int numTilesTaken) {
    int availableTiles = cgs->updatePatternLines(patternLinesChoice, numTilesTaken);
    if(availableTiles != -1) {
        for(unsigned int i = startIndex; i != listTurn.size(); i++) {
            AiTurn* turn = listTurn.at(i);
            if(turn->getPatternLinesChoice() == patternLinesChoice) {
                Tile tile = turn->getTileChoice();
                if((tile != colourChoice) 
                        || (availableTiles == 0 && tile == colourChoice)) {
                    turn->setValid(false);
                    turn->setPatternLines(false);
                } 
            }
        }
    }
}

void AiManager::updateWall(int row, int col, Tile tile) { 
    cgs->addTileAfterRound(tile, row, col);
    cgs->setAdjacent(row, col);
    for(unsigned int i = 0; i != invalidTurn.size(); i++) {
        AiTurn* turn = invalidTurn.at(i);
        if(turn->getPatternLinesChoice() == (row+1)) {
            Tile color = turn->getTileChoice();
            if(color == tile) {
                turn->setValid(false);
                turn->setPatternLines(false);
            } else if(color != tile && turn->isValid()) {
                turn->setPatternLines(true);
            }
        }
    }
}

void AiManager::createPatternLinesConstraint() {
    for(int i = 0; i != boardSize; i++) {
        Tile color = cgs->getTile(i);
        for(int j = 0; j != boardSize; j++) {
            AiTurn* turn = new AiTurn(color, j+1);
            invalidTurn.push_back(turn);
        }
    }
}

void AiManager::clearEndOfRound(AbstractBoard* board, bool isLoadGame) {
    Tile** patternLines = board->getPatternLines();
    if(!isLoadGame) {
        cgs->resetTable(boardSize);
        cgs->resetBoard(patternLines);
        startIndex = listTurn.size();
    }
    for(int i = 1; i != (boardSize+1); i++) {
        if(!board->isPatternLinesEmpty(i) && !board->isPatternLinesFilled(i-1)) {
            Tile tile = patternLines[i-1][0];
            for(unsigned int j = 0; j != invalidTurn.size(); j++) {
                AiTurn* turn = invalidTurn.at(j);
                if(turn->getPatternLinesChoice() == i) {
                    if(turn->getTileChoice() == tile) {
                        turn->setPatternLines(true);
                    } else {
                        turn->setPatternLines(false);
                    }
                }
                
            }
        } else if(isLoadGame && board->isPatternLinesFilled(i-1)) {
            for(unsigned int j = 0; j != invalidTurn.size(); j++) {
                AiTurn* turn = invalidTurn.at(j);
                if(turn->getPatternLinesChoice() == i) {
                    turn->setPatternLines(false);             
                }               
            }
        }
    }
}

std::string AiManager::getTurn(Wall wall) {
    std::string mTurn = heuristic->createPotentialTurn(cgs, wall, startIndex, listTurn);
    return mTurn;
}

void AiManager::updateForLoadGame(AbstractBoard* board, Factory* factory, Vector* vector) {
    cgs->setPatternLines(board->getPatternLines());
    createPatternLinesConstraint();
    Wall wall = board->getWall();
    for(int i = 0; i != boardSize; i++) {
        for(int j = 0; j != boardSize; j++) {
            Tile tile = wall[i][j];
            if(tile >= 'A' && tile <= 'Z') {
                updateWall(i, j, tile);
            }
        }
    }
    clearEndOfRound(board, true);
    cgs->setFloorLine(board->getFloorLine(), board->getFloorLineLength());
    updateGameState(factory);
    generatePossibleTurn();
    setCenterTurnAndState(vector, board);
}