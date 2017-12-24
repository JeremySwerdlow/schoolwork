#=================================
# Number File Generator - Python 
# 
# Input: an integer n
# 
# Output: a .txt file holding 
#  n number of integers
# 
# Group: Jeremy, Abe, Thu
# ===============================

# ---------- Imports ------------

import random
import sys

# ---------- Functions -----------

# ---------- number_generator ----

def number_generator(size):

    fileName = str(size)
    
    numberFile = open(fileName, "w")
    
    for i in range(size - 1):
        randomNum = random.random() * 100000
        
        numberFile.write(str(randomNum) + ", ")
    randomNum = random.random() * 100000
    numberFile.write(str(randomNum))
        
    numberFile.close()
  
# ---------- Test Code -----------

if __name__ == "__main__":
    number_generator(10)