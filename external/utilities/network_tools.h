#ifndef NETWORK_TOOLS_H
#define NETWORK_TOOLS_H

#include <string>
#include <curl/curl.h>

namespace Network
{
    size_t writeData(void* ptr, size_t size, size_t nmemb, void* stream); 
    bool downloadFile(const std::string & url, const std::string & targetFile);
}

#endif