#include "Process.hpp"

Process::Process(unsigned time, unsigned slice, unsigned memory, byte level)
{
	estado = EM_EXECUCAO;
	this->time = time;
	this->slice = slice;
	this->memory = memory;
	this->level = level;
	total = slice;
	call = 0;
	duration = 0;
}
unsigned Process::getTime()
{
	return time;
}
unsigned Process::getTotal()
{
	return total;
}
unsigned Process::getDuration()
{
	return duration;
}
state_t Process::getState()
{
	return estado;
}
unsigned Process::getMemory()
{
	return memory;
}
byte Process::getLevel()
{
	return level;
}
byte Process::getSlice()
{
	return call;
}
void Process::setLevel()
{
	if (level < 4 && call == 10)
	{
		level++;
		call = 0;
	}
}
void Process::setSlice()
{
	if (estado == BLOQUEADO || estado == EM_EXECUCAO) return;
	if (estado == EM_ESPERA)
	{
		call++;
		slice--;
		estado = slice == 0 ? MORTO : EM_EXECUCAO;
	}
}
void Process::setDuration()
{
	if (estado != FINISH)
		duration++;
}
void Process::setChange(unsigned m, unsigned n)
{
	estado = estado == EM_ESPERA ? BLOQUEADO : estado;
	estado = estado == EM_EXECUCAO ? EM_ESPERA : estado;
	estado = memory < n - m && estado == BLOQUEADO ? PRONTO : estado;
}
bool Process::end()
{
	if (estado == FINISH)
		return false;
	estado = estado == MORTO ? FINISH : estado;
	return estado == FINISH ? true : false;
}