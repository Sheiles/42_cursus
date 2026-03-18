#include "../unity/unity.h"
#include "../../includes/cub3d.h"

void setUp(void) {
    // Set up code before each test
}

void tearDown(void) {
    // Clean up code after each test
}

void test_parse_no_texture_valid_path(void) {
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));
    char *line = "NO ./textures/north_wall.xpm";
    
    int result = parse_no_texture(line, &game);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_NOT_NULL(game.no_texture.path);
    
    // Clean up
    if (game.no_texture.path)
        free(game.no_texture.path);
}

void test_parse_so_texture_valid_path(void) {
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));
    char *line = "SO ./textures/south_wall.xpm";
    
    int result = parse_so_texture(line, &game);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_NOT_NULL(game.so_texture.path);
    
    // Clean up
    if (game.so_texture.path)
        free(game.so_texture.path);
}

void test_parse_we_texture_valid_path(void) {
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));
    char *line = "WE ./textures/west_wall.xpm";
    
    int result = parse_we_texture(line, &game);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_NOT_NULL(game.we_texture.path);
    
    // Clean up
    if (game.we_texture.path)
        free(game.we_texture.path);
}

void test_parse_ea_texture_valid_path(void) {
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));
    char *line = "EA ./textures/east_wall.xpm";
    
    int result = parse_ea_texture(line, &game);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_NOT_NULL(game.ea_texture.path);
    
    // Clean up
    if (game.ea_texture.path)
        free(game.ea_texture.path);
}

void test_parse_texture_invalid_empty_path(void) {
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));
    char *line = "NO ";
    
    int result = parse_no_texture(line, &game);
    TEST_ASSERT_EQUAL(-1, result);
}

void test_parse_texture_invalid_no_path(void) {
    t_game game;
    ft_memset(&game, 0, sizeof(t_game));
    char *line = "NO";
    
    int result = parse_no_texture(line, &game);
    TEST_ASSERT_EQUAL(-1, result);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_parse_no_texture_valid_path);
    RUN_TEST(test_parse_so_texture_valid_path);
    RUN_TEST(test_parse_we_texture_valid_path);
    RUN_TEST(test_parse_ea_texture_valid_path);
    RUN_TEST(test_parse_texture_invalid_empty_path);
    RUN_TEST(test_parse_texture_invalid_no_path);
    
    return UNITY_END();
}
