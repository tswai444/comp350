//Trinity Swai
//10-27-2026

#include <stdio.h>

int main(int argc, char* argv[])
{
    int i;
    if (argc < 2)
    {
        printf("Specify file name to load\n");
        return 0;
    }

    FILE* loadFil;
    loadFil = fopen(argv[1], "r");
    if (loadFil == 0)
    {
        printf("File not found\n");
        return 0;
    }

    FILE* floppy;
    floppy = fopen("diskc.img", "r+");
    if (floppy == 0)
    {
        printf("diskc.img not found\n");
        return 0;
    }

    // Load the disk map from sector 1, tracks available sectors
    char map[512];
    fseek(floppy, 512, SEEK_SET);
    for (i = 0; i < 512; i++)
        map[i] = fgetc(floppy);

    // Load the directory from sector 2
    char dir[512];
    fseek(floppy, 512 * 2, SEEK_SET);
    for (i = 0; i < 512; i++)
        dir[i] = fgetc(floppy);

    for (i = 0; i < 512; i = i + 0x20)
        if (dir[i] == 0) break;

    if (i == 512)
    {
        printf("Not enough room in directory\n");
        return 0;
    }
    int dirindex = i;

    for (i = 0; i < 6; i++)
        dir[dirindex + i] = 0x00;

    for (i = 0; i < 6; i++)
    {
        if (argv[1][i] == 0) break;
        dir[dirindex + i] = argv[1][i];
    }
    dirindex = dirindex + 6;

    int sectcount = 0;
    int fileEnded = 0;
    while (!fileEnded)
    {
        if (sectcount == 26)
        {
            printf("Not enough space in directory entry for file\n");
            return 0;
        }

        // Search map for an available sector (0x00 = free)
        for (i = 3; i < 256; i++)
            if (map[i] == 0) break;

        if (i == 256)
        {
            printf("Not enough room for file\n");
            return 0;
        }

        // Mark map entry as taken (0xFF = used)
        map[i] = 0xFF;
        dir[dirindex] = i;
        dirindex++;
        sectcount++;

        fseek(floppy, i * 512, SEEK_SET);
        for (i = 0; i < 512; i++)
        {
            int c = fgetc(loadFil);
            if (c == EOF)
            {
                fputc(0x0, floppy);
                fileEnded = 1;
                break;
            }
            else
            {
                fputc(c, floppy);
            }
        }
    }

    // Write updated map back to sector 1
    fseek(floppy, 512, SEEK_SET);
    for (i = 0; i < 512; i++)
        fputc(map[i], floppy);

    // Write updated directory back to sector 2
    fseek(floppy, 512 * 2, SEEK_SET);
    for (i = 0; i < 512; i++)
        fputc(dir[i], floppy);

    fclose(floppy);
    fclose(loadFil);
    return 0;
}