/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libaudio.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:26:11 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/12/03 17:40:47 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libaudio.hpp"

LibAudio::LibAudio(void)
{
    _result = ma_engine_init(NULL, &_engine);
    if (_result != MA_SUCCESS)
    {
        std::cout << "Failed to initialize the engine." << std::endl;
        return;
    }
}

LibAudio::~LibAudio(void)
{
    close();
}

void LibAudio::close()
{
    ma_engine_uninit(&_engine);
}

LibAudio::LibAudio(LibAudio const &cpy)
{
    *this = cpy;
}

LibAudio &LibAudio::operator=(LibAudio const &cpy)
{
    if (this != &cpy)
    {
        _result = cpy._result;
        _engine = cpy._engine;
    }
    return *this;
}

void LibAudio::playSound(std::string const &path)
{
    ma_engine_play_sound(&_engine, path.c_str(), NULL);
}

void LibAudio::playMusic(std::string const &path)
{
    ma_engine_play_sound(&_engine, path.c_str(), NULL);
}

void LibAudio::stopMusic(void)
{
    ma_engine_stop(&_engine);
}

LibAudio *createLib(void)
{
    return (new LibAudio());
}

void destroyLib(LibAudio *lib)
{
    delete (lib);
}
