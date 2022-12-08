/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libaudio.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:25:46 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/12/03 17:39:57 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBAUDIO_HPP
#define LIBAUDIO_HPP

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>
// #include "../../../../tmp/miniaudio/miniaudio.h/miniaudio.h" // tmp
#include "../../IALibs.hpp"

#include <iostream>
#include <vector>

class LibAudio : public IALibs
{
    private:
        void close();

        ma_result _result;
        ma_engine _engine;

    public:
        LibAudio(void);
        virtual ~LibAudio(void);
        LibAudio(LibAudio const &cpy);
        LibAudio &operator=(LibAudio const &cpy);

        void playSound(std::string const &path);
        void playMusic(std::string const &path);
        void stopMusic();
};

extern "C"
{
    LibAudio *createLib(void);
    void destroyLib(LibAudio *lib);
}

#endif /* !LIBAUDIO_HPP */