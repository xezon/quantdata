
#pragma comment(lib, "quantdata.lib")

#include <iquantdata.h>
#include <assert.h>
#include <common/util_c.h>
#include "apikey.h"

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	EQuantDataResult result;

	TQuantDataAllocatorSettings allocatorSettings;
	allocatorSettings.alloc = c_malloc;
	allocatorSettings.free = c_free;
	result = QuantData_SetAllocator(&allocatorSettings);
	assert(result == QuantDataResult_Success);

	IQuantDataHub* pHub = 0;
	result = QuantData_CreateHub(&pHub);
	assert(result == QuantDataResult_Success);

	TQuantDataLoadSettings loadSettings = {0};
	result = pHub->Load(pHub, &loadSettings);
	assert(result == QuantDataResult_Success);

	TQuantDataProviderSettings providerSettings = {0};
	providerSettings.provider = QuantDataProvider_AlphaVantage;
	providerSettings.apikey = apikey_alphavantage;
	result = pHub->SetProvider(pHub, &providerSettings);
	assert(result == QuantDataResult_Success);

	IQuantDataPeriods* pPeriods = 0;
	result = pHub->GetPeriods(pHub, &pPeriods);
	assert(result == QuantDataResult_Success);
	pPeriods->Release(pPeriods);

	TQuantDataSymbolsSettings symbolSettings = {0};
	symbolSettings.download = 0;
	symbolSettings.index = QuantDataSymbolSource_Default;

	IQuantDataSymbols* pSymbols = 0;
	result = pHub->GetSymbols(pHub, &pSymbols, &symbolSettings);
	assert(result == QuantDataResult_Success);
	SAFE_RELEASE(pSymbols);

	symbolSettings.download = 1;
	result = pHub->GetSymbols(pHub, &pSymbols, &symbolSettings);
	SAFE_RELEASE(pSymbols);

	providerSettings.provider = QuantDataProvider_OpenExchange;
	providerSettings.apikey = "test";
	result = pHub->SetProvider(pHub, &providerSettings);
	symbolSettings.download = 1;
	result = pHub->GetSymbols(pHub, &pSymbols, &symbolSettings);
	assert(result == QuantDataResult_Success);
	SAFE_RELEASE(pSymbols);

	TQuantDataDownloadSettings downloadSettings = {0};
	downloadSettings.symbol = "MSFT";
	downloadSettings.period = QuantDataPeriod_Minute;
	downloadSettings.adjusted = 0;
	result = pHub->Download(pHub, &downloadSettings);
	assert(result == QuantDataResult_Success);

	SAFE_RELEASE(pHub);

	return 0;
}
