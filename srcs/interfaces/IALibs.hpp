/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IALibs.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:31:30 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/12/02 14:33:51 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IALIBS_HPP
#define IALIBS_HPP

#include <string>

/*
** IALIBS = Interface Audio Libs
*/

#define AUDIO_GAME_MUSIC "assets/audio/GameMusic.wav"
#define AUDIO_GAME_SNAKE_MOVE "assets/audio/Snake_Move.wav"
#define AUDIO_GAME_SNAKE_DEATH "assets/audio/Snake_Death.wav"
#define AUDIO_GAME_SNAKE_GROW_UP "assets/audio/Snake_GrowUp.wav"

# define AUDIO_EAT_NORMAL_FOOD "assets/audio/eat_normal_food.wav"
# define AUDIO_EAT_BONUS_FOOD "assets/audio/eat_bonus_food.wav"
# define AUDIO_EAT_MALUS_FOOD "assets/audio/eat_malus_food.wav"
# define AUDIO_NORMAL_FOOD_SPAWN "assets/audio/normal_food_spawn.wav"
# define AUDIO_BONUS_FOOD_SPAWN "assets/audio/bonus_food_spawn.wav"
# define AUDIO_MALUS_FOOD_SPAWN "assets/audio/malus_food_spawn.wav"
# define AUDIO_OBSTACLE_SPAWN "assets/audio/obstacle_spawn.wav"

class IALibs
{
public:
    virtual ~IALibs() = default;
    virtual void playSound(std::string const &path) = 0;
    virtual void playMusic(std::string const &path) = 0;
    virtual void stopMusic() = 0;
};

#endif /* !IALIBS_HPP */