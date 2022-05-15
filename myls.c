#include <stdio.h>		/* Header file for system call printf */
#include <unistd.h>		/* Header file for system call gtcwd */
#include <sys/types.h>		/* Header file for system calls opendir, readdir y closedir */
#include <dirent.h>
#include <string.h>


int main(int argc, char *argv[])
{
	char *dirName; 
	
	char address[PATH_MAX];

	DIR *dir;

	if(argc==2) /* If there is one argument passed it corresponds to the name of the directory */
	{
	dirName=argv[1];
	}
	else if (argc == 1){ /* If the name of the directory is not specified, 	use the current directory*/
	dirName = getcwd(address,PATH_MAX); // Stores in char address the current directory of maximum size PATH_MAX
	}
	else{
	perror("More arguments than needed");
	return -1;
	}
	
	dir = opendir(dirName); /* Open the directory */

	struct dirent *t1; /* Create a structure to store content of the 	directory */

	/* Error occured when opening the directory */
	if (dir == NULL){
	perror("Unable to open directory");
	return -1;}

	t1=readdir(dir);
	
	/* It will read each of the entries of the directory and print the 	name of the entry, ONE PER LINE, using printf */
	while(t1 != NULL){
	printf("%s\n",t1->d_name);
	t1=readdir(dir);}

	closedir(dir);/* Close the directory */


	return 0;
}

