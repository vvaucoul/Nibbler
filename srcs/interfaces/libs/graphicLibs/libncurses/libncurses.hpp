/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libncurses.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:16:01 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/12/01 19:13:58 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBNCURSES_HPP
#define _LIBNCURSES_HPP

#include <curses.h>
// #include "../../../../tmp/ncurses-6.3/include/curses.h"
#include "../../../ILibs.hpp"
#include <iostream>

#define ERR_TERMINAL_SIZE "LibNcurses: Terminal size is too small"

class LibNcurses : public ILibs
{
private:
    lib_parameter_t _parameter;

    WINDOW *_window;

    input_t _input;

    LibNcurses(void);
    void initInputs(void);
    void libSleep(void);

public:
    LibNcurses(lib_parameter_t const parameter);
    LibNcurses(LibNcurses const &cpy);
    LibNcurses &operator=(LibNcurses const &cpy);
    virtual ~LibNcurses(void);

    input_t getInput(void);
    void update(game_t const &game);
    void setSpeed(uint32_t speed);
};

/*******************************************************************************
 *                             NCURSES ENTRYPOINTS                             *
 ******************************************************************************/

extern "C"
{
    LibNcurses *initGLib(lib_parameter_t const parameter);
    void deleteGLib(LibNcurses *lib);
}

#endif /* _LIBNCURSES_HPP */