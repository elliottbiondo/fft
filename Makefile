all:
	gcc fft.c -o fft.exe
	./fft.exe 1024
	python plot.py
