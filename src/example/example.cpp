
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

	result = QuantData_Init();
	assert(result == EQuantDataResult::Success);

	IQuantDataSeries* pSeries = nullptr;
	TQuantDataCreationSettings settings;
	settings.alloc = utils::alloc;
	settings.free = utils::free;
	result = QuantData_CreateSeries(&pSeries, &settings);
	assert(result == EQuantDataResult::Success);

	TQuantDataLoadSettings loadSettings;
	result = pSeries->Load(&loadSettings);
	assert(result == EQuantDataResult::Success);

	TQuantDataProviderSettings providerSettings;
	providerSettings.provider = EQuantDataProvider::AlphaVantage;
	providerSettings.apikey = apikey_alphavantage;
	result = pSeries->SetProvider(&providerSettings);
	assert(result == EQuantDataResult::Success);

	IQuantDataPeriods* pPeriods;
	result = pSeries->GetNativePeriods(&pPeriods);
	assert(result == EQuantDataResult::Success);

	pPeriods->Release();

	TQuantDataDownloadSettings downloadSettings;
	downloadSettings.symbol = "MSFT";
	downloadSettings.period = CQuantDataPeriod::Minute;
	downloadSettings.adjusted = false;

	result = pSeries->Download(&downloadSettings);
	assert(result == EQuantDataResult::Success);

	result = pSeries->Release();
	assert(result == EQuantDataResult::Success);

	result = QuantData_Shutdown();
	assert(result == EQuantDataResult::Success);

	return 0;
}
