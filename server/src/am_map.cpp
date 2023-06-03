// Emacs style mode select   -*- C++ -*-
//-----------------------------------------------------------------------------
//
// $Id$
//
// Copyright (C) 1993-1996 by id Software, Inc.
// Copyright (C) 2006-2020 by The Odamex Team.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//  AutoMap module.
//
//-----------------------------------------------------------------------------

#include "odamex.h"
#include "am_map.h"
#include "g_mapinfo.h"

int am_cheating = 0;

bool automapactive = false;

static const char *ColorNames[] = {
		"Background",
		"YourColor",
		"WallColor",
		"TwoSidedWallColor",
		"FloorDiffWallColor",
		"CeilingDiffWallColor",
		"ExtraFloorWallColor",
		"ThingColor",
		"ThingColor_Item",
		"ThingColor_CountItem",
		"ThingColor_Monster",
		"ThingColor_NocountMonster",
		"ThingColor_Friend",
		"SpecialWallColor",
		"SecretWallColor",
		"GridColor",
		"XHairColor",
		"NotSeenColor",
		"LockedColor",
		"IntraTeleportColor",
		"InterTeleportColor",
		"SecretSectorColor",
		"UnexploredSecretColor",
		"PortalColor",
		"AlmostBackgroundColor",
		NULL
};

bool IsIdentifier(const OScanner& os)
{
	// [A-Za-z_]+[A-Za-z0-9_]*

	if (os.getToken().empty())
		return false;

	const std::string token = os.getToken();
	for (std::string::const_iterator it = token.begin(); it != token.end(); ++it)
	{
		const char& ch = *it;
		if (ch == '_')
			continue;

		if (ch >= 'A' && ch <= 'Z')
			continue;

		if (ch >= 'a' && ch <= 'z')
			continue;

		if (it != token.begin() && ch >= '0' && ch <= '9')
			continue;

		return false;
	}

	return true;
}

//
// Parse automap in server, but don't actually use the data.
//
void ZMapInfoParser::parseAutomap(bool overlay)
{
	bool colorset = false;

	os.mustScan();
	os.assertTokenIs("{");
	while (os.scan())
	{
		if (os.compareToken("}"))
			return;

		if (!IsIdentifier(os)) // todo: replace with OScanner function
		{
			os.error("Expected identifier (unexpected end of file).");
		}
		std::string key = os.getToken();
		os.mustScan();
		os.assertTokenIs("=");

		if (iequals(key, "base"))
		{
			if (colorset)
				os.error("'base' must be specified before the first color");

			os.mustScan();

			if (os.compareTokenNoCase("doom"))
				;
			else if (os.compareTokenNoCase("raven"))
				;
			else if (os.compareTokenNoCase("strife"))
				;
			else
				os.warning("'base' expected \"doom\", \"heretic\", or \"strife\"; got %s",
				           os.getToken().c_str());
		}
		else if (iequals(key, "showlocks"))
		{
			os.mustScanBool();
		}
		else
		{
			int i;
			for (i = 0; ColorNames[i] != NULL; ++i)
			{
				if (iequals(key, ColorNames[i]))
				{
					os.mustScan();
					colorset = true;
					break;
				}
			}

			if (ColorNames[i] == NULL)
			{
				os.error("Unknown automap color key '%s'", key.c_str());
			}
		}
	}
}

bool AM_ClassicAutomapVisible()
{
	return automapactive && !viewactive;
}

bool AM_OverlayAutomapVisible()
{
	return automapactive && viewactive;
}

void AM_SetBaseColorDoom()
{
	
}

void AM_SetBaseColorRaven()
{
	
}

void AM_SetBaseColorStrife()
{
	
}

void AM_Start()
{
	
}

BOOL AM_Responder(event_t* ev)
{
	return false;
}

void AM_Drawer()
{
	
}

VERSION_CONTROL(am_map_cpp, "$Id$")
