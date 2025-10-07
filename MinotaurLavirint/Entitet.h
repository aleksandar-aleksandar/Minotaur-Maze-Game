#pragma once

class Entitet {
protected:
    int x, y;
public:
    Entitet(int x, int y);
    virtual ~Entitet();

    void pomeri(int dx, int dy);

    void setXY(int xNew, int yNew);

    int getX() const;
    int getY() const;

};

