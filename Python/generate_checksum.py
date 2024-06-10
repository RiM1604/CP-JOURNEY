import hashlib
import sys

def generate_checksum(file_path):
    sha256_hash = hashlib.sha256()
    with open(file_path, "rb") as f:
        for byte_block in iter(lambda: f.read(4096), b""):
            sha256_hash.update(byte_block)
    return sha256_hash.hexdigest()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 generate_checksum.py <file_path>")
        sys.exit(1)
    file_path = sys.argv[1]
    checksum = generate_checksum(file_path)
    print(checksum)
