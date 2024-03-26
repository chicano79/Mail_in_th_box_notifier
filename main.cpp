#include "mbed.h"
#include "HX711.h"

#define WAIT_PERIOD 2000ms

DigitalOut LED_BLUE(PB_3);
HX711 scale(PA_12, PB_0); //PinName pinData, PinName pinSck, uint8_t gain

unsigned int get_bufferSzie(char *buf);

BufferedSerial Serial(USBTX, USBRX);

float calibration_factor = 120; //Adjust this value to calibrate the exact weight
int averageSamples = 100;

int temp;


char weight_val[32];

int main(void)
{
     
    scale.setScale(0);
    //temp = scale.tare(); //Reset the scale to 0

    scale.setOffset(8610038); //this was retrieved from initial caliberation...
    
    long zero_factor = scale.averageValue(averageSamples); // Take average of several readings to stabilize the measurement
     
    while (true) {
        scale.setScale(calibration_factor); 
        float weight = scale.getGram();

        sprintf(weight_val, "Weight is: %d Grms\r\n",  (int)weight);
        Serial.write(weight_val, get_bufferSzie(weight_val));

        LED_BLUE = !LED_BLUE;

        ThisThread::sleep_for(WAIT_PERIOD);
    }
}


unsigned int get_bufferSzie(char *buf) {

    unsigned int count = 0;

    while(*(buf++) != '\0') {
        ++count;
    }
    
    return count;
}