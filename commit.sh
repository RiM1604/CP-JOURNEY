#!/bin/bash

# Check if there are any staged changes
git add --all
git reset main.cpp input.txt output.txt
if git diff --cached --quiet; then
    echo "No changes in the staging area to commit."
else
  # Commit with a message passed as an argument
    git commit -m "$@"
    git push -u origin main
fi
