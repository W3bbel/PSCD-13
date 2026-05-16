#include <TFT_eSPI.h>
#include <TFT_eWidget.h>
#include "display.hpp"

Display display;

// Potentiometer
const int potPin = 27;  // GPIO27
const int minADC = 0;    // ADC minimum value (0V)
const int maxADC = 4095; // ADC maximum value (3.3V)
const float minVoltage = 0.0;
const float maxVoltage = 3.3;

void setup() {
    pinMode(37, OUTPUT);
    digitalWrite(37, HIGH);
    
    analogReadResolution(12);  // 12-bit resolution (0-4095)
    analogSetAttenuation(ADC_11db);  // 0-3.3V range

    display.setupDisplay();
}

void loop() {
    static float x = 0;
    static unsigned long lastAdd = 0;
    
    //point added every 100ms
    if (millis() - lastAdd >= 100) {
        lastAdd = millis();
        
        int potValue = analogRead(potPin);

        float voltage = map(potValue, minADC, maxADC, minVoltage, maxVoltage);
        
        display.updateData(potValue/34.125);
        display.refreshDisplay();
    }
}
