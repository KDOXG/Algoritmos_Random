#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <ostream>
#include <cstring>
#include <cstdlib>
#include <cstdbool>
#include "Process.hpp"

int error(const char* arg);

int main(int argc, char* argv[])
{
    if (argc < 4) return error("Erro: parâmetros insuficientes! Desligando...\n");

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
			i = (byte)param.find(',', i);
			aux = param.substr(0, i - 1);
			time = std::stoul(aux, NULL, 0);
			i += 2;

			j = (byte)param.find(',', i);
			aux = param.substr(i, j - 1);
			slice = std::stoul(aux, NULL, 0);
			j += 2;

			k = (byte)param.find(',', j);
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
	file.close();
	for (unsigned i = 0; i < processList.size(); i++)
		if (processList[i].getMemory() > totalMemory)
			return error("Erro: um ou mais processos nao possuem memoria o suficiente! Desligando...\n");

    //Existem cinco filas de processos pois existe uma para cada prioridade
    std::list<Process*> processes[5];
	//Existe tambem uma fila de processos esperando por memoria disponivel
	std::list<Process*> memoryWait;
	
	//Loop principal	***********************

	//Variavel auxiliar para comparar o nivel do processo que esta esperando na lista de espera com o lido atualmente
	byte waiter = 5;
	unsigned k;			//Contador de loop para achar a primeira lista de prioridades valida
	unsigned j;			//Contador de loop para preencher todas as CPUs declaradas
	while (n > 0)
	{
		k = 0;
		j = 0;

		//Insercao na lista pelo tempo
		for (unsigned i = 0; i < processList.size(); i++)
		{
			if (processList[i].getTime() == time && !processList[i].end())
				processes[processList[i].getLevel()].push_back(&processList[i]);
		}

		//Remocao geral na lista	***********************
		while (j < CPU)
		{
			// Analisando os processos da lista de espera
			if (memoryWait.size() != 0)
			{
				waiter = memoryWait.front()->getLevel();
				for (std::list<Process*>::iterator it = memoryWait.begin(); it != memoryWait.end(); it++)
				{
					if ((*it)->getStatus() != PRONTO)
						waiter = (*it)->getLevel() < waiter ? (*it)->getLevel() : waiter;
					else
						processes[(*it)->getLevel()].push_back(*it);
				}
			}

			while (k < 5 && (processes[k].size() == 0 || k < waiter))
				k++;
			if (k == 5)
				break;

			// Tirando processo da lista de processos a executar caso ja tenha terminado
			if (processes[k].front()->getStatus() == FINISH)
			{
				processes[k].pop_front();
			}

			// Processo pronto para processar
			if ((	processes[k].front()->getStatus() == EM_ESPERA
					||	processes[k].front()->getStatus() == PRONTO)
					&& processes[k].front()->getMemory() + memory <= totalMemory)
			{
				processes[k].front()->setSlice(time);
				processes[k].front()->setLevel();
				processes[processes[k].front()->getLevel()].push_back(processes[k].front());
				processes[k].pop_front();
			}
			// Memoria faltando
			else if (processes[k].front()->getStatus() != EM_EXECUCAO)
			{
				processes[k].front()->setChange(memory, totalMemory);
				if (processes[k].front()->getStatus() == BLOQUEADO)
					memoryWait.push_back(processes[k].front());
				else
					processes[k].push_back(processes[k].front());
				processes[k].pop_front();
			}
			j++;
		}

		//Atualizacao na lista
		for (unsigned i = 0; i < processList.size(); i++)
		{
			if (processList[i].end())
				n--;
			processList[i].setDuration();
			processList[i].setChange(memory,totalMemory);
		}

		//Avanco no tempo
		time++;
	}

	//Escrita dos resultados no arquivo	*************

	unsigned i = 0;
	std::ofstream file_out;
	file_out.open("data.txt", std::ios::app);
	while (!file_out.fail() && i < processList.size())
	{
		file_out << processList[i].getTime() << ", ";
		file_out << processList[i].getRead() << ", ";
		file_out << processList[i].getTotal() << ", ";
		file_out << processList[i].getDuration() << "\n";
		i++;
	}
	file_out.close;

    return 0;
}

int error(const char* arg)
{
    std::cout << arg;
    return -1;
}