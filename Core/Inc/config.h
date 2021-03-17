#ifndef CONFIG_H_
#define CONFIG_H_

// IMU config
#include "mpu9250.h"
// ? ADD SMPLRT_DIV
static MPU9250_config mpu9250_default_config =
{
	{90.0f, 90.0f, 90.0f},	// Euler offsets
	MPU9250_AFS_2G,		// Ascale
	MPU9250_GFS_250DPS, // Gscale
	MPU9250_MFS_16BITS, // Mscale
	MPU9250_MMODE_100,	// Mmode
	
	true,				// force calibration on startup
	{12.381678, 12.381678, -923.776245},	// magbias[3]
	{0.862595, 2.022901, -1.541985},	// gyroBias[3]
	{-83.557129 / 1000.0, 5.432129 / 1000.0, 139.282227 / 1000.0},	// accelBias[3]

	-1,					// alg_rate [Hz]
	100.0				// euler_rate [Hz]
};

#include "stm32f4xx_hal.h"
// Pressure sensor config
#define SEA_PRESSURE 1013	// pressure at sea level [hPa]

// Timing parameters [ms]
#define DATA_PRINT_DELAY 1000
#define LOG_SAVE_DELAY 2373
#define LOG_BMP_DELAY 100
#define LOG_IMU_DELAY 100
#define LOG_MOT_DELAY 100
#define LOG_GPS_DELAY 2000
#define LOG_TARGET_YAW_DELAY 1000
// Radio timeout value is set in SX1278 config 
#define SENSING_BMP_DELAY 50

// Peripherial state
#define BMP_TOP_ENABLE 1
#define BMP_BTM_ENABLE 1
#define BUZZER_ENABLE 1
#define SD_ENABLE 1
#define RADIO_ENABLE 1
#define GPS_ENABLE 1
#define MPU_ENABLE 1

// Debug messages
#define RUN_DEBUG 1
#define LOGING_DEBUG 0
#define LOGING_PRINT_DATA 1
#define LOGING_PRINT_SENSORS 1
#define LOGING_PRINT_RADIO 1
#define LOGING_PRINT_INFO 1
#define DUPLEX_DEBUG 1
#define SENSING_DEBUG 1
#define STEERING_DEBUG 0

// GPS default values
#define DEFAULT_LAT 50
#define DEFAULT_LONG 19
#define DEFAULT_ALT 250


#endif /* CONFIG_H_ */
