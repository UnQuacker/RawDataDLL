#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
using namespace std;

class RawDataDLL {
public:
	RawDataDLL();
	void WriteData(int sector);
	void ReadData(char* dest, int sector);
	void RunTest(char* dest, int sector);
private:
};

extern "C" __declspec(dllexport) void* Create() {
	return (void*) new RawDataDLL();
}

extern "C" __declspec(dllexport) void WriteData(RawDataDLL rawDataDLL, int sector) {
	rawDataDLL.WriteData(sector);
}

extern "C" __declspec(dllexport) void ReadData(RawDataDLL rawDataDLL, char* dest, int sector) {
	rawDataDLL.ReadData(dest, sector);
}

extern "C" __declspec(dllexport) void RunTest(RawDataDLL rawDataDLL, char* dest, int sector) {
	rawDataDLL.RunTest(dest, sector);
}