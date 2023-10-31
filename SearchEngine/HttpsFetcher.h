#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>

#include <curl/curl.h>

using namespace std;

class HttpsFetcher
{
public:
    HttpsFetcher();

    /**
     * Fetches the headers and content for the specified URL. The content is
     * placed as a list of all the lines fetched under the "Content" key.
     *
     * @param url the URL to fetch
     * @return a map with the headers and content
     * @throws IOException if unable to fetch headers and content
     */
    string fetchURL(CURL * curl, string url);

    /**
     * Uses a socket to open a connection to the web server associated
     * with the provided URL. Supports HTTP and HTTPS connections.
     *
     * @param url the URL to connect
     * @return a stream for writing to the URL
     * @throws UnknownHostException if the host is not known
     */
    CURL * openConnection(string url);

    /**
     * 
     * 
     * 
    */
    void closeConnection(CURL *curl);

    /**
     * Writes a simple HTTP GET request to the provided socket writer.
     *
     * @param url the URL to fetch via the socket connection
     */
    void printGetRequest(string url);

    /**
     * Gets the header fields from a reader associated with a socket connection.
     * Requires that the socket reader has not yet been used, otherwise this
     * method will return unpredictable results.
     *
     * @param header a string of header fetched from URL
     * @return a map of header fields to a list of header values
     * @throws IOException if unable to read from the socket
     */
    map<string, vector<string>> getHeaderFields(string header);

    /**
     * Gets the content from a socket. Whether this output includes headers
     * depends on how the socket connection has already been used.
     *
     * @param response the stream created from a socket connection
     * @return a string of lines read from the socket reader
     * @throws IOException if unable to read from the socket
     */
    string getContent(CURL * curl);
};
