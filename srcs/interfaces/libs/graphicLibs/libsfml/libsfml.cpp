/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsfml.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:29:10 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/12/06 14:41:30 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsfml.hpp"

#include <tuple>
#include <iostream>
#include <ctime>
#include <chrono>

/*******************************************************************************
 *                      LIBSFML CONSTRUCTORS / DESTRUCTOR                      *
 ******************************************************************************/

LibSFML::LibSFML(lib_parameter_t const &parameter)
{
    // Update map (add borders)
    lib_parameter_t new_parameter = parameter;
    new_parameter.height += 1;
    new_parameter.width += 1;

    ILibs::_parameter = new_parameter;

    _window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Nibbler");
    /* Set Screen Size */
    _window.setSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));

    /* Set Screen Position */
    _window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - _window.getSize().x / 2, sf::VideoMode::getDesktopMode().height / 2 - _window.getSize().y / 2));

    // _window.setFramerateLimit(parameter.fps);
    _window.setFramerateLimit(60);

    // Check Shaders
    if (!sf::Shader::isAvailable())
    {
        std::cout << "Shaders are not available on this system" << std::endl;
    }

    // Load the shader code
    // _vertexShader.loadFromFile("assets/SFML/Shaders/ShadowsVertex.glsl", sf::Shader::Type::Vertex);
    // _fragmentShader.loadFromFile("assets/SFML/Shaders/ShadowsFragments.glsl", sf::Shader::Type::Fragment);

    srand(time(NULL));
    initInputs();
    initSprites();
    initBackground();
    initFont();
}

LibSFML::LibSFML(LibSFML const &cpy)
{
    *this = cpy;
}

LibSFML &LibSFML::operator=(LibSFML const &cpy)
{
    if (this != &cpy)
    {
        _parameter = cpy._parameter;
        _textures = cpy._textures;
        _sprites = cpy._sprites;
        _background = cpy._background;
        _font = cpy._font;
        _score = cpy._score;
        _spritesApple = cpy._spritesApple;
    }
    return (*this);
}

LibSFML::~LibSFML(void)
{
}

/*******************************************************************************
 *                                   LIBSFM                                    *
 ******************************************************************************/

void LibSFML::initFont(void)
{
    if (!_font.loadFromFile("assets/fonts/font_pixel.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
        exit(1);
    }
    else
    {
        _score.setFont(_font);
        _score.setCharacterSize(14);
        _score.setFillColor(sf::Color::White);
        _score.setPosition(0, 0);
    }
}

sf::Sprite LibSFML::loadSprite(std::string const &name, std::string const &path)
{
    sf::Texture texture;
    sf::Sprite sprite;

    if (_textures.find(name) != _textures.end())
    {
        sf::Texture::bind(&_textures[name]);
    }
    else if ((texture.loadFromFile(path)) == false)
    {
        std::cerr << "Error loading texture: " << path << std::endl;
        exit(1);
    }
    texture.setSmooth(false);
    _textures[name] = texture;
    sprite.setTexture(_textures[name]);
    _sprites[name] = sprite;
    return (sprite);
}

void LibSFML::initSprites(void)
{
    /* Default Map */
    loadSprite("MAP_EMPTY", "assets/sprites/nibbler_grass01.png");
    loadSprite("MAP_GRASS", "assets/sprites/nibbler_grass02.png");
    loadSprite("MAP_GRASS_HUGE", "assets/sprites/nibbler_grass03.png");
    loadSprite("MAP_OBSTACLE", "assets/sprites/nibbler_rock_no_bg.png");

    /* Border Water */
    loadSprite("MAP_WATER_BOTTOM", "assets/sprites/nibbler_water_bottom.png");
    loadSprite("MAP_WATER_TOP", "assets/sprites/nibbler_water_top.png");
    loadSprite("MAP_WATER_LEFT", "assets/sprites/nibbler_water_left.png");
    loadSprite("MAP_WATER_RIGHT", "assets/sprites/nibbler_water_right.png");
    loadSprite("MAP_WATER_TOP_LEFT", "assets/sprites/nibbler_water_top_left.png");
    loadSprite("MAP_WATER_TOP_RIGHT", "assets/sprites/nibbler_water_top_right.png");
    loadSprite("MAP_WATER_BOTTOM_LEFT", "assets/sprites/nibbler_water_bottom_left.png");
    loadSprite("MAP_WATER_BOTTOM_RIGHT", "assets/sprites/nibbler_water_bottom_right.png");

    loadSprite("MAP_WATER", "assets/sprites/nibbler_water.png");

    /* Apples Sprites */
    loadSprite("APPLE", "assets/sprites/nibbler_food_normal.png");
    loadSprite("APPLE_GOLD", "assets/sprites/nibbler_food_bonus.png");
    loadSprite("APPLE_POISON", "assets/sprites/nibbler_food_malus.png");

    /* Snake Sprites */
    loadSprite("SNAKE_HEAD_TOP", "assets/sprites/nibbler_snake_head_from_bottom.png");
    loadSprite("SNAKE_HEAD_BOTTOM", "assets/sprites/nibbler_snake_head_from_top.png");
    loadSprite("SNAKE_HEAD_LEFT", "assets/sprites/nibbler_snake_head_from_right.png");
    loadSprite("SNAKE_HEAD_RIGHT", "assets/sprites/nibbler_snake_head_from_left.png");

    loadSprite("SNAKE_TAIL_TOP", "assets/sprites/nibbler_snake_tail_to_top.png");
    loadSprite("SNAKE_TAIL_BOTTOM", "assets/sprites/nibbler_snake_tail_to_bottom.png");
    loadSprite("SNAKE_TAIL_LEFT", "assets/sprites/nibbler_snake_tail_to_left.png");
    loadSprite("SNAKE_TAIL_RIGHT", "assets/sprites/nibbler_snake_tail_to_right.png");

    loadSprite("SNAKE_BODY_BOTTOM_TOP", "assets/sprites/nibbler_snake_from_top_to_bottom.png");
    loadSprite("SNAKE_BODY_TOP_BOTTOM", "assets/sprites/nibbler_snake_from_bottom_to_top.png");
    loadSprite("SNAKE_BODY_RIGHT_LEFT", "assets/sprites/nibbler_snake_from_left_to_right.png");
    loadSprite("SNAKE_BODY_LEFT_RIGHT", "assets/sprites/nibbler_snake_from_right_to_left.png");
    loadSprite("SNAKE_BODY_LEFT_TOP", "assets/sprites/nibbler_snake_from_top_to_left.png");
    loadSprite("SNAKE_BODY_LEFT_BOTTOM", "assets/sprites/nibbler_snake_from_bottom_to_left.png");
    loadSprite("SNAKE_BODY_RIGHT_TOP", "assets/sprites/nibbler_snake_from_top_to_right.png");
    loadSprite("SNAKE_BODY_RIGHT_BOTTOM", "assets/sprites/nibbler_snake_from_bottom_to_right.png");

    loadSprite("SNAKE_BODY_TOP_LEFT", "assets/sprites/nibbler_snake_from_left_to_top.png");
    loadSprite("SNAKE_BODY_TOP_RIGHT", "assets/sprites/nibbler_snake_from_right_to_top.png");
    loadSprite("SNAKE_BODY_BOTTOM_LEFT", "assets/sprites/nibbler_snake_from_left_to_bottom.png");
    loadSprite("SNAKE_BODY_BOTTOM_RIGHT", "assets/sprites/nibbler_snake_from_right_to_bottom.png");

    loadSprite("SNAKE_TONGUE_TOP", "assets/sprites/nibbler_tongue_main_from_bottom.png");
    loadSprite("SNAKE_TONGUE_BOTTOM", "assets/sprites/nibbler_tongue_main_from_top.png");
    loadSprite("SNAKE_TONGUE_LEFT", "assets/sprites/nibbler_tongue_main_from_right.png");
    loadSprite("SNAKE_TONGUE_RIGHT", "assets/sprites/nibbler_tongue_main_from_left.png");

    loadSprite("SNAKE_TONGUE_HEAD_TOP", "assets/sprites/nibbler_tongue_head_from_bottom.png");
    loadSprite("SNAKE_TONGUE_HEAD_BOTTOM", "assets/sprites/nibbler_tongue_head_from_top.png");
    loadSprite("SNAKE_TONGUE_HEAD_LEFT", "assets/sprites/nibbler_tongue_head_from_right.png");
    loadSprite("SNAKE_TONGUE_HEAD_RIGHT", "assets/sprites/nibbler_tongue_head_from_left.png");
}

void LibSFML::initInputs(void)
{
    ILibs::_inputs.insert(std::make_pair(0, input_t::NONE));
    ILibs::_inputs.insert(std::make_pair(sf::Keyboard::Key::Up, input_t::UP));
    ILibs::_inputs.insert(std::make_pair(sf::Keyboard::Key::Left, input_t::LEFT));
    ILibs::_inputs.insert(std::make_pair(sf::Keyboard::Key::Down, input_t::DOWN));
    ILibs::_inputs.insert(std::make_pair(sf::Keyboard::Key::Right, input_t::RIGHT));
    ILibs::_inputs.insert(std::make_pair(sf::Keyboard::Key::W, input_t::UP));
    ILibs::_inputs.insert(std::make_pair(sf::Keyboard::Key::A, input_t::LEFT));
    ILibs::_inputs.insert(std::make_pair(sf::Keyboard::Key::S, input_t::DOWN));
    ILibs::_inputs.insert(std::make_pair(sf::Keyboard::Key::D, input_t::RIGHT));
    ILibs::_inputs.insert(std::make_pair(sf::Keyboard::Key::Escape, input_t::QUIT));
    ILibs::_inputs.insert(std::make_pair(sf::Keyboard::Key::U, input_t::LIB1));
    ILibs::_inputs.insert(std::make_pair(sf::Keyboard::Key::I, input_t::LIB2));
    ILibs::_inputs.insert(std::make_pair(sf::Keyboard::Key::O, input_t::LIB3));
}

float LibSFML::MapRangeClamped(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void LibSFML::drawSquare(uint32_t x, uint32_t y, uint32_t size, sf::Color color)
{
    sf::RectangleShape rectangle(sf::Vector2f(size, size));
    rectangle.setFillColor(color);
    rectangle.setPosition(x, y);
    rectangle.setSize(sf::Vector2f(size, size));
    _window.draw(rectangle);
}

void LibSFML::updateInput(void)
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (_parameter.inputHandler != nullptr)
        {
            if (event.type == sf::Event::KeyPressed)
                _parameter.inputHandler(ILibs::_inputs[event.key.code]);
            else if (event.type == sf::Event::Closed)
            {
                _window.close();
                _parameter.inputHandler(input_t::QUIT);
            }
            else
                _parameter.inputHandler(input_t::NONE);
        }
    }
}

/*
** Init background staticly
** To get the same background each time
*/
void LibSFML::initBackground(void)
{
    uint32_t i = 0;

    /* Grass Background */
    for (uint32_t y = 1; y < MAP_SIZE_Y - 1; y++)
    {
        for (uint32_t x = 1; x < MAP_SIZE_X - 1; x++)
        {
            background_t bg;
            i = rand() % 3;

            bg.pos.x = x;
            bg.pos.y = y;

            if (i == 0)
                bg.sprite = _sprites["MAP_EMPTY"];
            else if (i == 1)
                bg.sprite = _sprites["MAP_GRASS"];
            else if (i == 2)
                bg.sprite = _sprites["MAP_GRASS_HUGE"];
            bg.sprite.setPosition(x * TEXTURES_SIZE * SCALE_X(), y * TEXTURES_SIZE * SCALE_Y());
            bg.sprite.setScale(SCALE_X(), SCALE_Y());
            _background.push_back(bg);
        }
    }

    /* Border Water Background TOP */
    for (uint32_t x = 1; x < MAP_SIZE_X - 1; x++)
    {
        background_t bg;
        bg.pos.x = x;
        bg.pos.y = 0;
        bg.sprite = _sprites["MAP_WATER_TOP"];
        bg.sprite.setScale(SCALE_X(), SCALE_Y());
        bg.sprite.setPosition(x * TEXTURES_SIZE * SCALE_X(), 0);
        _background.push_back(bg);
    }
    /* Border Water Background BOTTOM */
    for (uint32_t x = 1; x < MAP_SIZE_X - 1; x++)
    {
        background_t bg;
        bg.pos.x = x;
        bg.pos.y = MAP_SIZE_Y - 1;
        bg.sprite = _sprites["MAP_WATER_BOTTOM"];
        bg.sprite.setScale(SCALE_X(), SCALE_Y());
        bg.sprite.setPosition(x * TEXTURES_SIZE * SCALE_X(), (MAP_SIZE_Y - 1) * TEXTURES_SIZE * SCALE_Y());
        _background.push_back(bg);
    }
    /* Border Water Background LEFT */
    for (uint32_t y = 1; y < MAP_SIZE_Y - 1; y++)
    {
        background_t bg;
        bg.pos.x = 0;
        bg.pos.y = y;
        bg.sprite = _sprites["MAP_WATER_LEFT"];
        bg.sprite.setScale(SCALE_X(), SCALE_Y());
        bg.sprite.setPosition(0, y * TEXTURES_SIZE * SCALE_Y());
        _background.push_back(bg);
    }
    /* Border Water Background RIGHT */
    for (uint32_t y = 1; y < MAP_SIZE_Y - 1; y++)
    {
        background_t bg;
        bg.pos.x = MAP_SIZE_X - 1;
        bg.pos.y = y;
        bg.sprite = _sprites["MAP_WATER_RIGHT"];
        bg.sprite.setScale(SCALE_X(), SCALE_Y());
        bg.sprite.setPosition((MAP_SIZE_X - 1) * TEXTURES_SIZE * SCALE_X(), y * TEXTURES_SIZE * SCALE_Y());
        _background.push_back(bg);
    }

    /* Border Water Background TOP LEFT */
    background_t bg;
    bg.pos.x = 0;
    bg.pos.y = 0;
    bg.sprite = _sprites["MAP_WATER_TOP_LEFT"];
    bg.sprite.setScale(SCALE_X(), SCALE_Y());
    bg.sprite.setPosition(0, 0);
    _background.push_back(bg);

    /* Border Water Background TOP RIGHT */
    bg.pos.x = MAP_SIZE_X - 1;
    bg.pos.y = 0;
    bg.sprite = _sprites["MAP_WATER_TOP_RIGHT"];
    bg.sprite.setScale(SCALE_X(), SCALE_Y());
    bg.sprite.setPosition((MAP_SIZE_X - 1) * TEXTURES_SIZE * SCALE_X(), 0);
    _background.push_back(bg);

    /* Border Water Background BOTTOM LEFT */
    bg.pos.x = 0;
    bg.pos.y = MAP_SIZE_Y - 1;
    bg.sprite = _sprites["MAP_WATER_BOTTOM_LEFT"];
    bg.sprite.setScale(SCALE_X(), SCALE_Y());
    bg.sprite.setPosition(0, (MAP_SIZE_Y - 1) * TEXTURES_SIZE * SCALE_Y());
    _background.push_back(bg);

    /* Border Water Background BOTTOM RIGHT */
    bg.pos.x = MAP_SIZE_X - 1;
    bg.pos.y = MAP_SIZE_Y - 1;
    bg.sprite = _sprites["MAP_WATER_BOTTOM_RIGHT"];
    bg.sprite.setScale(SCALE_X(), SCALE_Y());
    bg.sprite.setPosition((MAP_SIZE_X - 1) * TEXTURES_SIZE * SCALE_X(), (MAP_SIZE_Y - 1) * TEXTURES_SIZE * SCALE_Y());
    _background.push_back(bg);

    // Fill water background non drawed

    if (MAP_SIZE_X != MAP_SIZE_Y)
    {
        if (MAP_SIZE_X > MAP_SIZE_Y)
        {
            for (uint32_t y = MAP_SIZE_Y; y < WINDOW_HEIGHT / TEXTURES_SIZE; y++)
            {
                for (uint32_t x = 0; x < WINDOW_WIDTH / TEXTURES_SIZE; x++)
                {
                    background_t bg;
                    bg.pos.x = x;
                    bg.pos.y = y;
                    bg.sprite = _sprites["MAP_WATER"];
                    bg.sprite.setScale(SCALE_X(), SCALE_Y());
                    bg.sprite.setPosition(x * TEXTURES_SIZE * SCALE_X(), y * TEXTURES_SIZE * SCALE_Y());
                    _background.push_back(bg);
                }
            }
        }
        else
        {
            for (uint32_t x = MAP_SIZE_X; x < WINDOW_WIDTH / TEXTURES_SIZE; x++)
            {
                for (uint32_t y = 0; y < WINDOW_HEIGHT / TEXTURES_SIZE; y++)
                {
                    background_t bg;
                    bg.pos.x = x;
                    bg.pos.y = y;
                    bg.sprite = _sprites["MAP_WATER"];
                    bg.sprite.setScale(SCALE_X(), SCALE_Y());
                    bg.sprite.setPosition(x * TEXTURES_SIZE * SCALE_X(), y * TEXTURES_SIZE * SCALE_Y());
                    _background.push_back(bg);
                }
            }
        }
    }
}

void LibSFML::drawBackground(void)
{
    /* Draw Background */
    for (uint32_t i = 0; i < _background.size(); i++)
    {
        if (i >= _background.size())
            break;
        _window.draw(_background[i].sprite);
    }
}

void LibSFML::drawMap(game_t const &game)
{
    /* Draw Obstacles */
    for (uint32_t i = 0; i < game.obstacles.size(); i++)
    {
        _sprites["MAP_OBSTACLE"].setPosition(game.obstacles[i].second * TEXTURES_SIZE * SCALE_X(), game.obstacles[i].first * TEXTURES_SIZE * SCALE_Y());
        _sprites["MAP_OBSTACLE"].setPosition(_sprites["MAP_OBSTACLE"].getPosition().x + TEXTURES_SIZE, _sprites["MAP_OBSTACLE"].getPosition().y + TEXTURES_SIZE);
        _sprites["MAP_OBSTACLE"].setScale(SCALE_X(), SCALE_Y());
        _window.draw(_sprites["MAP_OBSTACLE"]);
    }

    /* Draw Apples */
    for (uint32_t i = 0; i < game.foods.size(); i++)
    {
        const std::string type = game.foods[i].type == NORMAL ? "APPLE" : game.foods[i].type == BONUS ? "APPLE_GOLD"
                                                                                                      : "APPLE_POISON";
        _sprites[type].setPosition(game.foods[i].x * TEXTURES_SIZE * SCALE_X(), game.foods[i].y * TEXTURES_SIZE * SCALE_Y());
        _sprites[type].setPosition(_sprites[type].getPosition().x + TEXTURES_SIZE, _sprites[type].getPosition().y + TEXTURES_SIZE);
        _sprites[type].setScale(SCALE_X(), SCALE_Y());
        _window.draw(_sprites[type]);
    }
}

snake_part_t LibSFML::snakeAssignPart(game_t const &game, uint32_t index)
{
    std::vector<std::pair<int, int>> snake = game.snake;
    snake_part_t part;

    /* Assign Current Part */
    part.x = snake[index].second;
    part.y = snake[index].first;

    /* Assign Previous Part */
    if (index > 0)
    {
        part.previous_x = snake[index - 1].second;
        part.previous_y = snake[index - 1].first;
    }
    else
    {
        part.previous_x = -1;
        part.previous_y = -1;
    }

    /* Assign Next Part */
    if (index < snake.size() - 1)
    {
        part.next_x = snake[index + 1].second;
        part.next_y = snake[index + 1].first;
    }
    else
    {
        part.next_x = -1;
        part.next_y = -1;
    }

    /* Assign Head */
    if (index == 0)
        part.isHead = true;
    else
        part.isHead = false;

    /* Assign Tail */
    if (index == snake.size() - 1)
        part.isTail = true;
    else
        part.isTail = false;

    /* Assign Body */
    if (!part.isHead && !part.isTail)
        part.isBody = true;
    else
        part.isBody = false;

    /* Assign Corner */
    if (part.isBody)
    {
        if ((part.x == part.previous_x && part.x != part.next_x) || (part.y == part.previous_y && part.y != part.next_y))
            part.isCorner = true;
        else
            part.isCorner = false;
    }

    /* Assign Direction */
    part.headDirection = game.snake_direction;

    return (part);
}

void LibSFML::snakeDrawPart(snake_part_t const &part)
{
    /* Draw Head */
    if (part.isHead)
    {
        std::string head = "SNAKE_HEAD_";
        if (part.headDirection == UP)
            head += "TOP";
        else if (part.headDirection == DOWN)
            head += "BOTTOM";
        else if (part.headDirection == LEFT)
            head += "LEFT";
        else if (part.headDirection == RIGHT)
            head += "RIGHT";
        _sprites[head].setPosition(part.x * TEXTURES_SIZE * SCALE_X(), part.y * TEXTURES_SIZE * SCALE_Y());
        _sprites[head].setPosition(_sprites[head].getPosition().x + TEXTURES_SIZE, _sprites[head].getPosition().y + TEXTURES_SIZE);
        _sprites[head].setScale(SCALE_X(), SCALE_Y());
        _window.draw(_sprites[head]);
    }
    /* Draw Tail */
    else if (part.isTail)
    {
        std::string tail = "SNAKE_TAIL_";
        if (part.previous_x == part.x && part.previous_y < part.y)
            tail += "TOP";
        else if (part.previous_x == part.x && part.previous_y > part.y)
            tail += "BOTTOM";
        else if (part.previous_x < part.x && part.previous_y == part.y)
            tail += "LEFT";
        else if (part.previous_x > part.x && part.previous_y == part.y)
            tail += "RIGHT";
        _sprites[tail].setPosition(part.x * TEXTURES_SIZE * SCALE_X(), part.y * TEXTURES_SIZE * SCALE_Y());
        _sprites[tail].setPosition(_sprites[tail].getPosition().x + TEXTURES_SIZE, _sprites[tail].getPosition().y + TEXTURES_SIZE);
        _sprites[tail].setScale(SCALE_X(), SCALE_Y());
        _window.draw(_sprites[tail]);
    }
    /* Draw Body */
    else if (part.isBody)
    {
        std::string body = "SNAKE_BODY_";
        if (part.previous_x == part.x && part.previous_y < part.y)
            body += "TOP";
        else if (part.previous_x == part.x && part.previous_y > part.y)
            body += "BOTTOM";
        else if (part.previous_x < part.x && part.previous_y == part.y)
            body += "LEFT";
        else if (part.previous_x > part.x && part.previous_y == part.y)
            body += "RIGHT";
        if (part.next_x == part.x && part.next_y < part.y)
            body += "_TOP";
        else if (part.next_x == part.x && part.next_y > part.y)
            body += "_BOTTOM";
        else if (part.next_x < part.x && part.next_y == part.y)
            body += "_LEFT";
        else if (part.next_x > part.x && part.next_y == part.y)
            body += "_RIGHT";
        _sprites[body].setPosition(part.x * TEXTURES_SIZE * SCALE_X(), part.y * TEXTURES_SIZE * SCALE_Y());
        _sprites[body].setPosition(_sprites[body].getPosition().x + TEXTURES_SIZE, _sprites[body].getPosition().y + TEXTURES_SIZE);
        _sprites[body].setScale(SCALE_X(), SCALE_Y());
        _window.draw(_sprites[body]);
    }
    /* Draw Corner */
    else if (part.isCorner)
    {
        std::string corner = "SNAKE_CORNER_";
        if (part.previous_x == part.x && part.previous_y < part.y)
            corner += "TOP";
        else if (part.previous_x == part.x && part.previous_y > part.y)
            corner += "BOTTOM";
        else if (part.previous_x < part.x && part.previous_y == part.y)
            corner += "LEFT";
        else if (part.previous_x > part.x && part.previous_y == part.y)
            corner += "RIGHT";
        if (part.next_x == part.x && part.next_y < part.y)
            corner += "_TOP";
        else if (part.next_x == part.x && part.next_y > part.y)
            corner += "_BOTTOM";
        else if (part.next_x < part.x && part.next_y == part.y)
            corner += "_LEFT";
        else if (part.next_x > part.x && part.next_y == part.y)
            corner += "_RIGHT";
        _sprites[corner].setPosition(part.x * TEXTURES_SIZE * SCALE_X(), part.y * TEXTURES_SIZE * SCALE_Y());
        _sprites[corner].setPosition(_sprites[corner].getPosition().x + TEXTURES_SIZE, _sprites[corner].getPosition().y + TEXTURES_SIZE);
        _sprites[corner].setScale(SCALE_X(), SCALE_Y());
        _window.draw(_sprites[corner]);
    }
}

bool LibSFML::AppleInFrontOfSnake(game_t const &game)
{
    auto const &part = game.snake[0];

    for (auto const &apple : game.foods)
    {
        if (game.snake_direction == UP)
        {
            if (part.second == apple.x && part.first - 1 == apple.y)
                return (true);
        }
        else if (game.snake_direction == DOWN)
        {
            if (part.second == apple.x && part.first + 1 == apple.y)
                return (true);
        }
        else if (game.snake_direction == LEFT)
        {
            if (part.second - 1 == apple.x && part.first == apple.y)
                return (true);
        }
        else if (game.snake_direction == RIGHT)
        {
            if (part.second + 1 == apple.x && part.first == apple.y)
                return (true);
        }
    }

    return (false);
}

void LibSFML::drawSnake(game_t const &game)
{
    std::vector<std::pair<int, int>> _snake = game.snake;
    snake_part_t part = snakeAssignPart(game, 0);

    /* Draw Snake */

    /* Start with Head */
    snakeDrawPart(part);

    /* Then Body */
    for (uint32_t i = 1; i < _snake.size() - 1; i++)
    {
        part = snakeAssignPart(game, i);
        snakeDrawPart(part);
    }

    /* Then Tail */
    part = snakeAssignPart(game, _snake.size() - 1);
    snakeDrawPart(part);

    part = snakeAssignPart(game, 0);
    /* Draw Tongue */
    if (AppleInFrontOfSnake(game) == true)
    {
        std::string tongue = "SNAKE_TONGUE_HEAD_";
        if (part.headDirection == UP)
            tongue += "TOP";
        else if (part.headDirection == DOWN)
            tongue += "BOTTOM";
        else if (part.headDirection == LEFT)
            tongue += "LEFT";
        else if (part.headDirection == RIGHT)
            tongue += "RIGHT";
        _sprites[tongue].setPosition(part.x * TEXTURES_SIZE * SCALE_X(), part.y * TEXTURES_SIZE * SCALE_Y());
        _sprites[tongue].setPosition(_sprites[tongue].getPosition().x + TEXTURES_SIZE, _sprites[tongue].getPosition().y + TEXTURES_SIZE);
        _sprites[tongue].setScale(SCALE_X(), SCALE_Y());
        _window.draw(_sprites[tongue]);

        std::string tongue2 = "SNAKE_TONGUE_";
        uint32_t x, y;
        if (part.headDirection == UP)
            tongue2 += "TOP";
        else if (part.headDirection == DOWN)
            tongue2 += "BOTTOM";
        else if (part.headDirection == LEFT)
            tongue2 += "LEFT";
        else if (part.headDirection == RIGHT)
            tongue2 += "RIGHT";
        {
            x = part.x;
            y = part.y;
            if (part.headDirection == UP)
                y--;
            else if (part.headDirection == DOWN)
                y++;
            else if (part.headDirection == LEFT)
                x--;
            else if (part.headDirection == RIGHT)
                x++;
        }
        _sprites[tongue2].setPosition(x * TEXTURES_SIZE * SCALE_X(), y * TEXTURES_SIZE * SCALE_Y());
        _sprites[tongue2].setPosition(_sprites[tongue2].getPosition().x + TEXTURES_SIZE, _sprites[tongue2].getPosition().y + TEXTURES_SIZE);
        _sprites[tongue2].setScale(SCALE_X(), SCALE_Y());
        _window.draw(_sprites[tongue2]);
    }
}

void LibSFML::displayScore(game_t const &game)
{
    std::string score = "Score: " + std::to_string(game.score);
    _score.setString(score);
    _window.draw(_score);
}

void LibSFML::libSleep(void)
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() < 2000 / _parameter.fps)
    {
        updateInput();
        end = std::chrono::system_clock::now();
    }
}

/*******************************************************************************
 *                               LIBSFML PUBLIC                                *
 ******************************************************************************/

void LibSFML::update(game_t const &game)
{
    _window.clear(sf::Color::Black);
    updateInput();
    drawBackground();
    drawMap(game);
    drawSnake(game);
    displayScore(game);
    _window.display();
    libSleep();
}

/*******************************************************************************
 *                              SFML ENTRYPOINTS                               *
 ******************************************************************************/

LibSFML *initGLib(lib_parameter_t const parameter)
{
    return (new LibSFML(parameter));
}

void deleteGLib(LibSFML *lib)
{
    delete (lib);
}