/*
Its is under the MIT license, to encourage reuse by cut-and-paste.

The original files are hosted here: https://github.com/sago007/PlatformFolders

Copyright (c) 2015-2016 Poul Sander

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "platform_folders.h"
#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>

#ifndef _WIN32

#include <pwd.h>
#include <unistd.h>

/**
 * Retrives the effective user's home dir.
 * If the user is running as root we ignore the HOME environment. It works badly with sudo.
 * Writing to $HOME as root implies security concerns that a multiplatform program cannot be assumed to handle.
 * @return The home directory. HOME environment is respected for non-root users if it exists.
 */
static std::string getHome()
{
	std::string res;
	int uid = getuid();
	const char *homeEnv = std::getenv("HOME");
	if (uid != 0 && homeEnv)
	{
		// We only acknowlegde HOME if not root.
		res = homeEnv;
		return res;
	}
	struct passwd *pw = nullptr;
	struct passwd pwd;
	long bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
	if (bufsize < 0)
	{
		bufsize = 16384;
	}
	std::vector<char> buffer;
	buffer.resize(bufsize);
	int error_code = getpwuid_r(uid, &pwd, buffer.data(), buffer.size(), &pw);
	if (error_code)
	{
		throw std::runtime_error("Unable to get passwd struct.");
	}
	const char *tempRes = pw->pw_dir;
	if (!tempRes)
	{
		throw std::runtime_error("User has no home directory");
	}
	res = tempRes;
	return res;
}

#endif

#ifdef _WIN32
// Make sure we don't bring in all the extra junk with windows.h
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
// stringapiset.h depends on this
#include <windows.h>
// For SUCCEEDED macro
#include <winerror.h>
// For WideCharToMultiByte
#include <stringapiset.h>
// For SHGetFolderPathW and various CSIDL "magic numbers"
#include <shlobj.h>

namespace sago
{
	namespace internal
	{

		std::string win32_utf16_to_utf8(const wchar_t *wstr)
		{
			std::string res;
			// If the 6th parameter is 0 then WideCharToMultiByte returns the number of bytes needed to store the result.
			int actualSize = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
			if (actualSize > 0)
			{
				// If the converted UTF-8 string could not be in the initial buffer. Allocate one that can hold it.
				std::vector<char> buffer(actualSize);
				actualSize = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &buffer[0], static_cast<int>(buffer.size()), nullptr, nullptr);
				res = buffer.data();
			}
			if (actualSize == 0)
			{
				// WideCharToMultiByte return 0 for errors.
				throw std::runtime_error("UTF16 to UTF8 failed with error code: " + std::to_string(GetLastError()));
			}
			return res;
		}

	} // namesapce internal
} // namespace sago

class FreeCoTaskMemory
{
	LPWSTR pointer = NULL;

public:
	explicit FreeCoTaskMemory(LPWSTR pointer) : pointer(pointer){};
	~FreeCoTaskMemory()
	{
		CoTaskMemFree(pointer);
	}
};

static std::string GetKnownWindowsFolder(REFKNOWNFOLDERID folderId, const char *errorMsg)
{
	LPWSTR wszPath = NULL;
	HRESULT hr;
	hr = SHGetKnownFolderPath(folderId, KF_FLAG_CREATE, NULL, &wszPath);
	FreeCoTaskMemory scopeBoundMemory(wszPath);

	if (!SUCCEEDED(hr))
	{
		throw std::runtime_error(errorMsg);
	}
	return sago::internal::win32_utf16_to_utf8(wszPath);
}

static std::string GetAppData()
{
	return GetKnownWindowsFolder(FOLDERID_RoamingAppData, "RoamingAppData could not be found");
}

static std::string GetAppDataCommon()
{
	return GetKnownWindowsFolder(FOLDERID_ProgramData, "ProgramData could not be found");
}

static std::string GetAppDataLocal()
{
	return GetKnownWindowsFolder(FOLDERID_LocalAppData, "LocalAppData could not be found");
}
#else
#include <map>
#include <fstream>
#include <sys/types.h>
// For strlen and strtok
#include <cstring>
#include <sstream>
// Typically Linux. For easy reading the comments will just say Linux but should work with most *nixes

static void throwOnRelative(const char *envName, const char *envValue)
{
	if (envValue[0] != '/')
	{
		char buffer[200];
		std::snprintf(buffer, sizeof(buffer), "Environment \"%s\" does not start with an '/'. XDG specifies that the value must be absolute. The current value is: \"%s\"", envName, envValue);
		throw std::runtime_error(buffer);
	}
}

static std::string getLinuxFolderDefault(const char *envName, const char *defaultRelativePath)
{
	std::string res;
	const char *tempRes = std::getenv(envName);
	if (tempRes)
	{
		throwOnRelative(envName, tempRes);
		res = tempRes;
		return res;
	}
	res = getHome() + "/" + defaultRelativePath;
	return res;
}

#endif

namespace sago
{

	std::string getDataHome()
	{
#ifdef _WIN32
		return GetAppData();
#elif defined(__APPLE__)
		return getHome() + "/Library/Application Support";
#else
		return getLinuxFolderDefault("XDG_DATA_HOME", ".local/share");
#endif
	}

} // namespace sago