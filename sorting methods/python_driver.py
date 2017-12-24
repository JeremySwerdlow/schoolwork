#=================================
# Driver Program - Python
#
# Input: Sorting Method:
#  Options are merge, quick,
#  or insertion
#
# Output: File containing the
#  time it takes to sort 10, 100
#  1 000, 10 000, and 100 000 
#  random numbers using the given
#  method
#
# Group: Thu, Jeremy, Abe
#=================================

# ---------- Imports -------------

import os
import time


import number_generator as numGen
import merge_sort as mSort
import insertion_sort as iSort
import quick_sort as qSort

# ---------- Functions -----------

# ---------- _fileCreator --------

def _fileCreator(base_size, iter=5):
	file_list = []

	size = base_size
	for i in range(iter):
		numGen.number_generator(size)
		file_list.append(str(size))
		size *= base_size
	
	return file_list
	
# ---------- _fileToList ---------

def _fileToList(file):
	open_file = open(file, 'r+')
	data_string = open_file.read()
	data_List = data_string.split(', ')
	
	return data_List

# ---------- _deleteFiles --------

def _deleteFiles(fileNameList):
	for name in fileNameList:
		os.remove(name)
		
	print('Files Deleted.')
	return
	
# ---------- _askDelete ----------

def _askDelete(fileNameList):
	answer = input('Do you want to delete the generated files? (y/n): ')
	if answer == 'y':
		_deleteFiles(fileNameList)
	elif answer == 'n':
		print('Files Kept.')
		return
	else:
		print('''Oops, that input wasn't valid. Please answer with either a
y or n, signifying yes or no.\n''')
		_askDelete(fileNameList)
	
# ---------- methodTester --------
			
def methodTester(sortMethod, baseSize=10):
	
	#store the sorted file names
	sorted_files = []
	
	
	# Create the random number files
	files = _fileCreator(baseSize)
	
	
	# Create the time table file
	timing_file = open(str(sortMethod) + "Sort_test_times", 'w')
	timing_file.write("Input Size (n):	Time cost:")
	

	# For each of the files:
	for file in files:
		
		# Create a list from the numbers stored in the file
		number_list = _fileToList(file)
		number_count = len(number_list)
		for i in range(number_count):
			number_list[i] = float(number_list[i])
		
		
		# Create the file to store the sorted list
		sortedFileName = str(file) + "_" + sortMethod + "sort_sorted"
		sorted_files.append(sortedFileName)
		sortedFile = open(sortedFileName, 'w')
		
		
		# Check sorting method, then sort while timing
		if sortMethod == 'merge':
			start_time = time.time()
			numberListSorted = mSort.mergeSort(number_list, 1, len(number_list))
			stop_time = time.time()
		elif sortMethod == 'quick':
			start_time = time.time()
			numberListSorted = qSort.quickSort(number_list, 0, len(number_list) - 1)
			stop_time = time.time()
		elif sortMethod == 'insertion':
			start_time = time.time()
			numberListSorted = iSort.insertionSort(number_list, len(number_list))
			stop_time = time.time()
		else:
			print('''Uh oh, the provided sort method has yet to be implemented!
Please use either 'merge', 'quick', or 'insertion'.\n''')
		
		
		# Store the sorted list in its respective file
		sortedFile.write(str(numberListSorted))
		sortedFile.close()
		
		
		# Calculate the time taken, then add it to the timing file
		sort_time = stop_time - start_time
		timing_file.write("\n" + str(number_count) + "		" + str(sort_time))
	
	
	# Close the timing file, and prompt the user on whether
	#  or not to delete the created files used to calculate
	#  the timing data.
	timing_file.close()
	files.extend(sorted_files)	
	_askDelete(files)
		
# ---------- Test Code -----------		
		
if __name__ == '__main__':
	print('''
This code is used to test Merge, Quick, and Insertion sort implementations 
in Python. They will be tested in that order, and will ask if you wish to 
delete or keep the files created to test each method. The timing will be 
stored in a .txt file named XXX_test_times, where XXX is the sorting method. 
This file is located in the same directory as this file.''')
	print('\nNow testing Merge Sort.')
	methodTester('merge')
	print('\nNow testing Quick Sort.')
	methodTester('quick')
	print('\nNow testing Insertion Sort.')
	methodTester('insertion')
	print('''
All three methods have been tested, with the times taken stored in files as
described above. Please take a second to review the data generated. 
Thank you for running this test code.''')