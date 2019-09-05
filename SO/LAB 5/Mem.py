from queue import Queue 
import random

VMEM_SIZE = 40
PMEM_SIZE = 160
PAGE_SIZE = 4
PAGE_QTY = 10
  
def pageFaults(pages, n, capacity): 

    s = set()  
  
    indexes = Queue()  
   
    page_faults = 0
    for i in range(n): 
          
        if (len(s) < capacity): 

            if (pages[i] not in s): 
                s.add(pages[i])  
  
                page_faults += 1
  
                indexes.put(pages[i]) 

        else: 
              
            if (pages[i] not in s): 
                  
                val = indexes.queue[0]  
                indexes.get()  
                s.remove(val)  
                s.add(pages[i])  
                indexes.put(pages[i])  
                page_faults += 1
  
    return page_faults 
  
# Driver code  
if __name__ == '__main__': 
    pages = [7, 0, 1, 2, 0, 3, 0,  
                4, 2, 3, 0, 3, 2]  
    n = len(pages)  
    capacity = 4
    print(pageFaults(pages, n, capacity)) 