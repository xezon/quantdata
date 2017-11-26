
#pragma once

#include <cpprest/http_client.h>
#include <quantdata.h>

namespace quantdata {

inline EQuantDataResult HandleHttpException(const web::http::http_exception& exception)
{
	std::cout << exception.what() << std::endl;
	return EQuantDataResult::HttpException;
}

} // namespace quantdata
