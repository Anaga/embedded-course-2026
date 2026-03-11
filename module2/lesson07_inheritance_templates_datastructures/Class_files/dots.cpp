#include "dots.h"

#define BOARD_SIZE 25

point::point()
{
    uint8_t val_x = (uint8_t)random(0, 26);
    uint8_t val_y = (uint8_t)random(0, 26);
    Serial.printf("Point with a random\n");
    this->x = val_x;
    this->y = val_y;
    print();
}

point::point(uint8_t X_val, uint8_t Y_val)
{
    Serial.printf("Point instance constructor call, x%d, y%d\n", X_val, Y_val);
    this->x = X_val;
    this->y = Y_val;
}

point::~point()
{
    Serial.printf("Point destructor call\n");
}

void point::print()
{
    Serial.printf("Point loc: x%d, y%d\n", x, y);
}

uint8_t point::distance(point A, point B)
{
    uint8_t delta_x = A.x - B.x;
    uint8_t delta_y = A.y - B.y;
    return delta_x + delta_y;
}

void point::move_x(){
    this->x++;
    if (x>BOARD_SIZE) {
        this->x = 0;
    }
}

void point::move_y(){
    this->y++;
    if (y>BOARD_SIZE) {
        this->y = 0;
    }
}