// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <cstdint>
#include <filesystem>
#include <conio.h>
#include <vector>
#include <regex>
#include <map>
#include <future>
#include <string>
#include <stdarg.h>
#include <bitset>
#include <iomanip>
#include <algorithm>
#include <limits>

// TODO: reference additional headers your program requires here

typedef unsigned __int64 ulong;
typedef unsigned __int64 u64;
typedef signed __int64 s64;

typedef unsigned int uint;
typedef unsigned int u32;
typedef signed int s32;

typedef unsigned short ushort;
typedef unsigned short u16;
typedef signed short s16;

typedef unsigned char u8;
typedef signed char s8;

#include "CommonStructures.h"
#include "DownloadClient.h"
#include "TitleInfo.h"
#include "Tools.h"
#include "MapleTicket.h"

using namespace CommonTools;
using namespace CommonStructures;

//Third Party libraries
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/beast/core.hpp>
#include <boost/asio.hpp>
#include <boost/progress.hpp>
using namespace boost::filesystem;
namespace po = boost::program_options;

#include "ThirdParty\frozen.h"
#include "ThirdParty\rang.hpp"
#include "ThirdParty\cdecrypt.cpp"

using namespace std;

#include <windows.h>
#include <Wininet.h>
#pragma comment (lib, "Wininet.lib")