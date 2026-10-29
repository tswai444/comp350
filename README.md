# Project C - Operating System Project

Name: Trinity Swai

## 1. What I Did
In this project, I added file reading and program execution to the OS, and built a basic shell:

* **readFile:** Added a function to look through the disk directory at sector 2, find a file matching a given name, and read its sectors into a buffer.
* **executeProgram:** Wrote a function to load a program into memory segment 0x2000 and run it using launchProgram.
* **terminate:** Updated terminate so that when a program finishes running, it automatically reloads and executes the shell instead of freezing.
* **Interrupt 0x21:** Updated handleInterrupt21 to support AX=3 (readFile), AX=4 (executeProgram), and AX=5 (terminate).
* **Shell (shell.c):** Created a basic shell program that prompts the user for input and supports two commands using syscalls:
  - `type <filename>`: Prints out the contents of a text file.
  - `exec <filename>`: Runs another program.
* **loadFile utility:** Used loadFile.c to put the kernel, shell, test programs, and message file directly onto diskc.img.

## 2. How to Verify It
1. Run `./compileOS.sh` in the terminal to compile all files and load them onto `diskc.img`.
2. Boot `diskc.img` in the emulator.
3. When the shell loads, test reading a file by typing:
   `type messag`
   This will print out the text from message.txt.
4. Test running a program by typing:
   `exec tstpr2`
   This will run tstpr2, print "tstpr2 is working!", and then bring you back to the shell prompt.