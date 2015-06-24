
#include "Escola.h"
#include "File_manager.h"
#include "Random_data.h"

void openFile(FILE **ppFile, char* param){
	(*ppFile) = fopen(FULLFILEPATH,param);
	if((*ppFile) == NULL)
	{ 
		fileGenericProblemError();
	}
}

void closeFile(FILE **ppFile){
	fclose((*ppFile));
}

long currentSizeInFile(FILE** ppFile)
{
	long retValue = -1;
		retValue = ftell(*ppFile);
	return retValue;
}


void printEntries(pREGISTRO pRegistro){
	//printf("Matricula: %d\n",pRegistro->matricula);

    Registro registro;
    memcpy(&registro,pRegistro,sizeof(Registro));
	printf("Matricula: %d\n",registro.matricula);
	printf("Nome: %s %s\n", registro.aluno.nome, registro.aluno.sobrenome);
	printf("Data de Nascimento: %d/%d/%d\n", registro.aluno.dataNascimento.dia, registro.aluno.dataNascimento.mes, registro.aluno.dataNascimento.ano);
	printf("Disciplinas: %s, %s, %s, %s, %s\n\n", registro.aluno.disciplina1, registro.aluno.disciplina2, registro.aluno.disciplina3,
					              registro.aluno.disciplina4,registro.aluno.disciplina5);
	//printf("Disciplina: %s\n", registro.aluno.disciplina1);
}

void fDataWriteBlock(FILE* pFile, ppREGISTRO ppRegistro, int quanty){
	if(pFile == NULL){
		fileGenericProblemError();
	}else{
		fwrite((*ppRegistro),sizeof(Registro) * quanty,1,pFile);
	}
}

void fDataReadBlock(FILE* pFile, ppREGISTRO ppRegistro, int quanty, int position){
	if(pFile == NULL){
		fileGenericProblemError();
	}else{
		fseek(pFile,position * (sizeof(Registro) * quanty), SEEK_SET);
		fread((*ppRegistro),sizeof(Registro) * quanty,1,pFile);
	}
}

void fileGenericProblemError(){
	perror("\nError operating file!\n");
	exit(1);
}

void fIndexTableWriteBlock(FILE* pFile, ppINDEX_TABLE ppIndex_Table, int quanty){
	int i;

	if(pFile == NULL){
		fileGenericProblemError();
	}else{
		fwrite((*ppIndex_Table),sizeof(INDEX_TABLE) * quanty,1,pFile);
	}
}

void fIndexTableReadBlock(FILE* pFile, ppINDEX_TABLE ppIndex_Table, int quanty, int position){
	if(pFile == NULL){
		fileGenericProblemError();
	}else{
		fseek(pFile,position * (sizeof(INDEX_TABLE) * quanty), SEEK_SET);
		fread((*ppIndex_Table),sizeof(INDEX_TABLE) * quanty,1,pFile);
	}
}

void openFileIndexTable(FILE **ppFile, char* param){
	(*ppFile) = fopen(FULLFILEPATH_INDEX_TABLE,param);
	if((*ppFile) == NULL)
	{
		fileGenericProblemError();
	}
}



void readEntryPosition(int position)
{

	pREGISTRO pRegistro;
	pRegistro = (pREGISTRO) malloc(sizeof(Registro));
	/* (pData)->data = (pPARTIDA) malloc(sizeof(PARTIDA)); */

	FILE** ppFile;
	ppFile = (FILE**) malloc(sizeof(FILE*));

	Registro registro;
	/* testeD.data = (pPARTIDA) malloc(sizeof(PARTIDA)); */
	/* printEntries((&testeD)); */
	openFile(ppFile,"r+b");
	fDataReadPosition((*ppFile),&registro,position);
	printEntries((&registro));
	closeFile(ppFile);

	/* free((pData)->data); */
	free((pRegistro));
	free(ppFile);
}

void fDataReadPosition(FILE* pFile, pREGISTRO pRegistro, int position)
{
	if(pFile == NULL)
	{
		fileGenericProblemError();
	}
	else
	{
		fseek(pFile,sizeof(Registro) * position, SEEK_SET);
		fDataRead(pFile,pRegistro);
	}
}

void fDataRead(FILE* pFile, pREGISTRO pRegistro)
{
	if(pFile == NULL)
	{
		fileGenericProblemError();
	}
	else
	{
		fread(pRegistro,sizeof(Registro),1,pFile);
	}
}


