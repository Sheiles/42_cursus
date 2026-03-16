# cub3D Testing Setup

## Overview
This directory contains Unity testing framework setup for testing cub3D functions.

## Structure
```
tests/
├── unity/                  # Unity testing framework files
│   ├── unity.c
│   ├── unity.h
│   └── unity_internals.h
├── unit_tests/             # Test files
│   ├── test_utils.c        # Tests for utils.c functions
│   └── test_parser.c       # Tests for parser functions (TODO)
├── Makefile               # Build configuration for tests
├── download_unity.sh      # Script to download Unity framework
└── README.md             # This file
```

## Quick Start

1. **Run all tests:**
   ```bash
   cd tests
   make run_tests
   ```

2. **Build specific tests:**
   ```bash
   make test_utils      # Build utils tests only
   make clean           # Clean compiled tests
   make re              # Rebuild everything
   ```

3. **Run specific tests:**
   ```bash
   ./test_utils         # Run utils tests
   ```

## Adding New Tests

1. Create a new test file in `unit_tests/` directory
2. Include Unity framework: `#include "../unity/unity.h"`
3. Include your header: `#include "../../includes/cub3d.h"`
4. Write test functions using Unity assertions
5. Add the test target to Makefile

### Example Test Function
```c
void test_function_name(void) {
    // Setup
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));
    
    // Test
    int result = your_function(&game, params);
    
    // Assert
    TEST_ASSERT_EQUAL(expected_value, result);
}
```

## Available Unity Assertions

- `TEST_ASSERT_EQUAL(expected, actual)`
- `TEST_ASSERT_NOT_NULL(pointer)`
- `TEST_ASSERT_NULL(pointer)`
- `TEST_ASSERT_TRUE(condition)`
- `TEST_ASSERT_FALSE(condition)`
- `TEST_ASSERT_EQUAL_STRING(expected, actual)`

## Current Tests

### test_utils.c
- `test_is_wall_valid_position()` - Tests wall detection for open spaces
- `test_is_wall_wall_position()` - Tests wall detection for walls
- `test_is_wall_out_of_bounds()` - Tests out-of-bounds behavior

## Notes

- Tests use a simplified test environment without MLX dependencies
- Memory allocations in tests should be cleaned up in tearDown()
- All tests pass with 0 failures when properly implemented
