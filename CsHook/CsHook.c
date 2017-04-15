// CsHook.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "d3dscene.h"
#include "cavestory.h"

#define EXTERN_DLL_EXPORT __declspec(dllexport)

// use this to trick the game into thinking version.dll is actually doing its job
char fakeVersionData[] = { 
	0x9C, 0x02, 0x34, 0x00, 0x00, 0x00, 0x56, 0x00, 0x53, 0x00, 0x5F, 0x00, 0x56, 0x00, 0x45, 0x00, 0x52, 0x00, 0x53, 0x00, 0x49, 0x00, 0x4F, 0x00, 0x4E, 0x00, 0x5F, 0x00, 0x49, 0x00, 0x4E, 0x00,
	0x46, 0x00, 0x4F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBD, 0x04, 0xEF, 0xFE, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x06, 0x00, 0x00, 0x00,
	0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFA, 0x01, 0x00, 0x00,
	0x01, 0x00, 0x53, 0x00, 0x74, 0x00, 0x72, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x67, 0x00, 0x46, 0x00, 0x69, 0x00, 0x6C, 0x00, 0x65, 0x00, 0x49, 0x00, 0x6E, 0x00, 0x66, 0x00, 0x6F, 0x00, 0x00, 0x00,
	0xD6, 0x01, 0x00, 0x00, 0x01, 0x00, 0x30, 0x00, 0x34, 0x00, 0x31, 0x00, 0x31, 0x00, 0x30, 0x00, 0x34, 0x00, 0x62, 0x00, 0x30, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x09, 0x00, 0x01, 0x00, 0x46, 0x00,
	0x69, 0x00, 0x6C, 0x00, 0x65, 0x00, 0x44, 0x00, 0x65, 0x00, 0x73, 0x00, 0x63, 0x00, 0x72, 0x00, 0x69, 0x00, 0x70, 0x00, 0x74, 0x00, 0x69, 0x00, 0x6F, 0x00, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x44, 0x00, 0x6F, 0x00, 0x75, 0x00, 0x6B, 0x00, 0x75, 0x00, 0x74, 0x00, 0x73, 0x00, 0x75, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x0B, 0x00, 0x01, 0x00, 0x46, 0x00, 0x69, 0x00, 0x6C, 0x00,
	0x65, 0x00, 0x56, 0x00, 0x65, 0x00, 0x72, 0x00, 0x73, 0x00, 0x69, 0x00, 0x6F, 0x00, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x00, 0x2C, 0x00, 0x20, 0x00, 0x30, 0x00, 0x2C, 0x00, 0x20, 0x00,
	0x30, 0x00, 0x2C, 0x00, 0x20, 0x00, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x14, 0x00, 0x01, 0x00, 0x49, 0x00, 0x6E, 0x00, 0x74, 0x00, 0x65, 0x00, 0x72, 0x00, 0x6E, 0x00, 0x61, 0x00,
	0x6C, 0x00, 0x4E, 0x00, 0x61, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x00, 0x00, 0x44, 0x00, 0x6F, 0x00, 0x75, 0x00, 0x6B, 0x00, 0x75, 0x00, 0x74, 0x00, 0x73, 0x00, 0x75, 0x00, 0x20, 0x00, 0x4D, 0x00,
	0x6F, 0x00, 0x6E, 0x00, 0x6F, 0x00, 0x67, 0x00, 0x61, 0x00, 0x74, 0x00, 0x61, 0x00, 0x72, 0x00, 0x69, 0x00, 0x00, 0x00, 0x48, 0x00, 0x12, 0x00, 0x01, 0x00, 0x4C, 0x00, 0x65, 0x00, 0x67, 0x00,
	0x61, 0x00, 0x6C, 0x00, 0x43, 0x00, 0x6F, 0x00, 0x70, 0x00, 0x79, 0x00, 0x72, 0x00, 0x69, 0x00, 0x67, 0x00, 0x68, 0x00, 0x74, 0x00, 0x00, 0x00, 0x28, 0x00, 0x43, 0x00, 0x29, 0x00, 0x20, 0x00,
	0x8B, 0x95, 0x7A, 0x76, 0xA4, 0x5B, 0x30, 0xFF, 0x69, 0x00, 0x78, 0x00, 0x65, 0x00, 0x6C, 0x00, 0x20, 0x00, 0x32, 0x00, 0x30, 0x00, 0x30, 0x00, 0x34, 0x00, 0x00, 0x00, 0x42, 0x00, 0x0D, 0x00,
	0x01, 0x00, 0x4F, 0x00, 0x72, 0x00, 0x69, 0x00, 0x67, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x61, 0x00, 0x6C, 0x00, 0x46, 0x00, 0x69, 0x00, 0x6C, 0x00, 0x65, 0x00, 0x6E, 0x00, 0x61, 0x00, 0x6D, 0x00,
	0x65, 0x00, 0x00, 0x00, 0x44, 0x00, 0x6F, 0x00, 0x75, 0x00, 0x6B, 0x00, 0x75, 0x00, 0x74, 0x00, 0x73, 0x00, 0x75, 0x00, 0x2E, 0x00, 0x65, 0x00, 0x78, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x3C, 0x00, 0x0E, 0x00, 0x01, 0x00, 0x50, 0x00, 0x72, 0x00, 0x6F, 0x00, 0x64, 0x00, 0x75, 0x00, 0x63, 0x00, 0x74, 0x00, 0x4E, 0x00, 0x61, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x8B, 0x95, 0x7A, 0x76, 0xA4, 0x5B, 0x30, 0xFF, 0x69, 0x00, 0x78, 0x00, 0x65, 0x00, 0x6C, 0x00, 0x20, 0x00, 0x1E, 0x6D, 0x9F, 0x7A, 0x69, 0x72, 0x9E, 0x8A, 0x00, 0x00, 0x3A, 0x00, 0x0B, 0x00,
	0x01, 0x00, 0x50, 0x00, 0x72, 0x00, 0x6F, 0x00, 0x64, 0x00, 0x75, 0x00, 0x63, 0x00, 0x74, 0x00, 0x56, 0x00, 0x65, 0x00, 0x72, 0x00, 0x73, 0x00, 0x69, 0x00, 0x6F, 0x00, 0x6E, 0x00, 0x00, 0x00,
	0x31, 0x00, 0x2C, 0x00, 0x20, 0x00, 0x30, 0x00, 0x2C, 0x00, 0x20, 0x00, 0x30, 0x00, 0x2C, 0x00, 0x20, 0x00, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x01, 0x00, 0x56, 0x00,
	0x61, 0x00, 0x72, 0x00, 0x46, 0x00, 0x69, 0x00, 0x6C, 0x00, 0x65, 0x00, 0x49, 0x00, 0x6E, 0x00, 0x66, 0x00, 0x6F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x04, 0x00, 0x00, 0x00, 0x54, 0x00,
	0x72, 0x00, 0x61, 0x00, 0x6E, 0x00, 0x73, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x74, 0x00, 0x69, 0x00, 0x6F, 0x00, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x04, 0xB0, 0x04,
};

// 0x4A6220 start of NPC data
CS_ENTITY* CS_npcTable = (CS_ENTITY*)0x4A6220;
// 0x498548 NPC function pointer table
void(**CS_npcFuncTable)(CS_ENTITY*) = (VOID(**)(CS_ENTITY*))0x498548;

int(*CS_randInt)(int, int) = (int(*)(int, int))0x40F350;

BOOL(*CS_peek_message)() = (BOOL(*)())0x40B340;

LONG CS_wndProc = 0x412CA0;


void hijack_d3d() {
	// destroy existing dd7 configuration
	// dunno if this is actually necessary might want to keep it? ueh
	//0x421570 - destroy bitmap objects
	//0x40B6C0(x) - destroy directdraw surfaces(?)
	//0049E458 AppWinHandle
	HWND appWinHandle = *(HWND*)0x49E458;
	//((VOID(*)(VOID))0x421570)();
	//((VOID(*)(HWND))0x40B6C0)(appWinHandle);

	initD3D(appWinHandle);
	while (CS_peek_message()) {		
		render_frame();
		Sleep(10);
	}
	cleanD3D();
}


void hijack_npcwiggle(CS_ENTITY* This) {
	for (int i = 0; i < 0x200; i++) {
		CS_ENTITY* npc = &CS_npcTable[i];
		if (npc->inUse) {
			npc->xPos += CS_randInt(-1, 1) * 0x200;
		}
	}
}


EXTERN_DLL_EXPORT BOOL GetFileVersionInfoA(
	_In_       LPCTSTR lptstrFilename,
	_Reserved_ DWORD   dwHandle,
	_In_       DWORD   dwLen,
	_Out_      LPVOID  lpData) {
	memcpy(lpData, fakeVersionData, 0x53C);
	return 1;
}


EXTERN_DLL_EXPORT BOOL GetFileVersionInfoW(
	_In_       LPCWSTR lptstrFilename,
	_Reserved_ DWORD   dwHandle,
	_In_       DWORD   dwLen,
	_Out_      LPVOID  lpData) {
	memcpy(lpData, fakeVersionData, 0x53C);
	return 1;
}


EXTERN_DLL_EXPORT DWORD GetFileVersionInfoSizeA(
	_In_      LPCSTR lptstrFilename,
	_Out_opt_ LPDWORD lpdwHandle) {

	/*
	 *	this is where we'll do the shenanigans
	 */
	//npcFuncTable[37] = &hijack_npcwiggle;
	hijack_d3d();
	return 0x53C;
}	


__declspec(dllexport) DWORD WINAPI  GetFileVersionInfoSizeW(
	_In_      LPCWSTR lptstrFilename,
	_Out_opt_ LPDWORD lpdwHandle) {
	return 0x53C;
}


EXTERN_DLL_EXPORT BOOL WINAPI  VerQueryValueA(
	_In_  LPCVOID pBlock,
	_In_  LPCTSTR lpSubBlock,
	_Out_ LPVOID  *lplpBuffer,
	_Out_ PUINT   puLen) {

	*lplpBuffer = (LPVOID)((int)pBlock + 0x28);
	*puLen = 0x38;

	return 1;
}


EXTERN_DLL_EXPORT BOOL WINAPI  VerQueryValueW(
	_In_  LPCVOID pBlock,
	_In_  LPCTSTR lpSubBlock,
	_Out_ LPVOID  *lplpBuffer,
	_Out_ PUINT   puLen) {

	*lplpBuffer = (LPVOID)((int)pBlock + 0x28);
	*puLen = 0x38;

	return 1;
}
