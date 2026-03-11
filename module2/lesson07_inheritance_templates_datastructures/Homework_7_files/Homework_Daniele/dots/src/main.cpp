/**
 * main.cpp
 *
 * Homework 6 - Bunny Escape Game
 *
 * Game summary:
 * - The bunny spawns at a random position
 * - The hole is at (12, 12), radius 5
 * - BTN_X on GPIO1 moves bunny on X
 * - BTN_Y on GPIO0 moves bunny on Y
 * - Total allowed moves = 25
 * - Red LED on GPIO3 is ON at startup
 * - Green LED on GPIO10 turns ON when bunny is safe
 *
 * Important notes:
 * - Buttons use INPUT_PULLUP
 * - Interrupts are used on FALLING edge
 * - Debounce is handled in software using millis()
 * - LED is common anode, so LOW means LED ON
 */

#include <Arduino.h>
#include <stdint.h>

#include "dots.h"

// ============================================================
// Serial configuration
// ============================================================

#define SERIAL_SPEED  115200u
#define STARTUP_DELAY 4000u

// ============================================================
// Hardware configuration
// ============================================================

static const uint8_t BTN_X_PIN = 1;
static const uint8_t BTN_Y_PIN = 0;

static const uint8_t RED_LED_PIN   = 3;
static const uint8_t GREEN_LED_PIN = 10;

// Common anode RGB LED -> active-low
static const uint8_t LED_ON  = LOW;
static const uint8_t LED_OFF = HIGH;

// ============================================================
// Game configuration
// ============================================================

static const uint8_t FIELD_MAX   = 25;
static const uint8_t HOLE_X      = 12;
static const uint8_t HOLE_Y      = 12;
static const uint8_t HOLE_RADIUS = 5;
static const uint8_t MAX_MOVES   = 25;

static const uint32_t DEBOUNCE_MS = 50;

// ============================================================
// Game objects
// ============================================================

point bunny;              // random spawn
point hole(HOLE_X, HOLE_Y);

// ============================================================
// ISR communication flags
// The ISR only sets flags. Real work is done in loop().
// ============================================================

volatile bool btnXInterruptFlag = false;
volatile bool btnYInterruptFlag = false;

// ============================================================
// Debounce timestamps
// ============================================================

static uint32_t lastBtnXMs = 0;
static uint32_t lastBtnYMs = 0;

// ============================================================
// Game state
// ============================================================

static uint8_t moveCount = 0;
static bool gameOver = false;

// ============================================================
// Interrupt service routines
// Keep them very short
// ============================================================

void IRAM_ATTR onBtnXFall()
{
    btnXInterruptFlag = true;
}

void IRAM_ATTR onBtnYFall()
{
    btnYInterruptFlag = true;
}

// ============================================================
// LED helper functions
// ============================================================

static void setDangerState()
{
    digitalWrite(RED_LED_PIN, LED_ON);
    digitalWrite(GREEN_LED_PIN, LED_OFF);
}

static void setSafeState()
{
    digitalWrite(RED_LED_PIN, LED_OFF);
    digitalWrite(GREEN_LED_PIN, LED_ON);
}

// ============================================================
// Print current game status after a move
// ============================================================

static void printMoveStatus(const char* buttonName)
{
    uint8_t dist = bunny.distance(bunny, hole);
    uint8_t movesLeft = (MAX_MOVES > moveCount) ? (MAX_MOVES - moveCount) : 0;

    Serial.printf(
        "[Move %u] %s -> Bunny at (%u, %u) | Distance: %u | Moves left: %u\n",
        moveCount,
        buttonName,
        bunny.getX(),
        bunny.getY(),
        dist,
        movesLeft
    );
}

// ============================================================
// Check win / lose conditions
// ============================================================

static void checkGameState()
{
    uint8_t dist = bunny.distance(bunny, hole);

    // Win condition
    if (dist <= HOLE_RADIUS)
    {
        setSafeState();
        gameOver = true;

        Serial.println();
        Serial.printf(
            "*** BUNNY IS SAFE! Reached the hole in %u moves! ***\n",
            moveCount
        );
        return;
    }

    // Lose condition
    if (moveCount >= MAX_MOVES)
    {
        setDangerState();
        gameOver = true;

        Serial.println();
        Serial.println("*** GAME OVER! The hawk caught the bunny! ***");
    }
}

// ============================================================
// Process one valid move
// ============================================================

static void processMoveX()
{
    if (gameOver)
    {
        return;
    }

    bunny.moveX(1);
    moveCount++;

    printMoveStatus("BTN_X");
    checkGameState();
}

static void processMoveY()
{
    if (gameOver)
    {
        return;
    }

    bunny.moveY(1);
    moveCount++;

    printMoveStatus("BTN_Y");
    checkGameState();
}

// ============================================================
// Setup
// ============================================================

void setup()
{
    Serial.begin(SERIAL_SPEED);
    delay(STARTUP_DELAY);

    // Seed random generator
    randomSeed((uint32_t)micros());

    // Configure LED pins
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);

    // Startup state: bunny in danger
    setDangerState();

    // Configure buttons with internal pull-ups
    pinMode(BTN_X_PIN, INPUT_PULLUP);
    pinMode(BTN_Y_PIN, INPUT_PULLUP);

    // Attach interrupts on FALLING edge
    attachInterrupt(digitalPinToInterrupt(BTN_X_PIN), onBtnXFall, FALLING);
    attachInterrupt(digitalPinToInterrupt(BTN_Y_PIN), onBtnYFall, FALLING);

    // Print game header
    Serial.println();
    Serial.println("================================================");
    Serial.println(" Bunny Escape Game");
    Serial.println("================================================");
    Serial.printf(
        "Bunny spawned at (%u, %u)\n",
        bunny.getX(),
        bunny.getY()
    );
    Serial.printf(
        "Hole is at (%u, %u). Radius: %u\n",
        hole.getX(),
        hole.getY(),
        HOLE_RADIUS
    );
    Serial.printf("Moves allowed: %u\n", MAX_MOVES);
    Serial.println("---");
}

// ============================================================
// Main loop
// ISR sets flags, loop debounces and processes them
// ============================================================

void loop()
{
    if (gameOver)
    {
        return;
    }

    uint32_t now = millis();

    // BTN_X on GPIO1
    if (btnXInterruptFlag)
    {
        btnXInterruptFlag = false;

        // Debounce check
        if ((now - lastBtnXMs) >= DEBOUNCE_MS)
        {
            lastBtnXMs = now;

            // Confirm the pin is still pressed
            if (digitalRead(BTN_X_PIN) == LOW)
            {
                processMoveX();
            }
        }
    }

    // BTN_Y on GPIO0
    if (btnYInterruptFlag)
    {
        btnYInterruptFlag = false;

        // Debounce check
        if ((now - lastBtnYMs) >= DEBOUNCE_MS)
        {
            lastBtnYMs = now;

            // Confirm the pin is still pressed
            if (digitalRead(BTN_Y_PIN) == LOW)
            {
                processMoveY();
            }
        }
    }
}