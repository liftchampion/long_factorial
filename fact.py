import sys
import math

if len(sys.argv) != 2:
    print('Please, give 1 numeric argument')
    sys.exit()

print(str(math.factorial(int(sys.argv[1]))))
