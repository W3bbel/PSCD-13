#include "display.hpp"

void Display::refreshDisplay()
{
    xValue += 1;
    renderGraph();
    renderHeart();
    renderTemp();
    renderFall();
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

    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(10, 140);
    tft.print("Value:");

    graph.createGraph(GRAPHWIDTH, GRAPHHEIGHT, TFT_BLACK);
    
    graph.setGraphScale(0, GRAPHWIDTH, 0, GRAPHHEIGHT);
    graph.setGraphGrid(0, 10, 0, 10, TFT_DARKGREY);
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

void Display::renderTime()
{
}

void Display::renderHeart()
{
    tft.fillRect(HEARTX, HEARTY, 150, 20, TFT_BLACK);  //clear area
    tft.setCursor(HEARTX, HEARTY);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.printf("Value: %d", value);         
}

void Display::renderTemp()
{
    tft.fillRect(TEMPX, TEMPY, 150, 20, TFT_BLACK);  //clear area
    tft.setCursor(TEMPX, TEMPY);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.printf("Body temp: %d°C Ambient temp: %d°C", bodyTemp, ambientTemp);  
}

void Display::renderFall()
{
    tft.fillRect(FALLX, FALLY, 150, 20, TFT_BLACK);  //clear area
    tft.setCursor(FALLX, FALLY);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    if (fallDetected) tft.printf("You are falling!");
    else tft.printf("Not falling.");
}
