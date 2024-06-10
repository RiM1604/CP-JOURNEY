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

# Function to execute the custom command between 10 PM and 11 PM
execute_custom_command() {
    # Check if the custom command has already been executed today
    if [ ! -f "/tmp/custom_command_executed" ]; then
        # Run the monthly_update.py script
        python3 ./Python/monthly_update.py
        # Add and commit all untracked and modified files except main.cpp
        ./commit.sh "Automatic commit $(date '+%Y-%m-%d %H:%M:%S')"
        # Mark that the custom command has been executed today
        touch "/tmp/custom_command_executed"
    else
            # Get the modification time of the file
            modified_time=$(stat -c %Y /tmp/custom_command_executed)
            # Calculate the time difference in seconds
            current_time=$(date +%s)
            time_diff=$((current_time - modified_time))
            # echo ${time_diff}
            # Check if more than 24 hours have passed since the last execution
            if [ $time_diff -ge 1800 ]; then
                echo "More than half an hour has passed since the last execution."
                # Remove the file to allow execution again
                rm /tmp/custom_command_executed
            else
                echo "Less than half an hour has passed since the last execution. Skipping."
                return
            fi
    fi
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
    # Execute the custom command between 7 AM and 11 PM
    execute_custom_command
else
    echo "Compilation failed!"
fi
# Clean up
rm -rf main
