
#!/bin/bash

# Function to calculate the difference in minutes between two times
time_diff_in_minutes() {
    local start_time=$1
    local end_time=$2
    local start_seconds=$(date -d "$start_time" +%s)
    local end_seconds=$(date -d "$end_time" +%s)
    local diff_seconds=$((end_seconds - start_seconds))
    local diff_minutes=$((diff_seconds / 60))
    echo $diff_minutes
}

# Function to generate checksum using Python script
generate_checksum() {
    python3 ./Python/generate_checksum.py main.cpp
}

# Get the start time from the main.cpp file
start_time=$(grep "// Start Time:" main.cpp | awk '{print $4}')

# Get the current time for the end time
end_time=$(date '+%H:%M:%S')

# Calculate the time taken in minutes
time_taken=$(time_diff_in_minutes "$start_time" "$end_time")

# Compile the main.cpp file
g++ -DLOCAL -g -fsanitize=address,undefined -o main main.cpp
success=$?
if [ $success -eq 0 ]; then
    echo "Start of Program"
    echo
    ./main < input.txt > output.txt
    echo
    echo "End of Program"

    # Replace End Time and Time Taken fields if they exist
    sed -i "s|// End Time  :.*|// End Time  : $end_time|" main.cpp
    sed -i "s|// Time Taken:.*|// Time Taken: $time_taken minutes|" main.cpp

    # Generate or update the checksum
    generate_checksum
else
    echo "Compilation failed!"
fi

# Clean up
rm -rf main