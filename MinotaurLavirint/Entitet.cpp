#pragma once
#include "Entitet.h"
    Entitet::Entitet(int x, int y) : x(x), y(y) {}
    Entitet::~Entitet() {}

    void Entitet::pomeri(int dx, int dy) {
        this->x += dx;
        this->y += dy;
    }
    
    void Entitet::setXY(int xNew, int yNew) {
        this->x = xNew;
        this->y = yNew;
    };

    int Entitet::getX() const { return x; }
    int Entitet::getY() const { return y; }

