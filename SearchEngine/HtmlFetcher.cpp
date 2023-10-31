#include "HtmlFetcher.h" // Include your header file here
#include <iostream>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

HtmlFetcher::HtmlFetcher() {
    // Constructor implementation (if needed)
}

bool HtmlFetcher::isHtml(map<string, vector<string>> headers) {
    // Check if "Content-Type" header is present and the first value starts with "text/html"
    auto it = headers.find("content-type");
    if (it != headers.end() && !it->second.empty()) {
        string contentType = it->second[0];
        // Convert to lowercase for case-insensitive comparison
        transform(contentType.begin(), contentType.end(), contentType.begin(), ::tolower);
        if (contentType.find("text/html") == 0) {
            return true;
        }
    }
    return false;
}

int HtmlFetcher::getStatusCode(map<string, vector<string>> headers) {
    // Parse the HTTP status code from the status line
    auto it = headers.find("status code");
    if (it != headers.end() && !it->second.empty()) {
        string statusLine = it->second[0];
        int statusCode = stoi(statusLine);
        //if (sscanf(statusLine.c_str(), "HTTP/1.%*s %d", &statusCode) == 1) {
        return statusCode;
        //}
    }
    return -1;
}

bool HtmlFetcher::isRedirect(map<string, vector<string>> headers) {
    // Check if status code is a valid redirect (300-399) and "Location" header exists
    int statusCode = getStatusCode(headers);
    if (statusCode >= 300 && statusCode <= 399) {
        return true;
    }
    return false;
}

string HtmlFetcher::fetch(CURL *curl, string url, int redirects) {
    // TODO handle redirects
    CURLcode res;
    string readBuffer;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
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
    }
    return readBuffer;
}

string HtmlFetcher::fetch(CURL *curl, string url) {
    // Call the fetch method with 0 redirects
    return fetch(curl, url, 0);
}
