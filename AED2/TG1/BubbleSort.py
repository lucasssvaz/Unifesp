import pandas as pd
import time

current_time = lambda: int(round(time.time() * 1000))

def BubbleSort(data):
    nRows = data.shape[0]
    nColumns = data.shape[1]
    
    for i in range(nRows):
        swap = 0
        for j in range(1,nRows-i):
            k = 0
            while (k < nColumns):
                if (data.iloc[j-1,k] == data.iloc[j,k]):
                    k = k+1
                else:
                    if (data.iloc[j-1,k] > data.iloc[j,k]):
                        aux = data.iloc[j-1]
                        data.iloc[j-1] = data.iloc[j]
                        data.iloc[j] = aux
                        swap = 1
                        print("SWAP")            
                    break
            print(str(i) + "," + str(j) + "," + str(k))
        if not swap:
            break    
    return

files = {'1':'credit.csv','2':'eeg.csv','3':'kc1.csv','4':'phoneme.csv'}

dataset = files[input("Select the dataset:\n1) Credit \n2) Eeg-eye \n3) KC1 \n4) Phoneme \n")]

database = pd.read_csv(dataset)

start = current_time()

BubbleSort(database)

elapsed = current_time() - start

print(elapsed)

database.to_csv('Final_'+dataset)
