
#include "Random_data.h"
#include "Escola.h"
#include "File_manager.h"

const char NamesPrefix[][5] = {"bel", "nar", "xan", "bell", "natr", "ev"};

const char NamesSuffix[][5] = {"us", "ix", "ox", "ith",	"ath", "um", "ator", "or", "axia","imus", "ais", "itur", "orex", "o","y"};

const char NamesStems[][10] = {"adur", "aes", "anim", "apoll", "imac","educ", "equis", "extr", "guius", "hann","equi", "amora", "hum", "iace", "ille",
							   "inept", "iuv", "obe", "ocul", "orbis"};

const char disciplinas[][16]= {"PRA", "EDA", "CAL", "CDI II", "ALG II", "BAN I", "COMP", "ANN", "SOP", "REC", "TEG", "CGR", "TEC", "IA", "PIM", "CDI I"};

void randomAluno(ppALUNO ppAluno){
    
	randomName((*ppAluno)->nome);
	randomName((*ppAluno)->sobrenome);
	randomDate(&(*ppAluno)->dataNascimento);
//	randomDisciplina(&(ppAluno)->disciplina);
    randomDisciplina((*ppAluno)->disciplina1);
    randomDisciplina((*ppAluno)->disciplina2);
    randomDisciplina((*ppAluno)->disciplina3);
    randomDisciplina((*ppAluno)->disciplina4);
    randomDisciplina((*ppAluno)->disciplina5);
/*	strcpy((*ppAluno)->disciplina1, disciplinas[rand()%QNTDISCIPLINAS]);
    strcpy((*ppAluno)->disciplina2, disciplinas[rand()%QNTDISCIPLINAS]);
    strcpy((*ppAluno)->disciplina3, disciplinas[rand()%QNTDISCIPLINAS]);
    strcpy((*ppAluno)->disciplina4, disciplinas[rand()%QNTDISCIPLINAS]);
    strcpy((*ppAluno)->disciplina5, disciplinas[rand()%QNTDISCIPLINAS]);
    strcpy((*ppAluno)->disciplina5, disciplinas[rand()%QNTDISCIPLINAS]);*/

 //   printf("DisciplinaTeste: %s\n", ((*ppAluno)->disciplina1));
}

/**
 * Generate a random date betewen 01012000-01012014
 */
void randomDate(pDATANASCIMENTO data){
	data->dia = 1 + rand() % 30;
	data->mes = 1 + rand() % 11;
	data->ano = (1945 + rand() % 55) + 1;
}

/**
 * Generate random time name
 */
void randomName(char* name){
	name[0]=0; //initialize the string to "" (zero length string).
	//add the prefix...
	strcat(name, NamesPrefix[(rand() % 7)]);
	//add the stem...
	strcat(name, NamesStems[(rand() % 20)]);
	//add the suffix...
	strcat(name, NamesSuffix[(rand() % 16)]);
	//Make the first letter capital...
	name[0]=toupper(name[0]);

}

void randomDisciplina(char* place){
//	place[0]=0; //initialize the string to "" (zero length string).
	//add the prefix...
//	strcat(place, disciplinas[(rand() % 16)]);
	strcpy(place, disciplinas[(rand()%QNTDISCIPLINAS)]);
	//add the stem...
//	char stems[6];
//    strcpy(stems,PlaceStems[(rand() % 20)]);
//	stems[0] = toupper(stems[0]);
//	strcat(place, stems);
	//add the suffix...
//	strcat(place, PlaceSuffix[(rand() % 16)]);
	//Make the first letter capital...
//	place[0]=toupper(place[0]);
}

//Nova funcao faz o sort




void intercalateSort(int blockSize, int k_vias, int cmpKey1, int cmpKey2)
{
	ppALUNO ppAluno;

	FILE** ppFile;
	ppFile = (FILE**) malloc(sizeof(FILE*));
	ppREGISTRO ppRegistro;
	int i=0;

	//cmp function pointer
	void *cmp;
	cmp = &cmpEncapsulate;


	int count = 0;
	int id = -1;
	int position,idReg,j, stackIndex=0;

	int lenght = blockSize;
	ppRegistro = (ppREGISTRO) malloc(sizeof(pREGISTRO) * lenght);
	for(i=0;i<lenght;i++){
		ppRegistro[i] = (pREGISTRO) malloc(sizeof(Registro));
	}

	ppAluno = (ppALUNO) malloc(sizeof(pALUNO));
	(*ppAluno) = (pALUNO) malloc(sizeof(Aluno));

	//Allocate all the stacks
	ppSTACK ppStack,ppStackNew;
	ppStack = malloc(sizeof(pSTACK) * (k_vias + 1));
	ppStackNew = malloc(sizeof(pSTACK));
	for(i=0;i<k_vias+1;i++){
		ppStack[i] = malloc(sizeof(STACK));
		ppStack[i]->registro = NULL;
		ppStack[i]->next = NULL;
	}

	//Allocate the queue
	ppQUEUE ppQueue;
	ppQUEUE iterator;
	ppQueue = malloc(sizeof(pQUEUE));
	*ppQueue = malloc(sizeof(QUEUE));
	(*ppQueue)->registro = NULL;
	(*ppQueue)->next = NULL;

	position = -1;
	stackIndex = 0;
	do{
		position++;

		//read 1 block for each stack
		openFile(ppFile,"r+b");
		fDataReadBlock((*ppFile),ppRegistro,blockSize/(sizeof(Registro)), position);

		//put in the stack
		i=0;
		while(i<blockSize/sizeof(Registro)){
			if(ppRegistro[i] != NULL){
				*ppStackNew = malloc(sizeof(STACK));

				//FAKE PUSH
				(*ppStackNew)->next = malloc(sizeof(pSTACK));
				(*ppStackNew)->next = ppStack[stackIndex];
				(*ppStackNew)->registro = malloc(sizeof(Registro));
				memcpy((*ppStackNew)->registro,ppRegistro[i],sizeof(Registro));
				ppStack[stackIndex] = *ppStackNew;

				i++;
			}else{
				/* printf("TESTE data.c ppData[i] eh null!\n"); */
			}
		}
		stackIndex++;
		closeFile(ppFile);
	}while(stackIndex < k_vias);
	printf("Before\n");

	//test print all ids in stack
	ppSTACK iterators = malloc(sizeof(pSTACK));

	//sort all k_vias and put in the queue
	stackIndex = 0;
	do{
		sortStack(ppStack[stackIndex],ppStack[stackIndex+1],ppQueue,cmp,cmpKey1,cmpKey2);
		stackIndex += 2;
	}while(stackIndex < k_vias-2);
	printf("Before3333\n");

	//at her, the queue has all the references to ppDATA already sort
	//just write this references in an external file

	ppINDEX_TABLE ppIndexTable;
	ppIndexTable = malloc(sizeof(INDEX_TABLE*)*lenght);

	//the block size
	for(i=0;i<lenght;i++){
		ppIndexTable[i] = malloc(sizeof(INDEX_TABLE));
	}

	/* //this way will try on-be-one, Using block is more fast */
	/* //iterate untill it is finished */
	i = 0;
	openFileIndexTable(ppFile,"a+b");

	if(ppQueue)	{
		iterator = malloc(sizeof(pQUEUE));
		iterator = ppQueue;
			printf("olaaa");
		//write the first out

		while(*iterator){
			//get next and write
			if(*iterator && (*iterator)->registro){
				i++;
				pREGISTRO registro = malloc(sizeof(Registro));
				registro = (*iterator)->registro;
				ppIndexTable[i]->byteIndex = registro->matricula * sizeof(Registro);//use in byte
				//TODO WRITE her on-by-one if needed

				//when get the limit size of block, write in file
				if(i == k_vias-1){


					fIndexTableWriteBlock(*ppFile,ppIndexTable,k_vias);
					i = 0;
				}
			}
				iterator = &(*iterator)->next;
				//repeat
		}
	}
	printf("at end\n");
	closeFile(ppFile);
}

int cmpEncapsulate(void *p1, void *p2, void *typeCmp){
	DataNascimento date1;
	DataNascimento date2;

	if(p1 && p2 && typeCmp){
		pREGISTRO registro1 = (pREGISTRO) p1;
		pREGISTRO registro2 = (pREGISTRO) p2;
		int type = *(int*) typeCmp;

		switch (type){
			case 0:
				return cmpChar(registro1->aluno.nome, registro2->aluno.nome);
				break;
			case 1:
				return cmpChar(registro1->aluno.sobrenome, registro2->aluno.sobrenome);
				break;
			case 2:
				return cmpChar(registro1->aluno.disciplina1, registro2->aluno.disciplina1);
				break;
			case 3:
				date1 = registro1->aluno.dataNascimento;
				date2 = registro2->aluno.dataNascimento;
				return cmpDate(&date1,&date2);
				break;
			default:
				printf("This option doesn't exist!");
				break;
		}
	}
        
}

int cmpChar(char *first, char *second){
	if(first && second){
		return strcmp(first,second);
	}
}

int cmpDate(pDATANASCIMENTO first, pDATANASCIMENTO second)
{
	if(first && second){
		int day1,day2,month1,month2,year1,year2;

		year1 = first->ano;
		year2 = second->ano;

		if( year1 == year2){
			month1 = first->mes;
			month2 = second->mes;

			if( month1 == month2){
				day1 = first->dia;
				day2 = second->dia;

				if( day1 == day2){
					return 0;
				}else if ( day1 < day2){
					return -1;
				}else{
					return 1;
				}
			}
			else if(month1 < month2){
				return -1;
			}else{
				return 1;
			}
		}else if(year1 < year2){
			return -1;
		}else{
			return 1;
		}
	}
}

void sortStack(pSTACK first , pSTACK second, ppQUEUE queue,int(* cmp)(void *p1, void *p2, void *typeCmp), int cmpKey1, int cmpKey2){

	pREGISTRO elem;

	int cont = 0;
	/* while ( first && second ) { */
	while ( cont < (4096/sizeof(Registro))) {
		elem = malloc(sizeof(Registro));

		if ( (*cmp)(first->registro,second->registro,&cmpKey1) == 0 ){
			pop(&first,&elem);
			//se o primeiro criterio eh igual, tenta com o segundo
			if ( (*cmp)(first->registro,second->registro,&cmpKey2) == 0 ){
				//se o segundo eh igual, insere o first, na proxima vai o second
				 pop(&first,&elem);
			}else if ( (*cmp)(first->registro,second->registro,&cmpKey2) < 0 ){
				pop(&first,&elem);
			}else{  //se eh maior
				pop(&second,&elem);
			}

		}else if ((*cmp)(first->registro,second->registro,&cmpKey1) < 0 ){
			pop(&first,&elem);
		}else{ //se nao eh maior
			pop(&second,&elem);
		}
		insertQueue(queue, elem);
		/* printf("elem id eh ======>>>>>> %d\n",elem->id); */
		cont++;
	}
	/* printf("tam do cont!!!! %d\n",cont); */
}

void pop(ppSTACK ppStack, ppREGISTRO elem){
   		memcpy(*elem,(*ppStack)->registro,sizeof(Registro));
		*ppStack = (*ppStack)->next;
}

void insertQueue(ppQUEUE queue, pREGISTRO elem){
	int i=0;
	if(queue){
		ppQUEUE iterator = malloc(sizeof(ppQUEUE));
		iterator = queue;

		while(*iterator){
			i++;
			iterator = &(*iterator)->next;
		}
		*iterator = malloc(sizeof(QUEUE));
		((*iterator))->registro = malloc(sizeof(Registro));
		memcpy((*iterator)->registro,elem,sizeof(Registro));
		(*iterator)->next = NULL;
	}
}

void readRandomEntriesBlockSorted(int blockSize){
	ppALUNO ppAluno;

	FILE** ppFile;
	FILE** ppFileIndexTable;
	ppFile = (FILE**) malloc(sizeof(FILE*));
	ppFileIndexTable = (FILE**) malloc(sizeof(FILE*));
	ppREGISTRO ppRegistro;
	int i=0;

	int count = 0;
	int id = -1;
	int ask = 0;
	int position,posId;
	int k_vias = 8;
	int lenght = blockSize;

	ppRegistro = (ppREGISTRO) malloc(sizeof(pREGISTRO) * lenght);

	for(i=0;i<lenght;i++){
		ppRegistro[i] = (pREGISTRO) malloc(sizeof(Registro));
	}

	ppAluno = (ppALUNO) malloc(sizeof(pALUNO));
	(*ppAluno) = (pALUNO) malloc(sizeof(Aluno));


	ppINDEX_TABLE ppIndexTable;
	ppIndexTable = malloc(sizeof(pINDEX_TABLE) * k_vias);

	//the block size
	for(i=0;i<k_vias;i++){
		ppIndexTable[i] = malloc(sizeof(INDEX_TABLE));
	}


	openFileIndexTable(ppFileIndexTable,"r+b");
	printf("Reading the first block ...\n");
	position = 0;

	while(!feof(*ppFileIndexTable) && ask ==0){

		fIndexTableReadBlock((*ppFileIndexTable),ppIndexTable,k_vias, position);
		position++;

		for(i=1;i<k_vias;i++){
			if(ppIndexTable[i] != NULL){
				posId = ppIndexTable[i]->byteIndex;
 				posId = posId/sizeof(Registro);
 				readEntryPosition(posId);

			}
		}

		printf("What do you want to do now?\n");
		printf("[0] Next Block\n");
		printf("[1] Stop reading ...\n");
		scanf("%d",&ask);

		position++;
	}

	closeFile(ppFileIndexTable);

	for(i=0;i<lenght;i++){
		free(ppRegistro[i]);
	}
	//Liberandooo
	free(ppRegistro);
	free((*ppAluno));
	free(ppAluno);
}


