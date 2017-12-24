# ================================
# QuickSort Algorithm - Python
# 
# Input: a list of numbers, 
#  and the length of the list
#
# Output: the list of numbers,  
#  but sorted by QuickSort method
#
# Group: Abe, Thu, Jeremy
# ================================

# ---------- Functions -----------

# ---------- _partition -----------

def _partition(numList, p, r, debug):
	partition = numList[r]
    
	i = p - 1
	
	if debug:
		print("List:", numList, "\nPartition:", partition, "\n")
	
	for j in range(p, r):
		if numList[j] <= partition:
			i += 1 
			numList[i], numList[j] = numList[j], numList[i] 
			
	numList[i + 1], numList[r] = numList[r], numList[i + 1]
	return i + 1

# ---------- quickSort -----------

def quickSort(numList, p, r, debug=False):
	
	if p < r:
		q = _partition(numList, p, r, debug)
		quickSort(numList, p, q - 1, debug)
		quickSort(numList, q + 1, r, debug)
	return numList

# ---------- Test Code -----------

if __name__ == "__main__":
	A = [5, 7, 3, 4, 10, 22, 11, 17, 0, 35, .5, .137, -.52, -20, 5/3]
	ASorted = quickSort(A, 0, len(A) - 1)
	print(ASorted)