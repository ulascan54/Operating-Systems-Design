# 20200702119
# Ulaş Can Demirbağ
import matplotlib.pyplot as plt
import numpy as np
import sys

def read_image(filename):
    with open(filename, 'r') as file:
        # Read the first line to get the size of the image
        size = int(file.readline())
        
        # Initialize a 2D matrix to store the pixel values
        image_matrix = []
        
        # Read the next N*N lines and populate the matrix
        for _ in range(size):
            row = []
            for _ in range(size):
                row.append(int(file.readline()))
            image_matrix.append(row)
    
    return image_matrix

if len(sys.argv) < 2:
    print("Error: Insufficient number of arguments.")
    print("Usage: python script.py <filename>")
    sys.exit(1)

# Example usage
filename = sys.argv[1]
image_matrix = read_image(filename)

# Convert matrix rows to a NumPy array
matrix_array = np.array(image_matrix)

# Create an image using matplotlib
plt.imshow(matrix_array, cmap='gray', interpolation='nearest')
plt.colorbar()  # Add a colorbar to the right of the image
plt.show()
