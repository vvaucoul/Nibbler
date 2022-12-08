/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libncurses.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:15:57 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/12/03 20:24:48 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libncurses.hpp"
#include <sys/ioctl.h>
#include <unistd.h>
#include <tuple>
#include <ctime>
#include <chrono>

LibNcurses::LibNcurses(lib_parameter_t const parameter)
{
    _parameter = parameter;

    initInputs();

    initscr();
    cbreak();
    noecho();

    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    curs_set(0);
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_BLACK);
}

LibNcurses::LibNcurses(LibNcurses const &cpy)
{
    *this = cpy;
}

LibNcurses &LibNcurses::operator=(LibNcurses const &cpy)
{
    if (this != &cpy)
    {
        _parameter = cpy._parameter;
    }
    return (*this);
}

LibNcurses::~LibNcurses(void)
{
    endwin();
}

void LibNcurses::initInputs(void)
{
    ILibs::_inputs.insert(std::make_pair(0, input_t::NONE));
    ILibs::_inputs.insert(std::make_pair(KEY_UP, input_t::UP));
    ILibs::_inputs.insert(std::make_pair(KEY_DOWN, input_t::DOWN));
    ILibs::_inputs.insert(std::make_pair(KEY_LEFT, input_t::LEFT));
    ILibs::_inputs.insert(std::make_pair(KEY_RIGHT, input_t::RIGHT));

    ILibs::_inputs.insert(std::make_pair('w', input_t::UP));
    ILibs::_inputs.insert(std::make_pair('s', input_t::DOWN));
    ILibs::_inputs.insert(std::make_pair('a', input_t::LEFT));
    ILibs::_inputs.insert(std::make_pair('d', input_t::RIGHT));

    ILibs::_inputs.insert(std::make_pair(27, input_t::QUIT));

    ILibs::_inputs.insert(std::make_pair('u', input_t::LIB1));
    ILibs::_inputs.insert(std::make_pair('i', input_t::LIB2));
    ILibs::_inputs.insert(std::make_pair('o', input_t::LIB3));
}

void LibNcurses::setSpeed(uint32_t speed)
{
    (void)speed;
}

input_t LibNcurses::getInput(void)
{
    return (_input);
}

static std::pair<uint32_t, uint32_t> getTerminalSize(void)
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return (std::make_pair(w.ws_col, w.ws_row));
}

static std::pair<uint32_t, uint32_t> centerText(std::string const &text)
{
    std::pair<uint32_t, uint32_t> size = getTerminalSize();

    if (text.size() > size.first)
        return (std::make_pair(0, 0));
    else if (text.size() == size.first)
        return (std::make_pair(0, size.second / 2));
    else
        return (std::make_pair((size.first / 2) - (text.size() / 2), size.second / 2));
}

static uint32_t centerSize(uint32_t value, uint32_t max_size)
{
    if (value > max_size)
        return (0);
    else if (value == max_size)
        return (0);
    else
        return ((max_size / 2) - (value / 2));
}

void LibNcurses::libSleep(void)
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() < 2000 / _parameter.fps)
    {
        int ch = getch();

        if (ch > 0)
        {
            if (ILibs::_inputs.find(ch) != ILibs::_inputs.end())
            {
                _input = ILibs::_inputs[ch];
                _parameter.inputHandler(ILibs::_inputs[ch]);
            }
        }

        end = std::chrono::system_clock::now();
    }
}

void LibNcurses::update(game_t const &game)
{
    uint32_t terminal_x = 0;
    uint32_t terminal_y = 0;

    int ch = getch();

    if (ch > 0)
    {
        if (ILibs::_inputs.find(ch) != ILibs::_inputs.end())
        {
            _input = ILibs::_inputs[ch];
            _parameter.inputHandler(ILibs::_inputs[ch]);
        }
    }
    werase(stdscr);

    wattron(stdscr, COLOR_PAIR(1));
    mvprintw(30, 0, "Score : %d", game.score);

    std::tie(terminal_x, terminal_y) = getTerminalSize();

    if (terminal_x < _parameter.width || terminal_y < _parameter.height + 2)
    {
        wattron(stdscr, COLOR_PAIR(2));
        mvprintw(centerText(ERR_TERMINAL_SIZE).second, centerText(ERR_TERMINAL_SIZE).first, ERR_TERMINAL_SIZE);
        return;
    }
    wattron(stdscr, COLOR_PAIR(2));
    mvprintw(0, centerText("Nibbler - Ncurses").first, "%s\n", "Nibbler - Ncurses");
    wattron(stdscr, COLOR_PAIR(1));

    uint32_t center_size_x = centerSize(_parameter.width, terminal_x);
    // uint32_t center_size_y = centerSize(_parameter.height, terminal_y - 2);

    /* Draw Obstacles */
    for (auto &obstacle : game.obstacles)
    {
        mvprintw(obstacle.first + 2, obstacle.second + center_size_x, "%s", "#");
    }

    /* Draw Snakes */
    uint32_t i = 0;
    for (auto &snake : game.snake)
    {
        if (i == 0)
            mvprintw(snake.first + 2, snake.second + center_size_x, "%s", "X");
        else if (i == game.snake.size() - 1)
            mvprintw(snake.first + 2, snake.second + center_size_x, "%s", ".");
        else
            mvprintw(snake.first + 2, snake.second + center_size_x, "%s", "x");
        i++;
    }

    /* Draw Foods */
    for (auto &food : game.foods)
    {
        mvprintw(food.y + 2, food.x + center_size_x, "%s", "o");
    }

    /* Draw Background X */
    for (uint32_t x = 0; x < _parameter.width + 1; x++)
    {
        mvprintw(1, x + center_size_x, "%s", "#");
        mvprintw(_parameter.height + 2, x + center_size_x, "%s", "#");
    }

    /* Draw Background Y */
    for (uint32_t y = 0; y < _parameter.height + 2; y++)
    {
        mvprintw(y + 1, center_size_x - 1, "%s", "#");
        mvprintw(y + 1, _parameter.width - 1 + center_size_x + 1, "%s", "#");
    }

    wrefresh(stdscr);
    libSleep();
}

/*******************************************************************************
 *                             NCURSES ENTRYPOINTS                             *
 ******************************************************************************/

LibNcurses *initGLib(lib_parameter_t const parameter)
{
    return (new LibNcurses(parameter));
}

void deleteGLib(LibNcurses *lib)
{
    delete (lib);
}