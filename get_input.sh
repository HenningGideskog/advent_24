#!/bin/bash

# Ensure a day number is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <day>"
    echo "Example: $0 1"
    exit 1
fi

DAY=$1
GIT_ROOT=$(git rev-parse --show-toplevel)

# Ensure the .session_cookie file exists
SESSION_FILE="${GIT_ROOT}/.session_cookie"
if [ ! -f "${SESSION_FILE}" ]; then
    echo "Error: .session_cookie file not found in ${GIT_ROOT}."
    echo "Please create a .session_cookie file with your session token."
    exit 1
fi
SESSION_COOKIE=$(cat "${SESSION_FILE}")

# Define the URL for the input
URL="https://adventofcode.com/2024/day/${DAY}/input"

# Define the directory and output file
DAY_DIR="${GIT_ROOT}/day${DAY}"
OUTPUT="${DAY_DIR}/input_${DAY}.txt"

# Check if the directory exists, create it if it doesn't
if [ ! -d "${DAY_DIR}" ]; then
    echo "Directory ${DAY_DIR} does not exist. Creating it..."
    mkdir "${DAY_DIR}"
fi

# Fetch the input using curl
echo "Fetching input for Day ${DAY}..."
curl -s -H "Cookie: session=${SESSION_COOKIE}" "${URL}" -o "${OUTPUT}"

# Check if the curl command was successful
if [ $? -eq 0 ]; then
    echo "Input saved to ${OUTPUT}."
else
    echo "Failed to fetch input for Day ${DAY}. Please check your session cookie and internet connection."
    exit 1
fi
