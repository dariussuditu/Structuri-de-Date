import random
import time

#radix sort

def radix_sort(v, b):

    maxim = max(v)
    nrcifre = 0

    while maxim > 0:
        nrcifre += 1
        maxim //= b
    
    for i in range(nrcifre):
        
        partiale = [[] for _ in range(b)]
        
        for j in range(len(v)):
            digit_val = (v[j] // (b ** i)) % b
            partiale[digit_val].append(v[j])

        v = []
        for partial in partiale:
            v.extend(partial)
        
    return v


#merge sort
def merge_sort(v):
    if len(v) <= 1:
        return v
    
    mij = len(v) // 2
    stanga = v[:mij]
    dreapta = v[mij:]
    
    stanga = merge_sort(stanga)
    dreapta = merge_sort(dreapta)
    
    v_sortat = []
    i = j = 0
    
    while i < len(stanga) and j < len(dreapta):
        if stanga[i] < dreapta[j]:
            v_sortat.append(stanga[i])
            i += 1
        else:
            v_sortat.append(dreapta[j])
            j += 1
            
    v_sortat += stanga[i:]
    v_sortat += dreapta[j:]
    
    return v_sortat


def shell_sort(v):
    pas = len(v) // 2
    
    while pas > 0:
        for i in range(pas, len(v)):
            temp = v[i]
            j = i
            
            while j >= pas and v[j - pas] > temp:
                v[j] = v[j - pas]
                j -= pas
                
            v[j] = temp
            
        pas //= 2
        
    return v



def quick_sort(v):
    if len(v) <= 1:
        return v
    
    pivot = v[len(v) // 2]
    st = [x for x in v if x < pivot]
    mij = [x for x in v if x == pivot]
    dr = [x for x in v if x > pivot]
    
    return quick_sort(st) + mij + quick_sort(dr)


def insertion_sort(v):
    for i in range(1, len(v)):
        key = v[i]
        j = i - 1
        
        while j >= 0 and v[j] > key:
            v[j + 1] = v[j]
            j -= 1
        
        v[j + 1] = key
    
    return v


def sort_check(v):
    check=True
    for i in range (0,len(v)-1):
        if(v[i]>v[i+1]):
            check=False
    return check




def testing(t):
    k=0
    while(k<t):
        n=int(input("nr de numere: "))
        print('Testul cu numarul: ',k)
        max=int(input("max: "))  
        arr_random=[]
        arr_sorted=[]
        arr_reverse=[]
        for i in range (0,n):
            c=n-i
            arr_random.append(random.randint(0,max))
            arr_sorted.append(i)
            arr_reverse.append(c)

        start=time.time()
        radix_sort(arr_random,10)
        end=time.time()
        print('Timp radix ',end-start)
        print(sort_check(radix_sort(arr_random,10)))

        start=time.time()
        merge_sort(arr_random)
        end=time.time()
        print('Timp merge ',end-start)
        print(sort_check(merge_sort(arr_random)))


        start=time.time()
        shell_sort(arr_random)
        end=time.time()
        print('Timp shell ',end-start)
        print(sort_check(shell_sort(arr_random)))

        start=time.time()
        quick_sort(arr_random)
        end=time.time()
        print('Timp quick ',end-start)
        print(sort_check(quick_sort(arr_random)))

        start=time.time()
        insertion_sort(arr_random)
        end=time.time()
        print('Timp insertion ',end-start)
        print(sort_check(insertion_sort(arr_random)))

        start=time.time()
        sorted(arr_random)
        end=time.time()
        print(end-start)
        print('Timp nativ ',end-start)
        print(sort_check(sorted(arr_random)))

        k=k+1
        



testing(1)




