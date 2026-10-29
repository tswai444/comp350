//Trinity Swai
//10-14-2026

void printString(char* str);
void readString(char* buf);
void readSector(char* buffer, int sector);
void writeSector(char* buffer, int sector);

void readFile(char* filename, char* buffer, int* sectorsRead) {
    char dir[512];
    int dirEntry, i, j;
    int sectCount = 0;

    // Load sector 2
    readSector(dir, 2);

    //Search through the directory entries 
    for (dirEntry = 0; dirEntry < 512; dirEntry += 32) {
        int found = 1;
        for (i = 0; i < 6; i++) {
            if (dir[dirEntry + i] != filename[i]) {
                found = 0;
                break;
            }
        }
        if (found == 1) {
            // Load file sectors into buffer
            for (j = 0; j < 26; j++) {
                int sector = dir[dirEntry + 6 + j];
                if (sector == 0) break;
                readSector(buffer + (sectCount * 512), sector);
                sectCount++;
            }
            *sectorsRead = sectCount;
            return;
        }
    }
    *sectorsRead = 0;
}

void executeProgram(char* name) {
    char buffer[13312]; // Max file size (13kB)
    int sectorsRead = 0;
    int i;

    readFile(name, buffer, &sectorsRead);
    if (sectorsRead > 0) {
        for (i = 0; i < 13312; i++) {
            putInMemory(0x2000, i, buffer[i]);
        }
        launchProgram(0x2000);
    } else {
        printString("Error: program not found.\r\n");
    }
}

void terminate() {
    char shellname[6];
    shellname[0] = 's';
    shellname[1] = 'h';
    shellname[2] = 'e';
    shellname[3] = 'l';
    shellname[4] = 'l';
    shellname[5] = '\0';
    
    executeProgram(shellname);
}

void handleInterrupt21(int ax, int bx, int cx, int dx) {
    switch(ax) {
        case 0:
            printString(bx);
            break;
        case 1:
            readString(bx);
            break;
        case 2:
            readSector(bx, cx);
            break;
        case 3:
            readFile(bx, cx, dx);
            break;
        case 4:
            executeProgram(bx);
            break;
        case 5:
            terminate();
            break;
        default:
            printString("Error: invalid interrupt function.\r\n");
    }
}

void main() {
    makeInterrupt21();
    executeProgram("shell");
    while(1);
}
