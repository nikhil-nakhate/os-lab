#include <stdio.h> 
#include <sys/stat.h> 

int main (int argc, char* argv[]) 
   {
      char* filename = argv[1]; 
      struct stat buf;
      
      stat (filename, &buf); 
      
      if (buf.st_mode & S_IWUSR)
         printf ("User has write permission for the file %s\n", filename); 
      else
         printf ("User doesn't have write permission for the file %s\n", filename);
      return 0; 
   }
