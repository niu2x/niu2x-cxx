#include <nxc/curlx.h>

// namespace nxc {

// static struct curl_slist* get_headers(const vector<string>& request_headers)
// {
//     struct curl_slist* headers = nullptr;

//     for (auto it = request_headers.begin(); it != request_headers.end();
//     it++) {
//         headers = curl_slist_append(headers, (*it).c_str());
//     }

//     return headers;
// }

// static void curl_setup_proxy(CURL* curl)
// {
//     String proxyHost;
//     int proxyPort;
//     HeCore::HeGameInitializer::getProxy(&proxyHost, &proxyPort);
//     if (proxyHost.length() > 0 && proxyPort > 0) {
//         if (proxyHost.find_last_of(":") == string::npos) {
//             curl_easy_setopt(curl, CURLOPT_PROXY, proxyHost.c_str());
//         } else {
//             curl_easy_setopt(curl, CURLOPT_PROXY,
//                 proxyHost.insert(0, "[").append("]").c_str());
//         }
//         curl_easy_setopt(curl, CURLOPT_PROXYPORT, proxyPort);
//     } else {
//         curl_easy_setopt(curl, CURLOPT_PROXY, "");
//         curl_easy_setopt(curl, CURLOPT_PROXYPORT, 0);
//     }
// }

// static size_t ss_write_callback(
//     void* contents, size_t size, size_t nmemb, void* userp)
// {
//     ((std::stringstream*)userp)->write((char*)contents, size * nmemb);
//     return size * nmemb;
// }

// CurlX::CurlX(CURL* curl, CURLM* session)
// : curl_(curl)
// , session_(session)
// , weak_(curl != nullptr)
// , headers_(nullptr)
// , resolve_(nullptr)
// {
//     setup();
// }

// CurlX::~CurlX() { cleanup(); }

// void CurlX::set_proxy() { curl_setup_proxy(curl_); }
// void CurlX::set_url(const URL& url)
// {
//     url_ = url;
//     set(CURLOPT_URL, url.c_str());
// }

// void CurlX::multi_perform_setup() { curl_multi_add_handle(session_, curl_); }

// void CurlX::multi_perform_cleanup()
// {
//     curl_multi_remove_handle(session_, curl_);
// }

// Result<int> CurlX::multi_poll(CURLM* session, int timeout)
// {
//     int still_running;
//     CURLMcode mc = curl_multi_perform(session, &still_running);
//     if (!mc && still_running)
//         mc = curl_multi_poll(session, nullptr, 0, timeout, nullptr);
//     if (!mc) {
//         return still_running;
//     } else
//         return E::CURL_MULTI;
// }

// void CurlX::multi_read(CURLM* session)
// {
//     struct CURLMsg* m;
//     do {
//         int msgq = 0;
//         m = curl_multi_info_read(session, &msgq);
//         if (m && (m->msg == CURLMSG_DONE)) {
//             CURL* e = m->easy_handle;
//             CurlX* instance;
//             curl_easy_getinfo(e, CURLINFO_PRIVATE, &instance);
//             auto result = instance->handle_perform(m->data.result);
//             instance->multi_callback_(result);
//         }
//     } while (m);
// }

// Result<String> CurlX::perform()
// {
//     CCLog("CurlX::perform %s", url_.c_str());
//     clear_response();
//     auto res = curl_easy_perform(curl_);
//     return handle_perform(res);
// }

// void CurlX::multi_perform(std::function<void(Result<String>)> callback)
// {
//     CCLog("CurlX::multi_perform %s", url_.c_str());
//     clear_response();
//     multi_perform_setup();
//     multi_callback_ = [this, callback](Result<String> result) {
//         multi_perform_cleanup();
//         callback(result);
//     };
// }

// void CurlX::cleanup()
// {
//     reset();

//     if (!weak_)
//         free_curl();

//     if (headers_) {
//         curl_slist_free_all(headers_);
//         headers_ = nullptr;
//     }
//     if (resolve_) {
//         curl_slist_free_all(resolve_);
//         resolve_ = nullptr;
//     }
// }

// void CurlX::clear_response()
// {
//     memset(errorbuf_, 0, CURL_ERROR_SIZE);
//     buffer_.clear();
// }

// void CurlX::reset() { curl_easy_reset(curl_); }

// void CurlX::setup()
// {
//     if (!weak_)
//         alloc_curl();
//     set(CURLOPT_WRITEFUNCTION, ss_write_callback);
//     set(CURLOPT_WRITEDATA, &buffer_);
//     set(CURLOPT_ERRORBUFFER, errorbuf_);
//     set(CURLOPT_NOSIGNAL, 1L);
//     // set(CURLOPT_VERBOSE, 1);
//     set(CURLOPT_SSL_VERIFYHOST, 0);
//     set(CURLOPT_SSL_VERIFYPEER, 0);
//     set(CURLOPT_FOLLOWLOCATION, 1);
//     set(CURLOPT_PRIVATE, (void*)this);
// }

// void CurlX::set_headers(const std::vector<String>& headers)
// {
//     if (headers_) {
//         set(CURLOPT_HTTPHEADER, nullptr);
//         curl_slist_free_all(headers_);
//         headers_ = nullptr;
//     }

//     headers_ = get_headers(headers);
//     set(CURLOPT_HTTPHEADER, headers_);
// }

// void CurlX::set_resolve(const Host& host, const Ip& ip)
// {
//     if (resolve_) {
//         set(CURLOPT_RESOLVE, nullptr);
//         curl_slist_free_all(resolve_);
//         resolve_ = nullptr;
//     }
//     resolve_ = curl_slist_append(resolve_, (host + ":80:" + ip).c_str());
//     resolve_ = curl_slist_append(resolve_, (host + ":433:" + ip).c_str());
//     set(CURLOPT_RESOLVE, resolve_);
// }

// void CurlX::alloc_curl() { curl_ = curl_easy_init(); }

// void CurlX::free_curl()
// {
//     if (curl_) {
//         curl_easy_cleanup(curl_);
//         curl_ = nullptr;
//     }
// }

// INFO_GET_FUNC(long, http_code, CURLINFO_RESPONSE_CODE);
// INFO_GET_FUNC(long, connect_code, CURLINFO_HTTP_CONNECTCODE);
// INFO_GET_FUNC(double, total_time, CURLINFO_TOTAL_TIME);
// INFO_GET_FUNC(double, connect_time, CURLINFO_CONNECT_TIME);
// INFO_GET_FUNC(double, app_connect_time, CURLINFO_APPCONNECT_TIME);

// Result<String> CurlX::handle_perform(CURLcode res)
// {
//     if (res == CURLE_OK) {
//         long http_code = 0;
//         curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &http_code);
//         if (200 != http_code) {
//             return E::HTTP;
//         } else {
//             return buffer_.str();
//         }
//     } else {

//         std::string err_msg = curl_easy_strerror(res);

//         CCLog("errorbuf_ %s\n", errorbuf_);
//         CCLog("err_msg %s\n", err_msg.c_str());
//         CCLog("res %d\n", res);

//         if (strstr(errorbuf_, "Resolving timed out")) {
//             return { E::CURL_RESOLVE, std::move(err_msg) };
//         }

//         else if (strstr(errorbuf_, "Connection timeout")) {
//             return { E::CURL_CONNECT, std::move(err_msg) };
//         }

//         else if (strstr(errorbuf_, "Connection timed out")) {
//             return { E::CURL_CONNECT, std::move(err_msg) };
//         }
//         return { E::CURL, curl_easy_strerror(res) };
//     }
// }

// Result<String> http_get(const URL& url)
// {
//     CurlX curl(nullptr, nullptr);
//     curl.set_proxy();
//     curl.set(CURLOPT_URL, url.c_str());
//     curl.set(CURLOPT_CONNECTTIMEOUT_MS, DEFAULT_HTTP_CONNECTION_TIMEOUT);
//     curl.set(CURLOPT_TIMEOUT_MS, DEFAULT_HTTP_TIMEOUT);
//     return curl.perform();
// }

// } // namespace nxc