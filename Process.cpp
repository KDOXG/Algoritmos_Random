#include "Process.hpp"

Process::Process(unsigned time, unsigned slice, unsigned memory, byte level)
{
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
unsigned Process::getTotal()
{
	return total;
}
byte Process::getLevel()
{
	return level;
}
void Process::setLevel()
{
	if (level < 4)
		level++;
	call = 0;
}
byte Process::getSlice()
{
	return call;
}
void Process::setSlice()
{
	slice--;
}
unsigned Process::getDuration()
{
	return duration;
}
void Process::setDuration()
{
	duration++;
}
bool Process::end()
{
	if (slice == 0)
		return true;
	else
		return false;
}
