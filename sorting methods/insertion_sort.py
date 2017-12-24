# ================================
# InsertionSort Algorithm - Python
# 
# Input: a list of numbers
# 
# Output: same list, but sorted
#  by InsertionSort method
# 
# Parameters:
#  numList: a list of numbers
#  n: number of elts in numList
#
# Group: Thu, Jeremy, Abe
# ================================

# ---------- Imports -------------

import math
import sys

# ---------- Functions -----------

# ---------- insertionSort -------

def insertionSort(numList, n, debug=False):

    for i in range(1, n):	
        key = numList[i]
        j = i - 1
        
        if debug:
        	print("\nkey:", key, "\nList:", numList)
        
        while j >= 0 and numList[j] > key:
            numList[j + 1] = numList[j]
            j -= 1
            
        numList[j + 1] = key
        
    return numList

# ---------- Test Code -----------

if __name__ == "__main__":

    A = [5, -6, 4, -20, 3, 2, 1, 6, 13, 10]
    test = insertionSort(A, len(A))
    print(test)