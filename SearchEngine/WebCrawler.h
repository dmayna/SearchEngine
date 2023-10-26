#pragma once

#include <iostream>
#include <queue>

using namespace std;

class WebCrawler {
    public:
        WebCrawler();
        WebCrawler(int inDepth);
        void crawl();
        void addUrl(string url);


    private:
        queue<string> * urls;
        int depth;
};

/*
Begin with a base URL that you select, and place it on the top of your queue

Pop the URL at the top of the queue and download it

Parse the downloaded HTML file and extract all links

Insert each extracted link into the queue

Goto step 2, or stop once you reach some specified limit
*/