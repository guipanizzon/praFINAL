#pragma once
#include <string.h> //Needed for strcat()
#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define TAMSTRING 40
#define QNTDISCIPLINAS 15
#define QNTSOBRENOMES 15
#define QNTNOMES 20


#define APPENDB 	"a+b"
#define READB		"r"
#define FULLFILEPATH "cadastroAlunos.bin"
#define FILENAME_INDEX_TABLE "indexTableFile.bin"
#define FULLFILEPATH_INDEX_TABLE "indexTableFile.bin"

	typedef struct DataNascimento{
		int dia;
		int mes;
		int ano;
	}DataNascimento;


	typedef struct Aluno{
        int idMatricula;
	    char nome[TAMSTRING];
	    char sobrenome[TAMSTRING];
	    DataNascimento dataNascimento;
	    //Disciplinas disciplina;
	    char disciplina1[TAMSTRING];
	    char disciplina2[TAMSTRING];
	    char disciplina3[TAMSTRING];
	    char disciplina4[TAMSTRING];
	    char disciplina5[TAMSTRING];
	}Aluno;

	typedef struct Registro{
		unsigned int matricula;
		Aluno aluno;
	}Registro;


	typedef struct INDEX_TABLE *pINDEX_TABLE;
	typedef struct INDEX_TABLE **ppINDEX_TABLE;


	typedef struct Registro *pREGISTRO;
	typedef struct Registro **ppREGISTRO;

	typedef struct Aluno *pALUNO;
	typedef struct Aluno **ppALUNO;

//	typedef struct Disciplinas *pDISCIPLINAS;
//	typedef struct Disciplinas **ppDISCIPLINAS;

	typedef struct DataNascimento *pDATANASCIMENTO;
	typedef struct DataNascimento **ppDATANASCIMENTO;


	typedef struct INDEX_TABLE{
		unsigned int byteIndex;
	}INDEX_TABLE;


    typedef struct Table {
    unsigned int numElements;
    unsigned int key;
    unsigned int *hashTableColisoes;
    int deleted;
} Table;

typedef struct HashTable {
    unsigned int numElements;
    unsigned int sizeOfTable;
    Table **hashTable;
} HashTable;

    typedef struct tabelaIndex{
        int id;
        int posicao;
    }TabelaIndex;



