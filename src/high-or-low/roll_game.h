//
// Created by nickganter on 8/3/25.
//

#ifndef ROLL_GAME_H
#define ROLL_GAME_H
#include <dpp/dispatcher.h>

class roll_game {
public:
    roll_game(
        dpp::cluster& bot,
        dpp::slashcommand_t& event,
        const int* max): bot(bot), event(event), max(*max) {

    }
    void roll() const;
    ~roll_game() = default;
private:
    dpp::cluster &bot;
    dpp::slashcommand_t &event;
    int max = 100;
};


#endif //ROLL_GAME_H
