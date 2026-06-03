#include "display.hpp"

void Display::refreshDisplay()
{
    xValue += 1;
    renderGraph();
    tft.fillRect(DATAX, 131, 150, 110, TFT_BLACK);
    renderHeart();
    renderTemp();
    renderWorkout();
}

void Display::updateData(sensor_record newVal)
{
    values = newVal;
}

void Display::setupDisplay()
{
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(HEARTX, HEARTY);
    tft.printf("Heart Rate:");
    tft.setCursor(TEMPX, TEMPY);
    tft.printf("Body Temp:");
    tft.setCursor(WORKX, WORKY);
    tft.printf("Workout Mode:");

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

    trace.addPoint(xValue, values.heart_rate_bpm);
}

void Display::renderHeart()
{
    tft.setCursor(DATAX, HEARTY);
    tft.printf("%d BPM", values.heart_rate_bpm);         
}

void Display::renderTemp()
{
    tft.setCursor(DATAX, TEMPY);
    tft.printf("%dC", values.skin_temp_c);  
}

void Display::renderWorkout()
{
    tft.setCursor(DATAX, WORKY);
    if (values.workout_mode) tft.printf("ON");
    else tft.printf("OFF");
}
