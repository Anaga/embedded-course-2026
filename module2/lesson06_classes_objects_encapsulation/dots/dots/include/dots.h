#include <stdint.h>
#include <Arduino.h>

class point
{
protected:
    uint8_t x;
    uint8_t y;

public:
    point();  // Empty const 
    point(uint8_t X_val, uint8_t Y_val); //const with loc
    ~point();
    virtual void print() const;
    
    void moveX(uint8_t delta);
    void moveY(uint8_t delta);

    uint8_t getX() const;
    uint8_t getY() const;

    uint8_t distanceTo(const point& other) const;
    uint8_t distance(point A, point B);
};

class circle : public point {
private:
    uint8_t radius_;

public:
    circle(uint8_t x, uint8_t y, uint8_t radius);
    ~circle() override;

    void print() const override;

    uint8_t radius() const;
    float   area() const;
    float   circumference() const;
};