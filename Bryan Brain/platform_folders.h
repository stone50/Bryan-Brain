/*
Its is under the MIT license, to encourage reuse by cut-and-paste.

The original files are hosted here: https://github.com/sago007/PlatformFolders

Copyright (c) 2015 Poul Sander

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

#ifndef SAGO_PLATFORM_FOLDERS_H
#define SAGO_PLATFORM_FOLDERS_H

#include <vector>
#include <string>

/**
 * The namespace I use for common function. Nothing special about it.
 */
namespace sago {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace internal {
#ifdef _WIN32
std::string win32_utf16_to_utf8(const wchar_t* wstr);
#endif
}
#endif  //DOXYGEN_SHOULD_SKIP_THIS

/**
 * Retrives the base folder for storing data files.
 * You must add the program name yourself like this:
 * @code{.cpp}
 * string data_home = getDataHome()+"/My Program Name/";
 * @endcode
 * On Windows this defaults to %APPDATA% (Roaming profile)
 * On Linux this defaults to ~/.local/share but can be configured by the user
 * @return The base folder for storing program data.
 */
std::string getDataHome();
}  //namespace sago

#endif  /* PLATFORM_FOLDERS_H */
