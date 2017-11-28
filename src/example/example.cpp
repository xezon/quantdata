
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
	
	TQuantDataAllocatorSettings allocatorSettings;
	allocatorSettings.alloc = mem::alloc;
	allocatorSettings.free = mem::free;
	result = QuantData_SetAllocator(&allocatorSettings);
	assert(result == EQuantDataResult::Success);

	IQuantDataHub* pHub = nullptr;
	result = QuantData_CreateHub(&pHub);
	assert(result == EQuantDataResult::Success);

	TQuantDataLoadSettings loadSettings;
	result = pHub->Load(&loadSettings);
	assert(result == EQuantDataResult::Success);

	TQuantDataProviderSettings providerSettings;
	providerSettings.provider = EQuantDataProvider::AlphaVantage;
	providerSettings.apikey = apikey_alphavantage;
	result = pHub->SetProvider(&providerSettings);
	assert(result == EQuantDataResult::Success);

	IQuantDataPeriods* pPeriods;
	result = pHub->GetPeriods(&pPeriods);
	assert(result == EQuantDataResult::Success);
	pPeriods->Release();

	TQuantDataSymbolsSettings symbolSettings;
	symbolSettings.download = false;
	symbolSettings.index = EQuantDataSymbolSource::Default;
	IQuantDataSymbols* pSymbols = nullptr;
	result = pHub->GetSymbols(&pSymbols, &symbolSettings);
	assert(result == EQuantDataResult::Success);
	pSymbols->Release();

	providerSettings.provider = EQuantDataProvider::OpenExchange;
	providerSettings.apikey = "test";
	result = pHub->SetProvider(&providerSettings);
	symbolSettings.download = true;
	result = pHub->GetSymbols(&pSymbols, &symbolSettings);
	assert(result == EQuantDataResult::Success);
	pSymbols->Release();

	TQuantDataDownloadSettings downloadSettings;
	downloadSettings.symbol = "MSFT";
	downloadSettings.period = CQuantDataPeriod::Minute;
	downloadSettings.adjusted = false;
	result = pHub->Download(&downloadSettings);
	assert(result == EQuantDataResult::Success);

	result = pHub->Release();
	assert(result == EQuantDataResult::Success);

	return 0;
}
