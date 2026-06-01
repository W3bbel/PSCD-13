#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <TFT_eSPI.h>
#include <TFT_eWidget.h>

#define GRAPHX 10
#define GRAPHY 10
#define GRAPHWIDTH 300
#define GRAPHHEIGHT 120

#define TIMEX 1
#define TIMEY 1

#define HEARTX 10
#define HEARTY 140

#define TEMPX 10
#define TEMPY 160

#define FALLX 10
#define FALLY 200

class Display {
public:
    void refreshDisplay();
    void updateData(int newVal);
    void setupDisplay();
private:
    void renderGraph();
    void renderTime();
    void renderHeart();
    void renderTemp();
    void renderFall();

    int value = 0;
    int xValue = 0;
    time_t timestamp;
    int bodyTemp = 0;
    int ambientTemp = 0;
    bool fallDetected = false;

    TFT_eSPI tft = TFT_eSPI();
    GraphWidget graph = GraphWidget(&tft);
    TraceWidget trace = TraceWidget(&graph);
};

#endif