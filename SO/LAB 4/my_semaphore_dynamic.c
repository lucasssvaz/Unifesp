#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define N_RES 1024

int Mutex_Busy = 0;

pid_t *Dict_Proc = NULL;
int DProc_Size = 0;
sem_t **Dict_Res = NULL;
int DRes_Size = 0;
int Res_Avail[N_RES];
int **Matrix_Req = NULL;
int **Matrix_Aloc = NULL;
int MReq_Size = 0;
int MAloc_Size= 0;

int (*_sem_wait)(sem_t *) = NULL;
int (*_sem_post)(sem_t *) = NULL;
int (*_sem_init)(sem_t *, int, unsigned int) = NULL;
int (*_sem_getvalue)(sem_t *, int *) = NULL;

int VerifyMap_Proc(pid_t Process);
int InsertMap_Proc();
int VerifyMap_Res(sem_t *Sem);
int InsertMap_Res(sem_t *Sem);
void Res_Init(sem_t *Sem, int value);

//=====================================================

void PrintMat()
{
	(Matrix_Aloc != NULL) ? printf("Aloc Matrix: %d\n", Matrix_Aloc[0][0]) : printf("Aloc Matrix: NULL\n");
	(Matrix_Req != NULL) ? printf("Req Matrix: %d\n", Matrix_Req[0][0]) : printf("Req Matrix: NULL\n");
	(Res_Avail != NULL) ? printf("Avail Vector: %d\n", Res_Avail[0]) : printf("Avail Vector: NULL\n");
	printf("\n");
}

//---------------------------------------------------

int VerifyMap_Proc(pid_t Process)
{
    if (DProc_Size == 0)
        return -1;

    int i;

    for (i = 0; i < DProc_Size; i++)
        if (Dict_Proc[i] == Process)
        return i;

    return -1;
}

//-----------------------------------------------------

int VerifyMap_Res(sem_t *Sem)
{
    if (DRes_Size == 0)
        return -1;

    int i;

    for (i = 0; i < DRes_Size; i++)
        if (Dict_Res[i] == Sem)
        return i;

    return -1;
}

//-----------------------------------------------------

int InsertMap_Proc()
{
    int Pos;
    pid_t Process = gettid();

    Pos = VerifyMap_Proc(Process);

    if (Pos >= 0)
        return Pos;

    if (DProc_Size == 0)
    {
        Dict_Proc = (pid_t *) calloc (1, sizeof(pid_t));
        Dict_Proc[0] = Process;
        DProc_Size = 1;
        return 0;
    }
    else
    {
    	DProc_Size++;
        Dict_Proc = (pid_t *) realloc (Dict_Proc, DProc_Size*sizeof(pid_t));
        Dict_Proc[DProc_Size-1] = Process;
        return DProc_Size-1;
    }

}

//-----------------------------------------------------

int InsertMap_Res(sem_t *Sem)
{
    int Pos;

    Pos = VerifyMap_Res(Sem);

    if (Pos >= 0)
        return Pos;

    if (DRes_Size == 0)
    {
        DRes_Size = 1;
        Dict_Res = (sem_t **) calloc (1, sizeof(sem_t*));
        Dict_Res[0] = Sem;
        return 0;
    }
    else
    {
        DRes_Size++;
        Dict_Res = (sem_t **) realloc (Dict_Res, DRes_Size*sizeof(sem_t*));
        Dict_Res[DRes_Size-1] = Sem;
        return DRes_Size-1;
    }

}

//-----------------------------------------------------

void Res_Init(sem_t *Sem, int value)
{
    int Pos = InsertMap_Res(Sem);
    Res_Avail[Pos] = value;
    return;
}

//-----------------------------------------------------

void Matrix_Req_Insert ( sem_t *Sem)
{
    int Proc_Pos = InsertMap_Proc();
    int Res_Pos = InsertMap_Res(Sem);
    int i;

    if (Matrix_Req == NULL)
    {
    	MReq_Size = 1;
        Matrix_Req = (int **) calloc (1 ,sizeof (int*)) ;
        Matrix_Req[0] = (int *) calloc(N_RES,sizeof (int)) ;
    }
    else
    {
        if (Proc_Pos >= MReq_Size)
        {
        	MReq_Size = Proc_Pos+1;
            Matrix_Req = (int **) realloc(Matrix_Req, MReq_Size*sizeof(int *));
            for (i = 0; i < MReq_Size; i++)
            	if (Matrix_Req[i] == NULL)
            		Matrix_Req[i] = (int *) calloc(N_RES,sizeof (int));
        }
    }

    //printf("Proc: %d, Res: %d, Count: %d\n", Proc_Pos, Res_Pos, Proc_Count);

    Matrix_Req[Proc_Pos][Res_Pos] += 1;
    
    //printf("Proc: %d, Res: %d, Matrix: %d\n", Proc_Pos, Res_Pos, *Matrix[Proc_Pos][Res_Pos]);
}

//-----------------------------------------------------

void Matrix_Aloc_Insert (sem_t *Sem)
{
    int Proc_Pos = InsertMap_Proc();
    int Res_Pos = InsertMap_Res(Sem);
    int i;

    if (Matrix_Aloc == NULL)
    {
    	MAloc_Size = 1;
        Matrix_Aloc = (int **) calloc (1 ,sizeof (int*)) ;
        Matrix_Aloc[0] = (int *) calloc(N_RES,sizeof (int)) ;
    }
    else
    {    
        if (Proc_Pos >= MAloc_Size)
        {
        	MAloc_Size = Proc_Pos+1;
            Matrix_Aloc = (int **) realloc(Matrix_Aloc, MAloc_Size*sizeof(int *));
            for (i = 0; i < MAloc_Size; i++)
            	if (Matrix_Aloc[i] == NULL)
            		Matrix_Aloc[i] = (int *) calloc(N_RES,sizeof (int));
        }
    }

    //printf("Proc: %d, Res: %d, Count: %d\n", Proc_Pos, Res_Pos, Proc_Count);

    Matrix_Aloc[Proc_Pos][Res_Pos] += 1;

    //printf("Proc: %d, Res: %d, Matrix: %d\n", Proc_Pos, Res_Pos, *Matrix[Proc_Pos][Res_Pos]);
}

//-----------------------------------------------------
void Update_Req(sem_t *Sem)
{
    int Proc_Pos = InsertMap_Proc();
    int Res_Pos = InsertMap_Res(Sem);

    Res_Avail[Res_Pos] -= 1;
    Matrix_Req[Proc_Pos][Res_Pos] -= 1;
    Matrix_Aloc_Insert(Sem);
}

//------------------------------------------------------

void Matrix_Remove (sem_t *Sem)
{
    int Proc_Pos = InsertMap_Proc();
    int Res_Pos = InsertMap_Res(Sem);

    if (Proc_Pos < MAloc_Size){
    	Matrix_Aloc[Proc_Pos][Res_Pos] -= 1;
    }
    Res_Avail[Res_Pos]++;
}

//------------------------------------------------------

int Deadlock_Detection()
{
    int i, j;
    int Work[N_RES];
    int Finish[MReq_Size];

    //printf("Work\n");

    for (i = 0; i < N_RES; i++){
        Work[i] = Res_Avail[i];
        //printf("%d ", Work[i]);
    }
    
    //printf("\nFinish\n");

    for (i = 0; i < MReq_Size; i++)
    {
        Finish[i] = 1;
        for (j = 0; j < N_RES; j++){
            if(Matrix_Req[i][j] != 0)
                Finish[i] = 0;
        }
        //printf("%d ", Finish[i]);
    }

    //printf("\n");

    i = 0;
    int Flag = 1;

    while (i < MReq_Size)
    {
        if (Finish[i] == 0)
        {
            Flag = 1;
            for (j = 0; j < N_RES; j++)
            {
                if (Matrix_Req[i][j] > Work[j])
                    Flag = 0;
            }
            
            if (Flag)
            {
                for (j = 0; j < N_RES ; j++){
                	if (Matrix_Aloc != NULL)
                	{
                		if (Matrix_Aloc[i] != NULL)
                		{
                			//printf("Proc = %d\n", MReq_Size);
                			//printf("i = %d, j = %d\n", i, j);
                			//printf("Matrix Aloc i = %d\n", Matrix_Aloc[i]);
                			//fflush(stdout);
                    		Work[j] += Matrix_Aloc[i][j];    
                    	}      
                	}
                }
                Finish[i] = 1;
                i = 0;
            }
        }
        i++;
    }

    for (i = 0; i < MReq_Size; i++){
    	//printf("%d ", Finish[i]);
        if(Finish[i] == 0)
            return 1;
    }

    //printf("\n");

    return 0;    
}

//=====================================================

int sem_wait(sem_t *sem) {

    int r;
    if (!_sem_wait) {
        _sem_wait = dlsym(RTLD_NEXT, "sem_wait");
    }

    while(Mutex_Busy);
    Mutex_Busy = 1;

    Matrix_Req_Insert(sem);

    //PrintMat();

    if(Deadlock_Detection()){
        printf("\n%s======================== DEADLOCK DETECTED! ABORTING... ========================%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
        exit(-1);
    }

    r = _sem_wait(sem);

    Update_Req(sem);

    Mutex_Busy = 0;

    //PrintMat();

    return(r);
}

int sem_post(sem_t *sem) {

    int r;
    if (!_sem_post) {
        _sem_post = dlsym(RTLD_NEXT, "sem_post");
    }

    while(Mutex_Busy);
    Mutex_Busy = 1;

    r = _sem_post(sem);

    Matrix_Remove(sem);

    Mutex_Busy = 0;

    return(r);
}

int sem_init(sem_t *sem, int pshared, unsigned int value){

    int r;
    if (!_sem_init) {
        _sem_init = dlsym(RTLD_NEXT, "sem_init");
    }

    while(Mutex_Busy);
    Mutex_Busy = 1;

    Res_Init(sem, value);

    r = _sem_init(sem, pshared, value);

    Mutex_Busy = 0;

    return(r);
}

int sem_getvalue(sem_t *sem, int *sval){

    int r;
    if (!_sem_getvalue) {
        _sem_getvalue = dlsym(RTLD_NEXT, "sem_getvalue");
    }

    r = _sem_getvalue(sem, sval);
    return(r);
}