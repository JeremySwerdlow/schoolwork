from random import randint
from os import popen, path
from time import sleep


if __name__ == '__main__':
    # make sure compiled file exists
    dir_files = popen('ls').read().split('\n')
    if not 'matrix' in dir_files:
        popen('gcc matrix_multiplication.c -o matrix')
        while not path.exists('matrix'):
            sleep(0.5) # sleep to ensure file is compiled before run
    # run matrix 10 times with random numbers
    for i in range(10):
        n = str(randint(64, 400))
        print(popen('./matrix ' + n).read().rstrip())
