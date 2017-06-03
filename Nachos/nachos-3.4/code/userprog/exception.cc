// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.


#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>


#define BUF_SIZE 100
char buf[100];

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

void updatePC(){

		// Note that we have to maintain three PC registers, 
		// namely : PCReg, NextPCReg, PrevPCReg. 
		// (See machine/machine.cc, machine/machine.h) for more details.
		int pc, nextpc, prevpc;

		// Read PCs
		prevpc = machine->ReadRegister(PrevPCReg);
		pc = machine->ReadRegister(PCReg);
		nextpc = machine->ReadRegister(NextPCReg);

		// Update PCs
		prevpc = pc;
		pc = nextpc;
		nextpc = nextpc + 4;	// PC incremented by 4 in MIPS

		// Write back PCs
		machine->WriteRegister(PrevPCReg, prevpc);
		machine->WriteRegister(PCReg, pc);
		machine->WriteRegister(NextPCReg, nextpc);
	}



void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

   switch(which)
    {
        case SyscallException:
            switch(type)
            {
                case SC_Halt:
                         DEBUG('a', "Shutdown, initiated by user program.\n");
                         interrupt->Halt();
                         break;
                case SC_Close: 
		        {
		  
	                     DEBUG('a', "Close() system call invoked \n");
		  	
		                 int fd2 = machine->ReadRegister(4);
		                 close(fd2);

		                 updatePC();
		        }	
		        break;

				case SC_Print:	
				   		 {
                         DEBUG('a', "Print() system call invoked \n");
						 int vaddr = machine->ReadRegister(4);     //arguments are stored in from r4 r5 ...etc...only one argument hence r4
						 // This address (pointer to the string to be printed) is 
						 // the address that pointes to the user address space.
						 // Simply trying printf("%s", (char*)addr) will not work
						 // as we are now in kernel space.

						 // Get the string from user space.

						 int size = 0;

						 buf[BUF_SIZE - 1] = '\0';               // For safety.

						 do{
						 // Invoke ReadMem to read the contents from user space

						 machine->ReadMem(vaddr,    // Location to be read
						 sizeof(char),      // Size of data to be read
						 (int*)(buf+size)   // where the read contents 
				          );                 // are stored ...inititally in the beginnig of the array buf

						 // Compute next address
						 vaddr+=sizeof(char);    size++;

						 } while( size < (BUF_SIZE - 1) && buf[size-1] != '\0');

						 size--;
						 DEBUG('a', "Size of string = %d", size);

						 printf("%s", buf);
						 bzero(buf, sizeof(char)*BUF_SIZE);  // Zeroing the buffer.
						 updatePC();
						 }
					     break; // SC_Print
                         
                  case SC_Open:	
				   		 {
						 DEBUG('a', "Open() system call invoked \n");
						 int fd = machine->ReadRegister(4);     //arguments are stored in from r4 r5 ...etc...only one argument hence r4 filename
						 
						 int size = 0;

						 buf[BUF_SIZE - 1] = '\0';               // For safety.

						 do{
						 // Invoke ReadMem to read the contents from user space

						 machine->ReadMem(fd,    // Location to be read
						 sizeof(char),      // Size of data to be read
						 (int*)(buf+size)   // where the read contents 
				          );                 // are stored

						 // Compute next address
						 fd+=sizeof(char);    size++;

						 } while( size < (BUF_SIZE - 1) && buf[size-1] != '\0');

						 size--;           //one extra null char
						 DEBUG('a', "Size of string = %d", size);

						 int fd1=open(buf,O_CREAT|O_RDWR,0666);
						 machine->WriteRegister(2,fd1);
						 bzero(buf, sizeof(char)*BUF_SIZE);  // Zeroing the buffer.
						 updatePC();
						 }
					     break; // SC_Open

					case SC_Write:	
		            {
		
						 DEBUG('a', "Write() system call invoked \n");
						 int ipstring = machine->ReadRegister(4);
		
						 int ipsize = machine->ReadRegister(5);
		
						 int fd3 = machine->ReadRegister(6);
		
						 int size = 0;

						 buf[BUF_SIZE - 1] = '\0';               // For safety.

						do{
			// Invoke ReadMem to read the contents from user space

							machine->ReadMem(ipstring,    // Location to be read
							sizeof(char),      // Size of data to be read
							(int*)(buf+size)   // where the read contents 
							);                 // are stored

			// Compute next address
							ipstring+=sizeof(char);    size++;

						} while( size < (BUF_SIZE - 1) && buf[size-1] != '\0'); // till last character is not a null character or the size exceeds the buffer

						size--;
						DEBUG('a', "Size of string = %d", size); // last is null so subtract 1
		
						if( ipsize > size )  
				     	ipsize = size;          // only the actual size read and written is stored

						printf("Content To Be Written : %s", buf);
						if( (write(fd3,buf,ipsize)) < 0)
		 			    printf("ERROR...ERROR\n");
		
						bzero(buf, sizeof(char)*BUF_SIZE);  // Zeroing the buffer.
						updatePC();
		    
		
							}
					break;
						case SC_Read:	
						{
		
						DEBUG('a', "Read() system call invoked \n");
						int ipstring = machine->ReadRegister(4);
		
						int ipsize = machine->ReadRegister(5);
		
						int fd4 = machine->ReadRegister(6);
			
						bzero(buf, sizeof(char)*BUF_SIZE);
						int sizeread;
						sizeread = read(fd4,buf,ipsize);  // the no of bytes read is returned 
						if( sizeread < 0)
		  				  printf("ERROR...ERROR\n");

						printf("\nContent Read : %s\n", buf);
		
						int size;
						for(size =0; size < sizeread ; size++ )      //this write has to be performed as the return 
                                                    //type of read is int and the return value is the size of the string 
						{
						machine->WriteMem(ipstring,    // Location to be read
						sizeof(char),      // Size of data to be read
						(int)(buf+size)   // where the read contents 
						);                 // are stored

			// Compute next address
						ipstring+=sizeof(char);  // the int ipstring is incremented by the size of the char while 
									 // correspondingly the size variable is incremented by 1 for every char read 

						}

						size--;                     // the last char is null char '\0'
						DEBUG('a', "Size of string = %d", size);
		
						machine->WriteRegister(2,sizeread);   //reg2 always stores the return value
						bzero(buf, sizeof(char)*BUF_SIZE);  // Zeroing the buffer.
						updatePC();
		    
						}
		
		    		break; // SC_Read

		case SC_Sed:	
						{
                           		
						DEBUG('a', "Sed() system call invoked \n");
						int arg1 = machine->ReadRegister(4);
		
						int arg2 = machine->ReadRegister(5);
		
						int file = machine->ReadRegister(6);
                        system("sed s/$word1/$word2/g $file");		


						}
                 break;
                
                 default:
                        printf("Unknown/Unimplemented system call %d!", type);
                        ASSERT(FALSE); // Should never happen
                        break;
            } // End switch(type)
	break; // End case SyscallException

    default:
                printf("Unexpected user mode exception %d %d\n", which, type);
                ASSERT(FALSE);
    break;
    }
}



	
