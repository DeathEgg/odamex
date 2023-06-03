// Emacs style mode select   -*- C++ -*-
//-----------------------------------------------------------------------------
//
// Copyright (C) 2006-2021 by The Odamex Team.
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
//   Functions regarding reading and interpreting MAPINFO lumps.
//
//-----------------------------------------------------------------------------

#pragma once
#include "oscanner.h"

extern BOOL HexenHack; // Semi-Hexen-compatibility mode

struct ZMapInfoParser
{
	enum MapInfoFormat
	{
		MIF_UNKNOWN,
		MIF_HEXEN,
		MIF_ZDOOM,
	} formattype;

	ZMapInfoParser(int lump, const char* lumpname)
	    : os(constructOScanner(lump, lumpname))
	{
	}

	OScanner os;

	OScanner constructOScanner(int lump, const char* lumpname);

	void parseOpenBrace();
	bool parseCloseBrace();
	bool checkAssign();
	void parseAssign();

	void parseMapDefinition(level_pwad_info_t& info);
	void parseMapInfo(level_pwad_info_t& gamedefaults, level_pwad_info_t& defaultinfo);

	void parseAutomap(bool overlay);
};

void G_ParseMapInfo();
