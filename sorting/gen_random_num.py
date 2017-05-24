import sys
import random

def gen(count):
    # generate random number
    i = 0
    print(count)
    while (i < count):
        rand_num = random.randint(0, count)
        print("%d " % rand_num, end="")
        i += 1
    print()

if __name__ == '__main__':
    count = sys.argv[1]
    gen(int(count))