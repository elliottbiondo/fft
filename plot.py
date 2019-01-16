import matplotlib.pyplot as plt

datafiles = ["input", "output"]

for datafile in datafiles:
    with open("{}.txt".format(datafile), 'r') as f:
        lines = f.readlines()

    data = [float(line.strip()) for line in lines]
    plt.plot(range(len(data)), data)
    plt.savefig("{}.pdf".format(datafile))
    plt.clf()

