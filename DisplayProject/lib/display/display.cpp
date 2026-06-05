#include "display.hpp"

void Display::refreshDisplay()
{
    xValue += 1;
    if (!renderEmergency()){
        tft.fillRect(DATAX, 151, 90, 110, TFT_BLACK);
        if (values.heart_rate_valid){
            renderGraph();
            renderHeart();
        }
        if (values.skin_temp_valid) renderTemp();
        renderWorkout();
    }
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

    tft.setTextSize(1);
    tft.setCursor(GRAPHX+GRAPHWIDTH+2, GRAPHY-4);
    tft.printf("180");
    tft.setCursor(GRAPHX+GRAPHWIDTH+2, (GRAPHY+GRAPHHEIGHT)/2);
    tft.printf("BPM");
    tft.setCursor(GRAPHX+GRAPHWIDTH+2, GRAPHY+GRAPHHEIGHT-4);
    tft.printf("40");

    trace.startTrace(TFT_GREEN);
    tft.setTextSize(2);
}

void Display::renderGraph()
{
    if (xValue > GRAPHWIDTH) { //graph reset
        xValue = 0;
        graph.drawGraph(GRAPHX, GRAPHY);
        trace.startTrace(TFT_GREEN);
    }

    trace.addPoint(xValue, values.heart_rate_bpm - GRAPHMIN);
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

bool Display::renderEmergency()
{
    if (values.abnormal_heart_rate || values.fall_detected || values.panic_pressed){
        tft.fillRect(DATAX + 90, 151, 40, 110, TFT_BLUE);
        return true;
    }
    tft.fillRect(DATAX + 90, 151, 40, 110, TFT_BLACK);
    return false;
}
