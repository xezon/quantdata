
#pragma once

#include <string>
#include <memory>
#include <cassert>
#include <type_traits>

#ifndef CURL_STATICLIB
#define CURL_STATICLIB
#endif
#include <curl/curl.h>

#define CURL_EASY_SETOPT_WITH_CHECK(curl, option, value) { \
	CURLcode code = curl_easy_setopt(curl, option, value); \
	if (code != CURLE_OK) { \
		return code; \
	} \
}

template <class Allocator = std::allocator<char>>
class CDownloader
{
private:
	struct CurlEasyInitRaii
	{
		CurlEasyInitRaii()
			: m_curl(curl_easy_init()) {
		}
		~CurlEasyInitRaii() {
			if (m_curl) {
				curl_easy_cleanup(m_curl);
			}
		}
		inline operator CURL*() {
			return m_curl;
		}
	private:
		CURL* m_curl;
	};

public:
	static_assert(std::is_same<typename Allocator::value_type, char>::value,
		"Allocator type must be of type char");

	using TData = std::basic_string<char, std::char_traits<char>, Allocator>;
	using TDataAllocator = typename TData::allocator_type;

	struct SDownloadSettings
	{
		const char* url = nullptr;
		const char* certtype = nullptr;
		const char* certfile = nullptr;
	};

	struct SDownloadInfo
	{
		long responseCode = 0l;
		curl_off_t bytesDownloaded = 0l;
	};

	static CURLcode Download(const SDownloadSettings& settings, TData* pHeader, TData* pPage, SDownloadInfo* pInfo)
	{
		CurlEasyInitRaii curl;

		if (!curl)
			return CURLE_FAILED_INIT;
		
		CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_HEADER, 0L);
		CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_URL, settings.url);

		if (pPage)
		{
			pPage->clear();
			CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_WRITEFUNCTION, WriteToString);
			CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_WRITEDATA, pPage);
		}

		if (pHeader)
		{
			pHeader->clear();
			CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_HEADERFUNCTION, WriteToString);
			CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_HEADERDATA, pHeader);
		}

		if (is_valid_string(settings.certtype))
		{
			CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_SSLCERTTYPE, settings.certtype);
		}
		else if (is_valid_string(settings.certfile))
		{
			CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_SSL_VERIFYPEER, 1L);
			CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_CAINFO, settings.certfile);
		}
		else
		{
			CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		}

		CURLcode code = curl_easy_perform(curl);

		if (pInfo)
		{
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &pInfo->responseCode);
			curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD_T, &pInfo->bytesDownloaded);
		}

		return code;
	}

private:
	static size_t WriteToString(char* src, size_t size, size_t nmemb, TData* dst)
	{
		assert(dst != nullptr);

		dst->append(src, size * nmemb);
		return size * nmemb;
	}
};

#undef CURL_EASY_SETOPT_WITH_CHECK
