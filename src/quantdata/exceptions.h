
#pragma once


#include <quantdata.h>
#include <quantdata/types.h>
#include <cpprest/http_client.h>
#include <exception>

namespace quantdata {

inline EQuantDataResult HandleException(const web::http::http_exception& exception)
{
	std::cout << exception.what() << std::endl;
	return EQuantDataResult::HttpException;
}

inline EQuantDataResult HandleException(const web::json::json_exception& exception)
{
	std::cout << exception.what() << std::endl;
	return EQuantDataResult::JsonException;
}

inline EQuantDataResult HandleException(const json::json_exception& exception)
{
	std::cout << exception.what() << std::endl;
	return EQuantDataResult::JsonException;
}

} // namespace quantdata
