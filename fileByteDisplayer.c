#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("ERROR: Path to the file must be specified\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "rb");

    if (file == NULL) {
        printf("ERROR: Specified file does not exist\n");
        return 2;
    }

    int linesToRead = -1;
    int linesToSkip = 0;
    int endLine = -1;
    int lineSize = 16;


    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            linesToSkip = atoi(argv[i + 1]);
            if (linesToSkip < 0) {
                printf("WARNING: Number of skipped lines cannot be negative. No lines will be skipped\n");
                linesToSkip = 0;
            }
        }
        else if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            endLine = atoi(argv[i + 1]);
            if (endLine < 1) {
                printf("WARNING: The final line line has to be at least the first one. Reverting to default behaviour\n");
                endLine = -1;
            }
        }
        else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            linesToRead = atoi(argv[i + 1]);
            if (linesToRead < 1) {
                printf("WARNING: At least one line must be read. Reverting to default behaviour\n");
                linesToRead = -1;
            }
        }
        else if (strcmp(argv[i], "-l") == 0 && i + 1 < argc)
        {
            lineSize = atoi(argv[i + 1]);
            if (lineSize < 1) {
                printf("WARNING: Each line must contain at least one byte. Reverting to default (16)\n");
                lineSize = 16;
            }
        }
        else{
            printf("ERROR: Unrecognized argument: %s\n", argv[i]);
            continue;
        }
        i++;
    }

    if (endLine != -1) {
        if (linesToRead != -1)
            linesToRead = linesToRead < endLine - linesToSkip + 1 ? linesToRead : endLine - linesToSkip + 1;
        else
            linesToRead = endLine - linesToSkip + 1;
    }

    fseek(file, linesToSkip * lineSize, SEEK_SET);

    int linesRead = 0;
    unsigned char bytes[lineSize];

    while(!feof(file) && (linesToRead <= 0 || linesRead < linesToRead))
    {
        printf("%3d. ", linesRead + linesToSkip);

        int cutOffVal = lineSize;
        for(int i = 0; i < lineSize; i++)
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
            if((bytes[i] < 32 && bytes[i] != 26) || bytes[i] == 127)
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
