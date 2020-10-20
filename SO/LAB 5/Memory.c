//
//			Lucas Saavedra Vaz - 120503
//			Vinícius Santiago do Amaral - 120640
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define PAGE_SIZE 4096			// 4KB
#define PMEM_SIZE 268435456		// 256MB
#define VMEM_SIZE 536870912		// 512MB
#define N_PAGES 131072			// VMEM_SIZE/PAGE_SIZE
#define HASH_SIZE 65536			// PMEM_SIZE/PAGE_SIZE

//#define DEBUG

#ifdef DEBUG
	#define P_DEBUG(x) x
#else
	#define P_DEBUG(x)
#endif

typedef struct S_Cell{
	unsigned long Virtual_Page;
	unsigned long Frame;
	struct S_Cell *Next;
} Cell;

Cell *Hash_Table[HASH_SIZE];

//==================================================================================================================================

void Hash_Initialize()
{
	for (int i = 0; i < HASH_SIZE; i++)
		Hash_Table[i] = NULL;
}

//---------------------------------------------------------------------------

static inline unsigned long Hash_Addr(unsigned long Virtual_Addr)
{
	return floor(Virtual_Addr/PAGE_SIZE);
}

//---------------------------------------------------------------------------

static inline unsigned long Hash_Function(unsigned long Virtual_Page)
{
	return Virtual_Page % HASH_SIZE;
}

//---------------------------------------------------------------------------

static inline Cell *Cell_Create(unsigned long Virtual_Page, unsigned long Frame)
{
	Cell *New_Cell = (Cell *) calloc (1,sizeof(Cell));
	
	New_Cell->Virtual_Page = Virtual_Page;
	New_Cell->Frame = Frame;

	return New_Cell;
}

//---------------------------------------------------------------------------

void Hash_Insert(unsigned long Virtual_Addr, unsigned long Frame)
{
	Cell *Last;
	unsigned long Page = Hash_Addr(Virtual_Addr);
	Cell *New_Cell = Cell_Create(Page, Frame);
	unsigned long H = Hash_Function(Page);

	if (Hash_Table[H] == NULL)
	{
		Hash_Table[H] = New_Cell;
		return;
	}

	for (Last = Hash_Table[H]; Last->Next != NULL; Last = Last->Next);

	Last->Next = New_Cell;
}

//---------------------------------------------------------------------------

static inline unsigned long Random_Addr()
{
	return round(1.0*rand()/RAND_MAX*VMEM_SIZE);
}

//---------------------------------------------------------------------------

static inline unsigned long Random_Frame()
{
	return round(1.0*rand()/RAND_MAX*65536);
}

//---------------------------------------------------------------------------

Cell *Hash_Search(unsigned long Virtual_Addr)
{
	unsigned long Page = Hash_Addr(Virtual_Addr);
	unsigned long H = Hash_Function(Page);
	Cell *Aux;

	for (Aux = Hash_Table[H]; Aux != NULL; Aux = Aux->Next)
		if (Aux->Virtual_Page == Page)
			return Aux;

	return NULL;
}

//==================================================================================================================================

int main()
{
	long long int Virtual_Addr, Frame_Num;
	Cell *Search;
	int N;

	srand(time(NULL));

	Hash_Initialize();

	printf("Enter the number of Hash Inputs:\n");
	scanf("%d", &N);

	printf("\n");

	for (int i = 0; i < N; i++)
	{
		printf("Enter the Virtual Address (Negative values for random):\n");
		scanf("%lli", &Virtual_Addr);
		if (Virtual_Addr < 0) Virtual_Addr = Random_Addr();
		
		printf("Enter the Frame Number (Negative values for random):\n");
		scanf("%lli", &Frame_Num);
		if (Frame_Num < 0) Frame_Num = Random_Frame();

		if (Hash_Search(Virtual_Addr) == NULL)
		{
			Hash_Insert(Virtual_Addr, Frame_Num);
			printf("Added Virual Address %lli and Frame %lli to the Hash.\n\n", Virtual_Addr, Frame_Num);
		}
		else
		{
			printf("Virual Address %lli already in the Hash Table.\n\n", Virtual_Addr);
		}

	}

	printf("\n");

	do
	{

		printf("Enter the Virtual Address to search (Negative values to exit):\n");
		scanf("%lli", &Virtual_Addr);

		if (Virtual_Addr < 0) break;

		Search = Hash_Search(Virtual_Addr);

		if (Search == NULL)
			printf("Page Miss!\n");
		else
			printf("Virtual Address %lli references Virtual Page %lu, that points to Frame %lu.\n", Virtual_Addr, Search->Virtual_Page, Search->Frame);

		printf("\n");

	}while(1);

	return 0;
}