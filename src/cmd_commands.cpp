/*       +------------------------------------+
 *       | Inspire Internet Relay Chat Daemon |
 *       +------------------------------------+
 *
 *  InspIRCd is copyright (C) 2002-2006 ChatSpike-Dev.
 *                       E-mail:
 *                <brain@chatspike.net>
 *                <Craig@chatspike.net>
 *
 * Written by Craig Edwards, Craig McLure, and others.
 * This program is free but copyrighted software; see
 *            the file COPYING for details.
 *
 * ---------------------------------------------------
 */

using namespace std;

#include "inspircd_config.h"
#include "inspircd.h"
#include "inspircd_io.h"
#include <time.h>
#include <string>
#include <ext/hash_map>
#include <map>
#include <sstream>
#include <vector>
#include <deque>
#include "users.h"
#include "ctables.h"
#include "globals.h"
#include "message.h"
#include "commands.h"
#include "inspstring.h"
#include "helperfuncs.h"
#include "hashcomp.h"
#include "typedefs.h"
#include "command_parse.h"
#include "cmd_commands.h"

extern ServerConfig* Config;
extern InspIRCd* ServerInstance;

void cmd_commands::Handle (char **parameters, int pcnt, userrec *user)
{
	for (nspace::hash_map<std::string,command_t*>::iterator i = ServerInstance->Parser->cmdlist.begin(); i != ServerInstance->Parser->cmdlist.end(); i++)
	{
		WriteServ(user->fd,"902 %s :%s %s %d",user->nick,i->second->command.c_str(),i->second->source.c_str(),i->second->min_params);
	}
	WriteServ(user->fd,"903 %s :End of COMMANDS list",user->nick);
}


