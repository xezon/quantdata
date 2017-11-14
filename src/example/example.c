
#pragma comment(lib, "quantdata.lib")

#include <iquantdata.h>
#include <assert.h>
#include <common/utils_c.h>
#include "apikey.h"

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	EQuantDataResult result;

	result = QuantDataInit();
	assert(result == QuantDataResult_Success);

	IQuantDataSeries* pSeries = 0;
	TQuantDataCreationSettings settings;
	settings.alloc = Alloc;
	settings.free = Free;
	result = QuantDataCreateSeries(&pSeries, &settings);
	assert(result == QuantDataResult_Success);

	TQuantDataLoadSettings loadSettings;
	result = QuantDataSeriesLoad(pSeries, &loadSettings);
	assert(result == QuantDataResult_Success);

	result = QuantDataSeriesRelease(pSeries);
	assert(result == QuantDataResult_Success);

	result = QuantDataCleanup();
	assert(result == QuantDataResult_Success);

	return 0;
}
