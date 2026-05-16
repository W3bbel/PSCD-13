#include "display.hpp"

void Display::refreshDisplay()
{
    xValue += 1;
    renderGraph();
    renderText();
}

void Display::updateData(int newVal)
{
    value = newVal;
}

void Display::setupDisplay()
{
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(10, 140);
    tft.print("Value:");

    graph.createGraph(GRAPHWIDTH, GRAPHHEIGHT, TFT_BLACK);
    
    // Scale: X from 0 to 300 (width), Y from 0 to 4095 (ADC range)
    graph.setGraphScale(0, GRAPHWIDTH, 0, GRAPHHEIGHT);
    graph.setGraphGrid(0, 10, 0, 10, TFT_DARKGREY); //Y grid 400 units
    graph.drawGraph(GRAPHX, GRAPHY);
    
    trace.startTrace(TFT_GREEN);
}

void Display::renderGraph()
{
    if (xValue > GRAPHWIDTH) { //graph reset
        xValue = 0;
        graph.drawGraph(GRAPHX, GRAPHY);
        trace.startTrace(TFT_GREEN);
    }

    trace.addPoint(xValue, value);
}

void Display::renderText()
{
    tft.fillRect(10, 140, 150, 10, TFT_BLACK);  //clear area
    tft.setCursor(10, 140);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.printf("Value: %d", value);         
}
