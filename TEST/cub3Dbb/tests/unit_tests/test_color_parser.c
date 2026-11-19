#include "../unity/unity.h"
#include "../../includes/cub3d.h"

void setUp(void) {
    // Set up code before each test
}

void tearDown(void) {
    // Clean up code after each test
}

void test_parse_floor_color_valid_rgb(void) {
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));
    char *line = "F 220,100,0";
    
    int result = parse_floor_color(line, &game);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(220, game.floor_color.r);
    TEST_ASSERT_EQUAL(100, game.floor_color.g);
    TEST_ASSERT_EQUAL(0, game.floor_color.b);
}

void test_parse_floor_color_invalid_high_value(void) {
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));
    char *line = "F 256,100,0";
    
    int result = parse_floor_color(line, &game);
    TEST_ASSERT_EQUAL(-1, result);
}

void test_parse_floor_color_invalid_negative_value(void) {
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));
    char *line = "F -1,100,0";
    
    int result = parse_floor_color(line, &game);
    TEST_ASSERT_EQUAL(-1, result);
}

void test_parse_floor_color_invalid_format_missing_comma(void) {
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));
    char *line = "F 255 100,0";
    
    int result = parse_floor_color(line, &game);
    TEST_ASSERT_EQUAL(-1, result);
}

void test_parse_ceiling_color_valid_rgb(void) {
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));
    char *line = "C 135,206,235";
    
    int result = parse_ceiling_color(line, &game);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(135, game.ceiling_color.r);
    TEST_ASSERT_EQUAL(206, game.ceiling_color.g);
    TEST_ASSERT_EQUAL(235, game.ceiling_color.b);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_parse_floor_color_valid_rgb);
    RUN_TEST(test_parse_floor_color_invalid_high_value);
    RUN_TEST(test_parse_floor_color_invalid_negative_value);
    RUN_TEST(test_parse_floor_color_invalid_format_missing_comma);
    RUN_TEST(test_parse_ceiling_color_valid_rgb);
    
    return UNITY_END();
}
