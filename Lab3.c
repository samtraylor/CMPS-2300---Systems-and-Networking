#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>

/*
Program using various system calls to demonstrate what the lab questions dictate

@author Sam Traylor
@version 1.0
*/

int forky(int x) { // Question 1. Fork
	printf("Variable x initialized as %d\n",x); 
	int rc = fork(); //for both parent and child, initial value is x = 100

	if(rc < 0) {
		fprintf(stderr, "Fork failed.\n");
		exit(1);
	}

	else if(rc == 0) { //child process created 
		x += 1; 
		printf("child process has run. x is now %d\n",x); //prints x's value after the change, which is 101.
		exit(0);
	}
	else { //continuation of "main" path that parent is going down
		pid_t rc_wait = wait(NULL);
		x += 1; 
		printf("Parent process run. x is now %d\n",x); //prints x's val after change, which is 101.
	printf("Value of x after being changed by both child and parent: %d\n\n", x); //this value is 101. X was changed previously in SEPERATE processes, which use seperate memory meaning there's essentially two seperate clones of x.
	}
	return 0;
}

int forkOpen(void) { // Question 2. Fork and Open

	int saved_stdout = dup(STDOUT_FILENO); //preserve current standard out settings so they can be reset later
	close(STDOUT_FILENO); //close standard out, which causes output to redirect to file that's opened next line

	int descriptor = open("./Lab3test1.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

	int rc = fork();

	if(rc < 0) {
		fprintf(stderr, "Fork failed.\n");
		exit(1);
	}
	else if(rc == 0) { //child process
		printf("%d is the file descriptor for the opened file.\n", descriptor); //child successfully accesses and prints (which actually writes) descriptor
		exit(0);
	}
	else { //Parent process continued
		pid_t rc_wait = wait(NULL);
		printf("%d is the file descriptor for the opened file.\n", descriptor); //parent successfully accesses and prints (which actually writes) descriptor
		dup2(saved_stdout, STDOUT_FILENO); //restore standard out so that it again prints to terminal
		close(saved_stdout);
	}


	return 0;
	/*
	When the two try to write to the file concurrently, the parent goes first, then the child process writes.
	*/
}

int forkPrint(void) { // Question 3. Fork and Print
	bool childExecd = false;
	int rc = fork();

	if(rc < 0) {
		fprintf(stderr, "Fork failed.\n");
		exit(1);
	}
	else if (rc == 0) { //Child process condition 
		printf("hello\n");
		childExecd = true;
	}
	if (childExecd == true) { //Parent process condition: only satisfied if child has already run, so always prints in the right order without using wait()
		printf("goodbye.\n");
		exit(1);
	}
	return 0;
}	

int forkExec(void) { //Question 4. Fork and Exec. Every exec after the first doesn't execute, but im demonstrating the proper code
	bool pointless;
	int rc = fork();

	if(rc < 0) {
		fprintf(stderr, "Fork failed.\n");
		exit(1);
	}
	else if (rc == 0) {
		char *args[]={"/bin/ls", (char*) NULL}; 
		char *argsL[] = {"-l", (char*) NULL}; //added -l flag as an additional argument to bash command ls
		char *path = getenv("PATH");
		char *envp[] = {path,(char*) NULL};

        execvp(args[0],args);
        execv(args[0],args);

		execl(args[0], args[0],argsL[1]); 
		execlp(args[0], args[0], argsL[0],argsL[1]);

		execle(args[0],args[0],argsL[0],envp);

	 	// execvpe(args[0],args,envp);
	 	   
	 	/* 
	 	error: execvpe is an "Undefined symbol for architecture x86_64"
	 	This compiles correctly on linux virtual machine 
	 	*/
	 	
	 	exit(0); //wont even run because of the nature of exec(), but still good practice for child process
	}
	else {
		pointless = true;
	}
	 return 0;
}
	 	/* 
	 	all these variants exist to offer syntactically different options of calling the same exec functionality.
		For example, some take in a file name character array to specify the file, whereas others use a *FILE pointer.
		Some only take in a null-terminated array for specifying file location, others take in an array with arguments for the executable.
		Furthermore, others like execvpe and execle allow you to specify the environment.
		*/

int waitFunct(void) { //Question 5. Wait
	int rc = fork();

	if(rc < 0) {
		fprintf(stderr, "Fork failed.\n");
		exit(1);
	}
	else if(rc == 0) { //child process created 
		printf("I'm the child process\n");
		exit(0);
	}
	else { //parent going down main path
		pid_t rc_wait = wait(NULL);
		printf("I'm the parent process\n");
		printf("wait() returns: %d\n", rc_wait);
	} 
	return 0;
	/* 
	Wait returns the PID of the parent process with this setup. 
	With the wait statement in the child process, wait returns -1
	*/
}

int waitPID(void) { //Question 6. Wait and PID
	int *status;
	
	int rc = fork();
	if(rc < 0) {
		fprintf(stderr, "Fork failed.\n");
		exit(1);
	}
	else if(rc == 0) { //child process created 
		printf("Working on child process with PID %d.\n", (int) getpid());
		exit(0);
	}
	else { //parent going down main path
		pid_t rc_wait = waitpid(-1,status,0);
		printf("Parent done.\n");
	} 
	return 0;
} 
/*
	waitpid() would be useful primarily when you have more than one child process but need to specify
	a particular one to execute before the parent. It could also be useful because of the three options you
	can call the options parameter with, allowing more specific control over the function.
*/

int standardOut(void) { //Question 7. Standard Out

	int saved_stdout = dup(STDOUT_FILENO); //preserve current standard out settings so they can be reset later
	bool stdClosed = false;

	int rc = fork();

	if(rc < 0) {
		fprintf(stderr, "Fork failed.\n");
		exit(1);
	}
	else if(rc == 0) { //child process created 
		int saved_stdout = dup(STDOUT_FILENO); //preserve current standard out settings so they can be reset later
		close(STDOUT_FILENO); //close standard out

		printf("Printing as test"); //this will print to an output buffer and stay there, not ending up in terminal nor a file.
		exit(1);
	}
	else {
		pid_t rc_wait = wait(NULL);
		if(stdClosed== true) { //If child has ran and closed standard out, then set it back to normal
			dup2(saved_stdout, STDOUT_FILENO); //restore standard out so that it again prints to terminal
			close(saved_stdout);
		}
	}
	return 0;
}
	
int main(void) {
	
	int x; 
	x = 100; 
	printf("-----starting forky-----\n");
	forky(x);  //End of code running question 1

	printf("-----forky done, now forkOpen-----\n");
	forkOpen(); //End of code running question 2

	printf("-----forkOpen done, now forkPrint------\n");
	forkPrint(); 
	sleep(3); //End of code running question 3

	/*	This is where 4 would go, but it's placed last for reasons explained later */ 

	printf("-----forkPrint done, now waitFunct------\n");
	wait(NULL);
	waitFunct(); //End of code running question 5 

	printf("-----waitFunct done, now waitPID------\n");
	waitPID(); //End of code running question 6
	//sleep(5);

	printf("-----waitPID done, now standardOut-----\n");
	standardOut();
	sleep(5);

	printf("-----standardOut done, now forcExec-----\n");
	forkExec(); //End of code running question 4, but it's results will print last 
	sleep(3);

	printf("-----forkExec done.-----\n"); //this functionis run last due to the nature of the exec call 

	return 0;
}