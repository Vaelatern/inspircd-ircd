/*
 * InspIRCd -- Internet Relay Chat Daemon
 *
 *   Copyright (C) 2009-2010 Daniel De Graaf <danieldg@inspircd.org>
 *   Copyright (C) 2007 Robin Burchell <robin+git@viroteck.net>
 *
 * This file is part of InspIRCd.  InspIRCd is free software: you can
 * redistribute it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "inspircd.h"
#include "core_info.h"

CommandAdmin::CommandAdmin(Module* parent)
	: Command(parent, "ADMIN", 0, 0)
{
	Penalty = 2;
	syntax = "[<servername>]";
}

/** Handle /ADMIN
 */
CmdResult CommandAdmin::Handle (const std::vector<std::string>& parameters, User *user)
{
	if (parameters.size() > 0 && parameters[0] != ServerInstance->Config->ServerName)
		return CMD_SUCCESS;
	user->SendText(":%s %03d %s :Administrative info for %s", ServerInstance->Config->ServerName.c_str(),
		RPL_ADMINME, user->nick.c_str(),ServerInstance->Config->ServerName.c_str());
	if (!AdminName.empty())
		user->SendText(":%s %03d %s :Name     - %s", ServerInstance->Config->ServerName.c_str(),
			RPL_ADMINLOC1, user->nick.c_str(), AdminName.c_str());
	user->SendText(":%s %03d %s :Nickname - %s", ServerInstance->Config->ServerName.c_str(),
		RPL_ADMINLOC2, user->nick.c_str(), AdminNick.c_str());
	user->SendText(":%s %03d %s :E-Mail   - %s", ServerInstance->Config->ServerName.c_str(),
		RPL_ADMINEMAIL, user->nick.c_str(), AdminEmail.c_str());
	return CMD_SUCCESS;
}

RouteDescriptor CommandAdmin::GetRouting(User* user, const std::vector<std::string>& parameters)
{
	if (parameters.size() > 0)
		return ROUTE_UNICAST(parameters[0]);
	return ROUTE_LOCALONLY;
}
