//
// Created by nickganter on 8/3/25.
//

#include "roll_game.h"

#include <format>
#include <dpp/cluster.h>

void roll_game::roll() const {
    // Example roll logic
    if (max < 0) {
        dpp::message msg(event.command.channel_id, "Why did you try to roll a negative?! Roll again");
        return;
    }
    const int rolled = rand() % max + 1;
    const std::string user_mention = event.command.get_issuing_user().get_mention();

    const std::string rolled_message = std::format("{} rolled: {} (1-{})", user_mention, rolled, max);
    const dpp::message msg(event.command.channel_id, rolled_message);
    bot.message_create(msg);
}
