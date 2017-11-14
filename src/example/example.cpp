
#pragma comment(lib, "quantdata.lib")

#include <iquantdata.h>
#include <cassert>
#include <common/utils.h>
#include "apikey.h"

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	EQuantDataResult result;

	result = QuantDataInit();
	assert(result == EQuantDataResult::Success);

	IQuantDataSeries* pSeries = nullptr;
	TQuantDataCreationSettings settings;
	settings.alloc = Alloc;
	settings.free = Free;
	result = QuantDataCreateSeries(&pSeries, &settings);
	assert(result == EQuantDataResult::Success);

	TQuantDataLoadSettings loadSettings;
	result = pSeries->Load(&loadSettings);
	assert(result == EQuantDataResult::Success);

	result = pSeries->Release();
	assert(result == EQuantDataResult::Success);

	result = QuantDataCleanup();
	assert(result == EQuantDataResult::Success);

	return 0;
}
