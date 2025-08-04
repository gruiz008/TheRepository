#include <dpp/dpp.h>

#include "roll_game.h"
#include "sdtstrhelper.h"
#include "stringconstants.h"
const std::string BOT_TOKEN = "test";
int main() {
    roll_game game;
    dpp::cluster bot(BOT_TOKEN);
    bot.intents = dpp::intents::i_message_content | dpp::intents::i_guild_members | dpp::intents::i_default_intents;
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
         std::string command_name = to_lower(event.command.get_command_name());
        if (to_lower(command_name) == "hol") {
            event.reply(pre_game_message);
            game = roll_game(bot, event, &event.command.("max"));
        }
        if (to_lower(command_name) == "roll") {

        }
    });

    return 0;
}