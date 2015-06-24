/*
 * File_manager.h
 *
 *  Created on: Mar 16, 2015
 *      Author: gui
 */

#ifndef FILE_MANAGER_H_
#define FILE_MANAGER_H_
#pragma once
#include "Escola.h"

void closeFile(FILE **ppFile);
void openFile(FILE **ppFile, char* param);
void printEntries(pREGISTRO pRegistro);

void fDataWriteBlock(FILE* pFile, ppREGISTRO ppRegistro, int quanty);
void fDataReadBlock(FILE* pFile, ppREGISTRO ppRegistro, int quanty, int position);
void fileGenericProblemError();
void readEntryPosition(int position);
void fDataReadPosition(FILE* pFile, pREGISTRO pRegistro, int position);
void fDataRead(FILE* pFile, pREGISTRO pRegistro);
void fIndexTableWriteBlock(FILE* pFile, ppINDEX_TABLE ppIndex_Table, int quanty);
void fIndexTableReadBlock(FILE* pFile, ppINDEX_TABLE ppIndex_Table, int quanty, int position);
void openFileIndexTable(FILE **ppFile, char* param);

#endif /* FILE_MANAGER_H_ */
