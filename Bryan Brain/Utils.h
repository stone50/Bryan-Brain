#pragma once

#include <cstdlib>
#include <windows.h>
#include <stringapiset.h>
#include <shlobj.h>
#include <string>
#include <vector>
#include <stdexcept>
#include <filesystem>

namespace Bryan {
	namespace Utils {
		constexpr float RAND_FACTOR = 2.0f / RAND_MAX;

        // returns a random float between -1 and 1
        inline float random() {
            return (rand() * RAND_FACTOR) - 1;
        }

        const std::filesystem::path DATA_PATH = ([]() -> std::filesystem::path {
            LPWSTR wszPath;
            HRESULT hr;
            hr = SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_CREATE, NULL, &wszPath);

            if ((HRESULT)hr < 0)
            {
                throw std::runtime_error("RoamingAppData could not be found");
            }

            std::string res;
            // If the 6th parameter is 0 then WideCharToMultiByte returns the number of bytes needed to store the result.
            int actualSize = WideCharToMultiByte(CP_UTF8, 0, wszPath, -1, nullptr, 0, nullptr, nullptr);
            if (actualSize > 0)
            {
                // If the converted UTF-8 string could not be in the initial buffer. Allocate one that can hold it.
                std::vector<char> buffer(actualSize);
                actualSize = WideCharToMultiByte(CP_UTF8, 0, wszPath, -1, &buffer[0], static_cast<int>(buffer.size()), nullptr, nullptr);
                res = buffer.data();
            }
            if (actualSize == 0)
            {
                // WideCharToMultiByte return 0 for errors.
                throw std::runtime_error("UTF16 to UTF8 failed with error code: " + std::to_string(GetLastError()));
            }

            CoTaskMemFree(wszPath);
            return res;
        })();
    };
}