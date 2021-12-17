#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS 2000

PulseOximeter pox;
float h = 0, o = 0;
int c = 0;
uint32_t tsLastReport = 0;

void setup()
{
    Serial.begin(9600);
    if (!pox.begin()) {
        Serial.println("Try reconnecting to the system");
        for(;;);
    }
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
}

void loop()
{
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate: ");
        if(round(h/c) > 10)
        Serial.print(round(h/c));
        else
        Serial.print("100");
        Serial.print("bpm / SpO2: ");
        Serial.print(round(o/c));
        Serial.println("%");
        tsLastReport = millis();
        h = 0, o = 0;
        c = 0;
    }
    else{
        h += pox.getHeartRate();
        o += pox.getSpO2();
        c++;
    }
}
