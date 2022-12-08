/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libopengl.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 10:10:01 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/12/06 17:32:02 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libopengl.hpp"
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <chrono>

std::map<uint32_t, input_t> _g_inputs;
void (*_g_handler)(const input_t &input);

LibOpenGL::LibOpenGL(lib_parameter_t const &parameter)
{
    _parameter = parameter;
    _g_handler = _parameter.inputHandler;

    initInputs();

    if (!glfwInit())
        exit(1);
    _window = glfwCreateWindow(960, 960, "Nibbler", NULL, NULL);
    if (!_window)
    {
        glfwTerminate();
        exit(1);
    }
    // center window
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(_window, (mode->width - 960) / 2, (mode->height - 960) / 2);

    glfwMakeContextCurrent(_window);
    glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSwapInterval(1);
    // if (glewInit() != GLEW_OK)
        // exit(1);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

LibOpenGL::LibOpenGL(LibOpenGL const &cpy)
{
    *this = cpy;
}

LibOpenGL::~LibOpenGL(void)
{
    glfwDestroyWindow(_window);
    glfwTerminate();
}

LibOpenGL &LibOpenGL::operator=(LibOpenGL const &cpy)
{
    if (this != &cpy)
    {
        _width = cpy._width;
        _height = cpy._height;
        _speed = cpy._speed;
    }
    return (*this);
}

void LibOpenGL::initInputs(void)
{
    ILibs::_inputs.insert(std::make_pair(0, input_t::NONE));
    ILibs::_inputs.insert(std::make_pair(GLFW_KEY_LEFT, input_t::LEFT));
    ILibs::_inputs.insert(std::make_pair(GLFW_KEY_RIGHT, input_t::RIGHT));
    ILibs::_inputs.insert(std::make_pair(GLFW_KEY_UP, input_t::UP));
    ILibs::_inputs.insert(std::make_pair(GLFW_KEY_DOWN, input_t::DOWN));
    ILibs::_inputs.insert(std::make_pair(GLFW_KEY_W, input_t::UP));
    ILibs::_inputs.insert(std::make_pair(GLFW_KEY_D, input_t::RIGHT));
    ILibs::_inputs.insert(std::make_pair(GLFW_KEY_S, input_t::DOWN));
    ILibs::_inputs.insert(std::make_pair(GLFW_KEY_A, input_t::LEFT));

    ILibs::_inputs.insert(std::make_pair(GLFW_KEY_U, input_t::LIB1));
    ILibs::_inputs.insert(std::make_pair(GLFW_KEY_I, input_t::LIB2));
    ILibs::_inputs.insert(std::make_pair(GLFW_KEY_O, input_t::LIB3));

    ILibs::_inputs.insert(std::make_pair(GLFW_KEY_ESCAPE, input_t::QUIT));

    _g_inputs = ILibs::_inputs;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
        _g_handler(input_t::QUIT);
    }
    else
        _g_handler(_g_inputs[key]);
}

void LibOpenGL::DrawSquare(uint32_t x, uint32_t y, uint32_t size_x, uint32_t size_y, uint32_t color)
{
    glBegin(GL_QUADS);
    glColor3ub((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
    glVertex2f(x, y);
    glVertex2f(x + size_x, y);
    glVertex2f(x + size_x, y + size_y);
    glVertex2f(x, y + size_y);
    glEnd();
}

uint32_t LibOpenGL::MapRangeClamped(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void LibOpenGL::libSleep(void)
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() < 2000 / _parameter.fps)
    {
        glfwPollEvents();
        end = std::chrono::system_clock::now();
    }
}

void LibOpenGL::update(game_t const &game)
{
    glfwSetKeyCallback(_window, key_callback);

    // Draw map with OpenGL
    int width, height;
    glfwGetFramebufferSize(_window, &width, &height);
    // float ratio = 800 / 600;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, height, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    static double _angle = 0;
    // if (_angle > 1.0f)
    // _angle = -1.0f;
    _angle += 1.0f;
    // glRotatef(50, 0.0f, 1.0f, 0.0f);

    uint32_t mx = _parameter.width;
    uint32_t my = _parameter.height;
    uint32_t sx = width / mx;
    uint32_t sy = height / my;

    /* Draw Obstacles */
    for (auto &obstacle : game.obstacles)
    {
        DrawSquare(obstacle.second * sx, obstacle.first * sy, sx, sy, 0x0000FF);
    }

    /* Draw Food */
    for (auto &food : game.foods)
    {
        DrawSquare(food.x * sx, food.y * sy, sx, sy, 0xFF0000);
    }

    /* Draw Snake */
    for (auto &snake : game.snake)
    {
        DrawSquare(snake.second * sx, snake.first * sy, sx, sy, 0x00FF00);
    }

    glfwSwapBuffers(_window);
    glfwPollEvents();
    libSleep();
}

/*******************************************************************************
 *                             OPENGL ENTRYPOINTS                               *
 ******************************************************************************/

LibOpenGL *initGLib(lib_parameter_t const parameter)
{
    return (new LibOpenGL(parameter));
}

void deleteGLib(LibOpenGL *lib)
{
    delete (lib);
}