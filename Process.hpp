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
	byte init;			//Nivel de prioridade inicial. Limite: 4
	byte level;         //Flag para nivel de prioridade.
	/*	0b00000001	- prioridade 0
	 *	0b00000010	- prioridade 1
	 *	0b00000100	- prioridade 2
	 *	0b00001000	- prioridade 3
	 *	0b00010000	- prioridade 4 (maxima)
	 *	0b1xxxxxxx	- inicializado em prioridade 4; nao alterar prioridade durante execucao
	 *	0bx1xxxxxx ou 0bx0xxxxxx	- nao inicializado em prioridade 4;
	 *	indica com 0 se a prioridade esta incrementando ou 1 se esta decrementando.
	 */	
	byte call;          //Quantidade de chamadas por nivel. Limite: 10
	unsigned read;		//Indicador para quando um processo for iniciado pela primeira vez
	unsigned duration;  //Numero de slices percorridos até o termino da execucao
	unsigned total;     //Número de slices necessários para executar o processo
public:
	Process(unsigned time, unsigned slice, unsigned memory, byte level);
	unsigned getTime();
	unsigned getRead();
	unsigned getTotal();
	unsigned getDuration();
	unsigned getMemory();
	byte getInit();
	state_t getStatus();
	byte getLevel();
	byte getSlice();
	void setLevel();
	void setSlice(unsigned time);
	void setDuration();
	void setChange(unsigned memory, unsigned totalMemory);
	bool end();
};