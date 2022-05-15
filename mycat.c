#include <stdio.h>		/* Header file for printf */
#include <sys/types.h>		/* Header file for system call  open */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>		/* Header file for system calls read, write y close */

#define BUFF 1024 /*size to read */



int main(int argc, char *argv[])
{

	/*If the number of arguments is less than two (argv[0] -> program, argv[|] -> file to be shown) we print the error and return -1*/

	if(argc < 2)
	{
		printf("Not enough arguments\n");
		return -1;
	}

	/*Extract the file name passed as argument */
	char *fileName=argv[1]; 
	int fidin;
	char buffer[BUFF]; /*Array to store the elements read from the file */
	int nread;

	fidin = open(fileName,O_RDONLY);
	
	if(fidin < 0){
	perror("Error opening the input file"); /* Unable to open the file */
	return -1;
	}

	
	nread = read(fidin,buffer,BUFF); /* Read the elements from the file */

	
	while (nread > 0){
	
	/*Write the content in the buffer in the standard output (console) */
	int nwrite = write(STDOUT_FILENO,buffer,nread); 

	if(nwrite < nread){
	/* Error writing the content of the buffer in the file */
	perror("Error writing in the output file"); 
	close(fidin);
	return -1;
	}

	nread = read(fidin,buffer,BUFF); /* Read the elements from the file */
	}


	if(nread==-1){
	perror("Error reading the file"); /* Error when reading the file */
	close(fidin);
	return-1;
	}


	close(fidin);


	return 0;
}
