#include "network_tools.h"
#include "Output.h"

namespace Network
{
    size_t writeData(void* ptr, size_t size, size_t nmemb, void* stream) 
    {
        size_t written = fwrite(ptr, size, nmemb, static_cast<FILE*>(stream));
        return written;
    }

    bool downloadFile(const std::string & url, const std::string & targetFile) 
    {
        bool retval = false;
    
        // download the file using curl library into DownloadCURL folder
        if(CURL* curl = curl_easy_init()) 
        {
            if(FILE* fp = fopen(targetFile.c_str(), "wb")) 
            {
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); 
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // follow redirects
                // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
                curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, 1L); // corp. proxies etc.
                curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.121 Safari/537.36");
                curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30);
                curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60);
                curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 15);

                // perform the request, res will get the return code
                CURLcode res = curl_easy_perform(curl);

                if(!res) 
                    retval = true;
                else
                {
                    out.print(TraceLevel::CRITICAL, "Libcurl error number: {}", res);
                    exit(-1);
                }
            
                fclose(fp);
            }
            curl_easy_cleanup(curl);
        }

        return retval;
    } 
}