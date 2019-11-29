#ifndef POSITION_H
#define POSITION_H

struct Position {
    private:
    int x;
    int y;
    
    public:
    void setX(int newX){x = newX;};
    void setY(int newY){y = newY;};
    int getX(){return x;};
    int getY(){return y;};
};

#endif