#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <TFT_eSPI.h>
#include <TFT_eWidget.h>
#include "sensorrecord.hpp"

#define GRAPHX 10
#define GRAPHY 10
#define GRAPHWIDTH 300
#define GRAPHHEIGHT 120

#define TIMEX 10
#define TIMEY 220

#define HEARTX 10
#define HEARTY 140

#define TEMPX 10
#define TEMPY 160

#define FALLX 10
#define FALLY 200

class Display {
public:
    void refreshDisplay();
    void updateData(sensor_record newVal);
    void setupDisplay();
private:
    void renderGraph();
    void renderTime();
    void renderHeart();
    void renderTemp();
    void renderFall();

    sensor_record values;
    int xValue = 0;

    TFT_eSPI tft = TFT_eSPI();
    GraphWidget graph = GraphWidget(&tft);
    TraceWidget trace = TraceWidget(&graph);
};

#endif