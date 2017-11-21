
#pragma once

#include <quantdata/types.h>
#include <common/mem.h>
#include <memory>
#include <cassert>
#include <type_traits>
#include <string_view>
#include <gsl/span>

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

namespace quantdata {

class CDownloader
{
private:
	struct CurlEasyInitRaii
	{
		CurlEasyInitRaii()
			: m_curl(curl_easy_init())
		{}
		~CurlEasyInitRaii() {
			if (m_curl)
				curl_easy_cleanup(m_curl);
		}
		operator CURL*() {
			return m_curl;
		}
	private:
		CURL* m_curl = nullptr;
	};

	struct CurlStringListRaii
	{
		~CurlStringListRaii() {
			if (m_slist)
				curl_slist_free_all(m_slist);
		}
		void append(const char* string) {
			m_slist = curl_slist_append(m_slist, string);
		}
		operator struct curl_slist*() {
			return m_slist;
		}
	private:
		struct curl_slist* m_slist = nullptr;
	};

public:
	template <class String = std::string>
	struct SDownloadSettings
	{
		using TString = String;
		using TStringSpan = gsl::span<TString>;
		using TStringView = std::string_view;

		TStringSpan httpHeaders;
		TStringView url;
		TStringView certtype;
		TStringView certfile;
	};

	struct SDownloadInfo
	{
		long responseCode = 0l;
		curl_off_t bytesDownloaded = 0l;
	};

	template <class Data = std::string, class String = std::string>
	static CURLcode Download(const SDownloadSettings<String>& settings, Data* pHeader, Data* pPage, SDownloadInfo* pInfo)
	{
		CurlEasyInitRaii curl;
		CurlStringListRaii curlHttpHeaders;

		if (!curl)
			return CURLE_FAILED_INIT;
		
		CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_HEADER, 0L);
		CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_URL, settings.url);

		if (pPage)
		{
			pPage->clear();
			CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_WRITEFUNCTION, WriteToData<Data>);
			CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_WRITEDATA, pPage);
		}

		if (pHeader)
		{
			pHeader->clear();
			CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_HEADERFUNCTION, WriteToData<Data>);
			CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_HEADERDATA, pHeader);
		}

		if (!settings.certtype.empty())
		{
			CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_SSLCERTTYPE, settings.certtype);
		}
		else if (!settings.certfile.empty())
		{
			CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_SSL_VERIFYPEER, 1L);
			CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_CAINFO, settings.certfile);
		}
		else
		{
			CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		}

		if (!settings.httpHeaders.empty())
		{
			for (const auto& httpHeader : settings.httpHeaders)
			{
				curlHttpHeaders.append(httpHeader.data());
			}
			CURL_EASY_SETOPT_WITH_CHECK(curl, CURLOPT_HTTPHEADER, curlHttpHeaders);
		}

		CURLcode code = curl_easy_perform(curl);

		if (pInfo)
		{
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &pInfo->responseCode);
			curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD_T, &pInfo->bytesDownloaded);
		}

		return code;
	}

	static const char* GetErrorString(CURLcode code)
	{
		return curl_easy_strerror(code);
	}

private:
	template <class Data>
	static size_t WriteToData(char* src, size_t size, size_t nmemb, Data* dst)
	{
		assert(dst != nullptr);
		dst->append(src, size * nmemb);
		return size * nmemb;
	}
};

} // namespace quantdata

#undef CURL_EASY_SETOPT_WITH_CHECK
