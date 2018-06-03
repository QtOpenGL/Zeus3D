#ifndef BOARD_H
#define BOARD_H
#include "Mesh.h"
/*
 * Board.h
 *
 *  Created on: 2018-5-25
 *      Author: Zeus
 */
class Board : public Mesh
{
public:
    Board();
    Board(const Board& rhs);
    virtual ~Board();

private:
    virtual void initFaces();
};

#endif // BOARD_H
