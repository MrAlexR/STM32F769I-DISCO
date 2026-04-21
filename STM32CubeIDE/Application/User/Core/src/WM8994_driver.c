#include "WM8994_driver.h"

HAL_StatusTypeDef WM8994_ReadReg(uint16_t reg, uint16_t *value)
{
    uint8_t data[2];

    //	Send data request to audio board
    HAL_StatusTypeDef status = HAL_I2C_Master_Receive(&hi2c4, WM8994_I2C_ADDR_HAL, data, sizeof(data), HAL_MAX_DELAY);
    if (status != HAL_OK)
        return 1;
    //	Convert uint8_t to uint16_t
    *value = (uint16_t)(data[0] << 8) | data[1];
    return HAL_OK;
}

HAL_StatusTypeDef WM8994_WriteReg(uint16_t reg, uint16_t value)
{
	//	Convert register address from uint16_t to uint8_t
	uint8_t data[4];
	data[0] = (reg >> 8) & 0xFF;
	data[1] = reg & 0xFF;

	//	Convert register value from uint16_t to uint8_t
	data[2] = (value >> 8) & 0xFF;
	data[3] = value & 0xFF;

	//	Send data to audio board
	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c4, WM8994_I2C_ADDR_HAL, data, sizeof(data), HAL_MAX_DELAY);
	if (status != HAL_OK)
		return 1;

	return HAL_OK;
}


HAL_StatusTypeDef WM8994_Driver_SoftwareReset()
{
	// R0: Reset register
	WM8994_Register R0 = {.address = 0x00, .value = 0x8994}; //Software reset register
	uint16_t value;
	//Write to R0 to reset device
	HAL_StatusTypeDef status = WM8994_WriteReg(R0.address, 0x0000);
	if (status != HAL_OK)
			return 1;
	// Read device family/ID
	status = WM8994_ReadReg(R0.address, &value);
	if (status != HAL_OK)
			return 1;
	//Check device ID
	if(value != WM8994_HARDWARE_ID) return 1;

    return 0;
}

WM8994_Init_Error WM8994_Driver_Init(uint16_t options)
{
	// Error status clear
	WM8994_Init_Error init_status = {.address = 0, .error = 0, .actualValue = 0, .setValue = 0};

	// Software Reset
	HAL_StatusTypeDef status = WM8994_Driver_SoftwareReset();
	if (status != HAL_OK)
	{
		init_status.error = 1;
		return init_status;
	}
	HAL_Delay(20);

	// Write configured registers
	init_status = WM8994_Write_Config(options);

	return init_status;
}

WM8994_Init_Error WM8994_Write_Config(uint16_t IO_side)
{
	WM8994_Init_Error init_status = {.address = 0, .error = 0, .actualValue = 0, .setValue = 0};
	HAL_StatusTypeDef status = HAL_OK;
	uint16_t REG_LIST_LEN = sizeof(RegisterList) / sizeof(RegisterList[0]);
	uint16_t value = 0;

	for(uint16_t i = 0; i < REG_LIST_LEN; i++)
	{
		// Enable only necessary registers (input and/or output)
		if(RegisterList[i].IO == 1 && !(IO_side & 0x1))	continue;	// Skip registers for input
		if(RegisterList[i].IO == 2 && !(IO_side & 0x2))	continue;	// Skip registers for output

		// Write register
		status = WM8994_WriteReg(RegisterList[i].address, RegisterList[i].value);
		if (status != HAL_OK)
		{
			init_status.error = i + 100;
			init_status.address = RegisterList[i].address;
			return init_status;
		}
		// Extra delay per register
		HAL_Delay(RegisterList[i].delay);
		HAL_Delay(10);

		// If we write to Write Sequencer, skip check
		if(RegisterList[i].address == SEQUENCER) continue;

		// Read register value
		status = WM8994_ReadReg(RegisterList[i].address, &value);
		if (status != HAL_OK)
		{
			init_status.error = i + 200;
			init_status.address = RegisterList[i].address;
			return init_status;
		}

		//	Mask the VU bits
		if(RegisterList[i].VU)	value = value | 0x0100;
		// Check register value
		if(value != RegisterList[i].value)
		{
			init_status.error = i + 300;
			init_status.address = RegisterList[i].address;
			init_status.setValue = RegisterList[i].value;
			init_status.actualValue = value;
			return init_status;
		}
	}

	return init_status;
}




