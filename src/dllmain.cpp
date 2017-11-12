
#include <quantdata.h>
#include <Windows.h>

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	(void)hinstDLL;
	(void)fdwReason;
	(void)lpvReserved;
	return TRUE;
}

EQuantDataResult QUANTDATA_CALL QuantDataInit()
{
	return EQuantDataResult::Success;
}

void QUANTDATA_CALL QuantDataCleanup()
{

}

EQuantDataResult QUANTDATA_CALL QuantDataCreateSeries(IQuantDataSeries** ppSeries)
{
	return EQuantDataResult::Success;
}
