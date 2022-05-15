#include <stdio.h>	/*Header file for system call printf*/
#include <sys/types.h>	/*Header file for system call fstat*/
#include <sys/stat.h>
#include <fcntl.h>	/*Header file for system call fcntl*/
#include <dirent.h> 	/*Header file for system call opendir, closedir,readdir...*/
#include <unistd.h>


int main(int argc, char *argv[])
{

	char address[PATH_MAX]; /* Array to store the current working directory */

	char *dirName; 
	
	DIR *dir; /* Initializing dir pointer to DIR structure */

	/*The function does not need arguments to be passed */
	if(argc > 1)
	{
		printf("No arguments needed\n");
		return -1;
	}

	dirName = getcwd(address,PATH_MAX);/* Use the current directory*/
	dir = opendir(dirName); /* Open the directory */

	struct dirent *t1; /* Create a structure to store content of the 	directory */

	/* Error occured when opening the directory */
	if (dir == NULL){
	perror("Unable to open directory\n");}

	t1 = readdir(dir);

	/* It will read each of the entries of the directory */
	while(t1 != NULL){
	
	/* If the entry is a regular file, open the file */
	  if(t1->d_type == DT_REG){
		int fid = open(t1->d_name,O_APPEND);
		if ( fid < 0){
		printf("Error opening the file of the directory %s\n",t1->d_name);
		return -1;}

	   /* Obtain the value using lseek and moving the file pointer to the end */
	   int size = lseek(fid,0,SEEK_END);

	   /*Print the name of the file followed by 4 blank spaces and the size */
	   printf("%s    %d\n",t1->d_name,size);

	   close(fid); // Close the file opened
	
	   }
	
	t1=readdir(dir);
	}

	/* This processis repeated for each entry in the directory and finally it will close the directory */


	closedir(dir);







	return 0;
}
