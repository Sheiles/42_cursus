#include "../unity/unity.h"
#include "../../includes/cub3d.h"

// Global test setup and teardown
void setUp(void) {
    // Set up code before each test
}

void tearDown(void) {
    // Clean up code after each test
}

void test_is_wall_valid_position(void) {
    t_game game;
    char *test_map[] = {"111", "101", "111", NULL};
    
    ft_memset(&game, 0, sizeof(t_game));
    game.map.grid = test_map;
    game.map.width = 3;
    game.map.height = 3;
    
    int result = is_wall(&game, 1.0, 1.0);
    TEST_ASSERT_EQUAL(0, result); // Should not be a wall (open space)
}

void test_is_wall_wall_position(void) {
    t_game game;
    char *test_map[] = {"111", "101", "111", NULL};
    
    ft_memset(&game, 0, sizeof(t_game));
    game.map.grid = test_map;
    game.map.width = 3;
    game.map.height = 3;
    
    int result = is_wall(&game, 0.0, 0.0);
    TEST_ASSERT_EQUAL(1, result); // Should be a wall
}

void test_is_wall_out_of_bounds(void) {
    t_game game;
    char *test_map[] = {"111", "101", "111", NULL};
    
    ft_memset(&game, 0, sizeof(t_game));
    game.map.grid = test_map;
    game.map.width = 3;
    game.map.height = 3;
    
    int result = is_wall(&game, -1.0, 0.0);
    TEST_ASSERT_EQUAL(1, result); // Should return wall for out of bounds
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_is_wall_valid_position);
    RUN_TEST(test_is_wall_wall_position);
    RUN_TEST(test_is_wall_out_of_bounds);
    
    return UNITY_END();
}
