/*
 * Random_data.h
 *
 *  Created on: Mar 16, 2015
 *      Author: gui
 */

#ifndef RANDOM_DATA_H_
#define RANDOM_DATA_H_
#pragma once
#include "Escola.h"

void generateRandomEntriesByQnt(int qntEntries,int blockSize);
void generateRandomEntriesByQnt2(int qntEntries);
void createIndexTable();
void insert();
void read();
void generateRandomEntriesBlock(int size, int blockSize);
void readRandomEntriesBlock(int blockSize);

void executionTime(clock_t time_start, clock_t time_end);
void printAllEntries();

void randomAluno(ppALUNO ppAluno);
void randomName(char* name);
void randomDate(pDATANASCIMENTO data);
void randomDisciplina(char* place);

void intercalateSort(int blockSize, int k_vias, int cmpKey1, int cmpKey2);
int cmpEncapsulate(void *p1, void *p2, void *typeCmp);
int cmpChar(char *first, char *second);
int cmpDate(pDATANASCIMENTO first, pDATANASCIMENTO second);


void readRandomEntriesBlockSorted(int blockSize);


typedef struct STACK *pSTACK;
typedef struct STACK **ppSTACK;


typedef struct STACK{
	pREGISTRO registro;
	pSTACK next;
}STACK;

typedef struct QUEUE *pQUEUE;
typedef struct QUEUE **ppQUEUE;

typedef struct QUEUE{
	pREGISTRO registro;
	pQUEUE next;
}QUEUE;

void pop(ppSTACK stack, ppREGISTRO elem);
void push(ppSTACK stack, ppSTACK newStack, pREGISTRO elem);
void insertQueue(ppQUEUE queue, pREGISTRO elem);
void sortStack(pSTACK first , pSTACK second, ppQUEUE queue,int(* cmp)(void *p1, void *p2, void *typeCmp), int cmpKey1, int cmpKey2);





#endif /* RANDOM_DATA_H_ */
