#pragma once

#include <map>
#include <vector>
#include <algorithm>
#include <string>

#include <curl/curl.h>

using namespace std;

/**
 * A specialized version of {@link HttpsFetcher} that follows redirects and
 * returns HTML content if possible.
 *
 * @see HttpsFetcher
 * @author Dmayna
 */
class HtmlFetcher
{
private:
    
public:
    HtmlFetcher(/* args */);

    /**
	 * Returns {@code true} if and only if there is a "Content-Type" header and
	 * the first value of that header starts with the value "text/html"
	 * (case-insensitive).
	 *
	 * @param headers the HTTP/1.1 headers to parse
	 * @return {@code true} if the headers indicate the content type is HTML
	 */
    bool isHtml(map<string, vector<string>> headers);

    /**
	 * Parses the HTTP status code from the provided HTTP headers, assuming the
	 * status line is stored under the {@code null} key.
	 *
	 * @param headers the HTTP/1.1 headers to parse
	 * @return the HTTP status code or -1 if unable to parse for any reasons
	 */
    int getStatusCode(map<string, vector<string>> headers);

    /**
	 * Returns {@code true} if and only if the HTTP status code is between 300 and
	 * 399 (inclusive) and there is a "Location" header with at least one value.
	 *
	 * @param headers the HTTP/1.1 headers to parse
	 * @return {@code true} if the headers indicate the content type is HTML
	 */
    bool isRedirect(map<string, vector<string>> headers);

    /**
	 * Fetches the resource at the URL using HTTP/1.1 and sockets. If the status
	 * code is 200 and the content type is HTML, returns the HTML as a single
	 * string. If the status code is a valid redirect, will follow that redirect
	 * if the number of redirects is greater than 0. Otherwise, returns
	 * {@code null}.
	 *
	 * @param url the url to fetch
	 * @param redirects the number of times to follow redirects
	 * @return the html or {@code null} if unable to fetch the resource or the
	 *         resource is not html
	 *
	 * @see #fetch(URL, int)
	 */
    string fetch(CURL *curl, string url, int redirects);

    /**
	 * Calls {@link #fetch(string, int)} with 0 redirects.
	 *
	 * @param url the url to fetch
	 * @return the html or {@code null} if unable to fetch the resource or the
	 *         resource is not html
	 *
	 */
    string fetch(CURL *curl, string url);
};
