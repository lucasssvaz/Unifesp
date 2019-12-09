import random
import time
import math

def Mutate (Population, Coef):
    NewPopulation = list(Population)
    NewCoef = list(Coef)
    
    for i in range(6):
        NewPopulation[i] = NewPopulation[i] + int(random.uniform(-STEP_POP,STEP_POP))
        if NewPopulation[i] > 1000:
            NewPopulation[i] = 1000
        if NewPopulation[i] < 10:
            NewPopulation[i] = 10
        for j in range(6):
            if float(NewCoef[i][j]) != 0:
                NewCoef[i][j] = NewCoef[i][j] + random.uniform(-STEP_COEF,STEP_COEF)
                if NewCoef[i][j] > 1:
                    NewCoef[i][j] = 1
                if NewCoef[i][j] < 0.000001:
                    NewCoef[i][j] = 0.000001

    return [NewPopulation,NewCoef]


def FunTime (Pop, Coefficients,YEARS):
    Population = list(Pop)
    Coef = list(Coefficients)
    Time=0.0
    Var=0;
    while Time<YEARS and Population[Grass]>0.1 and Population[Rabbit]>0.1 and Population[Insect]>0.1 and Population[Lizard]>0.1 and Population[Cobra]>0.1 and Population[Bird]>0.1 :
    
        DeltaPop[Grass] = (Coef[Grass][Grass]*Population[Grass]*(1-(1.0*Population[Grass]/K)-(Coef[Grass][Rabbit]*Population[Rabbit])-(Coef[Grass][Insect]*Population[Insect])))*DELTA_T
        DeltaPop[Rabbit] = (Population[Rabbit]*((Coef[Rabbit][Grass]*Population[Grass])-(Coef[Rabbit][Rabbit])-(Coef[Rabbit][Cobra]*Population[Cobra])-(Coef[Rabbit][Insect]*Population[Insect])))*DELTA_T
        DeltaPop[Insect] = (Population[Insect]*((Coef[Insect][Grass]*Population[Grass])-(Coef[Insect][Insect])-(Coef[Insect][Rabbit]*Population[Rabbit])-(Coef[Insect][Lizard]*Population[Lizard])-(Coef[Insect][Bird]*Population[Bird])))*DELTA_T
        DeltaPop[Lizard] = (Population[Lizard]*((Coef[Lizard][Insect]*Population[Insect])-(Coef[Lizard][Lizard])))*DELTA_T
        DeltaPop[Cobra] = (Population[Cobra]*((Coef[Cobra][Bird]*Population[Bird])-(Coef[Cobra][Cobra])+(Coef[Cobra][Rabbit]*Population[Rabbit])))*DELTA_T
        DeltaPop[Bird] = (Population[Bird]*((Coef[Bird][Insect]*Population[Insect])-(Coef[Bird][Bird])-(Coef[Bird][Cobra]*Population[Cobra])))*DELTA_T

        for i in range(6):
            Population[i] = Population[i] + DeltaPop[i]
            Var = Var + abs(DeltaPop[i])
            if Population[i]<=0:
                Population[i]=0


        Time = Time + DELTA_T


    return [YEARS-Time,Var]
    
    
def FindParam (Population,Coef,Generations,T,ALPHA,YEARS):
    BestCoef = list(Coef)
    BestPopulation = list(Population)
    Aux = FunTime(Population,Coef,YEARS)
    BestTime = Aux[0]
    BestVar = Aux[1]
    OldSol = [BestPopulation,BestCoef]
    OldTime = BestTime
    Delta=0
    File_Output = open("output.txt","w+")
    File_Output.write(str([BestPopulation,BestCoef,BestTime]))
    File_Output.close()
    

    for i in range(Generations):
        NewSol = Mutate(OldSol[0],OldSol[1])
        Aux = FunTime(NewSol[0],NewSol[1],YEARS)
        NewTime = Aux[0]
        NewVar = Aux[1]
        print('Iter: ' + str(i+1) + ', OldTime: ' + str(OldTime) + ', NewTime: ' + str(NewTime) + ', Best Time: '+ str(BestTime) + ', Prob: '+ str(math.exp(-Delta/T))+ ', T: '+ str(T)+ ', BestVar: '+ str(BestVar))
        Delta = NewTime - OldTime
        if Delta<0 or random.uniform(0,1) < math.exp(-Delta/T):
            OldSol = NewSol
            OldTime = NewTime
            if NewTime < BestTime:
                BestPopulation = list(NewSol[0])
                BestCoef = list(NewSol[1])
                BestTime = NewTime
                BestVar = NewVar
                File_Output = open("output.txt","w+")
                File_Output.write(str([BestPopulation,BestCoef,BestTime]))
                File_Output.close()
        if NewTime-BestTime==0:
            if NewVar-BestVar<0:
                BestPopulation = list(NewSol[0])
                BestCoef = list(NewSol[1])
                BestTime = NewTime
                BestVar = NewVar
                File_Output = open("output.txt","w+")
                File_Output.write(str([BestPopulation,BestCoef,BestTime]))
                File_Output.close()
        if math.exp(-Delta/T) < 0.00001:
            OldSol = [BestPopulation,BestCoef]
            OldTime = BestTime
        T = T*ALPHA
            
    return


M_PI = 3.14159265358979323846
ITER = 10000
T = 45700
ALPHA = 0.998775174634302
STEP_POP = 5
STEP_COEF = 0.00001
YEARS = 52*1000
DELTA_T = 0.01
DeltaPop = [0,0,0,0,0,0]
K = 500
Coef = []
Grass = 0
Rabbit = 1
Insect = 2
Lizard = 3
Cobra = 4
Bird = 5

File_Input = open("inputPY.txt","r")

random.seed(time.time())

for i in range(6):
    dados=[float(j) for j in File_Input.readline().strip().split(' ')]
    Coef.append(dados)

dados=[float(j) for j in File_Input.readline().strip().split(' ')]
Population = dados

File_Input.close()

FindParam(Population,Coef,ITER,T,ALPHA,YEARS)