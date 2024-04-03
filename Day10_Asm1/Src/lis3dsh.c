/*
 * lis3dsh.c
 *
 *  Created on: Apr 3, 2024
 *      Author: pranav
 */

#include "lis3dsh.h"

// Accel IO Functions
void LIS_WriteIO(uint8_t reg, uint8_t data[], uint8_t size) {
	// enable slave
	SPI_CS_Enable();
	// write register address
	SPI_Transmit(reg);
	// write data byte(s)
	for(int i=0; i<size; i++)
		SPI_Transmit(data[i]);
	// disable slave
	SPI_CS_Disable();
}

void LIS_ReadIO(uint8_t reg, uint8_t data[], uint8_t size) {
	reg |= BV(7); /*bug fixed R=1 */
	// enable slave
	SPI_CS_Enable();
	// write register address
	SPI_Transmit(reg);
	// read data byte(s)
	for(int i=0; i<size; i++)
		data[i] = SPI_Receive();
	// disable slave
	SPI_CS_Disable();
}

// Accel Init
void LIS_Init(void) {
	// Initialize SPI
	SPI_Init();
	DelayMs(3);
	// Set Data rate and Enable axes
	uint8_t config = (LIS_DATARATE_25 | LIS_XYZ_ENABLE);
	LIS_WriteIO(LIS_CTRL_REG4_ADDR, &config, 1);
	DelayMs(3);
}

// Accel Get Raw Data
LIS_Data LIS_GetData(void) {
	uint8_t data[2];
	uint16_t x, y, z;
	// read x low and x high and combine to 16-bit x reading
	LIS_ReadIO(LIS_OUT_X_L_ADDR, data, 2);
	x = ((uint16_t)data[1] << 8) | data[0];
	// read y low and y high and combine to 16-bit y reading
	LIS_ReadIO(LIS_OUT_Y_L_ADDR, data, 2);
	y = ((uint16_t)data[1] << 8) | data[0];
	// read z low and z high and combine to 16-bit z reading
	LIS_ReadIO(LIS_OUT_Z_L_ADDR, data, 2);
	z = ((uint16_t)data[1] << 8) | data[0];
	// fill readings in struct and return
	LIS_Data val;
	val.x = x;
	val.y = y;
	val.z = z;
	return val;
}

// Accel if Ready
int LIS_DRdy(void) {
	uint8_t status;
	do {
		LIS_ReadIO(LIS_STATUS_ADDR, &status, 1);
	} while( (status & LIS_STATUS_XYZ_Msk) == 0 );
	return 1;
}

extern int xCal,yCal, zCal;

void LIS_DRdy_Calib(void){
	int ret2 = LIS_DRdy();
	int sample = 100;
	if(ret2) {
		for(int i = 0; i <= sample; i++)
		{
			LIS_Data val = LIS_GetData();
			xCal = xCal + val.x;
			yCal = yCal + val.y;
			zCal = zCal + val.z;
		}
		xCal = xCal/100;
		yCal = yCal/100;
		zCal = zCal/100;
	}
}




