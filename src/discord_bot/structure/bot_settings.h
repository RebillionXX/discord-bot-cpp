#pragma once
#include <string>
#include <dpp/dpp.h>

namespace discord
{
	struct bot_settings {
		std::string m_token;
		dpp::snowflake m_guild_id;
	};
};