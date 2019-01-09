#ifndef AcceleroSensor_h
#define AcceleroSensor

#include "rpi-i2c.h"
#include "rpi-timer.h"
#include "rpi-uart.h"
#include <stdint.h>

#define SENS_SLAVE_ADRESS      (0xD6 >> 1) //on p30
//#define SENS_SLAVE_ADRESS_WRITE     (0xD6)

#define SENS_ACT_THS                (0x04)
#define SENS_ACT_DUR                (0x05)

#define SENS_INT_GEN_CFG_XL         (0x06)
#define SENS_INT_GEN_THS_X_XL       (0x07)
#define SENS_INT_GEN_THS_Y_XL       (0x08)
#define SENS_INT_GEN_THS_Z_XL       (0x09)
#define SENS_INT_GEN_DUR_XL         (0x0A)
/*#define SENS_REFERENCE_G            (0x0B) //niet nodig
#define SENS_INT1_CTRL              (0x0C)
#define SENS_INT2_CTRL              (0x0D)*/

#define SENS_WHO_AM_I               (0x0F)
#define SENS_STATUS_REG             (0x17)

#define SENS_CTRL_REG5_XL           (0x1F)
#define SENS_CTRL_REG6_XL           (0x20)
#define SENS_CTRL_REG7_XL           (0x21)
//#define SENS_CTRL_REG8              (0x22) 
/*In order to disable the I2C block for accelerometer and gyroscope the I2C_DISABLE bit
must be written to ‘1’ in CTRL_REG9 (23h), while for magnetometer the I2C_DISABLE bit
must be written to ‘1’ in CTRL_REG3_M (22h).*/
//#define SENS_CTRL_REG9              (0x23)
//#define SENS_CTRL_REG10             (0x24)
#define SENS_INT_GEN_SRC_XL         (0x26)
#define SENS_STATUS_REG_2           (0x27)
#define SENS_OUT_X_XL1              (0x28) //CHECK IF THIS IS ALLOWED
#define SENS_OUT_X_XL2              (0x29) //TWO 8-bit words in two's complement
#define SENS_OUT_Y_XL1              (0x2A)
#define SENS_OUT_Y_XL2              (0x2B)              
#define SENS_OUT_Z_XL1              (0x2C)
#define SENS_OUT_Z_XL2              (0x2D)

#define SENS_FIFO_CTRL              (0x2E)
#define SENS_FIFO_SRC               (0x2F)


struct Vector_Short {
    short x;
    short y;
    short z;
};


void writeRegister(unsigned int reg, unsigned int value);
unsigned int readRegister(unsigned int reg);
int acceleroSensor_begin();
struct Vector_Short readData();
void acceleroSensor_setup();
struct Vector_Short acceleroSensor_values();


#endif
