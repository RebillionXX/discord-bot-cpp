#include <discord_bot/discord.h>
#include <dpp/dpp.h>
#include <fmt/core.h>
#include <utils/quick_hash.h>
#include <string>

namespace discord
{
    discord_bot::discord_bot(const bot_settings& settings) : m_settings(settings) {
        fmt::print("discord-bot-cpp V0.0.1 starting...\n");
    }
    discord_bot::~discord_bot() {
        delete m_bot;
    }
    void discord_bot::init() {
        uint32_t intents = 
            dpp::intents::i_default_intents | 
            dpp::intents::i_message_content | 
            dpp::intents::i_guild_presences;
        m_bot = new dpp::cluster(m_settings.m_token, intents);

        m_bot->on_interaction_create([this](const dpp::interaction_create_t& event) { this->on_interaction_create(event); });
        m_bot->on_message_create([this](const dpp::message_create_t& event) { this->on_message_create(event); });
        m_bot->on_ready([&](const dpp::ready_t& event) {
            if (dpp::run_once<struct register_bot_commands>()) {
                this->register_commands();
                fmt::print("[discord-bot]: {} is now online.\n", m_bot->me.format_username());
            }
        });
        std::thread([&] {
            this->m_bot->start(false);
        }).detach();
    }
    void discord_bot::register_commands() {
        m_bot->guild_command_create(dpp::slashcommand{ 
            "ping", "ping pong!", m_bot->me.id }.
            add_permission(dpp::command_permission(947758500912701440, dpp::command_permission_type::cpt_user, true)),
        m_settings.m_guild_id);
    }

    void discord_bot::on_message_create(const dpp::message_create_t& event) {
        if (event.msg.content.starts_with("!help"))
            event.reply("no helps for you.");
    }
    void discord_bot::on_interaction_create(const dpp::interaction_create_t& event) {
        using namespace utils;
        uint64_t hash = quick_hash(event.command.get_command_name());
        switch (hash) {
        case "ping"_qh: {
            event.reply("pong!");
        } break;
        default:
            break;
        }
    }
}