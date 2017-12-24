# ================================
# MergeSort Algorithm - Python
# 
# Input: a list of numbers
# 
# Output: same list, but sorted
#  by merge sort
#
# Parameters:
#  numList: a list of numbers
#  p: the min number in numList
#  r: the max number in numList
#
# Group: Abe, Thu, Jeremy
# ================================

# ---------- Imports -------------

import math
import sys

# ---------- Functions -----------

# ---------- _merge --------------

def _merge(numList, p, q, r, debug):
    
    L = numList[p - 1:q]
    R = numList[q:r]
    
    if debug:
        print("\np, q, r:", p, q, r, "\nL, R:", L, R)

    L.append(sys.maxsize)
    R.append(sys.maxsize)
    
    i = 0
    j = 0
    for k in range(p - 1, r):
        if L[i] <= R[j]:
            numList[k] = L[i]
            i += 1
        else:
            numList[k] = R[j]
            j += 1
            
# ---------- mergeSort -----------
    
def mergeSort(numList, p, r, debug=False):
    if p < r:
        q = math.floor((p + r) / 2)
        mergeSort(numList, p, q, debug)
        mergeSort(numList, q + 1, r, debug)
        _merge(numList, p, q, r, debug)
    return numList

# ---------- Test Code -----------    
        
if __name__ == "__main__":
    A = [1, -5, 2, 6, 3, 0, -.5, -23, 5/3, 16, 12, 4, -2]
    ASorted = mergeSort(A, 1, len(A))
    print(ASorted)