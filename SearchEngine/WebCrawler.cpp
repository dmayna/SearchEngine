#include "WebCrawler.h"
#include "IndexBuilder.h"
#include "InvertedIndex.h"

#include <iostream>
#include <regex>
#include <sstream>
#include <cstdlib>


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

static size_t header_callback(char* buffer, size_t size,
    size_t nitems, void* userdata)
{
    std::string *headers = (std::string*) userdata;
    headers->append(buffer, nitems * size);
    return nitems * size;
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
            string readBuffer;
            string headers;
            string website = urls->front();
            urls->pop();
            
            curl = https_fetcher->openConnection(website);
            headers = https_fetcher->fetchURL(curl, website);
            cout << "Headers:\n" << headers << "\n";
            

            

            map<string, vector<string>> header_fields = https_fetcher->getHeaderFields(headers);
            /*for(auto it_map = header_fields.begin(); it_map != header_fields.end(); it_map++) {
                cout << "\nHeader: " << it_map->first << "\n";
                for(auto it_vec = it_map->second.begin(); it_vec != it_map->second.end(); it_vec++) {
                    cout << *it_vec << "\n";
                }
            }*/
            if (html_fetcher->isHtml(header_fields)) {
                readBuffer = html_fetcher->fetch(curl, website);
                readBuffer = html_cleaner->stripCss(readBuffer);
                readBuffer = html_cleaner->stripHtml(readBuffer);
                readBuffer = html_cleaner->stripBlockElements(readBuffer);
                readBuffer = html_cleaner->stripEntities(readBuffer);
                readBuffer = html_cleaner->stripTags(readBuffer);
                readBuffer = html_cleaner->stripComments(readBuffer);
                remove_ws(readBuffer);
                cout << "\nSTRIPPED HTML: \n" << readBuffer << "\n"; 
            } else {
                cout << "NOT HTML\n";
            }

            cout << "Status code: " << html_fetcher->getStatusCode(header_fields) << "\n";

            if (html_fetcher->isRedirect(header_fields)) {
                cout << "Is redirect\n";
            } else {
                cout << "NOT redirect\n";
            }
            curl_easy_cleanup(curl);
        }
    }
}


