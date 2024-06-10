import hashlib
import sys
from Python.generate_checksum import generate_checksum

def extract_original_checksum(file_path):
    with open(file_path, "r") as f:
        lines = f.readlines()
    # Remove any trailing empty lines
    while lines and lines[-1].strip() == '':
        lines.pop()
    # The checksum should be on the last remaining line if present
    if lines and lines[-1].strip().startswith("// Checksum: "):
        return lines[-1].strip()[len("// Checksum: "):]
    else:
        raise ValueError("No checksum found in the last line of the file.")

def generate_modified_checksum(file_path):
    sha256_hash = hashlib.sha256()
    with open(file_path, "rb") as f:
        file_content = f.read()
        lines = file_content.split(b'\n')
        # Remove any trailing empty lines
        while lines and lines[-1].strip() == b'':
            lines.pop()
        # Remove the actual checksum line if present
        if lines and lines[-1].startswith(b'// Checksum: '):
            lines.pop()
        # Reconstruct the file content without the checksum line
        file_without_checksum = b'\n'.join(lines)
        sha256_hash.update(file_without_checksum)
    return sha256_hash.hexdigest()

if __name__ == "__main__":
    file_path = 'main.cpp'
    try:
        original_checksum = extract_original_checksum(file_path)
        current_checksum = generate_modified_checksum(file_path)
        if current_checksum == original_checksum:
            print(f"{file_path} is unchanged.")
        else:
            print(f"{file_path} has been modified!")
    except ValueError as e:
        print(e)
