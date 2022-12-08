/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:34:12 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/12/06 18:13:12 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.hpp"

Wrapper::Wrapper(void)
{
    _libraryHandler = nullptr;
    _libraryAudioHandler = nullptr;

    _library = nullptr;
    _libraryAudio = nullptr;

    _libraries.insert(std::pair<library_t, std::string>(NCURSES, LIB_NCURSES));
    _libraries.insert(std::pair<library_t, std::string>(SFML, LIB_SFML));
    _libraries.insert(std::pair<library_t, std::string>(OPENGL, LIB_OPENGL));
    _libraries.insert(std::pair<library_t, std::string>(LIBAUDIO, LIB_AUDIO));
}

Wrapper::~Wrapper(void)
{
    if (_libraryHandler)
    {
        if ((dlclose(_libraryHandler)))
            libraryError();
        _libraryHandler = nullptr;
    }
    if (_libraryAudioHandler)
    {
        if ((dlclose(_libraryAudioHandler)))
            libraryError();
        _libraryAudioHandler = nullptr;
    }
}

Wrapper::Wrapper(Wrapper const &cpy)
{
    *this = cpy;
}

Wrapper &Wrapper::operator=(Wrapper const &cpy)
{
    if (this != &cpy)
    {
        *this = cpy;
    }
    return (*this);
}

void Wrapper::libraryError(void)
{
    throw DlErrorWrapper();
}

void *Wrapper::loadSymbol(void *handler, std::string const symbol)
{
    return (dlsym(handler, symbol.c_str()));
}

/*******************************************************************************
 *                                 EXCEPTIONS                                  *
 ******************************************************************************/

Wrapper::DlErrorWrapper::DlErrorWrapper() throw() {}
Wrapper::DlErrorWrapper::DlErrorWrapper(const DlErrorWrapper &copy) throw() { (void)copy; }
Wrapper::DlErrorWrapper::~DlErrorWrapper() throw() {}
Wrapper::DlErrorWrapper &Wrapper::DlErrorWrapper::operator=(const DlErrorWrapper &copy) throw()
{
    (void)copy;
    return (*this);
}
const char *Wrapper::DlErrorWrapper::what() const throw() { return (dlerror()); }

/*******************************************************************************
 *                              WRAPPER FUNCTIONS                              *
 ******************************************************************************/

/**
 * @brief Load a Dynamic library
 *
 * @param lib
 * @param lib_parameter
 */
void Wrapper::loadLibrary(std::string lib, lib_parameter_t const &lib_parameter)
{
    _libraryHandler = dlopen(lib.c_str(), RTLD_LAZY | RTLD_LOCAL);


    if (_libraryHandler == nullptr)
        libraryError();
    else
    {
        _init = reinterpret_cast<init_t>(loadSymbol(_libraryHandler, LIBRARY_LOADER));
        _delete = reinterpret_cast<delete_t>(loadSymbol(_libraryHandler, LIBRARY_UNLOADER));

        if (!_init || !_delete)
            libraryError();
        else
        {
            Wrapper::_library = _init(lib_parameter);
        }
    }
}
#include <unistd.h>
#include <stdio.h>
/**
 * @brief Unload Dynamic Library
 *
 * @param lib
 */
void Wrapper::unloadLibrary(ILibs *lib)
{
    if (_libraryHandler != nullptr)
    {
        if (lib != nullptr)
        {
            _delete(lib);
            lib = nullptr;
        }
        if ((dlclose(_libraryHandler)))
            libraryError();
        _libraryHandler = nullptr;
    }
}

/**
 * @brief Switch to another Interface (unload -> load)
 *
 * @param lib
 * @param lib_parameter
 * @return ILibs*
 */
ILibs *Wrapper::switchInterface(ILibs *interface, std::string lib, lib_parameter_t const &lib_parameter)
{
    unloadLibrary(interface);
    loadLibrary(lib, lib_parameter);
    return (_library);
}

/**
 * @brief Get the current Interface
 *
 * @return ILibs*
 */
ILibs *Wrapper::getInterface(void) const
{
    return (_library);
}

/**
 * @brief Get the Library Path object
 *
 * @param lib
 * @return std::string
 */
std::string Wrapper::getLibraryPath(library_t lib) const
{
    return (_libraries.at(lib));
}

/*******************************************************************************
 *                           WRAPPER FUNCTIONS AUDIO                           *
 ******************************************************************************/

void Wrapper::loadAudioLibrary(std::string lib)
{
    _libraryAudioHandler = dlopen(lib.c_str(), RTLD_LAZY | RTLD_LOCAL);
    if (!_libraryAudioHandler)
        libraryError();
    else
    {
        _init_al = reinterpret_cast<init_al_t>(loadSymbol(_libraryAudioHandler, LIBRARY_LOADER_AUDIO));
        _delete_al = reinterpret_cast<delete_al_t>(loadSymbol(_libraryAudioHandler, LIBRARY_UNLOADER_AUDIO));

        if (!_init_al || !_delete_al)
            libraryError();
        else
        {
            Wrapper::_libraryAudio = _init_al();
        }
    }
}

void Wrapper::unloadAudioLibrary(IALibs *lib)
{
    if (_libraryAudioHandler != nullptr)
    {
        if (lib != nullptr)
        {
            _delete_al(lib);
            lib = nullptr;
        }
        if ((dlclose(_libraryAudioHandler)))
            libraryError();
        _libraryAudioHandler = nullptr;
    }
}

IALibs *Wrapper::getAudioInterface(void) const
{
    return (_libraryAudio);
}