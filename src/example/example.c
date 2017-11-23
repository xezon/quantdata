
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

	result = QuantData_Init();
	assert(result == QuantDataResult_Success);

	IQuantDataSeries* pSeries = 0;
	TQuantDataCreationSettings creationSettings = {0};
	creationSettings.alloc = c_malloc;
	creationSettings.free = c_free;
	result = QuantData_CreateSeries(&pSeries, &creationSettings);
	assert(result == QuantDataResult_Success);

	TQuantDataLoadSettings loadSettings = {0};
	result = pSeries->Load(pSeries, &loadSettings);
	assert(result == QuantDataResult_Success);

	TQuantDataProviderSettings providerSettings = {0};
	providerSettings.provider = QuantDataProvider_AlphaVantage;
	providerSettings.apikey = apikey_alphavantage;
	result = pSeries->SetProvider(pSeries, &providerSettings);
	assert(result == QuantDataResult_Success);

	IQuantDataPeriods* pPeriods = 0;
	result = pSeries->GetNativePeriods(pSeries, &pPeriods);
	assert(result == QuantDataResult_Success);
	pPeriods->Release(pPeriods);

	TQuantDataSymbolSettings symbolSettings = {0};
	symbolSettings.download = 0;
	symbolSettings.index = 0;
	IQuantDataSymbols* pSymbols = 0;
	result = pSeries->GetSupportedSymbols(pSeries, &pSymbols, &symbolSettings);
	assert(result == QuantDataResult_Success);
	pSymbols->Release(pSymbols);

	symbolSettings.download = 1;
	result = pSeries->GetSupportedSymbols(pSeries, &pSymbols, &symbolSettings);
	assert(result == QuantDataResult_Success);
	pSymbols->Release(pSymbols);

	TQuantDataDownloadSettings downloadSettings = {0};
	downloadSettings.symbol = "MSFT";
	downloadSettings.period = QuantDataPeriod_Minute;
	downloadSettings.adjusted = 0;

	result = pSeries->Download(pSeries, &downloadSettings);
	assert(result == QuantDataResult_Success);

	result = pSeries->Release(pSeries);
	assert(result == QuantDataResult_Success);

	result = QuantData_Shutdown();
	assert(result == QuantDataResult_Success);

	return 0;
}
