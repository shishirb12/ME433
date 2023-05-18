# Write your code here :-)
from ulab import numpy as np
import time

dt = 1.0/100.0 # 100 Hz
t = np.arange(0.0, 1.0, 1.0/1024) # 10s


data = np.sin((2*np.pi)*t/100) + np.sin((2*np.pi)*t/250) + np.sin((2*np.pi)*t/50)

Y = np.fft.fft(data) # fft computing and normalization
#Y = Y[range(int(n/2))]


for j in range(len(Y[0])):
    print(f"({np.log(abs(Y[0][j]))})")
    time.sleep(0.05)

