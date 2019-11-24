#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdbool>
#include "Process.cpp"

int error(const char* arg);
bool check(std::vector<Process> a);

int main(int argc, char* argv[])
{
    if (argc <= 4) return error("Erro: parâmetros insuficientes! Desligando...\n");

    unsigned time = 0;					//Contador global de slices percorridos
    unsigned memory = 0;				//Contador global de memoria ocupada

    unsigned CPU = strtoul(argv[1],NULL,0);
    unsigned slice = strtoul(argv[2],NULL,0);
    unsigned totalMemory = strtoul(argv[3],NULL,0);
    std::string fileName;
    fileName.append(argv[4]);

    std::ifstream file;
    file.open(fileName,std::ifstream::in);

    std::vector<Process> processList;		//Lista de todos os processos
	unsigned n = 0;							//Quantidade de processos lidos do arquivo
	{
		Process* p;                         //Objeto auxiliar
		std::string param = std::string();  //String para guardar cada linha de arquivo
		std::string aux = std::string();    //Auxiliar para a string "param"
		unsigned time, slice, memory;       //Parametros temporarios para a instancia de cada objeto de processo
		byte level;                         //Outro parametro temporario para a instancia do objeto de processo
		byte i = 0, j, k;                   //Variaveis auxiliares para guardar indices intermediarios
		while (!file.fail())
		{
			param.erase(param.begin(), param.end());
			aux.erase(aux.begin(), aux.end());
			getline(file, param);

			i = 0;
			i = param.find(',', i);
			aux = param.substr(0, i - 1);
			time = std::stoul(aux, NULL, 0);
			i += 2;

			j = param.find(',', i);
			aux = param.substr(i, j - 1);
			slice = std::stoul(aux, NULL, 0);
			j += 2;

			k = param.find(',', j);
			aux = param.substr(j, k - 1);
			memory = std::stoul(aux, NULL, 0);
			k += 2;

			aux = param.substr(k, param.size() - 1);
			level = (byte)std::stoul(aux, NULL, 0);

			p = new Process(time, slice, memory, level);
			processList.push_back(*p);
			delete(p);
			n++;

		}   //No final, a lista processList tem todos os processos previstos para a CPU usar para escalonar
	}
	for (unsigned i = 0; i < processList.size(); i++)
		if (processList[i].getMemory() > totalMemory)
			return error("Erro: um ou mais processos nao possuem memoria o suficiente! Desligando...\n");

    //Existem cinco listas de processos pois existe uma para cada prioridade
    std::list<Process*> *processes = new std::list<Process*>[5];
	


    return 0;
}

int error(char* arg)
{
    std::cout << arg;
    return -1;
}
