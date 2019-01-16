import matplotlib.pyplot as plt

with open("samples.txt", 'r') as f:
    lines = f.readlines()


data = [float(line.strip()) for line in lines]

plt.plot(range(len(data)), data)
plt.show()

