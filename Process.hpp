typedef unsigned char byte;

enum state_t {
	EM_EXECUCAO,
	EM_ESPERA,
	BLOQUEADO,
	PRONTO,
	MORTO,
	FINISH
};

class Process
{
private:
	state_t estado;		//Estado atual do processo
	unsigned time;      //Representa o tempo em que o processo é recebido pelo SO
	unsigned slice;     //Número de slices restantes para executar o processo
	unsigned memory;    //Memoria a gastar
	byte level;         //Nivel de prioridade. Limite: 4
	byte call;          //Quantidade de chamadas por nivel. Limite: 10
	unsigned duration;  //Numero de slices percorridos até o termino da execucao
	unsigned total;     //Número de slices necessários para executar o processo
public:
	Process(unsigned time, unsigned slice, unsigned memory, byte level);
	unsigned getTime();
	unsigned getTotal();
	unsigned getDuration();
	state_t getState();
	unsigned getMemory();
	byte getLevel();
	byte getSlice();
	void setLevel();
	void setSlice();
	void setDuration();
	void setChange(unsigned m, unsigned n);
	bool end();
};