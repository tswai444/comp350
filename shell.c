//Trinity Swai
//10-27-2026

main() {
    char line[100];
    char buffer[13312];
    int sectorsRead;

    while(1) {
        syscall(0, "SHELL> ");
        syscall(1, line);

        /* Handle "type filename" command[cite: 5] */
        if (line[0] == 't' && line[1] == 'y' && line[2] == 'p' && line[3] == 'e' && line[4] == ' ') {
            char filename[7];
            int i;
            for (i = 0; i < 6; i++) {
                filename[i] = line[5 + i];
                if (line[5 + i] == '\r' || line[5 + i] == '\n' || line[5 + i] == '\0') {
                    filename[i] = '\0';
                    break;
                }
            }
            filename[6] = '\0';

            syscall(3, filename, buffer, &sectorsRead);
            if (sectorsRead > 0) {
                syscall(0, buffer);
                syscall(0, "\r\n");
            } else {
                syscall(0, "File not found!\r\n");
            }
        }
        /* Handle "exec programname" command[cite: 6] */
        else if (line[0] == 'e' && line[1] == 'x' && line[2] == 'e' && line[3] == 'c' && line[4] == ' ') {
            char progname[7];
            int i;
            for (i = 0; i < 6; i++) {
                progname[i] = line[5 + i];
                if (line[5 + i] == '\r' || line[5 + i] == '\n' || line[5 + i] == '\0') {
                    progname[i] = '\0';
                    break;
                }
            }
            progname[6] = '\0';

            syscall(4, progname);
            syscall(0, "Bad Program or Not Found!\r\n");
        }
        else {
            syscall(0, "Bad Command!\r\n");
        }
    }
}