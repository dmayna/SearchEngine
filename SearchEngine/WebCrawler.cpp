#include "WebCrawler.h"
#include "IndexBuilder.h"
#include "InvertedIndex.h"

#include <iostream>
#include <regex>
#include <sstream>
#include <cstdlib>
#include <curl/curl.h>

using namespace std;

void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

void remove_ws(string &s) {
    for (size_t i = 0; i < s.length(); i++)
    {
        if (s[i] == '\n')
        {
            s.erase(i,1);
        }
    }
    
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void WebCrawler::addUrl(string url) {
    urls->push(url);
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
                //cout << readBuffer << "\n";
                remove_ws(readBuffer);
                vector<string>words = split(readBuffer,' ');

                regex regexp("<\\s*body[^>]*>([\\s\\S]*)<\\s*/\\s*body\\s*>"); 
                smatch m;
                regex_search(readBuffer, m, regexp);
                cout<<"String that matches the pattern:"<<endl;
                for (auto x : m) 
                    cout << x << " "; 
                //bool found_body = false;
                //for (string word : words) {
                     //cout << "[" << word << "]\n";
                //}
                /*while (readBuffer.find("<") != std::string::npos) {
                    auto startpos = words = split(temp,' ');.find("<");
                    auto endpos = readBuffer.find(">") + 1;

                    if (endpos != std::string::npos)
                    {
                        readBuffer.erase(startpos, endpos - startpos);
                    }
                }*/
                //cout << "\n\nreadBuffer = \n" << readBuffer << "\n";
                /* always cleanup */ 
                curl_easy_cleanup(curl);
            }
        }
    }
}


