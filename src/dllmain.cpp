
#include <Windows.h>
#include <quantdata/manager.h>

#ifdef _DEBUG
#pragma comment(lib, "libcurl_a_debug.lib")
#else
#pragma comment(lib, "libcurl_a.lib")
#endif

quantdata::CManager g_manager;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	(void)hinstDLL;
	(void)fdwReason;
	(void)lpvReserved;

	return TRUE;
}

EQuantDataResult QUANTDATA_CALL QuantData_Init()
{
	return g_manager.Init();
}

EQuantDataResult QUANTDATA_CALL QuantData_Shutdown()
{
	return g_manager.Shutdown();
}

EQuantDataResult QUANTDATA_CALL QuantData_CreateSeries(IQuantDataSeries** ppSeries, const TQuantDataCreationSettings* pSettings)
{
	return g_manager.CreateSeries(ppSeries, pSettings);
}
