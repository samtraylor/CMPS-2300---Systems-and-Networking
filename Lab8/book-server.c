#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SERVER_PORT 5432
#define MAX_PENDING 1
#define MAX_LINE 256

int fiftyfifty() {
     srand(time(NULL)); //Initialize rand() using value from time()
     int result = (int) rand() % 2; //By using mod 2, from any random number we get 1 or 2
     return result; 
 } 

/*int randomNum(int lower, int upper, int cnt) { 
    int i; 
    for (i = 0; i < cnt; i++) { 
        int num = (rand() % (upper - lower + 1)) + lower; 
    } 
    return i;
} */

int main()
{
	struct sockaddr_in sin;
	char buf[MAX_LINE];
	int len;
  unsigned int l;
	int s, new_s;

	/* build address data structure */
	memset((char *)&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);

	/* setup passive open */
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("simplex-talk: socket");
		exit(1);
	}
	if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
		perror("simplex-talk: bind");
		exit(1);
	}
	listen(s, MAX_PENDING);

	int action;

	/* wait for connection, then receive and print text */
	while(1) {
		l = sizeof(sin);
		if ((new_s = accept(s, (struct sockaddr *)&sin, &l)) < 0) {
			perror("simplex-talk: accept");
			exit(1);
		}
		while ((len = recv(new_s, buf, sizeof(buf), 0))) {
			fputs(buf, stdout);

			action = fiftyfifty(); //determine 1 or 0 randomly to decide reaction;
			int questionNum = rand() % 2;
			int responseNum;
			int responseQuestNum; 
			char response[len+45];

			if(action == 1 && (buf[len - 3] != '?')) { 
				char question[len+30];
				char suffix[len + 15];
				
				if(questionNum == 1) {
					strcpy(suffix, "?\n");
					strcpy(question, "Did you come to me because ");
				}
				else {
					strcpy(suffix, "started?\n");
					strcpy(question, "How long since ");
				}
				strcat(buf,suffix);
				strcat(question,buf);
				send(new_s, question, sizeof(question),0);
			}

			else if(action == 0 && (buf[len - 3] != '?')) { 
				responseQuestNum = rand()%((3+1)-1) + 1;
				if(responseQuestNum == 1) {
					strcpy(response,"How does that make you feel?\n");
				}
				if(responseQuestNum == 2) {
					strcpy(response,"Is it really?\n");
				}
				if(responseQuestNum == 3) {
					strcpy(response,"Are you sure?\n");
				}
				send(new_s,response,sizeof(response),0);
			}
				
			else {
				srand(time(0));
				responseNum = rand() % 2;
				if(responseNum == 1) {
					strcpy(response,"Tell me more...\n");
				}
				if(responseNum == 0) {
					strcpy(response,"I'm sorry to hear that\n");
				}
				send(new_s,response,sizeof(response),0);
			}			
		}
		close(new_s);	
	}
}
