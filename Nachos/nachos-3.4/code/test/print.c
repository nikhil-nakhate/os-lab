#include "syscall.h"
  void main()
  {
   int id,rd;
   char *p = "NIKNAK";
   char buff[100];
   Print("Hello World\n");
   
   id = Open("this.txt");
   Write(p,8,id);
   Close(id);
   id = Open("this.txt");
   rd=Read(buff,12,id);
   Close(id);
   Halt();	// Optional. Just print stats
  }
