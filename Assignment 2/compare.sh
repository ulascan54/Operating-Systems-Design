#!/bin/bash
# Ulaş Can Demirbağ
# 20200702119

PROGRAMS=("hw2a" "hw2b")
INPUTS=("qr_code_64x64_grayscale.dat" "qr_code_128x128_grayscale.dat" "qr_code_512x512_grayscale.dat")

for prog in "${PROGRAMS[@]}"; do
    for inp in "${INPUTS[@]}"; do
        (gtime -v ./$prog $inp >/dev/null) 2>&1
    done
done
