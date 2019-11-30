#include "Process.hpp"

Process::Process(unsigned time, unsigned slice, unsigned memory, byte level)
{
	estado = EM_ESPERA;
	this->time = time;
	this->slice = slice;
	this->memory = memory;
	switch (level)
	{
	case 0:
		this->level = 0b00000001;
		break;
	case 1:
		this->level = 0b00000010;
		break;
	case 2:
		this->level = 0b00000100;
		break;
	case 3:
		this->level = 0b00001000;
		break;
	case 4:
		this->level = 0b10010000;
		break;
	}
	total = slice;
	read = -1;
	call = 0;
	duration = 0;
}
unsigned Process::getTime()
{
	return time;
}
unsigned Process::getRead()
{
	return read;
}
unsigned Process::getTotal()
{
	return total;
}
unsigned Process::getDuration()
{
	return duration;
}
state_t Process::getStatus()
{
	return estado;
}
unsigned Process::getMemory()
{
	return memory;
}
byte Process::getLevel()
{
	if ((level & 0b00010000) == 0b00010000) return 4;
	if ((level & 0b00001000) == 0b00001000) return 3;
	if ((level & 0b00000100) == 0b00000100) return 2;
	if ((level & 0b00000010) == 0b00000010) return 1;
	if ((level & 0b00000001) == 0b00000001) return 0;
	return 0;
}
void Process::setLevel()
{
	if ((level & 0b10000000) == 0b10000000) return;	//Inicializado com prioridade 4
	if (call == 10 && (level & 0b01000000) != 0b01000000)	//Incrementando a prioridade
	{
		level <<= 1;
		if ((level & 0b00010000) == 0b00010000)
			level |= 0b01000000;
		call = 0;
		return;
	}
	if (call == 10 && (level & 0b01000000) == 0b01000000)	//Decrementando a prioridade
	{
		if (((level & 0b10111111) >> (level+1)) != 0)
		level &= 0b10111111;
		level |= 0b10000000;
		level >>= 1;
		if (((level & 0b10111111) >> (level + 1)) != 0)
			level &= 0b10111111;
		call = 0;
		return;
	}
}
void Process::setSlice(unsigned time)
{
	if (estado == BLOQUEADO || estado == EM_EXECUCAO) return;
	if (estado == EM_ESPERA)
	{
		if (read == -1)
			read = time;
		call++;
		slice--;
		estado = slice == 0 ? MORTO : EM_EXECUCAO;
	}
}
void Process::setDuration()
{
	if (estado != FINISH || read != -1)
		duration++;
}
void Process::setChange(unsigned memory, unsigned totalMemory)
{
	estado = estado == EM_ESPERA ? BLOQUEADO : estado;
	estado = estado == EM_EXECUCAO ? EM_ESPERA : estado;
	estado = this->memory <= totalMemory - memory && estado == BLOQUEADO ? PRONTO : estado;
}
bool Process::end()
{
	if (estado == FINISH)
		return false;
	estado = estado == MORTO ? FINISH : estado;
	return estado == FINISH ? true : false;
}