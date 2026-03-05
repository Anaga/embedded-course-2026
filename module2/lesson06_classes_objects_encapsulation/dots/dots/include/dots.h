#include <stdint.h>
#include <Arduino.h>

class point
{
private:
    uint8_t x; 
    uint8_t y;
public:
    point(); // empty const (constructor)
    point(uint8_t X, uint8_t Y); // constructor with location | spesific cords
    ~point(); // destructor
    void print();
    uint8_t distance(point A, point B);
};

point::point(/* args(arguments) */) // random cords one | :: <- shows that something(thing after ::) is in the class
{
    Serial.printf("Point instance constructor call \n");
}

point::point(uint8_t X, uint8_t Y) // spesific cords inside class showy thingy
{
    Serial.printf("Point instance constructor call, x%d, y%d \n", X, Y);
    this->x = X;
    this->y = Y;
}

point::~point() // destructor
{
        Serial.printf("Point destructor call \n");
}

void point::print()
{
    Serial.printf("Point loc: x%d, y%d \n", x, y);
}

uint8_t point::distance(point A, point B)
{
    uint8_t delta_x = A.x - B.y;
    uint8_t delta_y = A.x - B.y;
    return delta_x + delta_y;
}