/*
 * Task 3: Sensor Data Class
 * Level: Advanced (C++)
 * 
 * Description:
 * Create a class to store and process sensor readings (temperature and humidity).
 * The class should store multiple readings and calculate statistics.
 * 
 * Skills tested:
 * - Class design
 * - Constructors
 * - Member variables (encapsulation)
 * - Member functions (methods)
 * - Data structures (arrays or vectors)
 * - Basic algorithms (average calculation)
 */

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

/*
 * Class: SensorData
 * -----------------
 * Stores sensor readings with timestamp, temperature, and humidity
 * 
 * Requirements:
 * 1. Store multiple readings
 * 2. Calculate average temperature
 * 3. Calculate average humidity
 * 4. Print all readings in a formatted way
 * 
 * Suggested private members:
 * - Vector or array to store readings
 * - Consider using a struct for each reading (timestamp, temp, humidity)
 * 
 * Public methods to implement:
 * - Constructor
 * - addReading(timestamp, temperature, humidity)
 * - getAverageTemperature()
 * - getAverageHumidity()
 * - printReadings()
 */

class SensorData {
private:
    // TODO: Add private member variables here
    // Hint: You might want to store readings in a vector
    //       Each reading could be a struct with: timestamp, temperature, humidity
    
public:
    // Constructor
    SensorData() {
        // TODO: Initialize your member variables
    }
    
    /*
     * Add a new sensor reading
     * 
     * timestamp: time in seconds since start
     * temperature: temperature in Celsius
     * humidity: humidity percentage (0-100)
     */
    void addReading(int timestamp, float temperature, float humidity) {
        // TODO: Store the reading
    }
    
    /*
     * Calculate and return average temperature
     * 
     * returns: average temperature, or 0.0 if no readings
     */
    float getAverageTemperature() {
        // TODO: Calculate average
        return 0.0;
    }
    
    /*
     * Calculate and return average humidity
     * 
     * returns: average humidity, or 0.0 if no readings
     */
    float getAverageHumidity() {
        // TODO: Calculate average
        return 0.0;
    }
    
    /*
     * Print all readings in a formatted table
     */
    void printReadings() {
        // TODO: Print all stored readings
        // Example format:
        // Time    Temp(°C)  Humidity(%)
        // ----    --------  -----------
        // 0       22.5      65.0
        // 10      23.0      64.5
    }
    
    /*
     * Get number of stored readings
     */
    int getReadingCount() {
        // TODO: Return number of readings
        return 0;
    }
};

/*
 * Test function - DO NOT MODIFY
 */
void runTests() {
    cout << "Running tests...\n\n";
    
    // Test 1: Basic functionality
    cout << "Test 1: Add readings and calculate averages\n";
    cout << "--------------------------------------------\n";
    SensorData sensor1;
    sensor1.addReading(0, 22.5, 65.0);
    sensor1.addReading(10, 23.0, 64.5);
    sensor1.addReading(20, 22.8, 65.2);
    
    cout << "Expected reading count: 3, Got: " << sensor1.getReadingCount();
    cout << (sensor1.getReadingCount() == 3 ? " ✓ PASS" : " ✗ FAIL") << "\n";
    
    float avgTemp = sensor1.getAverageTemperature();
    cout << fixed << setprecision(2);
    cout << "Average Temperature: " << avgTemp << "°C";
    cout << (avgTemp >= 22.75 && avgTemp <= 22.80 ? " ✓ PASS" : " ✗ FAIL") << "\n";
    
    float avgHum = sensor1.getAverageHumidity();
    cout << "Average Humidity: " << avgHum << "%";
    cout << (avgHum >= 64.85 && avgHum <= 64.95 ? " ✓ PASS" : " ✗ FAIL") << "\n\n";
    
    cout << "All readings:\n";
    sensor1.printReadings();
    cout << "\n";
    
    // Test 2: Empty sensor
    cout << "Test 2: Empty sensor (no readings)\n";
    cout << "------------------------------------\n";
    SensorData sensor2;
    cout << "Expected count: 0, Got: " << sensor2.getReadingCount();
    cout << (sensor2.getReadingCount() == 0 ? " ✓ PASS" : " ✗ FAIL") << "\n";
    cout << "Average Temperature: " << sensor2.getAverageTemperature() << "°C\n";
    cout << "Average Humidity: " << sensor2.getAverageHumidity() << "%\n\n";
    
    // Test 3: Single reading
    cout << "Test 3: Single reading\n";
    cout << "----------------------\n";
    SensorData sensor3;
    sensor3.addReading(0, 25.0, 70.0);
    cout << "Expected count: 1, Got: " << sensor3.getReadingCount();
    cout << (sensor3.getReadingCount() == 1 ? " ✓ PASS" : " ✗ FAIL") << "\n";
    cout << "Average Temperature: " << sensor3.getAverageTemperature() << "°C";
    cout << (sensor3.getAverageTemperature() == 25.0 ? " ✓ PASS" : " ✗ FAIL") << "\n";
    cout << "Average Humidity: " << sensor3.getAverageHumidity() << "%";
    cout << (sensor3.getAverageHumidity() == 70.0 ? " ✓ PASS" : " ✗ FAIL") << "\n\n";
    
    // Test 4: Many readings
    cout << "Test 4: Multiple readings\n";
    cout << "-------------------------\n";
    SensorData sensor4;
    for (int i = 0; i < 10; i++) {
        sensor4.addReading(i * 5, 20.0 + i * 0.5, 60.0 + i);
    }
    cout << "Expected count: 10, Got: " << sensor4.getReadingCount();
    cout << (sensor4.getReadingCount() == 10 ? " ✓ PASS" : " ✗ FAIL") << "\n";
    cout << "Average Temperature: " << sensor4.getAverageTemperature() << "°C\n";
    cout << "Average Humidity: " << sensor4.getAverageHumidity() << "%\n\n";
    sensor4.printReadings();
}

int main() {
    cout << "====================================\n";
    cout << "Task 3: Sensor Data Class\n";
    cout << "====================================\n\n";
    
    runTests();
    
    return 0;
}
