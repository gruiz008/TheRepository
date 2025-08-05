//
// Created by nickganter on 8/3/25.
//

#ifndef ROLL_GAME_H
#define ROLL_GAME_H
#include <dpp/dispatcher.h>

class roll_game {
public:
    roll_game(
        const dpp::cluster& bot,
        const dpp::slashcommand_t& event): bot(bot), event(event) {
    }
    void showButton() const;
    ~roll_game() = default;
private:
    const dpp::cluster &bot;
    const dpp::slashcommand_t &event;
};


#endif //ROLL_GAME_H
