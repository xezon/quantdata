
#include <Windows.h>
#include <quantdata/manager.h>

#ifdef _DEBUG
#pragma comment(lib, "cpprest141d_2_10.lib")
#else
#pragma comment(lib, "cpprest141_2_10.lib")
#endif

quantdata::CManager g_manager;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	(void)hinstDLL;
	(void)fdwReason;
	(void)lpvReserved;

	return TRUE;
}

EQuantDataResult QUANTDATA_CALL QuantData_CreateSeries(IQuantDataSeries** ppSeries, const TQuantDataCreationSettings* pSettings)
{
	return g_manager.CreateSeries(ppSeries, pSettings);
}
