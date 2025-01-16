#!/bin/bash

# Define the base directory names for kernel and user spaces
KERNEL_SPACE="/usr/src/kernel-source-2.4.27"
USER_SPACE="/usr/include"
DEST_DIR="/root/get_files/files"

# Create the destination directory if it doesn't exist
mkdir -p "$DEST_DIR"

# List of directories and files to copy
declare -a paths=(
    "$KERNEL_SPACE/arch/i386/kernel/entry.S"     # System call table
    "$KERNEL_SPACE/fs/getProcInfoF24.c"         # New system call implementation
    "$KERNEL_SPACE/fs/Makefile"                  # Makefile for building
    "$KERNEL_SPACE/include/asm-i386/unistd.h"    # System call number definition
    "$KERNEL_SPACE/include/linux/getProcInfoF24.h" # Header for struct definition
    "$KERNEL_SPACE/sched.c" # Sikecilir
    "$USER_SPACE/asm/unistd.h"                   # User-space syscall number
    "$USER_SPACE/linux/getProcInfoF24.h"        # User-space header for struct
)

# Copy each specified file if it exists
for path in "${paths[@]}"; do
    if [ -f "$path" ]; then
        # Copy the file to the destination directory, preserving directory structure
        cp --parents "$path" "$DEST_DIR"
    elif [ -d "$path" ]; then
        # If the path is a directory, copy it recursively
        cp -r --parents "$path" "$DEST_DIR"
    else
        echo "Warning: $path not found."
    fi
done

echo "Specified files and directories copied to $DEST_DIR"
