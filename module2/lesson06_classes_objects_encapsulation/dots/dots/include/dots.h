#include <stdint.h>
#include <Arduino.h>

class point
{
private:
    uint8_t x;
    uint8_t y;

public:
    point();  // Empty const 
    point(uint8_t X_val, uint8_t Y_val); //const with loc
    ~point();
    void print();
    uint8_t distance(point A, point B);
};

point::point()
{
    Serial.printf("Point instance constructor call \n");
}

point::point(uint8_t X_val, uint8_t Y_val)
{
    Serial.printf("Point instance constructor call, x%d, y%d \n", X_val, Y_val);
    this->x = X_val;
    this->y = Y_val;
    
}

point::~point()
{
    Serial.printf("Point desctructor call \n");
}

void point::print()
{
    Serial.printf("Point loc: x%d, y%d \n", x, y);
}

uint8_t point::distance(point A, point B){
    uint8_t delta_x = A.x - B.y;
    uint8_t delta_y = A.y - B.y;
    return delta_x + delta_y;
}

