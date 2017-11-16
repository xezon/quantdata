
#pragma once

#include <string>
#include <memory>
#include <cassert>
#include <type_traits>

#ifndef CURL_STATICLIB
#define CURL_STATICLIB
#endif
#include <curl/curl.h>

template <class Allocator = std::allocator<char>>
class CDownloader
{
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

	static CURLcode Download(TData& header, TData& page, const SDownloadSettings& settings)
	{
		header.clear();
		page.clear();
		CURL* curl = curl_easy_init();

		if (curl == nullptr)
			return CURLE_FAILED_INIT;

		CURLcode code;
		code = curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
		code = curl_easy_setopt(curl, CURLOPT_URL, settings.url);
		code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteToString);
		code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &page);
		code = curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteToString);
		code = curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header);

		if (IsValidString(settings.certtype))
		{
			code = curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, settings.certtype);
		}
		else if (IsValidString(settings.certfile))
		{
			code = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
			code = curl_easy_setopt(curl, CURLOPT_CAINFO, settings.certfile);
		}
		else
		{
			code = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		}

		code = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
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
