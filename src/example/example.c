
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

	result = QuantData_Init();
	assert(result == QuantDataResult_Success);

	IQuantDataSeries* pSeries = 0;
	TQuantDataCreationSettings settings;
	settings.alloc = Cmalloc;
	settings.free = Cfree;
	result = QuantData_CreateSeries(&pSeries, &settings);
	assert(result == QuantDataResult_Success);

	TQuantDataLoadSettings loadSettings;
	result = QuantDataSeries_Load(pSeries, &loadSettings);
	assert(result == QuantDataResult_Success);

	result = QuantDataSeries_Release(pSeries);
	assert(result == QuantDataResult_Success);

	result = QuantData_Shutdown();
	assert(result == QuantDataResult_Success);

	return 0;
}
