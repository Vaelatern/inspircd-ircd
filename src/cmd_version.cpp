/*   +------------------------------------+
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
#include "modules.h"
#include "dynamic.h"
#include "wildcard.h"
#include "message.h"
#include "commands.h"
#include "mode.h"
#include "xline.h"
#include "inspstring.h"
#include "dnsqueue.h"
#include "helperfuncs.h"
#include "hashcomp.h"
#include "socketengine.h"
#include "typedefs.h"
#include "command_parse.h"
#include "cmd_version.h"

extern ServerConfig* Config;
extern InspIRCd* ServerInstance;

void cmd_version::Handle (char **parameters, int pcnt, userrec *user)
{
	std::stringstream out(Config->data005);
	std::string token = "";
	std::string line5 = "";
	int token_counter = 0;

	WriteServ(user->fd,"351 %s :%s",user->nick,ServerInstance->GetVersionString().c_str());

	while (!out.eof())
	{
		out >> token;
		line5 = line5 + token + " ";
		token_counter++;

		if ((token_counter >= 13) || (out.eof() == true))
		{
			WriteServ(user->fd,"005 %s %s:are supported by this server",user->nick,line5.c_str());
			line5 = "";
			token_counter = 0;
		}
	}
}


