/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:32:48 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/12/06 18:09:41 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WRAPPER_HPP
#define _WRAPPER_HPP

#include <iostream>
#include <map>
#include <dlfcn.h>

#include "ILibs.hpp"
#include "IALibs.hpp"

#define LIB_NCURSES "./libs/libncurses.so"
#define LIB_SFML "./libs/libsfml.so"
#define LIB_OPENGL "./libs/libopengl.so"
#define LIB_AUDIO "./libs/libaudio.so"

typedef enum e_library
{
    NCURSES,
    SFML,
    OPENGL,
    LIBAUDIO
} library_t;

/*
** DLOPEN:
** RTLD_LAZY: The symbols in the library are not resolved until the code that references them is executed.
** RTLD_NOW: All symbols in the library are resolved when the library is loaded.
** RTLD_GLOBAL: The symbols defined by this library will be made available for symbol resolution of subsequently loaded libraries.
** RTLD_LOCAL: The symbols defined by this library will not be made available for symbol resolution of subsequently loaded libraries.
** RTLD_NODELETE: The library will not be unloaded when dlclose() is called.
** RTLD_NOLOAD: The library will not be loaded if it is not already loaded.
** RTLD_DEEPBIND: The library will be searched for symbols before any previously loaded library.
*/

typedef ILibs *(*init_t)(lib_parameter_t);
typedef void (*delete_t)(ILibs *);

typedef IALibs *(*init_al_t)(void);
typedef void (*delete_al_t)(IALibs *);

#define LIBRARY_LOADER "initGLib"
#define LIBRARY_UNLOADER "deleteGLib"

#define LIBRARY_LOADER_AUDIO "createLib"
#define LIBRARY_UNLOADER_AUDIO "destroyLib"

class Wrapper
{
private:
    void *_libraryHandler;      // Library Handler
    void *_libraryAudioHandler; // Library Audio Handler

    init_t _init;     // Init library
    delete_t _delete; // Delete library

    init_al_t _init_al;     // Init Audio library
    delete_al_t _delete_al; // Delete Audio library

    ILibs *_library;       // Interface between libraries
    IALibs *_libraryAudio; // Interface between Audio library

    void libraryError(void);
    void *loadSymbol(void *handler, std::string const symbol);

    std::map<library_t, std::string> _libraries;

public:
    Wrapper(void);
    Wrapper(Wrapper const &cpy);
    virtual ~Wrapper(void);
    Wrapper &operator=(Wrapper const &cpy);

    /* Library Functions */
    void loadLibrary(std::string lib, lib_parameter_t const &lib_parameter);
    void unloadLibrary(ILibs *lib);

    /* Interface Functions */
    ILibs *switchInterface(ILibs *interface, std::string lib, lib_parameter_t const &lib_parameter);
    ILibs *getInterface(void) const;

    /* Library Path functions */
    std::string getLibraryPath(library_t lib) const;

    /* Audio functions */
    void loadAudioLibrary(std::string lib);
    void unloadAudioLibrary(IALibs *lib);
    IALibs *getAudioInterface(void) const;

    class DlErrorWrapper : public std::exception
    {
    public:
        DlErrorWrapper() throw();
        DlErrorWrapper(const DlErrorWrapper &copy) throw();
        DlErrorWrapper &operator=(const DlErrorWrapper &copy) throw();
        virtual ~DlErrorWrapper() throw();
        virtual const char *what() const throw();
    };
};


#endif /* _WRAPPER_HPP */