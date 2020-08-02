#include "crc_header.h"


int main(void){
    //init data
    init_data();

    //init data
    unsigned char input[9] = {0,};
    unsigned __int64 before_value = 0x0;
    unsigned __int64 tmp = 0x0;
    //unsigned __int64 after_value = 0x676F5F675F695F6C;
    unsigned __int64 after_value = 0x4ce6b97f65c99119; //reversed value of crc_input[113~]
    __int64* find = 0;

   
    
    printf("\tSTART CALC CRC_VALUE\n");
    //first calculate the crc_value of crc_input[0~55]

    int cnt = 0;
    for (int i = 0x21; i < 0x7f; i++)
    {
        for (int j = 0x21; j < 0x7f; j++)
        {
            for (int k = 0x21; k < 0x7f; k++)
            {
                for (int l = 0x21; l < 0x7f; l++)
                {
                    input[0] = (unsigned char)i;
                    input[1] = (unsigned char)j;
                    input[2] = (unsigned char)k;
                    input[3] = (unsigned char)l;

                    for (int i = 0; i < 4; i++)
                    {
                        crc_input[16 * i] = input[i];
                    }

                    tmp = before_value;
                    for (int a = 0; a < 56; a++)
                    {
                        tmp = crc_cacl(tmp, crc_input[a]);
                    }

                    int index = input[0] << 24 | input[1] << 16 | input[2] << 8 | input[3];
                    crc_middle_index[cnt] = index;
                    crc_middle_tmp[cnt] = tmp;
                    //printf("\nCRC : 0x%16llx   ||  input : %s", crc_middle_tmp[cnt], (char*)&crc_middle_index[cnt]);
                    cnt++;

                }
            }
        }
    }
    
    memcpy(crc_middle, crc_middle_tmp, sizeof(crc_middle_tmp));

    //SORT IT
    printf("\tSTART SORTING\n");
    qsort(crc_middle, table_size, sizeof(unsigned __int64), compare);
    printf("\tQSORTED!!\n");
    
    /*
    first evaluate the reversed crc value of crc_input[56~112]
    
    comfirm whether the reversed value is in crc_middle or not.
    if not -> continue
    if it is -> break and print

    and then, find the input of the matched output.
    */

    printf("\tSTART CALC CRC_REV VALUE\n");

    
    for (int i = 0x21; i < 0x7f; i++)
    {
        for (int j = 0x21; j < 0x7f; j++)
        {
            for (int k = 0x21; k < 0x7f; k++)
            {
                for (int l = 0x21; l < 0x7f; l++)
                {
                    input[4] = (unsigned char)i;
                    input[5] = (unsigned char)j;
                    input[6] = (unsigned char)k;
                    input[7] = (unsigned char)l;

                    for (int i = 4; i < 8; i++)
                    {
                        crc_input[16 * i] = input[i];
                    }

                    tmp = after_value;
                    for (int a = 112; a > 55; a--)
                    {
                        tmp = crc_rev(tmp, crc_input[a]);
                    }

                    //checking value
                    
                    if (find = bsearch(&tmp, crc_middle, table_size, sizeof(unsigned __int64), compare)) {
                        
                        printf("\n\tCRC MIDDLE VALUE : 0x%llx\n\tBACK SIDE INPUT : %s\n", tmp, (char*)&input[4]);

                        for (int m = 0; m < table_size; m++)
                        {
                            if (crc_middle_tmp[m] == tmp) {
                                printf("\tFRONT SIDE INPUT : 0x%x", crc_middle_index[m]);
                                return 0;
                            }
                        }
                    }
                    else continue;


                }
            }
        }
    }

   

    
    



}