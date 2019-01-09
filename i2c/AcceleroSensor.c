#include "AcceleroSensor.h"
#include <stdio.h>
#include <math.h>
struct Vector_Short r;



void writeRegister(unsigned int reg, unsigned int value) {
    unsigned int data[] = {reg, value};
    write_bytes(SENS_SLAVE_ADRESS, data, 2);
}

unsigned int readRegister(unsigned int reg) {
    unsigned int buffer[1];
    unsigned int data[] = {reg};
    write_bytes(SENS_SLAVE_ADRESS, data, 1);
    read_bytes(SENS_SLAVE_ADRESS, buffer, 1);
    return buffer[0];
}

int acceleroSensor_begin() {
    //uprintf("Starting acceleroSensor_begin\n");

    /*int who = readRegister(SENS_WHO_AM_I);
    uprintf("The WHO register is: %d", (int)who);
    uprintf("\n\r");*/
    if (readRegister(SENS_WHO_AM_I) != 0x68) { 
        return 0;
    }

    unsigned int reg1 = 0x00;
    reg1 |= 0x0F;
    //reg1 |= (odrbw << 4);

    writeRegister(SENS_CTRL_REG5_XL, 0b01111000);//update every 2 sample, accelerometer activated on all axis //inputs the value of what the register should be (p51)
    writeRegister(SENS_CTRL_REG6_XL, 0b00000000); //All on default values
    writeRegister(SENS_CTRL_REG7_XL, 0b00000000); //No filters are added
   /* writeRegister(SENS_CTRL_REG8, 0b00000100); //More settings
    writeRegister(SENS_CTRL_REG9, 0b00000010);//0b00000010); //FIFO memory enabled
    writeRegister(SENS_CTRL_REG10, 0b00000000); //self test disabled*/

    return 1;
}

struct Vector_Short readData() {
    unsigned int data[] = {(SENS_OUT_X_XL1 | (1 << 7))};
    unsigned int buffer[6];

    write_bytes(SENS_SLAVE_ADRESS, data, 1);

    read_bytes(SENS_SLAVE_ADRESS, buffer, 6);
    //uprintf("In readData accelero\n");
    r.x = (buffer[1] << 8 | buffer[0]);// & 0xFFFF;
    r.y = (buffer[3] << 8 | buffer[2]);// & 0xFFFF;
    r.z = (buffer[5] << 8 | buffer[4]);// & 0xFFFF;
    uprintf("r.x: %dm/s² ", (int)r.x);
    uprintf("r.y: %dm/s² ", (int)r.y);
    uprintf("r.z: %dm/s² ", (int)r.z);
    uprintf("\n\r");
    return r;
}

void acceleroSensor_setup() {    
    //uprintf("Initializing acceleroSensor\n\r");
    while(!acceleroSensor_begin()) {
        uprintf("Could not find a valid sensor, check wiring!\n");
        delay_ms(200);
    }
    //uprintf("acceleroSensor ready\n");
}


struct Vector_Short acceleroSensor_values() {
   // unsigned int new_time = get_time_us();
    struct Vector_Short values = readData();

    uprintf("Acceleration ");
    uprintf("x: %dm/s² ", (int)values.x);
    uprintf("y: %dm/s² ", (int)values.y);
    uprintf("z: %dm/s² ", (int)values.z);
    uprintf("\n\r");

    return values;
}

