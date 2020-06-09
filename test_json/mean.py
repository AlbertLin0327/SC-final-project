import subprocess
import numpy as np

table = np.zero((3, 3, 3))

for i in range(10000):
	result = subprocess.run(['./hw_6_2_3'], stdout = subprocess.PIPE)