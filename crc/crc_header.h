#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#define table_size 94*94*94*94

unsigned __int64 crc_table[256];
unsigned char crc_input[256];
unsigned __int64 crc_middle[table_size];
unsigned __int64 crc_middle_tmp[table_size];
int crc_middle_index[table_size];


//asdf
void init_data(void);

//calc value, before_value, text / return after_value
unsigned __int64 crc_cacl(before_value, text);
//rev calc value, after_value, text / return before_value
unsigned __int64 crc_rev(after_value, text);

//compare function for qsort
int compare(const void* a, const void* b);

