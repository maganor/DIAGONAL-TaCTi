#ifndef API_H_INCLUDED
#define API_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    printf("%d\n", (int)realsize);
    printf("%.*s", (int)realsize, (char* )contents);
    return realsize;
}

int test() {
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://fakestoreapi.com/products/1");

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "X-Secret: AJAJAJA");
        curl_easy_setopt(curl, CURLOPT_HEADER, headers);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "Error en la solicitud: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }
    return 0;
}

#endif // API_H_INCLUDED
