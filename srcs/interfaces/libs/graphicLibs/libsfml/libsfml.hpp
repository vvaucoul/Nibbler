/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsfml.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:28:01 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/12/03 19:24:45 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBOPENGL_HPP
#define LIBOPENGL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "../../../ILibs.hpp"

#include <map>

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 960

#define MAP_SIZE_X _parameter.width
#define MAP_SIZE_Y _parameter.height

// #define SCALE_X() ((float)WINDOW_WIDTH / (float)(TEXTURES_SIZE * MAP_SIZE_X))
// #define SCALE_Y() ((float)WINDOW_HEIGHT / (float)(TEXTURES_SIZE * MAP_SIZE_Y))

#define MAX_SIZE() (MAP_SIZE_X > MAP_SIZE_Y ? MAP_SIZE_X : MAP_SIZE_Y)

#define SCALE_X() ((float)WINDOW_WIDTH / (float)(TEXTURES_SIZE * MAX_SIZE()))
#define SCALE_Y() ((float)WINDOW_HEIGHT / (float)(TEXTURES_SIZE * MAX_SIZE()))

#define TEXTURES_SIZE 16
#define NB_TEXTURES 256

typedef struct s_background
{
    sf::Vector2u pos;
    sf::Sprite sprite;
} background_t;

typedef struct s_snake_part
{
    int x;
    int y;

    int previous_x;
    int previous_y;

    int next_x;
    int next_y;

    bool isHead;
    bool isTail;

    bool isBody;
    bool isCorner;

    input_t headDirection;
} snake_part_t;

class LibSFML : public ILibs
{
private:
    sf::RenderWindow _window;

    std::map<std::string, sf::Texture> _textures; // Key = Texture Name, Value = Texture
    std::map<std::string, sf::Sprite> _sprites;   // Key = Sprite Name, Value = Sprite

    std::vector<sf::Sprite> _spritesApple;

    std::vector<background_t> _background;

    sf::Font _font;
    sf::Text _score;

    sf::Shader _vertexShader;
    sf::Shader _fragmentShader;

    void drawSquare(uint32_t x, uint32_t y, uint32_t size, sf::Color color);
    float MapRangeClamped(float x, float in_min, float in_max, float out_min, float out_max);

    void initInputs(void);
    void initSprites(void);
    void updateInput(void);
    void initBackground(void);
    void drawBackground(void);
    void drawMap(game_t const &game);

    bool AppleInFrontOfSnake(game_t const &game);

    void snakeDrawPart(snake_part_t const &part);
    snake_part_t snakeAssignPart(game_t const &game, uint32_t index);
    void drawSnake(game_t const &game);

    sf::Sprite loadSprite(std::string const &name, std::string const &path);

    void initFont(void);
    void displayScore(game_t const &game);
    void libSleep(void);

public:
    LibSFML(lib_parameter_t const &parameter);
    LibSFML(LibSFML const &cpy);
    LibSFML &operator=(LibSFML const &cpy);
    virtual ~LibSFML(void);

    void update(game_t const &game);
};

/*******************************************************************************
 *                              SFML ENTRYPOINTS                               *
 ******************************************************************************/

extern "C"
{
    LibSFML *initGLib(lib_parameter_t const parameter);
    void deleteGLib(LibSFML *lib);
}

#endif /* LIBOPENGL_HPP */