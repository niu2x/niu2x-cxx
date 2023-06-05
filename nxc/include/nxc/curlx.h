// #ifndef NXC_CURLX_H
// #define NXC_CURLX_H

// #include <nxc/error.h>
// #include <nxc/result.h>
// #include <nxc/api.h>

// namespace nxc {

// using URL = String;
// using Host = String;
// using Ip = String;

// // Result<String> http_get(const URL& url);

// class NXC_API CurlX : private Noncopyable {
// public:
//     CurlX();
//     ~CurlX();

//     void set_proxy();

//     void set_url(const URL& url);
//     void set_headers(const Vector<String>& headers);
//     void set_resolve(const Host& host, const Ip& ip);

//     template <class T>
//     void set(CURLoption opt, T param)
//     {
//         curl_easy_setopt(curl_, opt, param);
//     }

//     // static Result<int> multi_poll(CURLM* session, int timeout);
//     // static void multi_read(CURLM* session);

//     Result<String> perform();
//     void multi_perform(Function<void(Result<String>)> callback);

//     void reset();

//     long http_code() const;
//     long connect_code() const;

//     double total_time() const;
//     double connect_time() const;
//     double app_connect_time() const;

// private:
//     // CURL* curl_;
//     bool weak_;
//     // CURLM* session_;

//     void cleanup();

//     void setup();

//     void alloc_curl();
//     void free_curl();

//     void clear_response();

//     void multi_perform_setup();
//     void multi_perform_cleanup();

//     std::stringstream buffer_;
//     char errorbuf_[CURL_ERROR_SIZE];
//     Buffer errorbuf_;
//     Function<void(Result<String>)> multi_callback_;
//     Result<String> handle_perform(CURLcode perform_result);
//     struct curl_slist* headers_;
//     struct curl_slist* resolve_;
//     URL url_;
// };

// } // namespace nxc

// #endif
