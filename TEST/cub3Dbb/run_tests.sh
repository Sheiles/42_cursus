#!/bin/bash

echo "Setting up Unity testing framework for cub3D..."

# Navigate to tests directory
cd "$(dirname "$0")/tests"

# Download Unity if not present
if [ ! -f "unity/unity.c" ]; then
    echo "Unity not found. Downloading..."
    chmod +x download_unity.sh
    ./download_unity.sh
fi

# Build libft first
echo "Building libft..."
make -C ../includes/Libft

# Build and run tests
echo "Building tests..."
make re

echo "Running all tests..."
make run_tests

echo "Tests setup completed!"
