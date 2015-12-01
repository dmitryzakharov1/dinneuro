#include "func.h"

//////////////////////////////////////////////////
//удаление лишних пробелов в начале и конец строки
//////////////////////////////////////////////////
char *trim(char *str)
{
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;

    if( str == NULL ) { return NULL; }
    if( str[0] == '\0' ) { return str; }

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while( isspace(*frontp) ) { ++frontp; }
    if( endp != frontp )
    {
        while( isspace(*(--endp)) && endp != frontp ) {}
    }

    if( str + len - 1 != endp )
            *(endp + 1) = '\0';
    else if( frontp != str &&  endp == frontp )
            *str = '\0';

    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if( frontp != str )
    {
            while( *frontp ) { *endp++ = *frontp++; }
            *endp = '\0';
    }


    return str;
}

/////////////////////////////////////
//подсчитаем количество строк в файле
//////////////////////////////////////
int rowc(const char * filename) {
	FILE* myfile = fopen(filename, "r");
	int ch, number_of_lines = 0;

do 
{
    ch = fgetc(myfile);
    if(ch == '\n')
    	number_of_lines++;
} while (ch != EOF);

// last line doesn't end with a new line!
// but there has to be a line at least before the last line
if(ch != '\n' && number_of_lines != 0) 
    number_of_lines++;

fclose(myfile);

//printf("number of lines in test.txt = %d", number_of_lines);
return number_of_lines-1;
}


//////////////////////////////////////////////////////////////////////////
// Перевод входного файла в формате csv в формат fann 
// Также формирование единого файла или 2-х с тестовой и обучающей выборок
//
bool csv2fann2(const char * filename, int inputcount, int outputcount, int traincount, bool dropfirstcolandrow) {
FILE *infile, *testfile, *trainfile, *singlefile;
char * line = NULL;
       size_t len = 0;
       ssize_t read;
	   
char* token;
const char * delim = " ";

 //имя для единого файла
const char * singlefilename = "data.data";
//для тестовой и обучающей выборок
const char * testfilename = "data.test";
const char * trainfilename = "data.train";
		   
	   
infile = fopen(filename, "rb");
if (!infile) {
      printf("Failed to open %s: %s\n", filename, strerror(errno));
      return false;
    } else {
		printf("Successfully opened %s\n", filename);
	}
	   
	   //получим количество строк в файле
	   
	   //в начале надо узнать сколько строк в файле и пропускаем ли первую
	   //флаг пропуска первой строки
	   int rowcount = rowc(filename);
	   
	   int testrowcount, trainrowcount, singlerowcount;
	   
	   //если передать 100 в traincount создадим только файл *.data
	   if (traincount == 100) {
		  
		   
		   //формируем один файл
		   singlefile = fopen(singlefilename, "wb");
		   //printf("Successfully opened for write %s\n", singlefilename);
		   
		  if (dropfirstcolandrow) { 
			//пропускаем первую строку и столбец
		    singlerowcount = rowcount-1;			
		  } else { 
			//не пропускаем, считаем все
		    singlerowcount = rowcount;			
		  }
		  
		   //пишем первую строку
		    fprintf(singlefile, "%d %d %d\n", singlerowcount, inputcount, outputcount);
			
			//цикл построчного считывания
			int readedrowcounter = 1;	
			while ((read = getline(&line, &len, infile)) != -1) {
				//если задано пропускать первую строку и столбец
				   if ((dropfirstcolandrow == true) && (readedrowcounter == 1)) { 
				   //printf("Skip first row\n");
				   } else {
					   
					   int readedcolcounter=1;

					   if (readedrowcounter <  trainrowcount) {				   						   
						   while ((token = strsep(&line, delim)) != NULL)
							{
								//если пропускаем первый столбец, то дальше
							   if ((dropfirstcolandrow == true) && (readedcolcounter == 1)) { 
							   //printf("Skip first column\n");
							   } else {
								
													
													//printf("readedcolcounter = %d\n", readedcolcounter);
													
													//удаляем лишний пробелы из значения
													token = trim(token);
													//printf("%s\n", token);
													
													if (readedcolcounter <= inputcount+1) {
														//printf("input parameter\n");
														
														fprintf(singlefile, "%s ", token);
														//если достигли количества входных параметров, пишем новую строку
														if (readedcolcounter == inputcount+1) { fprintf(singlefile, "\n"); }
														
													} else {
														//printf("output parameter\n");
														//пишем новую строку с выходными параметрами
														fprintf(singlefile, "%s ", token);
														
														
														//если достигли конца строки, пишем новую строку
														if(readedcolcounter == (inputcount+outputcount-1)) { fprintf(singlefile, "\n"); }							
													}
								
							   }
								readedcolcounter++;
							}
						} 
				   
				   }
				readedrowcounter++;
			}
			
			fclose(singlefile);
		if (line) free(line);
		printf("Created single file with name %s\n", singlefilename);
			
		   
	   } 
	   else {
		//передано не 100, значит делим на обучающую и тестовую выборки   
		   testfile = fopen(testfilename, "wb");
			trainfile = fopen(trainfilename, "wb");
	   
	   
	   if (dropfirstcolandrow) {
		   //пропускаем первую строку и столбец
		    trainrowcount = (rowcount-1)*traincount/100;
			testrowcount = rowcount - trainrowcount;
			printf("Total rows %d\n", rowcount-1);
			printf("Train file row count %d\n", trainrowcount);
			printf("Test file row count %d\n", testrowcount);
	   } else {
		   //не пропускаем, считаем все
		    trainrowcount = rowcount*traincount/100;
			testrowcount = rowcount - trainrowcount;
			printf("Total rows %d\n", rowcount);
			printf("Train file row count %d\n", trainrowcount);
			printf("Test file row count %d\n", testrowcount);
	   }
	  
	  //запишем первую строку в файлы
	   fprintf(testfile, "%d %d %d\n", testrowcount, inputcount, outputcount);
	   fprintf(trainfile, "%d %d %d\n", trainrowcount, inputcount, outputcount);

	   //счетчик для считывания нужного количества строк и разделения на тестовую и обучающую выборки
	int readedrowcounter = 1;	
	while ((read = getline(&line, &len, infile)) != -1) {
           //printf("Retrieved line of length %zu :\n", read);
           //printf("%s", line);
		   
		   //debug
		   //printf("readedrowcounter=%d\n", readedrowcounter);
		   
		   //если задано пропускать первую строку и столбец
		   if ((dropfirstcolandrow == true) && (readedrowcounter == 1)) { 
		   //printf("Skip first row\n");
		   } else {
		   
		   //вначале обучающая выборка
		   //если не превышаем нужное количество, то пишем в обучающий файл
		   int readedcolcounter=1;

					   if (readedrowcounter <  trainrowcount) {				   						   
						   while ((token = strsep(&line, delim)) != NULL)
							{
								//если пропускаем первый столбец, то дальше
							   if ((dropfirstcolandrow == true) && (readedcolcounter == 1)) { 
							   //printf("Skip first column\n");
							   } else {
								
													
													//printf("readedcolcounter = %d\n", readedcolcounter);
													
													//удаляем лишний пробелы из значения
													token = trim(token);
													//printf("%s\n", token);
													
													if (readedcolcounter <= inputcount+1) {
														//printf("input parameter\n");
														
														fprintf(trainfile, "%s ", token);
														//если достигли количества входных параметров, пишем новую строку
														if (readedcolcounter == inputcount+1) { fprintf(trainfile, "\n"); }
														
													} else {
														//printf("output parameter\n");
														//пишем новую строку с выходными параметрами
														fprintf(trainfile, "%s ", token);
														
														
														//если достигли конца строки, пишем новую строку
														if(readedcolcounter == (inputcount+outputcount-1)) { fprintf(trainfile, "\n"); }							
													}
								
							   }
								readedcolcounter++;
							}
						} 
						
						
						else {
								//теперь пишем тестовый файл
								while ((token = strsep(&line, delim)) != NULL)
							{
								//если пропускаем первый столбец, то дальше
							   if ((dropfirstcolandrow == true) && (readedcolcounter == 1)) { 
							   //printf("Skip first column\n");
							   } else {
								
													
													//printf("readedcolcounter = %d\n", readedcolcounter);
													
													//удаляем лишний пробелы из значения
													token = trim(token);
													//printf("%s\n", token);
													
													if (readedcolcounter <= inputcount+1) {
														//printf("input parameter\n");
														
														fprintf(testfile, "%s ", token);
														//если достигли количества входных параметров, пишем новую строку
														if (readedcolcounter == inputcount+1) { fprintf(testfile, "\n"); }
														
													} else {
														//printf("output parameter\n");
														//пишем новую строку с выходными параметрами
														fprintf(testfile, "%s ", token);
														
														
														//если достигли конца строки, пишем новую строку
														if(readedcolcounter == (inputcount+outputcount-1)) { fprintf(testfile, "\n"); }							
													}
								
							   }
								readedcolcounter++;
							}
			 
						}
						
		   }
		   readedrowcounter++;
       }
	   
	   //конец формирования двух файлов
		fclose(testfile);
		fclose(trainfile);
		if (line) free(line);
		printf("Created 2 files with names: %s and %s \n", testfilename, trainfilename);
}

	   
//закрываем
fclose(infile);


return true;
}

/////////////////////////////////////////////////////////////
// Получает информацию о количестве входных и выходных данных
///////////////////////////////////	//////////////////////////
int * getparams(const char * filename) {
	static int  vals[3];
	FILE * infile;
	infile = fopen(filename, "rb");
	ssize_t read;
	char * line = NULL;
	size_t len = 0;
	char * token;
	const char * delim = " ";
	
	if ((read = getline(&line, &len, infile)) != -1) { 

	int colc=0;
		while ((token = strsep(&line, delim)) != NULL)
		{
			
			//удаляем лишний пробелы из значения
			token = trim(token);
			vals[colc] = atoi(token); 
			colc++;
		}
						
	}
	
	fclose(infile);
	return vals;
}
