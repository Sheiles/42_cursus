#!/bin/bash

# cub3D Test Runner Script
# Usage: ./test_runner.sh [test_name|all|help]

TEST_DIR="$(dirname "$0")"
cd "$TEST_DIR"

show_help() {
    echo "cub3D Test Runner"
    echo "Usage: $0 [option]"
    echo ""
    echo "Options:"
    echo "  all              Run all tests (default)"
    echo "  utils            Run utils tests only"
    echo "  color            Run color parser tests only"
    echo "  texture          Run texture parser tests only"
    echo "  clean            Clean compiled test files"
    echo "  help             Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0                # Run all tests"
    echo "  $0 utils          # Run only utils tests"
    echo "  $0 clean          # Clean test files"
}

run_specific_test() {
    local test_name=$1
    echo "=== Building $test_name test ==="
    if make "test_$test_name"; then
        echo "=== Running $test_name test ==="
        "./test_$test_name"
        return $?
    else
        echo "Failed to build $test_name test"
        return 1
    fi
}

case "${1:-all}" in
    "all")
        echo "Building and running all tests..."
        make run_tests
        ;;
    "utils")
        run_specific_test "utils"
        ;;
    "color")
        run_specific_test "color_parser"
        ;;
    "texture")
        run_specific_test "texture_parser"
        ;;
    "clean")
        echo "Cleaning test files..."
        make clean
        ;;
    "help"|"-h"|"--help")
        show_help
        ;;
    *)
        echo "Unknown option: $1"
        show_help
        exit 1
        ;;
esac
