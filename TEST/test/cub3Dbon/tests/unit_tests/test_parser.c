#include "../unity/unity.h"
#include "../../includes/cub3d.h"

void setUp(void) {
    // Set up code before each test
}

void tearDown(void) {
    // Clean up code after each test
}

void test_parse_no_texture_valid(void) {
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));
    char *line = "NO ./textures/north.xpm";
    
    int result = parse_no_texture(line, &game);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_NOT_NULL(game.no_texture.path);
    
    if (game.no_texture.path)
        free(game.no_texture.path);
}

void test_parse_no_texture_invalid_format(void) {
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));
    char *line = "NO";
    
    int result = parse_no_texture(line, &game);
    TEST_ASSERT_EQUAL(-1, result);
}

void test_parse_floor_color_valid(void) {
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));
    char *line = "F 255,128,64";
    
    int result = parse_floor_color(line, &game);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(255, game.floor_color.r);
    TEST_ASSERT_EQUAL(128, game.floor_color.g);
    TEST_ASSERT_EQUAL(64, game.floor_color.b);
}

void test_parse_floor_color_invalid_range(void) {
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));
    char *line = "F 256,128,64";
    
    int result = parse_floor_color(line, &game);
    TEST_ASSERT_EQUAL(-1, result);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_parse_no_texture_valid);
    RUN_TEST(test_parse_no_texture_invalid_format);
    RUN_TEST(test_parse_floor_color_valid);
    RUN_TEST(test_parse_floor_color_invalid_range);
    
    return UNITY_END();
}
