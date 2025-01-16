#!/bin/bash
# Ulaş Can Demirbağ
# 20200702119

# arguments
args=(10000 25000 50000 100000 250000 500000 1000000)

# executable file names
programs=(./hw1a.out ./hw1b.out ./hw1c.out ./hw1d.out)

# output file name
output_file="average_times.txt"

# remove the previous output file if it exists
rm -f $output_file

# run each program with each argument 5 times and calculate the average
for program in "${programs[@]}"; do
    for arg in "${args[@]}"; do
        total_time=0
        echo "Running $program with argument $arg"
        for i in {1..5}; do
            # execute the program with the argument and capture the output
            output=$($program $arg)

            # get the execution time from output
            time=$(echo "$output" | grep -Eo '[0-9]+\.[0-9]+')

            echo "Iteration $i: Execution time = $time ms"

            # add time to calculate the average_time
            total_time=$(echo "$total_time + $time" | bc)
        done

        # calculate average time
        average_time=$(echo "scale=6; $total_time / 5" | bc)

        echo "$program with argument $arg: Average execution time = $average_time ms"

        # save the result
        echo "$program with argument $arg: Average execution time = $average_time ms" >>$output_file
    done
done

echo "All averages computed. Results saved to $output_file"
