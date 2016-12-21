//
// Created by Mike Smith on 2016/12/19.
//

#ifndef FX_V8_H
#define FX_V8_H

#include <cstdint>
#include <cstddef>

namespace V8
{
	enum V8_SPEC
	{
		MEMORY_SIZE = 256,
		REGISTER_NUMBER = 16
	};
	
	class Emulator
	{
	private:
		uint8_t _mem[MEMORY_SIZE];
		int _pc;
		uint8_t _r[REGISTER_NUMBER];
		
		static inline uint8_t addf(uint8_t a, uint8_t b);
	
	public:
		Emulator(const uint8_t *mem = NULL, const uint8_t *r = NULL, int pc = 0);
		void reset(void);
		void loadCode(uint8_t *code, int len, int start_addr = 0);
		void loadMemory(const uint8_t *mem);
		void loadRegisters(const uint8_t *r);
		void setProgramCounter(int pc);
		void setMemory(int addr, uint8_t val);
		uint8_t getMemory(int addr) const;
		void setRegister(int index, uint8_t val);
		uint8_t getRegister(int index) const;
		int getProgramCounter(void) const;
		void run(void);
		bool step(void);
	};
	
	class Assembler
	{
		
	};
}

#endif //FX_V8_H
