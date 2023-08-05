#include "WebCrawler.h"
#include <iostream>
#include <cstdlib>
#include <curl/curl.h>

using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

WebCrawler::WebCrawler() {
    urls = new queue<string>;
    depth = 5;
}

WebCrawler::WebCrawler(int inDepth) {
    urls = new queue<string>;
    depth = inDepth;
}

void WebCrawler::crawl() {
    if (urls->empty())
    {
        cout << "Enter url to crawl";
    } else {
        while (!urls->empty()) {
            CURL *curl;
            CURLcode res;
            string readBuffer;

            curl = curl_easy_init();
            if(curl) {
                string website = urls->front();
                urls->pop();
                curl_easy_setopt(curl, CURLOPT_URL, website.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
                res = curl_easy_perform(curl);
                while (readBuffer.find("<") != std::string::npos) {
                    auto startpos = readBuffer.find("<");
                    auto endpos = readBuffer.find(">") + 1;

                    if (endpos != std::string::npos)
                    {
                        readBuffer.erase(startpos, endpos - startpos);
                    }
                }
                cout << "\n\nreadBuffer = \n" << readBuffer << "\n";
                /* always cleanup */ 
                curl_easy_cleanup(curl);
            }
        }
        
    }
}


