#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "csv.h"

//Преобразование входного файла в csv формате в 2 файла test и train в формате fann
//Требует libcsv
bool csv2fann(const char * filename, int inputcount, int outputcount, float traincount);

int rowc(const char * filename);

bool csv2fann2(const char * filename, int inputcount, int outputcount, int traincount, bool dropfirstcolandrow);

int * getparams(const char * filename);
