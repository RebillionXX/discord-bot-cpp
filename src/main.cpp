#include <string>
#include <discord_bot/discord.h>

using namespace discord;
discord_bot* g_discord;

int main() {
    g_discord = new discord_bot({ "YOUR TOKEN", 0x0 /* <- your server id*/ });
	g_discord->init();
	while (true);
}