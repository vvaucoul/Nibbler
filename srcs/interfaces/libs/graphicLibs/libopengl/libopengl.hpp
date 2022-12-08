/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libopengl.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 01:45:53 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/12/06 17:32:05 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBOPENGL_HPP
#define LIBOPENGL_HPP

// #include <GL/glew.h>
// #include <GL/glut.h>
 
#include <GLFW/glfw3.h>
#include "../../../ILibs.hpp"

class LibOpenGL : public ILibs
{
private:
    lib_parameter_t _parameter;

    uint32_t _width;
    uint32_t _height;
    uint32_t _speed;

    GLFWwindow *_window;

    void initInputs(void);
    void DrawSquare(uint32_t x, uint32_t y, uint32_t size_x, uint32_t size_y, uint32_t color);
    uint32_t MapRangeClamped(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max);
    void libSleep(void);

public:
    LibOpenGL(lib_parameter_t const &parameter);
    LibOpenGL(LibOpenGL const &cpy);
    LibOpenGL &operator=(LibOpenGL const &cpy);
    virtual ~LibOpenGL(void);

    void update(game_t const &game);
};

/*******************************************************************************
 *                             OPENGL ENTRYPOINTS                              *
 ******************************************************************************/

extern "C"
{
    LibOpenGL *initGLib(lib_parameter_t const parameter);
    void deleteGLib(LibOpenGL *lib);
}

#endif /* LIBOPENGL_HPP */