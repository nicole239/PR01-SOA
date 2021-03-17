#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define UNIDAD_TRABAJO 50

//Parametros
short int ES_EXPROPIATIVO;
int TOTAL_THREADS;
int QUANTUM;
float PORCENTAJE_A_REALIZAR;

//Resultado
double pi_Calculado = 0;

//Último índice de la serie que fue calculado por un thread
int indice_serie_actual = 0;

struct Thread{
    int total_boletos;
    int resultado_parcial_de_pi;
    int total_unidades_trabajo;
    int unidades_de_trabajo_pendientes;
};
//Puntero a arreglo de Threads de tamaño TOTAL_THREADS
struct Thread *threads;

void new_thread(struct Thread *thread, int boletos){
    thread->total_boletos = boletos;
    thread->resultado_parcial_de_pi = 0;
    thread->total_unidades_trabajo = 0;
    thread->unidades_de_trabajo_pendientes = 0;
}


void read_parameters()
{
    FILE *file;
    char *line;
    size_t len = 0;
    char *element;
    
    //Abre el archivo
    if((file = fopen("input.txt","r")) == NULL){
    	printf("Error al abrir archivo");
    	exit(1);
    }
    
    //Lee modo de operación
    getline(&line, &len, file);
    ES_EXPROPIATIVO = atoi(line);
    
    //Lee total de threads
    getline(&line, &len, file);
    TOTAL_THREADS = atoi(line);
    
    struct Thread threadArray[TOTAL_THREADS];
    
    //Total de boletos
    getline(&line, &len, file);
    element = strtok(line, " ");
    for(int i=0; i < TOTAL_THREADS; i++)
    {
    	new_thread(&threadArray[i], atoi(element));
    	element = strtok(NULL, " ");
    }
    
    //Cantidad de trabajo
    getline(&line, &len, file);
    element = strtok(line, " ");
    for(int i=0; i < TOTAL_THREADS; i++)
    {
    	threadArray[i].total_unidades_trabajo = atoi(element);
    	element = strtok(NULL, " ");
    }
    
    threads = threadArray;
    
    //Quantum o Porcentaje
    getline(&line, &len, file);    
    if(ES_EXPROPIATIVO)
    {
    	QUANTUM = atoi(line);   
    }else{
    	PORCENTAJE_A_REALIZAR = atof(line);
    }
    
    fclose(file);
    
}

int obtenerThread(int boleto_ganador){

    int cont = 0;

    for (int i = 0; i < TOTAL_THREADS; i++) {
        Thread* thread = threads[i];
        cont += thread->total_boletos;
        if(cont > boleto_ganador)
        {
            thread->total_boletos = 0;
            return *thread;
        } 
    }

    

	//utilizado por scheduler
	//busca el thread que tiene el boleto ganador utilizando rangos
	//retorna el thread o el �ndice del thread o algo as�
	//IMPORTANTE: No retornar un thread que ya termin�
	
	/*
	Ejemplo: Si hay 3 threads con 10 boletos cada uno. Total de 30.
	El thread 1 tiene los boletos del 0 al 9
	El thread 2 tiene los boletos del 10 al 19
	El thread 3 tiene los boletos del 20 al 29.
	
	Si el thread 2 termina, el total debe  actualizarse y los rangos cambian:
	El thread 1 tiene los boletos del 0 al 9
	El thread 3 tiene los boletos del 10 al 19
	*/
}

int main(int argc, char **argv)
{
    
    read_parameters();
    
    
    return 0;
}
