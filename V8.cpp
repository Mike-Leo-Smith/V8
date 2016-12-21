//
// Created by Mike Smith on 2016/12/19.
//

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <math.h>
#include <cstdio>
#include "V8.h"

namespace V8
{
	Emulator::Emulator(const uint8_t *mem, const uint8_t *r, int pc)
	{
		if (mem == NULL)
			memset(_mem, 0, MEMORY_SIZE);
		else
			memcpy(_mem, mem, MEMORY_SIZE);
		
		if (r == NULL)
			memset(_r, 0, REGISTER_NUMBER);
		else
			memcpy(_r, r, REGISTER_NUMBER);
		
		_pc = pc;
	}
	
	void Emulator::loadMemory(const uint8_t *mem)
	{
		memcpy(_mem, mem, MEMORY_SIZE);
	}
	
	void Emulator::loadRegisters(const uint8_t *r)
	{
		memcpy(_r, r, REGISTER_NUMBER);
	}
	
	void Emulator::setProgramCounter(int pc)
	{
		_pc = pc;
	}
	
	void Emulator::setMemory(int addr, uint8_t val)
	{
		_mem[addr] = val;
	}
	
	uint8_t Emulator::getMemory(int addr) const
	{
		return _mem[addr];
	}
	
	void Emulator::setRegister(int index, uint8_t val)
	{
		_r[index] = val;
	}
	
	uint8_t Emulator::getRegister(int index) const
	{
		return _r[index];
	}
	
	void Emulator::run(void)
	{
		while (step());
	}
	
	bool Emulator::step(void)
	{
		uint16_t instr;
		uint8_t r;
		int x;
		
		instr = (_mem[_pc] << 8) | _mem[_pc + 1];
		_pc += 2;
		
		switch (instr & 0xf000)
		{
		case 0x1000:
			_r[(instr & 0x0f00) >> 8] = (uint8_t)_mem[instr & 0x00ff];
			return true;
		case 0x2000:
			_r[(instr & 0x0f00) >> 8] = (uint8_t)(instr & 0x00ff);
			return true;
		case 0x3000:
			_mem[instr & 0x00ff] = _r[(instr & 0x0f00) >> 8];
			return true;
		case 0x4000:
			_r[instr & 0x000f] = _r[(instr & 0x00f0) >> 4];
			return true;
		case 0x5000:
			_r[(instr & 0x0f00) >> 8] = _r[(instr & 0x00f0) >> 4] + _r[instr & 0x000f];
			return true;
		case 0x6000:
			_r[(instr & 0x0f00) >> 8] = addf(_r[(instr & 0x00f0) >> 4], _r[instr & 0x000f]);
			return true;
		case 0x7000:
			_r[(instr & 0x0f00) >> 8] = _r[(instr & 0x00f0) >> 4] | _r[instr & 0x000f];
			return true;
		case 0x8000:
			_r[(instr & 0x0f00) >> 8] = _r[(instr & 0x00f0) >> 4] & _r[instr & 0x000f];
			return true;
		case 0x9000:
			_r[(instr & 0x0f00) >> 8] = _r[(instr & 0x00f0) >> 4] ^ _r[instr & 0x000f];
			return true;
		case 0xa000:
			r = _r[(instr & 0x0f00) >> 8];
			x = instr & 07;
			_r[(instr & 0x0f00) >> 8] = (r >> x) | (r << (8 - x));
			return true;
		case 0xb000:
			_pc = (_r[(instr & 0x0f00) >> 8] == _r[0]) ? (instr & 0x00ff) : _pc;
			return true;
		case 0xc000:
			return false;
		case 0xd000:
			_r[(instr & 0x0f00) >> 8] = _mem[_r[instr & 0x000f]];
			return true;
		case 0xe000:
			_mem[_r[instr & 0x000f]] = _r[(instr & 0x0f00) >> 8];
			return true;
		case 0xf000:
			_pc = (_r[(instr & 0x0f00) >> 8] < _r[0]) ? (instr & 0x00ff) : _pc;
			return true;
		default:
			break;
		}
	}
	
	uint8_t Emulator::addf(uint8_t a, uint8_t b)
	{
		uint32_t f;
		float sum;
		
		f = (uint32_t)((b & 0x80) << 24) | ((((b & 0x70) >> 4) + 0x7A) << 23) | ((b & 0x07) << 20);
		sum = *(float *)&f;
		f = (uint32_t)((b & 0x80) << 24) | ((((b & 0x70) >> 4) + 0x7A) << 23) | ((b & 0x07) << 20);
		sum += *(float *)&f;
		
		f = *(uint32_t *)&sum;
		return (uint8_t)(((f & 0x80000000) >> 24) | ((((f & 0x7F800000) >> 23) - 0x7A) << 4) | ((f & 0x7FFFFF) >> 20) | 0x08);
	}
	
	int Emulator::getProgramCounter(void) const
	{
		return _pc;
	}
	
	void Emulator::loadCode(uint8_t *code, int len, int start_addr)
	{
		memcpy(_mem + start_addr, code, len);
		_pc = start_addr;
	}
	
	void Emulator::reset(void)
	{
		memset(_mem, 0, MEMORY_SIZE);
		memset(_r, 0, REGISTER_NUMBER);
		_pc = 0;
	}
}