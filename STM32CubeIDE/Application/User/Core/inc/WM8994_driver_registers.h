#ifndef INC_WM8994_DRIVER_REGISTERS_H_
#define INC_WM8994_DRIVER_REGISTERS_H_

#define SEQUENCER	(uint16_t)0x110

typedef struct {
    uint16_t address;
    uint16_t value;
    uint8_t VU;
    uint16_t delay;
    uint8_t IO;
} WM8994_Register;

static const WM8994_Register RegisterList[] = {

	{.address = 0x102, .value = 0x0003, .VU = 0, .delay = 0, .IO = 0},	//0 Hardware bug fix
	{.address = 0x817, .value = 0x0000, .VU = 0, .delay = 0, .IO = 0},	//1 Hardware bug fix
	{.address = 0x102, .value = 0x0000, .VU = 0, .delay = 0, .IO = 0},	//2 Hardware bug fix
	{.address = 0x0039, .value = 0x006C, .VU = 0, .delay = 20, .IO = 0},//3 R57: VMID_BUF_ENA
	{.address = 0x0001, .value = 0x0013, .VU = 0, .delay = 20, .IO = 0},//4 R1: BIAS/VMID

		{.address = 0x0028, .value = 0x0011, .VU = 0, .delay = 0, .IO = 1},	//5 R40: IN1N to IN1
		{.address = 0x0029, .value = 0x0020, .VU = 0, .delay = 0, .IO = 1},	//6 R41: MIXER L links and volume
		{.address = 0x002A, .value = 0x0020, .VU = 0, .delay = 0, .IO = 1},	//7 R42: MIXER R links and volume
		{.address = 0x0004, .value = 0x0303, .VU = 0, .delay = 0, .IO = 1},	//8 R4: ADC L/R power + path to AIF1 enable

			{.address = 0x0005, .value = 0x0303, .VU = 0, .delay = 0, .IO = 2},	//0 R5: AFI1DAC1 LR and DACs
			{.address = 0x0601, .value = 0x0001, .VU = 0, .delay = 0, .IO = 2},	//1 R1537: AIF1 Time slot 0 (Left) to DAC 1 (Left) mixer path
			{.address = 0x0602, .value = 0x0001, .VU = 0, .delay = 0, .IO = 2},	//2 R1537: AIF1 Time slot 0 (Right) to DAC 1 (Right) mixer path
			{.address = 0x0604, .value = 0x0000, .VU = 0, .delay = 0, .IO = 2},	//3 R1540: DAC 2 path disable L
			{.address = 0x0605, .value = 0x0000, .VU = 0, .delay = 0, .IO = 2},	//4 R1541: DAC 2 path disable R

	{.address = 0x0440, .value = 0x00DB, .VU = 0, .delay = 0, .IO = 0},	//9	DRC
	{.address = 0x0410, .value = 0x1800, .VU = 0, .delay = 0, .IO = 0},	//10 HPF filter

		{.address = 0x0002, .value = 0x6350, .VU = 0, .delay = 0, .IO = 1},	//11 R2: Power IN1L/R and MIXERL/R
		{.address = 0x0018, .value = 0x010B, .VU = 1, .delay = 0, .IO = 1},	//12 R24: IN1L volume (def 10b)
		{.address = 0x001A, .value = 0x010B, .VU = 1, .delay = 0, .IO = 1},	//13 R26: IN1R volume
		{.address = 0x0606, .value = 0x0002, .VU = 0, .delay = 0, .IO = 1},	//14 R1542: Route L ADC to AIF1
		{.address = 0x0607, .value = 0x0002, .VU = 0, .delay = 0, .IO = 1},	//15 R1543: Route R ADC to AIF1

	  		{.address = 0x002D, .value = 0x0100, .VU = 0, .delay = 0, .IO = 2},	//5 R45: Select DAC1 (Left) to Left Headphone Output PGA (HPOUT1LVOL) path
			{.address = 0x002E, .value = 0x0100, .VU = 0, .delay = 0, .IO = 2},	//6 R46: Select DAC1 (Right) to Right Headphone Output PGA (HPOUT1RVOL) path
			{.address = 0x0110, .value = 0x8100, .VU = 0, .delay = 300, .IO = 2},//7 Sequence write: Cold start up for headphones ?
			{.address = 0x0420, .value = 0x0000, .VU = 0, .delay = 0, .IO = 2},	//8 R1056: Soft un-Mute the AIF1 Time slot 0 DAC1 path L&R
			{.address = 0x0051, .value = 0x0005, .VU = 0, .delay = 0, .IO = 2},	//9 R81: Class W envelope   ?????
			{.address = 0x0001, .value = 0x0303, .VU = 0, .delay = 0, .IO = 2},	//10 R1:Enable bias generator, Enable VMID, Enable HPOUT1 (Left) and Enable HPOUT1 (Right) input stages
			{.address = 0x0060, .value = 0x0022, .VU = 0, .delay = 0, .IO = 2},	//11 R96: Enable HPOUT1 (Left) and HPOUT1 (Right) intermediate stages
			{.address = 0x004C, .value = 0x9F25, .VU = 0, .delay = 20, .IO = 2},//12 R76 Enable Charge Pump   ??????

			//{.address = 0x0054, .value = 0x0033, .VU = 0, .delay = 0, .IO = 2},//13 Enable DC and trigger start-up mode on left and right channels
			{.address = 0x0060, .value = 0x00EE, .VU = 0, .delay = 0, .IO = 2},	//14 Enable HPOUT1 (Left) and HPOUT1 (Right) intermediate and output stages. Remove clamps
			{.address = 0x001C, .value = 0x0179, .VU = 1, .delay = 0, .IO = 2},	//18 R28 HPOUT1L VOL
			{.address = 0x001D, .value = 0x0179, .VU = 1, .delay = 0, .IO = 2},	//19 R29 HLOUT1R VOL
			{.address = 0x0610, .value = 0x01C0, .VU = 1, .delay = 0, .IO = 2},	//15 Un-mute DAC 1 (Left)
			{.address = 0x0611, .value = 0x01C0, .VU = 1, .delay = 0, .IO = 2},	//16 Un-mute DAC 1 (Right)
			{.address = 0x0420, .value = 0x0010, .VU = 0, .delay = 0, .IO = 2},	//17 Un-mute the AIF1 Time slot 0 DAC path


	{.address = 0x0700, .value = 0x000D, .VU = 0, .delay = 0, .IO = 0},	//16 DRC in GPIO as output interrupt
	{.address = 0x0210, .value = 0x0083, .VU = 0, .delay = 0, .IO = 0},	//17 R528: AIF1 Rate
	{.address = 0x0300, .value = 0x4050, .VU = 0, .delay = 0, .IO = 0}, //18 AIF1 Control: I2S, 24-bit
	{.address = 0x0302, .value = 0x0000, .VU = 0, .delay = 0, .IO = 0}, //19 Slave mode
	{.address = 0x0208, .value = 0x000A, .VU = 0, .delay = 0, .IO = 0}, //20 Enable AIF1 DSP + core digital clocks
	{.address = 0x0200, .value = 0x0001, .VU = 0, .delay = 0, .IO = 0}, //21 Enable AIF1 clock (MCLK1)


		{.address = 0x0400, .value = 0x01C0, .VU = 1, .delay = 0, .IO = 1},	//22 R1024 AIF1 ADC1 L Volume
		{.address = 0x0401, .value = 0x01C0, .VU = 1, .delay = 0, .IO = 1},	//23 R1025 AIF1 ADC1 R Volume
};

#endif /* INC_WM8994_DRIVER_REGISTERS_H_ */
