
#pragma comment(lib, "quantdata.lib")

#include <iquantdata.h>
#include <cassert>
#include <common/util.h>
#include <common/mem.h>
#include "apikey.h"

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	EQuantDataResult result;

	IQuantDataSeries* pSeries = nullptr;
	TQuantDataCreationSettings creationSettings;
	creationSettings.alloc = mem::alloc;
	creationSettings.free = mem::free;
	result = QuantData_CreateSeries(&pSeries, &creationSettings);
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

	TQuantDataSymbolsSettings symbolSettings;
	symbolSettings.download = false;
	symbolSettings.index = EQuantDataSymbolSource::Default;
	IQuantDataSymbols* pSymbols = nullptr;
	result = pSeries->GetSupportedSymbols(&pSymbols, &symbolSettings);
	assert(result == EQuantDataResult::Success);
	pSymbols->Release();

	symbolSettings.download = true;
	result = pSeries->GetSupportedSymbols(&pSymbols, &symbolSettings);
	assert(result == EQuantDataResult::Success);
	pSymbols->Release();

	TQuantDataDownloadSettings downloadSettings;
	downloadSettings.symbol = "MSFT";
	downloadSettings.period = CQuantDataPeriod::Minute;
	downloadSettings.adjusted = false;

	result = pSeries->Download(&downloadSettings);
	assert(result == EQuantDataResult::Success);

	result = pSeries->Release();
	assert(result == EQuantDataResult::Success);

	return 0;
}
