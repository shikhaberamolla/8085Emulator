# 8085Emulator
This project is a 8085 Emulator created in C++
It consists of:
3 Header files-
            reg.h-->To store and display the states of all the registers and flags.
            instdet.h-->Contains definitions of different instructions and their respective functions.
            mapfunc.h-->Links the instructions functions to our main program.
File with the main function
A .txt file which contains the microprocessor level code
    The first line of the file gives us the starting address of memory.
    The program is read from the file and stored in a map.
The output shows the final state of the registers and the values sotred in the memory locations mentioned in the program.
