//
//	Sistemas Operacionais - Lab 1
//		Lucas Saavedra Vaz
//			120503
//
//--------------------------------------
//
//	Error Return Codes
//
//	IO Error = -1
//	Pipe Error = -2
//	Process Error = -3
//	Info Gather Error = -4
//
//-------------------------------------
//
//	Special Commands
//
//	killbg = kill background process
//


//============================================================================================================================= DECLARATIONS


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <pwd.h>
#include <signal.h>

#define WRITE_END 1
#define READ_END 0

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define PRINTF_RED(X) printf("%s%s%s",ANSI_COLOR_RED,X,ANSI_COLOR_RESET)
#define PRINTF_GREEN(X) printf("%s%s%s",ANSI_COLOR_GREEN,X,ANSI_COLOR_RESET)
#define PRINTF_YELLOW(X) printf("%s%s%s",ANSI_COLOR_YELLOW,X,ANSI_COLOR_RESET)
#define PRINTF_BLUE(X) printf("%s%s%s",ANSI_COLOR_BLUE,X,ANSI_COLOR_RESET)
#define PRINTF_MAGENTA(X) printf("%s%s%s",ANSI_COLOR_MAGENTA,X,ANSI_COLOR_RESET)
#define PRINTF_CYAN(X) printf("%s%s%s",ANSI_COLOR_CYAN,X,ANSI_COLOR_RESET)

char **tokenizer(char *rawStr, int *NTok);
char ***parser(int NTok, char **tokStr);
int searchIOFilesBG(int NTok, char **tokStr, int *input, int *output, int *BG);
void printComMat(char ***ComMat, int inputFD, int outputFD, int BG);
void execBasic(char ***ComMat, int inputFD, int outputFD);
void execPipe(char ***ComMat, int inputFD, int outputFD);
static inline void execBG(char ***ComMat, int inputFD, int outputFD, int *CPID);
char *replaceSubstring(char *MainString, char *Substring);

int NCom;


//================================================================================================================================ FUNCTIONS

char *replaceSubstring(char *MainString, char *Substring){
	char *newString = (char *) calloc(2,sizeof(char));
	newString[0] = '~';

	int new_size = 1;

	int sub_size = strlen(Substring);

	while (MainString[sub_size+new_size-1] != '\0'){
		newString = (char *) realloc (newString, (new_size+2)*sizeof(char));
		newString[new_size] = MainString[sub_size+new_size-1];
		new_size++;
	}

	newString[new_size] = '\0';


	return newString;
}

//---------------------------------------------------------------------------------------------------------------------

static inline void welcome(){

	PRINTF_CYAN("\n*******************************************************************\n");
	PRINTF_RED("\n\t\t\tW ");
	PRINTF_GREEN("E ");
	PRINTF_YELLOW("L ");
	PRINTF_BLUE("C ");
	PRINTF_MAGENTA("O ");
	PRINTF_CYAN("M ");
	printf("E\n\n");
	PRINTF_YELLOW("\t\tSistemas Operacionais - Lab 1\n\t\tLucas Saavedra Vaz\n\t\t120503\n\n");
	PRINTF_CYAN("*******************************************************************\n\n");

	return;
}


//---------------------------------------------------------------------------------------------------------------------


void printComMat(char ***ComMat, int inputFD, int outputFD, int BG){
	int i = 0, j = 0;

	printf("inputFD: %d\noutputFD: %d\nBG: %d\n", inputFD, outputFD, BG);

	while (i < NCom){
		while (ComMat[i][j] != NULL){
			printf("%s ", ComMat[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}

	return;
}


//---------------------------------------------------------------------------------------------------------------------


int searchIOFilesBG(int NTok, char **tokStr, int *inputFD, int *outputFD, int *BG){

	int i;
	int PosOut = -1, PosIn = -1;

	if (tokStr[0] == NULL){
		return 0;
	}

	for (i = 0; i<NTok; i++){
		if (tokStr[i][0] == '<'){
			//input
			PosIn = i+1;
		} else if (tokStr[i][0] == '>'){
			//output
			PosOut = i+1;
		} else if (tokStr[i][0] == '&'){
			*BG = 1;
		}
	}

	if (PosIn != -1 && PosOut != -1){
		if (strcmp(tokStr[PosIn],tokStr[PosOut]) == 0){
			*inputFD = open(tokStr[PosIn], O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			*outputFD = *inputFD;
			if (*inputFD < 0){
				perror("Open (O_RDWR)");
				exit(-1);
			}
        }
    }
    if (PosIn != -1 && *inputFD < 0){
        *inputFD = open(tokStr[PosIn], O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (*inputFD < 0){
            perror("Open (O_RDONLY)");
            exit(-1);
        }
    }
    if (PosOut != -1 && *outputFD < 0){
        *outputFD = open(tokStr[PosOut], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (*outputFD < 0){
            perror("Open (O_WRONLY)");
            exit(-1);
        }
    }

	return 0;

}


//---------------------------------------------------------------------------------------------------------------------


char **tokenizer(char *rawStr, int *NTok){

	rawStr = strtok(rawStr,"\n");

	char *CurrentWord = strtok(rawStr," ");
	char **tokStr = (char **) malloc(sizeof(char *));

	*NTok = 0;

	do{
		(*NTok)++;
		tokStr = (char **) realloc(tokStr,(*NTok)*sizeof(char *));
		tokStr[(*NTok)-1] = CurrentWord;
	} while ((CurrentWord = strtok(NULL," ")) != NULL);

	return tokStr;

}


//-------------------------------------------------------------------------------------------------------------------


char ***parser(int NTok, char **tokStr){
	int i = 0;
	int NWord = 0;
	char ***ComMat = (char ***) calloc(1,sizeof(char **));
	ComMat[0] = (char **) calloc(1,sizeof(char *));

	if (tokStr[0] == NULL){
		NCom = 0;
		return NULL;
	}

	NCom = 1;

	/*

	ComMat[i] = Command
	ComMat[i][j] = Argument
	ComMat[i][j][k] = Character

	*/

	while (i < NTok){
		if (tokStr[i][0] == '<' || tokStr[i][0] == '>') {
			i+=1;
		} else if (tokStr[i][0] == '|') {
            ComMat[NCom-1] = (char **) realloc(ComMat[NCom-1],(NWord+1)*sizeof(char *));
			ComMat[NCom-1][NWord] = NULL;
			NWord = 0;
			NCom++;
			ComMat = (char ***) realloc(ComMat,NCom*sizeof(char **));
			ComMat[NCom-1] = (char **) calloc(1,sizeof(char *));
		} else if (tokStr[i][0] != '&') {
			NWord++;
			ComMat[NCom-1] = (char **) realloc(ComMat[NCom-1],NWord*sizeof(char *));
			ComMat[NCom-1][NWord-1] = tokStr[i];
		}
		i++;
	}

	ComMat[NCom-1] = (char **) realloc(ComMat[NCom-1],(NWord+1)*sizeof(char *));
    ComMat[NCom-1][NWord] = NULL;
	ComMat = (char ***) realloc(ComMat,(NCom+1)*sizeof(char **));
	ComMat[NCom] = NULL;

	return ComMat;
}

//------------------------------------------------------------------------------------------------------------------


void execPipe(char*** ComMat, int inputFD, int outputFD){

	int fd[NCom-1][2], i;

	for(i=0; i<NCom; i++){

		if(i != NCom-1){ 						//Not last
			if(pipe(fd[i])<0){
				perror("Pipe");
				exit(-2);
			}
		}

		if(fork()==0){						//Child

			if(i != NCom-1){
				dup2(fd[i][WRITE_END],STDOUT_FILENO);
				close(fd[i][READ_END]);
				close(fd[i][WRITE_END]);
			}

			if(i != 0){
				dup2(fd[i-1][READ_END],STDIN_FILENO);
				close(fd[i-1][WRITE_END]);
				close(fd[i-1][READ_END]);
			}

			if (i == 0 && inputFD != -1){
				dup2(inputFD,STDIN_FILENO);
			}

			if (i == NCom-1 && outputFD != -1){
				dup2(outputFD,STDOUT_FILENO);
			}

			execvp(ComMat[i][0],ComMat[i]);
			perror("Exec Pipe");
			exit(-3);

		} else if (i!=0){					//Parent (Not first)

			close(fd[i-1][READ_END]);
			close(fd[i-1][WRITE_END]);

		}

		wait(NULL);

	}
}


//-------------------------------------------------------------------------------------------------------------------


static inline void execBG(char*** ComMat, int inputFD, int outputFD, int *CPID){

	if((*CPID = fork()) == 0){

		if (inputFD != -1){
			dup2(inputFD,STDIN_FILENO);
		}

		if (outputFD != -1){
			dup2(outputFD,STDOUT_FILENO);
		}

		execvp(ComMat[0][0],ComMat[0]);
		perror("Exec BG");
		exit(-3);
	}

}


//-------------------------------------------------------------------------------------------------------------------


void execBasic(char*** ComMat, int inputFD, int outputFD){
	if (fork() > 0){
		wait(NULL);
	} else {

		if (inputFD != -1){
			dup2(inputFD,STDIN_FILENO);
		}

		if (outputFD != -1){
			dup2(outputFD,STDOUT_FILENO);
		}

		execvp(ComMat[0][0],ComMat[0]);
		perror("Exec Basic");
		exit(-3);
	}
	return;
}


//====================================================================================================================== MAIN


int main(){

	int NTok, BG = 0, inputFD = -1, outputFD = -1, exit_main, CPID = 0;
	char ***ComMat, rawStr[PATH_MAX], **tokStr, RawCwd[PATH_MAX], *cwd, *user, host[HOST_NAME_MAX], *path, *rawStrBak;
	struct passwd *pass;

	// FD[0] = Read, FD[1] = Write

	welcome();

	const char *homedir;

	if ((homedir = getenv("HOME")) == NULL) {
	    homedir = getpwuid(getuid())->pw_dir;
	}

	do{
		cwd = (char *) calloc(PATH_MAX+1, sizeof(char));
		BG = 0;
		inputFD = -1;
		outputFD = -1;

		if((pass = getpwuid(getuid())) == NULL){
			perror("Get Login");
			exit(-4);
		}

		user = pass->pw_name;

		if(gethostname(host, HOST_NAME_MAX) < 0){
			perror("Get Hostname");
			exit(-4);
		}

		if (getcwd(RawCwd,PATH_MAX) != NULL){
			PRINTF_GREEN(user);
			PRINTF_GREEN("@");
			PRINTF_GREEN(host);
			PRINTF_GREEN(":");
			if (strstr(RawCwd, homedir) != NULL){
				cwd = replaceSubstring(RawCwd, (char *) homedir);
			} else {
				strncpy(cwd,RawCwd,PATH_MAX);
			}
			PRINTF_CYAN(cwd);
			PRINTF_CYAN("$ ");
		} else {
			perror("get CWD");
			exit(-4);
		}

		fgets(rawStr,PATH_MAX,stdin);

		rawStrBak = (char *) malloc (sizeof(rawStr));
		strncpy(rawStrBak,rawStr,PATH_MAX);

		rawStrBak = strtok(rawStrBak,"\n");

		tokStr = tokenizer(rawStr, &NTok);
		ComMat = parser(NTok, tokStr);
		searchIOFilesBG(NTok, tokStr, &inputFD, &outputFD, &BG);

		//printComMat(ComMat, inputFD, outputFD, BG);


		if (BG && NCom) {

			execBG(ComMat, inputFD, outputFD, &CPID);

		} else if (NCom > 1){

			execPipe(ComMat, inputFD, outputFD);

		} else if (NCom && strcmp(ComMat[0][0],"exit") != 0){

			if (strcmp(ComMat[0][0],"cd") != 0 && strcmp(ComMat[0][0],"killbg") != 0){

				execBasic(ComMat, inputFD, outputFD);

			} else if (NCom && strcmp(ComMat[0][0],"killbg") != 0) {

				path = &rawStrBak[3];

				if (strcmp(path, "~") == 0)
					path = (char *) homedir;

				if (chdir(path) < 0){

					perror("cd");

				}
			} else if (NCom){
				if (CPID > 0){
					printf("%sKilling backgroung process, PID = %d%s",ANSI_COLOR_YELLOW,CPID,ANSI_COLOR_RESET);
					printf("\n");
					kill(CPID,SIGKILL);
					CPID = 0;
				} else {
					PRINTF_RED("No process running in backgroung!");
					printf("\n");
				}
			}
		}

		if (inputFD != -1 && outputFD != inputFD){
			close(inputFD);
		}

		if (outputFD != -1){
			close(outputFD);
		}

		if (NCom == 0){
			exit_main = 1;
		} else if (strcmp(ComMat[0][0],"exit") == 0){
			exit_main = 0;
		} else {
			exit_main = 1;
		}

	} while (exit_main);

	return 0;
}
