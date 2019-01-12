#include "AcceleroSensor.h"
#include <stdio.h>
#include <math.h>
struct Vector_Short r;
#define sensitivity (0.000061)

typedef int bool;
#define true 1
#define false 0

//Used Arduino library: https://github.com/sparkfun/SparkFun_LSM9DS1_Arduino_Library/tree/master/src?fbclid=IwAR1H9gLeBL78jaVXri4p0c1R4uzGLJc_oBsL6kuxXn2zOwDZPXpomcNJgWI


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


void readAccel()
{
    unsigned int data[] = {(SENS_OUT_X_XL1 | (1 << 7))};
    unsigned int buffer[6];

    write_bytes(SENS_SLAVE_ADRESS, data, 1);

    read_bytes(SENS_SLAVE_ADRESS, buffer, 6);
    r.x = (buffer[1] << 8) | buffer[0]; // Store x-axis values into ax
    r.y = (buffer[3] << 8) | buffer[2]; // Store y-axis values into ay
    r.z = (buffer[5] << 8) | buffer[4]; // Store z-axis values into az
    
    /* //geen idee wat het moet doen
    ax -= aBiasRaw[X_AXIS];
    ay -= aBiasRaw[Y_AXIS];
    az -= aBiasRaw[Z_AXIS];
	*/
}

void enableFIFO(bool enable)
{
	unsigned int temp = readRegister(SENS_CTRL_REG9);
	if (enable) temp |= (1<<1);
	else temp &= ~(1<<1);
	writeRegister(SENS_CTRL_REG9, temp);
}

void setFIFO(fifoMode_type fifoMode, unsigned int fifoThs)
{
	// Limit threshold - 0x1F (31) is the maximum. If more than that was asked
	// limit it to the maximum.
	unsigned int threshold = fifoThs <= 0x1F ? fifoThs : 0x1F;
	writeRegister(SENS_FIFO_CTRL, ((fifoMode & 0x7) << 5) | (threshold & 0x1F));
}

void calibrate()
{  
	unsigned int data[6] = {0, 0, 0, 0, 0, 0};
	unsigned int samples = 0;
	int i, j;
	int aBiasRawTemp[3] = {0, 0, 0};
    uprintf("before enable FIFO!\n\r");
	
	// Turn on FIFO and set threshold to 32 samples
	enableFIFO(true);
    uprintf("between enable FIFO and setFIFO!\n\r");
	setFIFO(FIFO_THS, 0x1F);
	while (samples < 0x1F)
	{
		samples = (readRegister(SENS_FIFO_SRC) & 0x3F); // Read number of stored samples
	}
	for(i = 0; i < samples ; i++) 
	{	// Read the gyro data stored in the FIFO
		readAccel();
		aBiasRawTemp[0] += r.x;
		aBiasRawTemp[1] += r.y;
		aBiasRawTemp[2] += r.z - (1./sensitivity); // Assumes sensor facing up!
	}  
	for (j = 0; j < 3; j++)
	{
		aBiasRaw[j] = aBiasRawTemp[j] / samples;
		aBias[j] = aBiasRaw[j]*sensitivity;
	}
	
	enableFIFO(false);
	setFIFO(FIFO_OFF, 0x00);
	
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
    
    writeRegister(SENS_CTRL_REG4, 0b00000000); //Gyroscope disabled
    writeRegister(SENS_CTRL_REG5_XL, 0b01111000);//update every 2 sample, accelerometer activated on all axis //inputs the value of what the register should be (p51)
    writeRegister(SENS_CTRL_REG6_XL, 0b10100000); //Output data rate, chosen: 
    writeRegister(SENS_CTRL_REG7_XL, 0b00000000); //No filters are added
    writeRegister(SENS_CTRL_REG8, 0b00000100); //More settings
    writeRegister(SENS_CTRL_REG9, 0b00000010); //FIFO memory enabled
    writeRegister(SENS_CTRL_REG10, 0b00000000); //self test disabled
    
    uprintf("Begin calibrate!\n\r");
    //calibrate();
    uprintf("End calibrate!\n\r"); 

    return 1;
}

void acceleroSensor_setup() {    
    //uprintf("Initializing acceleroSensor\n\r");
    while(!acceleroSensor_begin()) {
        uprintf("Could not find a valid sensor, check wiring!\n");
        delay_ms(200);
    }
    //uprintf("acceleroSensor ready\n");
}
