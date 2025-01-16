# 20200702119
# Ulaş Can Demirbağ

CC = gcc
LDFLAGS = -pthread

all: hw2a hw2b

hw2a: hw2a.c
	$(CC) $(CFLAGS) hw2a.c -o hw2a $(LDFLAGS)

hw2b: hw2b.c
	$(CC) $(CFLAGS) hw2b.c -o hw2b $(LDFLAGS)

run: run-a run-b

run-a:
	./hw2a qr_code_64x64_grayscale.dat > out/output_hw2a_64.dat
	./hw2a qr_code_128x128_grayscale.dat > out/output_hw2a_128.dat
	./hw2a qr_code_512x512_grayscale.dat > out/output_hw2a_512.dat

run-b:
	./hw2b qr_code_64x64_grayscale.dat > out/output_hw2b_64.dat
	./hw2b qr_code_128x128_grayscale.dat > out/output_hw2b_128.dat
	./hw2b qr_code_512x512_grayscale.dat > out/output_hw2b_512.dat

py: pya pyb

pya:
	python3 python.py out/output_hw2a_64.dat
	python3 python.py out/output_hw2a_128.dat
	python3 python.py out/output_hw2a_512.dat

pyb:
	python3 python.py out/output_hw2b_64.dat
	python3 python.py out/output_hw2b_128.dat
	python3 python.py out/output_hw2b_512.dat

pytest:
	python3 python.py qr_code_64x64_grayscale.dat
	python3 python.py qr_code_128x128_grayscale.dat
	python3 python.py qr_code_512x512_grayscale.dat


comp: 
	sh compare.sh > comp.txt

clean:
	rm -f hw2a hw2b
	rm -f out/output_hw2a_64.dat out/output_hw2a_128.dat out/output_hw2a_512.dat
	rm -f out/output_hw2b_64.dat out/output_hw2b_128.dat out/output_hw2b_512.dat
