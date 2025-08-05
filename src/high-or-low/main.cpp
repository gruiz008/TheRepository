#include <random>
#include <dpp/dpp.h>
#include "roll_game.h"
#include "sdtstrhelper.h"
#include "stringconstants.h"
const std::string BOT_TOKEN = "test";

bool is_valid_roll(const dpp::command_value &num_roll) {
    if (const int* num = std::get_if<int>(&num_roll)) {
        if (*num > 0) {
            return true;
        }
        return false;
    }
    return false;
}

int random_between(const int min, const int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    return dis(gen);
}

int main() {
    roll_game* game = nullptr;
    dpp::cluster bot(BOT_TOKEN);
    bot.intents = dpp::intents::i_message_content | dpp::intents::i_guild_members | dpp::intents::i_default_intents;
    bot.on_slashcommand([&bot, &game](const dpp::slashcommand_t& event) {
         const std::string command_name = to_lower(event.command.get_command_name());
        if (to_lower(command_name) == "hol") {
            event.reply(pre_game_message);

            game = new roll_game(bot, event);
        }
        if (to_lower(command_name) == "roll") {
            const dpp::command_value num_roll = event.get_parameter("num_roll");
            if (is_valid_roll(num_roll)) {
                const int* num = std::get_if<int>(&num_roll);
                int rolled_number = random_between(1, *num);
                const dpp::message msg(event.command.channel_id, std::format("{} rolled: {} (1-{})", event.command.get_issuing_user().get_mention(), rolled_number, *num));
                bot.message_create(msg);
            } else {
                event.reply("Roll a valid number greater than 0 ya goof.");
            }
        }
    });

    return 0;
}
