#define DPP_CORO 1
#include <random>
#include <dpp/dpp.h>
#include "roll_game.h"
#include "sdtstrhelper.h"
#include "stringconstants.h"
const std::string BOT_TOKEN = "";

bool is_valid_roll(const dpp::command_value &num_roll) {
    if (const int64_t *num = std::get_if<int64_t>(&num_roll)) {
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

int main(int argc, char **argv) {
    std::string bot_token = BOT_TOKEN;
    const bool coro_support = dpp::utility::is_coro_enabled();
    if (!coro_support) {
        std::cerr << "D++ coroutine support is not enabled. Please enable it to run this bot." << std::endl;
        return 1;
    }
    if (argc > 1) {
        bot_token = argv[1];
    }

    roll_game *game = nullptr;
    dpp::cluster bot(bot_token);
    bot.on_log(dpp::utility::cout_logger());
    bot.intents = dpp::intents::i_guilds;
    bot.on_ready([&bot](const dpp::ready_t &event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            std::cout << "Bot is online as " << bot.me.username << std::endl;
            bot.global_command_create(dpp::slashcommand("HoL", "Start a High or Low game", bot.me.id));
            bot.global_command_create(dpp::slashcommand("roll", "Roll a number against a range", bot.me.id)
                .add_option(dpp::command_option(dpp::co_integer, "num_roll", "The number to roll against", false)));
        }
    });
    bot.on_slashcommand([&bot, &game](const dpp::slashcommand_t &event) {
        const std::string command_name = to_lower(event.command.get_command_name());
        if (to_lower(command_name) == "hol") {
            event.reply(pre_game_message);
            game = new roll_game(bot, event);
        }
        if (to_lower(command_name) == "roll") {
            const dpp::command_value num_roll = event.get_parameter("num_roll");
            if (is_valid_roll(num_roll)) {
                const int64_t *num = std::get_if<int64_t>(&num_roll);
                const int value = static_cast<int>(*num);
                const int rolled_number = random_between(1, value);
                const std::string mention = event.command.member.get_mention();
                const std::string rolled_message =
                        mention + " rolled: " + std::to_string(rolled_number) + " (1-" + std::to_string(value) + ")";

                const dpp::message msg(event.command.channel_id, rolled_message);
                bot.message_create(msg);
            } else {
                event.reply("Roll a valid number greater than 0 ya goof.");
            }
        }
    });
    bot.on_button_click([&bot](const dpp::button_click_t &event) -> dpp::task<> {
        std::string mention = event.command.member.get_mention();
        std::string content = event.custom_id == "highRoll" ? "High" : "Low";
        dpp::message message(event.command.channel_id, mention + " selected High.");
        bot.message_create(message);
        co_return;
    });


    bot.start(dpp::st_wait);
}
