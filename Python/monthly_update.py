import os
import csv
import subprocess
import datetime

# Function to parse comment lines and extract question details
def parse_comments(lines):
    details = {}
    for line in lines:
        line = line.strip()
        if line.startswith("//"):
            # Check if the line is not a checksum line
            if not (line.startswith("// Checksum:") or line.startswith("// Author:")):
                key_value = line[2:].strip().split(':', 1)
                if len(key_value) == 2:
                    key = key_value[0].strip()
                    value = key_value[1].strip()
                    details[key] = value
    return details

# Function to update CSV file with question details
import os
import csv
from datetime import datetime

def update_csv(details):
    # Create filename based on the current month and year
    now = datetime.now()
    folder_name = "HISTORY"
    file_name = now.strftime("%Y-%m") + ".csv"
    csv_file = os.path.join(folder_name, file_name)

    # Ensure the HISTORY folder exists
    if not os.path.exists(folder_name):
        os.makedirs(folder_name)

    fieldnames = ["Date", "Start Time", "End Time", "Time Taken", "QUESTION LINK", "Rating", "Description", "Solved", "Learning"]

    # Check if CSV file exists
    is_empty = not os.path.exists(csv_file) or os.stat(csv_file).st_size == 0

    # Update or append data
    with open(csv_file, 'a', newline='') as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        if is_empty:
            writer.writeheader()  # Write header only if the file is empty
        writer.writerow(details)


# Function to get untracked .cpp files using Git and sort them by file creation time
def get_untracked_cpp_files():
    untracked_files = subprocess.check_output(["git", "ls-files", "--modified", "--others", "--exclude-standard", ":!main.cpp", "--", "*.cpp"]).decode().splitlines()
    # Sort untracked files based on file creation time
    untracked_files.sort(key=lambda x: os.path.getctime(x))
    # for file in untracked_files:
        # creation_time = datetime.datetime.fromtimestamp(os.path.getctime(file)).strftime('%Y-%m-%d %H:%M:%S')
        # print(f"{file} - Creation Time: {creation_time}")
    return untracked_files

# Main function to update CSV with untracked .cpp files
def main():
    untracked_files = get_untracked_cpp_files()
    if untracked_files:
        for file in untracked_files:
            with open(file, 'r') as f:
                lines = f.readlines()
                details = parse_comments(lines)
                if details.get("QUESTION LINK"):
                    update_csv(details)
                    print(f"Added details for {file} to CSV.")
    else:
        print("No untracked .cpp files found.")

if __name__ == "__main__":
    main()
