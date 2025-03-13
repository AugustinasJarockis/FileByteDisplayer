#include <stdio.h>

int main(int argc, char **argv)
{
    unsigned char bytes[16];

    FILE* file = fopen(argv[1], "rb");

    int bytesToRead = -1;
    if (argc == 3) {
        bytesToRead = atoi(argv[2]);
    }

    int linesRead = 0;

    while(!feof(file) && (bytesToRead <= 0 || linesRead < (bytesToRead / 16)))
    {
        int cutOffVal = 16;
        for(int i = 0; i < 16; i++)
        {
            fscanf(file, "%c", &bytes[i]);
            if(feof(file))
            {
                cutOffVal = i;
                break;
            }
            printf("%02x ", bytes[i]);
        }

        printf("| ");

        for(int i = 0; i < cutOffVal; i++)
        {
            if(bytes[i] == 10 || bytes[i] == 11 || bytes[i] == 13)
            {
                printf("~");
            }
            else
            {
                printf("%c", bytes[i]);
            }
        }

        printf("\n");
        linesRead++;
    }
    fclose(file);
    return 0;
}
