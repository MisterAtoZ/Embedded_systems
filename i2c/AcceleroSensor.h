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
#define SENS_REFERENCE_G            (0x0B) //niet nodig
#define SENS_INT1_CTRL              (0x0C)
#define SENS_INT2_CTRL              (0x0D)

#define SENS_WHO_AM_I               (0x0F)
#define SENS_STATUS_REG             (0x17)

#define SENS_CTRL_REG4					(0x1E)
#define SENS_CTRL_REG5_XL           (0x1F)
#define SENS_CTRL_REG6_XL           (0x20)
#define SENS_CTRL_REG7_XL           (0x21)
#define SENS_CTRL_REG8              (0x22) 
/*In order to disable the I2C block for accelerometer and gyroscope the I2C_DISABLE bit
must be written to ‘1’ in CTRL_REG9 (23h), while for magnetometer the I2C_DISABLE bit
must be written to ‘1’ in CTRL_REG3_M (22h).*/
#define SENS_CTRL_REG9              (0x23)
#define SENS_CTRL_REG10             (0x24)
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

short aBiasRaw[3];
float aBias[3];

typedef int bool;
#define true 1
#define false 0

// accel_scale defines all possible FSR's of the accelerometer:
enum accel_scale
{
	A_SCALE_2G,	// 00:  2g
	A_SCALE_16G,// 01:  16g
	A_SCALE_4G,	// 10:  4g
	A_SCALE_8G	// 11:  8g
};

// accel_oder defines all possible output data rates of the accelerometer:
enum accel_odr
{
	XL_POWER_DOWN, 	// Power-down mode (0x0)
	XL_ODR_10,		// 10 Hz (0x1)
	XL_ODR_50,		// 50 Hz (0x02)
	XL_ODR_119,		// 119 Hz (0x3)
	XL_ODR_238,		// 238 Hz (0x4)
	XL_ODR_476,		// 476 Hz (0x5)
	XL_ODR_952		// 952 Hz (0x6)
};

// accel_abw defines all possible anti-aliasing filter rates of the accelerometer:
enum accel_abw
{
	A_ABW_408,		// 408 Hz (0x0)
	A_ABW_211,		// 211 Hz (0x1)
	A_ABW_105,		// 105 Hz (0x2)
	A_ABW_50    	//  50 Hz (0x3)
};

enum interrupt_select
{
	XG_INT1 = SENS_INT1_CTRL,
	XG_INT2 = SENS_INT2_CTRL
};

enum interrupt_generators
{
	INT_DRDY_XL = (1<<0),	 // Accelerometer data ready (INT1 & INT2)
	INT_DRDY_G = (1<<1),	 // Gyroscope data ready (INT1 & INT2)
	INT1_BOOT = (1<<2),	 // Boot status (INT1)
	INT2_DRDY_TEMP = (1<<2),// Temp data ready (INT2)
	INT_FTH = (1<<3),		 // FIFO threshold interrupt (INT1 & INT2)
	INT_OVR = (1<<4),		 // Overrun interrupt (INT1 & INT2)
	INT_FSS5 = (1<<5),		 // FSS5 interrupt (INT1 & INT2)
	INT_IG_XL = (1<<6),	 // Accel interrupt generator (INT1)
	INT1_IG_G = (1<<7),	 // Gyro interrupt enable (INT1)
	INT2_INACT = (1<<7)	 // Inactivity interrupt output (INT2)
};	

enum accel_interrupt_generator
{
	XLIE_XL = (1<<0),
	XHIE_XL = (1<<1),
	YLIE_XL = (1<<2),
	YHIE_XL = (1<<3),
	ZLIE_XL = (1<<4),
	ZHIE_XL = (1<<5),
	GEN_6D = (1<<6)
};

enum h_lactive
{
	INT_ACTIVE_HIGH,
	INT_ACTIVE_LOW
};

enum pp_od
{
	INT_PUSH_PULL,
	INT_OPEN_DRAIN
};

typedef enum 
{
	FIFO_OFF = 0,
	FIFO_THS = 1,
	FIFO_CONT_TRIGGER = 3,
	FIFO_OFF_TRIGGER = 4,
	FIFO_CONT = 5
} fifoMode_type;

struct accelSettings //Mag missch ook weg!
{
	// Accelerometer settings:
    uint8_t enabled;
    uint8_t scale;
    uint8_t sampleRate;
	// New accel stuff:
	uint8_t enableX;
	uint8_t enableY;
	uint8_t enableZ;
	int8_t  bandwidth;
	uint8_t highResEnable;
	uint8_t highResBandwidth;
};

void writeRegister(unsigned int reg, unsigned int value);
unsigned int readRegister(unsigned int reg);
int acceleroSensor_begin();
struct Vector_Short readData();
void acceleroSensor_setup();
struct Vector_Short acceleroSensor_values();
void readAccel();
void enableFIFO(bool enable);
void setFIFO(fifoMode_type fifoMode, unsigned int fifoThs);
void calibrate();

#endif
