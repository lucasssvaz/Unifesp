//
//      Lucas Saavedra Vaz - 120503
//      Vinícius Santiago do Amaral - 120640
//

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

#define N_RES 255
#define N_PROC 255

int Mutex_Busy = 0;

pid_t Dict_Proc[N_PROC];
sem_t *Dict_Res[N_RES];
int Res_Avail[N_RES];
int Matrix_Req[N_PROC][N_RES]; 
int Matrix_Aloc[N_PROC][N_RES];
int DProc_Size = 0;
int DRes_Size = 0;
int MReq_Size = 0;
int MAloc_Size = 0;
int Res_Size = 0;

int (*_sem_wait)(sem_t *) = NULL;
int (*_sem_post)(sem_t *) = NULL;
int (*_sem_init)(sem_t *, int, unsigned int) = NULL;
int (*_sem_getvalue)(sem_t *, int *) = NULL;


//===========================================================================================

void PrintMat()
{

    printf("\nAloc Matrix\n");

    for (int i = 0; i < N_PROC; i++)
    {
        for (int j = 0; j < N_RES; j++)
        {
            printf("%d ", Matrix_Aloc[i][j]);
        }
        printf("\n");
    }

    printf("\nReq Matrix\n");

    for (int i = 0; i < N_PROC; i++)
    {
        for (int j = 0; j < N_RES; j++)
        {
            printf("%d ", Matrix_Req[i][j]);
        }
        printf("\n");
    }

    printf("\nAvail Array\n");

    for (int j = 0; j < N_RES; j++)
        {
            printf("%d ", Res_Avail[j]);
        }
    printf("\n\n");

}

//---------------------------------------------------------------------------------------------------

int VerifyMap_Proc(pid_t Process)
{
    int i;

    if (DProc_Size == 0){
        for (i = 0; i < N_PROC; i++)
            Dict_Proc[i] = -1;
    }
   

    for (i = 0; i < N_PROC; i++)
        if (Dict_Proc[i] == Process)
        return i;

    return -1;
}

//---------------------------------------------------------------------------------------------------

int VerifyMap_Res(sem_t *Sem)
{
    int i;

    if (DRes_Size == 0){
        for (i = 0; i < N_RES; i++)
            Dict_Res[i] = NULL;
    }

    for (i = 0; i < N_RES; i++)
        if (Dict_Res[i] == Sem)
        return i;

    return -1;
}

//-------------------------------------------------------------------------------------------------

int InsertMap_Proc()
{
    int Pos;
    pid_t Process = gettid();

    Pos = VerifyMap_Proc(Process);

    if (Pos >= 0)
        return Pos;

    DProc_Size++;
    Dict_Proc[DProc_Size-1] = Process;

    return DProc_Size-1;
    

}

//-----------------------------------------------------------------------------------------------

int InsertMap_Res(sem_t *Sem)
{
    int Pos;

    Pos = VerifyMap_Res(Sem);

    if (Pos >= 0)
        return Pos;

    DRes_Size++;
    Dict_Res[DRes_Size-1] = Sem;

    return DRes_Size-1;

}

//----------------------------------------------------------------------------------------------

void Res_Init(sem_t *Sem, int value)
{
    int Pos = InsertMap_Res(Sem);

    if (Res_Size == 0)
        for (int i = 0; i < N_RES; i++)
            Res_Avail[i] = 0;

    Res_Avail[Pos] = value;
    Res_Size++;

    return;
}

//----------------------------------------------------------------------------------------------

void Matrix_Req_Insert (sem_t *Sem)
{
    int Proc_Pos = InsertMap_Proc();
    int Res_Pos = InsertMap_Res(Sem);

    if (MReq_Size == 0)
        for (int i = 0; i < N_PROC; i++)
            for (int j = 0; j < N_RES; j++)
                Matrix_Req[i][j] = 0;

    if (Proc_Pos >= MReq_Size)
        MReq_Size = Proc_Pos+1;

    Matrix_Req[Proc_Pos][Res_Pos]++;

}

//---------------------------------------------------------------------------------------------

void Matrix_Aloc_Insert (sem_t *Sem)
{
    int Proc_Pos = InsertMap_Proc();
    int Res_Pos = InsertMap_Res(Sem);

    if (MAloc_Size == 0)
        for (int i = 0; i < N_PROC; i++)
            for (int j = 0; j < N_RES; j++)
                Matrix_Aloc[i][j] = 0;

    if (Proc_Pos >= MAloc_Size)
        MAloc_Size = Proc_Pos+1;

    Matrix_Aloc[Proc_Pos][Res_Pos]++;

}

//--------------------------------------------------------------------------------------------

void Update_Req(sem_t *Sem)
{
    int Proc_Pos = InsertMap_Proc();
    int Res_Pos = InsertMap_Res(Sem);

    Res_Avail[Res_Pos]--;
    Matrix_Req[Proc_Pos][Res_Pos]--;
    Matrix_Aloc_Insert(Sem);
}

//-------------------------------------------------------------------------------------------

void Matrix_Remove (sem_t *Sem)
{
    int Proc_Pos = InsertMap_Proc();
    int Res_Pos = InsertMap_Res(Sem);

    if (Matrix_Aloc[Proc_Pos][Res_Pos] > 0)
        Matrix_Aloc[Proc_Pos][Res_Pos]--;
    Res_Avail[Res_Pos]++;
}

//------------------------------------------------------------------------------------------

int Deadlock_Detection()
{
    int i, j;
    int Work[N_RES];
    int Finish[N_PROC];

    //PrintMat();

    //printf("Work\n");

    for (i = 0; i < N_RES; i++){
        Work[i] = Res_Avail[i];
        //printf("%d ", Work[i]);
    }
    
    //printf("\nFinish\n");

    for (i = 0; i < N_PROC; i++)
    {
        Finish[i] = 0;
        //printf("%d ", Finish[i]);
    }

    //printf("\n");

    i = 0;
    int Flag = 1;

    while (i < N_PROC)
    {
        //printf("%d\n", i);
        //printf("\n\nWork\n");
        for (j = 0; j < N_RES; j++)
            //printf("%d ", Work[j]);
        if (Finish[i] == 0)
        {
            Flag = 1;
            for (j = 0; j < N_RES; j++)
            {
                if (Matrix_Req[i][j] <= Work[j])
                    Flag *= 1;
                else
                    Flag *= 0;
            }
            
            if (Flag)
            {
                for (j = 0; j < N_RES ; j++){       
                    Work[j] += Matrix_Aloc[i][j];
                }
                Finish[i] = 1;
                i = -1;
            }
        }
        i++;
    }

    //printf("\nFinish\n");


    for (i = 0; i < N_PROC; i++){
        //printf("%d ", Finish[i]);
        if(Finish[i] == 0)
            return 1;
    }

    //printf("\n");

    fflush(stdout);

    return 0;    
}

//===========================================================================================

int sem_wait(sem_t *sem) {

    int r;
    if (!_sem_wait) {
        _sem_wait = dlsym(RTLD_NEXT, "sem_wait");
    }

    //while(Mutex_Busy);
    //Mutex_Busy = 1;

    Matrix_Req_Insert(sem);

    //PrintMat();

    if(Deadlock_Detection()){
        printf("\n%s======================== DEADLOCK DETECTED! ABORTING... ========================%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
        exit(-1);
    }

    r = _sem_wait(sem);

    Update_Req(sem);

    //Mutex_Busy = 0;

    //PrintMat();

    return(r);
}

int sem_post(sem_t *sem) {

    int r;
    if (!_sem_post) {
        _sem_post = dlsym(RTLD_NEXT, "sem_post");
    }

    //while(Mutex_Busy);
    //Mutex_Busy = 1;

    r = _sem_post(sem);

    Matrix_Remove(sem);

    //Mutex_Busy = 0;

    return(r);
}

int sem_init(sem_t *sem, int pshared, unsigned int value){

    int r;
    if (!_sem_init) {
        _sem_init = dlsym(RTLD_NEXT, "sem_init");
    }

    //while(Mutex_Busy);
    //Mutex_Busy = 1;

    Res_Init(sem, value);

    r = _sem_init(sem, pshared, value);

    //Mutex_Busy = 0;

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