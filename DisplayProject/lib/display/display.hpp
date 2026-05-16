#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <TFT_eSPI.h>
#include <TFT_eWidget.h>

#define GRAPHX 10
#define GRAPHY 10
#define GRAPHWIDTH 300
#define GRAPHHEIGHT 120

class Display {
public:
    void refreshDisplay();
    void updateData(int newVal);
    void setupDisplay();
private:
    void renderGraph();
    void renderText();

    int value = 0;
    int xValue = 0;
    TFT_eSPI tft = TFT_eSPI();
    GraphWidget graph = GraphWidget(&tft);
    TraceWidget trace = TraceWidget(&graph);
};

#endif