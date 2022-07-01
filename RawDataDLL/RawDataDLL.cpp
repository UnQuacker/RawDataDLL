#include "pch.h"
#include "RawDataDLL.h"

RawDataDLL::RawDataDLL() {

}

void RawDataDLL::WriteData(int sector) {

	HANDLE hDisk = ::CreateFile(R"(\\.\D:)", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hDisk == INVALID_HANDLE_VALUE) { return; };

	char dataToWrite[512] = "writedll";
	long SectorMove = sector * 512;
	DWORD dwBytesWritten = 0;

	DWORD dwPtr = SetFilePointer(hDisk,
		SectorMove,
		NULL,
		FILE_BEGIN);

	::WriteFile(hDisk, dataToWrite, sizeof(dataToWrite), &dwBytesWritten, NULL);
	::CloseHandle(hDisk);
}

void RawDataDLL::ReadData(char* dest, int sector) {

	HANDLE hDisk = ::CreateFile(R"(\\.\D:)", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hDisk == INVALID_HANDLE_VALUE) { return; };

	BYTE buf[512];
	DWORD dwRead;
	long SectorMove = sector * 512;

	DWORD dwPtr = SetFilePointer(hDisk,
		SectorMove,
		NULL,
		FILE_BEGIN);

	if (!::ReadFile(hDisk, buf, sizeof(buf), &dwRead, NULL) || dwRead != sizeof(buf)) { return; };
	::CloseHandle(hDisk);

	for (int i = 0; i < 512; i++)
	{
		dest[i] = buf[i];
	}

}

void RawDataDLL::RunTest(char* dest, int sector) {

	HANDLE hDisk = ::CreateFile(R"(\\.\D:)", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hDisk == INVALID_HANDLE_VALUE) { return; };

	char dataToWrite[512] = "writedll";
	long SectorMove = sector * 512;
	DWORD dwBytesWritten = 0;

	DWORD dwPtr = SetFilePointer(hDisk,
		SectorMove,
		NULL,
		FILE_BEGIN);

	::WriteFile(hDisk, dataToWrite, sizeof(dataToWrite), &dwBytesWritten, NULL);

	BYTE buf[512];
	char Temp[512];
	DWORD dwRead;

	DWORD dwPtr2 = SetFilePointer(hDisk,
		SectorMove,
		NULL,
		FILE_BEGIN);

	if (!::ReadFile(hDisk, buf, sizeof(buf), &dwRead, NULL) || dwRead != sizeof(buf)) { return; };
	::CloseHandle(hDisk);

	for (int i = 0; i < 512; i++)
	{
		Temp[i] = buf[i];
	}
	#pragma warning(suppress : 4996)
	strcpy(dest, Temp);
}