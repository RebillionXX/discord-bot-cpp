#pragma once
#include <discord_bot/structure/bot_settings.h>
#include <dpp/dpp.h>

namespace discord
{
	class discord_bot {
	public:
		discord_bot(const bot_settings& settings);
		~discord_bot();

		[[nodiscard]] dpp::cluster* get() const { return m_bot; }
		void init();
		void register_commands();

		void on_message_create(const dpp::message_create_t& event);
		void on_interaction_create(const dpp::interaction_create_t& event);
	public:
		bot_settings m_settings;
		dpp::cluster* m_bot;

		bool m_ready = false;
	};
};