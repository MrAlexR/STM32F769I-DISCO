#ifndef INC_WM8994_DRIVER_H_
#define INC_WM8994_DRIVER_H_

#include "main.h"
#include "WM8994_driver_registers.h"
#include <string.h>

#define WM8994_I2C_ADDR_7BIT   0x1A
#define WM8994_I2C_ADDR_HAL    (WM8994_I2C_ADDR_7BIT << 1)
#define WM8994_HARDWARE_ID	   0x8994

#define INPUT_LINE_IN	(uint16_t)0x1
#define OUTPUT_HEADPHONES (uint16_t)0x2

extern I2C_HandleTypeDef hi2c4;

typedef struct {
	uint16_t error;
    uint16_t address;
    uint16_t setValue;
    uint16_t actualValue;
} WM8994_Init_Error;

WM8994_Init_Error WM8994_Driver_Init(uint16_t options);
WM8994_Init_Error WM8994_Write_Config(uint16_t IO_side);
HAL_StatusTypeDef WM8994_WriteReg(uint16_t reg, uint16_t value);
HAL_StatusTypeDef WM8994_ReadReg(uint16_t reg, uint16_t *value);
HAL_StatusTypeDef WM8994_Driver_SoftwareReset();

#endif /* INC_WM8994_DRIVER_H_ */
