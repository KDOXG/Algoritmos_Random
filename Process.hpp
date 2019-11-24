typedef unsigned char byte;

class Process
{
private:
	unsigned time;      //Representa o tempo em que o processo é recebido pelo SO
	unsigned slice;     //Número de slices restantes para executar o processo
	unsigned memory;    //Memoria a gastar
	byte level;         //Nivel de prioridade. Limite: 4
	byte call;          //Quantidade de chamadas por nivel. Limite: 10
	unsigned duration;  //Numero de slices percorridos até o termino da execucao
	unsigned total;     //Número de slices necessários para executar o processo
public:
	Process(unsigned time, unsigned slice, unsigned memory, byte level);
	unsigned getMemory();
	unsigned getTotal();
	byte getLevel();
	void setLevel();
	byte getSlice();
	void setSlice();
	unsigned getDuration();
	void setDuration();
	bool end();
};

enum states {
	NOVO,
	EM_EXECUCAO,
	EM_ESPERA,
	BLOQUEADO,
	PRONTO,
	ZUMBI,
	MORTO
} state_t;
