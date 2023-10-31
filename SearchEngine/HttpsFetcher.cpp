#include "HttpsFetcher.h"
#include <sstream>
#include <string>

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

HttpsFetcher::HttpsFetcher() {
    // Constructor implementation (if needed)
}

string HttpsFetcher::fetchURL(CURL *curl, string url) {
    CURLcode res;
    //CURL *curl = openConnection(url);
    string headers;
    string readBuffer;

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headers);

        

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        //cout << readBuffer << "\n";
        if(CURLE_OK == res) {
            char *ct;
            /* ask for the content-type */
            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
        
            if((CURLE_OK == res) && ct)
                printf("We received Content-Type: %s\n", ct);
        }
    }
    //curl_easy_cleanup(curl);
    return headers;
}

CURL * HttpsFetcher::openConnection(string url) {
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    }
    return curl;
}


void HttpsFetcher::printGetRequest(string url) {
    // Implement the method to write an HTTP GET request to the provided socket writer
    // Use the connection for writing the request
}

map<string, vector<string>> HttpsFetcher::getHeaderFields(string header) {
    // Implement the method to read and parse header fields from the response
    // Read lines from the response and parse headers into a map
    map<string, vector<string>> headers;
    stringstream ss(header);
    string to;
    while (getline(ss,to,'\n')) {
        size_t colonPos = to.find(':');
        if (colonPos != string::npos) {
            string key = to.substr(0, colonPos);
            string value = to.substr(colonPos + 2); // + 2 to skip : and space for value data
            //cout << "Key: " << key << " | Val: " << value << "\n";
            headers[key].push_back(value);
        } else {
            if (to.rfind("HTTP", 0) == 0) {
                size_t colonPos = to.find(' ');
                if (colonPos != string::npos) {
                    string key = "status code";
                    string value = to.substr(colonPos + 1);
                    //cout << "Key: " << key << " | Val: " << value << "\n";
                    headers[key].push_back(value);
                }
            }
            

        }
        
    }
    return headers;
}

string HttpsFetcher::getContent(CURL * curl) {
    CURLcode res;
    string readBuffer;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    //cout << readBuffer << "\n";
    if(CURLE_OK == res) {
        char *ct;
        /* ask for the content-type */
        res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
    
        if((CURLE_OK == res) && ct)
            printf("We received Content-Type: %s\n", ct);
    }
    return readBuffer;
}
