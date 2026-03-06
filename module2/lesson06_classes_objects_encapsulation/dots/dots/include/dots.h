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
