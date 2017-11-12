
#pragma comment(lib, "quantdata.lib")

#include <iquantdata.h>
#include <cassert>
#include "apikey.h"

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	EQuantDataResult result;

	result = QuantDataInit();
	assert(result == EQuantDataResult::Success);

	result = QuantDataCleanup();
	assert(result == EQuantDataResult::Success);

	return 0;
}
