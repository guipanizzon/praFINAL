#include "Escola.h"
#include "Random_data.h"
#include "File_manager.h"

#define DESATIVADO 0
#define SIZE_DIGITOS_HASH 6
#define SIZE_DIGITOS_UNSIGNED_INT 10

unsigned int shortHash(unsigned int x) {
    char stringNum[SIZE_DIGITOS_UNSIGNED_INT * 2];
    char stringShort[SIZE_DIGITOS_HASH + 1];
    int i;

    //converte para string
    sprintf(stringNum, "%u", x);

    memcpy(stringShort, stringNum, SIZE_DIGITOS_HASH);
    stringShort[SIZE_DIGITOS_HASH] = '\0';

    return atoi(stringShort);
}

unsigned int functionHashInt(unsigned int x) {
    x = ((x >> 16) ^ x) * 0x3335b369;
    x = ((x >> 16) ^ x) * 0x3335b369;
    x = ((x >> 16) ^ x);
    return shortHash(x);
}

unsigned long function_hash_2(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

void criarHash(HashTable *table);
unsigned int shortHash(unsigned int x);
unsigned int functionHashInt(unsigned int x);

Table* busca_hash(unsigned int key, HashTable *table);
void remove_hash (unsigned int key, HashTable* table);
void show_hash(unsigned int key, HashTable* table);

void menu();

// main menu

int main() {
    printf("\t\tMenu\n");
    printf("\nWhat you want to do?");
    menu();
    return 0;
}

void menu() {
    //to use random values
    srand(time(NULL));
	HashTable *table;
    int menu, submenu, status = 0, subsubmenu;
    int size, blockSize=2048, qntEntries;

    unsigned int key;
    // execution time control
    clock_t time_start, time_end;

    do {
        printf("\n[1] Generate multiple random entries by quantities");
        printf("\n[2] Generate multiple random entries by file size");
        //printf("\n[3] Read entry in position using block");
        printf("\n[4] Read entries");
        printf("\n[7] Generate indexTable");
        printf("\n[8] Create Hash");
        printf("\n[9] Remove Hash");
        printf("\n[10] Show Hash");
        printf("\n[0] Exit\n");
        printf("\n");
        scanf("%d", &menu);

        switch (menu) {
            case 0:
                break;
            case 1:
                printf("What is the quantities entries?\n");
                scanf("%d", &qntEntries);

                //printf("What is the block size?\n");
                //scanf("%d",&blockSize);

                time_start = time(NULL);
                //generateRandomEntriesByQnt(qntEntries,blockSize);
                insert(qntEntries);
                time_end = time(NULL);

                executionTime(time_start, time_end);
                break;
            case 2:
                printf("\n Chose size:");
                printf("\n[0] MB");
                printf("\n[1] GB (default)");
                printf("\n");
                scanf("%d", &submenu);

                printf("What size?\n");
                switch (submenu) {
                    case 0:
                        scanf("%d", &size);
                        size *= 1024 * 1024;
                        break;
                    default:
                        scanf("%d", &size);
                        size *= 1024 * 1024 * 1024;
                        break;
                }

                printf("What is the block size?\n");
                scanf("%d", &blockSize);
                time_start = time(NULL);
                generateRandomEntriesBlock(size, blockSize);
                time_end = time(NULL);
                executionTime(time_start, time_end);
                break;

            case 3:
                printf("What is the block size?\n");
                scanf("%d", &blockSize);
                time_start = time(NULL);
                readRandomEntriesBlock(blockSize);
                time_end = time(NULL);
                executionTime(time_start, time_end);
                break;

            case 4:
                read();
                break;
            case 7:
		time_start = time(NULL);
                createIndexTable();
                time_end = time(NULL);

                executionTime(time_start, time_end);

                break;

            case 8:
                 criarHash(table);
                 break;

			case 9:
				printf("Enter the key:\n");
				scanf("%d",&key);
				remove_hash(key, table);
				break;

			case 10:
				printf("Enter the key: \n");
				scanf("%d",&key);
				show_hash(key, table);
            default:
                printf("\nPlease, select a valid option!!!");
                break;
        }

    } while (menu != 0);
}

void executionTime(clock_t time_start, clock_t time_end) {
    double duration;
    // calc time elapsed
    duration = (double) (time_end - time_start); /// CLOCKS_PER_SEC;

    // print elapsed time
    printf("\n=> This function was running for %.2lf seconds\n", duration);
}

void generateRandomEntriesByQnt(int qntEntries, int blockSize) {
    ppALUNO ppAluno;

    FILE** ppFile;
    ppFile = (FILE**) malloc(sizeof (FILE*));
    //ppREGISTROs *ppRegistro;
    pREGISTRO *ppRegistro;
    int i = 0;
    printf("Generating random entries ....\n");

    int currSizeBlock = 0;
    int maxSizeBlock = blockSize; //4096;//1024;//2048;//4096;

    int count = 0;
    int id = -1;

    //* multiply by 2 just to ensure enougth space
    int lenght = maxSizeBlock;
    ppRegistro = (ppREGISTRO) malloc(sizeof (pREGISTRO) * lenght);
    for (i = 0; i < lenght; i++) {
        ppRegistro[i] = (pREGISTRO) malloc(sizeof (Registro));
    }

    ppAluno = (ppALUNO) malloc(sizeof (pALUNO));
    (*ppAluno) = (pALUNO) malloc(sizeof (Aluno));
    long currSizeFile = 0.0f;
    int qnt = qntEntries;
    openFile(ppFile, "a+b");
    for (i = 0; i < qntEntries; i++) {
        currSizeBlock = 0;
        count = 0;

        while (((currSizeBlock + sizeof (Registro)) <= maxSizeBlock)) {
            count++; //keep count

            //Generete Aluno
            randomAluno(ppAluno);
            //Generate Data
            id++;
            ppRegistro[i]->matricula = id;

            //copy the random Aluno generated before
            memcpy(&(ppRegistro[i]->aluno), (*ppAluno), sizeof (Aluno));

            //		i++;
            currSizeBlock += sizeof (Registro);

        }
        fDataWriteBlock((*ppFile), ppRegistro, maxSizeBlock / sizeof (Registro));
        currSizeFile += currSizeBlock; //update current size of file
    }
    closeFile(ppFile);
    for (i = 0; i < lenght; i++) {
        free(ppRegistro[i]);
    }
    free(ppRegistro);
    free((*ppAluno));
    free(ppAluno);
}

void generateRandomEntriesBlock(int size, int blockSize) {
    ppALUNO ppAluno;

    FILE** ppFile;
    ppFile = (FILE**) malloc(sizeof (FILE*));
    //ppREGISTROs *ppRegistro;
    pREGISTRO *ppRegistro;
    int i = 0;
    printf("Generating random entries ....\n");
    /* long maxSizeFile = 1073741824;//1GygaByte */
    long maxSizeFile = size;
    /* int currSizeFile = 0; */
    int currSizeBlock = 0;
    int maxSizeBlock = blockSize; //4096;//1024;//2048;//4096;

    int count = 0;
    int id = -1;

    //* multiply by 2 just to ensure enougth space
    int lenght = maxSizeBlock;
    ppRegistro = (ppREGISTRO) malloc(sizeof (pREGISTRO) * lenght);
    for (i = 0; i < lenght; i++) {
        ppRegistro[i] = (pREGISTRO) malloc(sizeof (Registro));
    }

    ppAluno = (ppALUNO) malloc(sizeof (pALUNO));
    (*ppAluno) = (pALUNO) malloc(sizeof (Aluno));
    long currSizeFile = 0.0f;

    openFile(ppFile, "a+b");
    while (currSizeFile <= maxSizeFile) {

        currSizeBlock = 0;
        count = 0;
        i = 0;
        while ((currSizeBlock + sizeof (Registro)) <= maxSizeBlock) {
            count++; //keep count

            //Generete Aluno
            randomAluno(ppAluno);
            //GeneratrandomAlunoe Data
            id++;
            ppRegistro[i]->matricula = id;
            printf("%d\t%s\t%s\n", ppRegistro[i]->matricula, ppRegistro[i]->aluno.nome, ppRegistro[i]->aluno.sobrenome);

            //copy the random Aluno generated before
            memcpy(&(ppRegistro[i]->aluno), (*ppAluno), sizeof (Aluno));
            i++;
            currSizeBlock += sizeof (Registro);
        }
        fDataWriteBlock((*ppFile), ppRegistro, maxSizeBlock / sizeof (Registro));
        currSizeFile += currSizeBlock; //update current size of file
    }

    closeFile(ppFile);
    for (i = 0; i < lenght; i++) {
        free(ppRegistro[i]);
    }
    free(ppRegistro);
    free((*ppAluno));
    free(ppAluno);
}

void criarHash(HashTable *table) {
    FILE *tabela;
    TabelaIndex tabelaIndex;
    tabela = fopen("tabela.bin", "r");

    unsigned int count = 1000, hashId = 0, i, j = 0;
    Table **moreHashes;
    unsigned int *moreHashesColisoes;
    moreHashes = malloc(sizeof (Table*));

    int count_colisao = 0;
    int count_insercao = 0;

   // HashTable *table;
    table = malloc(sizeof(HashTable));
    table->numElements = 0;
    table->sizeOfTable = 0;
    table->hashTable = malloc(sizeof (Table*));
    *(table)->hashTable = malloc(sizeof (Table));


    printf("Entering an integer value \n");

    do {
        fread(&tabelaIndex, sizeof (TabelaIndex), 1, tabela);
       // printf("id: %d \t posicao: %d\n", tabelaIndex.id, tabelaIndex.posicao);

        hashId = functionHashInt(tabelaIndex.id);

        if (hashId > table->sizeOfTable) {
            moreHashes = realloc(table->hashTable, (hashId + 1) * sizeof (Table*));


            if (moreHashes != NULL) {

                for (i = table->sizeOfTable; i < hashId + 1; i++) {
                    moreHashes[i] = malloc(sizeof (Table));
                    moreHashes[i]->hashTableColisoes = malloc(sizeof (unsigned int));
                    moreHashes[i]->numElements = 0;
                }

                table->sizeOfTable = hashId + 1;
                (table)->hashTable = moreHashes;


            } else {
                free(table->hashTable);
                free(table);
                puts("Error (re)allocating memory");
                exit(1);
            }
        }

        //detecta colisao
        if (table->hashTable[hashId]->numElements != 0) {

            int numElements = table->hashTable[hashId]->numElements;
            moreHashesColisoes = (unsigned int *) realloc(table->hashTable[hashId]->hashTableColisoes, numElements * sizeof (unsigned int));

            if (moreHashesColisoes != NULL) {

                table->hashTable[hashId]->hashTableColisoes = moreHashesColisoes;

                table->hashTable[hashId]->hashTableColisoes[numElements - 1] = tabelaIndex.id;
                table->hashTable[hashId]->numElements = numElements + 1; // numElements;

                table->numElements += 1;
            } else {
                free(table->hashTable);
                free(table);
                puts("Error (re)allocating memory in collision");
                exit(1);
            }

            //printf("Colisao!!\n");
            count_colisao++;
        } else { //insere sem colisao
            table->hashTable[hashId]->key = tabelaIndex.id;
            table->hashTable[hashId]->numElements += 1;
            table->numElements += 1;
            table->hashTable[hashId]->deleted = 0;
        }
        count_insercao++;
        i++;
    } while (!feof(tabela));
    fclose(tabela);

    printf("Numbers entered: \n");
    for (i = 0; i < table->sizeOfTable; i++) {

        if (table->hashTable[i]->numElements != 0) {
         //   printf("%d=> %d ", i, table->hashTable[i]->key);

            if (table->hashTable[i]->numElements > 0) {
            //    printf(" [ ");

                for (j = 0; j < table->hashTable[i]->numElements - 1; j++) {
            //        printf("%d ", table->hashTable[i]->hashTableColisoes[j]);
                }
             //   printf("]\n");
            }
        }
    }

    printf("\nTotal de insercao: %d\n", count_insercao);
    printf("Total de colisao: %d\n", count_colisao);
    printf("Total indices alocados: %d\n", table->sizeOfTable);

    for (i = 0; i < table->sizeOfTable; i++) {
        free(table->hashTable[i]->hashTableColisoes);
    }
    free(table);
    free(moreHashes);
}

void read() {

    ppALUNO ppAluno;
    ppAluno = (ppALUNO) malloc(sizeof (pALUNO));
    (*ppAluno) = (pALUNO) malloc(sizeof (Aluno));
    FILE *fin = fopen("cadastroAlunos.bin", "r");
    while (!feof(fin)) {
        fread((*ppAluno), sizeof (Aluno), 1, fin);
        printf("%d\n", (**ppAluno).idMatricula);
    }

    fclose(fin);

}


void createIndexTable(){

    // printf("%d",sizeof(Aluno));
    TabelaIndex tabelaIndex;
    Aluno readTabela;
    FILE *tabela = fopen("tabela.bin", "w");

    //open file and read its size
    /*
    openFile(ppFile,"r+b");
    fseek((*ppFile), 0, SEEK_END);
    file_size = ftell((*ppFile)) / sizeof(Registro);
    rewind((*ppFile));

	ppRegistro = (ppREGISTRO) malloc(sizeof(pREGISTRO) * file_size);
	for(i = 0; i < file_size - 1; i++){
		ppRegistro[i] = (pREGISTRO) malloc(sizeof(Registro));
	}

	//read entire file at once
    fread((*ppRegistro), sizeof(Registro), file_size, (*ppFile));
	*/

    FILE *arquivoCadd = fopen("cadastroAlunos.bin", "r");
    int posicao = 0;

    while (!feof(arquivoCadd)) {

        fread(&readTabela, sizeof (Aluno), 1, arquivoCadd);
        posicao = posicao + sizeof (Aluno);
        tabelaIndex.id = readTabela.idMatricula;
        tabelaIndex.posicao = posicao;

        fwrite(&tabelaIndex, sizeof (TabelaIndex), 1, tabela);
      //  printf("id: %d \t posicao: %d\n", tabelaIndex.id, tabelaIndex.posicao);
    }

    fclose(arquivoCadd);
    fclose(tabela);

}

void insert(int quant) {
    //example data = {1, "Hello!", 3.14159265}, read_data;
    Aluno aluno, read, readTabela;
    //aluno.idMatricula=1;

    ppALUNO ppAluno;
    ppAluno = (ppALUNO) malloc(sizeof (pALUNO));
    (*ppAluno) = (pALUNO) malloc(sizeof (Aluno));

    FILE* fout = fopen("cadastroAlunos.bin", "w");
    int i;
    for (i = 0; i < quant; i++) {

        randomAluno(ppAluno);
        (*ppAluno)->idMatricula = i;
        fwrite((*ppAluno), sizeof (Aluno), 1, fout);
    }

    fclose(fout);

}

void generateIndexTable() {
    
    
   
    ppALUNO ppAluno;

    FILE** ppFile;
    ppFile = (FILE**) malloc(sizeof (FILE*));

    int i = 0;

    int count = 0;
    int id = -1;
    int ask;
    int position;

    //* multiply by 2 just to ensure enougth space

    //ppRegistro = (ppREGISTRO) malloc(sizeof(pREGISTRO) * lenght);

    //for(i=0;i<lenght;i++){
    //	ppRegistro[i] = (pREGISTRO) malloc(sizeof(Registro));
    //}
    pREGISTRO pRegistro;
    pRegistro = (pREGISTRO) malloc(sizeof (Registro));
    ppAluno = (ppALUNO) malloc(sizeof (pALUNO));
    (*ppAluno) = (pALUNO) malloc(sizeof (Aluno));
    printf("Reading the first block ...\n");
    position = -1;
    openFile(ppFile, "r");
    i = -1;
    int ch = getc((*ppFile));
    while (ch != EOF) {

        fseek(*ppFile, sizeof (Registro) * i, SEEK_SET);
        fread(pRegistro, sizeof (Registro), 1, *ppFile);
        //  fDataReadBlock((*ppFile),ppRegistro,(sizeof(Registro)), position);
        printEntries(pRegistro);
        i++;
    }
    closeFile(ppFile);

    free(pRegistro);
    free(pRegistro);
    free((*ppAluno));
    free(ppAluno);
}

void readRandomEntriesBlock(int blockSize) {
    ppALUNO ppAluno;

    FILE** ppFile;
    ppFile = (FILE**) malloc(sizeof (FILE*));
    ppREGISTRO ppRegistro;
    int i = 0;

    int count = 0;
    int id = -1;
    int ask;
    int position;

    //* multiply by 2 just to ensure enougth space
    int lenght = blockSize;
    ppRegistro = (ppREGISTRO) malloc(sizeof (pREGISTRO) * lenght);

    for (i = 0; i < lenght; i++) {
        ppRegistro[i] = (pREGISTRO) malloc(sizeof (Registro));

    }

    ppAluno = (ppALUNO) malloc(sizeof (pALUNO));
    (*ppAluno) = (pALUNO) malloc(sizeof (Aluno));

    printf("Reading the first block ...\n");
    position = -1;
    do {
        position++;

        openFile(ppFile, "r+b");
        fDataReadBlock((*ppFile), ppRegistro, blockSize / (sizeof (Registro)), position);

        i = 0;
        while (i < blockSize / sizeof (Registro)) {
            printEntries(ppRegistro[i]);
            i++;
        }
        closeFile(ppFile);

        printf("What now?\n");
        printf("[0] Next Block\n");
        printf("[1] Stop reading ...\n");
        scanf("%d", &ask);
    } while (ask == 0);

    for (i = 0; i < lenght; i++) {
        free(ppRegistro[i]);
    }
    free(ppRegistro);
    free((*ppAluno));
    free(ppAluno);
}

Table* busca_hash(unsigned int key, HashTable *table) {
    unsigned int hashId = functionHashInt(key);

    if (table->hashTable[hashId]->key == key) {
        if (table->hashTable[hashId]->deleted == 0) {
            return table->hashTable[hashId];
        }
    }
    return NULL;
}

void remove_hash (unsigned int key, HashTable* table) {
    int i;
    Table* hash = busca_hash(key, table);
    hash->deleted = 1;
}

void show_hash(unsigned int key, HashTable* table) {
     unsigned int hashId = functionHashInt(key), i;

     if (table->hashTable[hashId]->key == key) {
        printf("\ntable->hashTable[hashId]->key %d", table->hashTable[hashId]->key);
        printf("\ntable->hashTable[hashId]->numElements %d", table->hashTable[hashId]->numElements);
        printf("\ntable->hashTable[hashId]->deleted %d", table->hashTable[hashId]->deleted);
        printf("\n");
     }
}
