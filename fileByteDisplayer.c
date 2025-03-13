#include <stdio.h>

int main(int argc, char **argv)
{
    unsigned char bytes[16];

    FILE* file = fopen(argv[1], "rb");

    int linesToRead = -1;
    if (argc == 3) {
        linesToRead = atoi(argv[2]);
    }

    int linesRead = 0;

    while(!feof(file) && (linesToRead <= 0 || linesRead < linesToRead))
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
