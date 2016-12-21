#include <cstdio>
#include <cstdlib>
#include "V8.h"

void printV8(const V8::Emulator &emu)
{
	printf("\nPC\t");
	for (int i = 0; i < 16; i++)
		printf("R%1X\t", i);
	printf("\n%02X\t", emu.getProgramCounter());
	for (int i = 0; i < 16; i++)
		printf("%02X\t", emu.getRegister(i));
	printf("\n\n");
	
	printf("MEM\t");
	for (int i = 0; i < 16; i++)
		printf("x%1X\t", i);
	printf("\n");
	for (int i = 0; i < 16; i++)
	{
		printf("%1Xx:\t", i);
		for (int j = 0; j < 16; j++)
		{
			printf("%02X\t", emu.getMemory(i * 8 + j));
		}
		printf("\n");
	}
	printf("\n");
}

void printByStep(V8::Emulator &emu)
{
	system("clear");
	printf("\nINITIAL STATUS:\n\n");
	printV8(emu);
	getchar();
	while (emu.step())
	{
		printV8(emu);
		getchar();
	}
	printV8(emu);
	printf("HALT.\n\n");
}

int main()
{
	V8::Emulator emu;
	/*
	// Test #1
	uint8_t code[256] = { 0x21, 0x34, 0x22, 0x18, 0x50, 0x12, 0xc0, 0x00 };
	emu.loadCode(code, 8);
	emu.run();
	printV8(emu);
	printf("DONE.\n\n");
	getchar();
	*/
	// Test #2
	uint8_t rom[256];
	
	for (int i =0; i<256;i++)
	{
		scanf("%02X", rom + i);
	}
	emu.reset();
	emu.loadMemory(rom);
	emu.run();
	printV8(emu);
	
	return 0;
}