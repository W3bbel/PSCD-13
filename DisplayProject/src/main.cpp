#include <TFT_eSPI.h>
#include <TFT_eWidget.h>
#include "display.hpp"
#include "sensorrecord.hpp"

Display display;

extern "C" void app_main(void) {
    display.setupDisplay();
    static float x = 0;
    static unsigned long lastAdd = 0;
    sensor_record values;
    
    //point added every 100ms
    while (1)
    {
        if (millis() - lastAdd >= 100) {
            lastAdd = millis();
            display.updateData(values);
            display.refreshDisplay();
        }
    }
    return;
}