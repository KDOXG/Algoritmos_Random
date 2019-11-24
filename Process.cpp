#include "Process.hpp"

Process::Process(unsigned time, unsigned slice, unsigned memory, byte level)
{
	estado = EM_ESPERA;
	this->time = time;
	this->slice = slice;
	this->memory = memory;
	this->level = level;
	total = slice;
	call = 0;
	duration = 0;
}
unsigned Process::getMemory()
{
	return memory;
}
unsigned Process::getTime()
{
	return time;
}
unsigned Process::getTotal()
{
	return total;
}
byte Process::getLevel()
{
	return level;
}
void Process::setLevel(bool memory)
{
	if (memory)
	{

	}
	else
	{
		if (level < 4 && call == 10)
		{
			level++;
			call = 0;
		}
	}
}
byte Process::getSlice()
{
	return call;
}
void Process::setSlice()
{
	call++;
	slice--;
	estado = slice == 0 ? MORTO : EM_EXECUCAO;
}
unsigned Process::getDuration()
{
	return duration;
}
void Process::setDuration()
{
	duration++;
}
void Process::setChange(unsigned m, unsigned n)
{
	estado = estado == EM_EXECUCAO ? EM_ESPERA : estado;
	estado = estado == BLOQUEADO && memory < n - m ? PRONTO : estado;
}
bool Process::end()
{
	if (estado == FINISH)
		return false;
	estado = estado == MORTO ? FINISH : estado;
	return estado == FINISH ? true : false;
}