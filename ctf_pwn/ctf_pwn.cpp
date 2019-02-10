#include <iostream>
#include <Windows.h>

using namespace std;

HANDLE handle;

DWORD infinite = 10000;
DWORD zero = 0;
DWORD nop = 0x90;

DWORD basePointer = 0x509B74;
DWORD baseAddress = 0x0;

DWORD playerCoordXAddress = 0x0;
DWORD playerCoordYAddress = 0x0;
DWORD playerCoordZAddress = 0x0;
DWORD playerAngleYawAddress = 0x0;
DWORD playerAnglePitchAddress = 0x0;
DWORD playerHealthAddress = 0x0;
DWORD playerArmorAddress = 0x0;

DWORD playerCoordXOffset = 0x4;
DWORD playerCoordYOffset = 0x8;
DWORD playerCoordZOffset = 0xC;
DWORD playerAngleYawOffset = 0x40;
DWORD playerAnglePitchOffset = 0x44;
DWORD playerHealthOffset = 0xF8;
DWORD playerArmorOffset = 0xFC;

DWORD arAmmoAddress = 0x0;
DWORD smAmmoAddress = 0x0;
DWORD snAmmoAddress = 0x0;
DWORD sgAmmoAddress = 0x0;
DWORD cbAmmoAddress = 0x0;
DWORD psAmmoAddress = 0x0;
DWORD gnAmmoAddress = 0x0;

DWORD arTimerAddress = 0x0;
DWORD smTimerAddress = 0x0;
DWORD snTimerAddress = 0x0;
DWORD sgTimerAddress = 0x0;
DWORD cbTimerAddress = 0x0;
DWORD psTimerAddress = 0x0;
DWORD gnTimerAddress = 0x0;

DWORD arAmmoOffset = 0x150;
DWORD smAmmoOffset = 0x148;
DWORD snAmmoOffset = 0x14C;
DWORD sgAmmoOffset = 0x144;
DWORD cbAmmoOffset = 0x140;
DWORD psAmmoOffset = 0x13C;
DWORD gnAmmoOffset = 0x158;

DWORD arTimerOffset = 0x178;
DWORD smTimerOffset = 0x170;
DWORD snTimerOffset = 0x174;
DWORD sgTimerOffset = 0x16C;
DWORD cbTimerOffset = 0x168;
DWORD psTimerOffset = 0x164;
DWORD gnTimerOffset = 0x180;

float enemySpawnX = 150.0;
float enemySpawnY = 50.0;
float enemySpawnZ = 3.5;
float angleYawValue = 0.0;
float anglePitchValue = 0.0;
float actualSpin = 0.0;


HANDLE attachFunc() {
	HWND window = FindWindowA(NULL, "AssaultCube");
	if (window == NULL) {
		cout << "Window not found." << endl;
	}
	else {
		cout << "Found game window: " << window << endl;
		cout << "Hooking..." << endl;
	}
	DWORD processID;
	GetWindowThreadProcessId(window, &processID);
	handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
	if (processID == NULL) {
		cout << "Process not found." << endl;
		cout << "Hook Failed." << endl;
	}
	else {
		cout << "Hook Sucessful!" << endl;
		cout << "Process ID: " << processID << endl;
	}
	return handle;
}

void teleportTo(float x, float y, float z) {
	WriteProcessMemory(handle, (LPVOID)playerCoordXAddress, &x, sizeof(x), NULL);
	WriteProcessMemory(handle, (LPVOID)playerCoordYAddress, &y, sizeof(y), NULL);
	WriteProcessMemory(handle, (LPVOID)playerCoordZAddress, &z, sizeof(z), NULL);
}

void godMode() {
	WriteProcessMemory(handle, (LPVOID)playerHealthAddress, &infinite, sizeof(infinite), NULL);
	WriteProcessMemory(handle, (LPVOID)playerArmorAddress, &infinite, sizeof(infinite), NULL);
}

void infAmmo() {
	WriteProcessMemory(handle, (LPVOID)arAmmoAddress, &infinite, sizeof(infinite), NULL);
	WriteProcessMemory(handle, (LPVOID)smAmmoAddress, &infinite, sizeof(infinite), NULL);
	WriteProcessMemory(handle, (LPVOID)snAmmoAddress, &infinite, sizeof(infinite), NULL);
	WriteProcessMemory(handle, (LPVOID)sgAmmoAddress, &infinite, sizeof(infinite), NULL);
	WriteProcessMemory(handle, (LPVOID)cbAmmoAddress, &infinite, sizeof(infinite), NULL);
	WriteProcessMemory(handle, (LPVOID)psAmmoAddress, &infinite, sizeof(infinite), NULL);
	WriteProcessMemory(handle, (LPVOID)gnAmmoAddress, &infinite, sizeof(infinite), NULL);
}

void rapidFire() {
	WriteProcessMemory(handle, (LPVOID)arTimerAddress, &zero, sizeof(zero), NULL);
	WriteProcessMemory(handle, (LPVOID)smTimerAddress, &zero, sizeof(zero), NULL);
	WriteProcessMemory(handle, (LPVOID)snTimerAddress, &zero, sizeof(zero), NULL);
	WriteProcessMemory(handle, (LPVOID)sgTimerAddress, &zero, sizeof(zero), NULL);
	WriteProcessMemory(handle, (LPVOID)cbTimerAddress, &zero, sizeof(zero), NULL);
	WriteProcessMemory(handle, (LPVOID)psTimerAddress, &zero, sizeof(zero), NULL);
	WriteProcessMemory(handle, (LPVOID)gnTimerAddress, &zero, sizeof(zero), NULL);
}

void spin() {
	if (actualSpin >= 360) {
		actualSpin = 0;
	}
	else {
		actualSpin += 0.05;
	}
	WriteProcessMemory(handle, (LPVOID)playerAnglePitchAddress, &zero, sizeof(zero), NULL);
	WriteProcessMemory(handle, (LPVOID)playerAngleYawAddress, &actualSpin, sizeof(actualSpin), NULL);
}

void retrieveAdresses(HANDLE handle) {
	ReadProcessMemory(handle, (LPCVOID)basePointer, &baseAddress, sizeof(baseAddress), NULL);

	playerCoordXAddress = baseAddress + playerCoordXOffset;
	playerCoordYAddress = baseAddress + playerCoordYOffset;
	playerCoordZAddress = baseAddress + playerCoordZOffset;
	playerAngleYawAddress = baseAddress + playerAngleYawOffset;
	playerAnglePitchAddress = baseAddress + playerAnglePitchOffset;
	playerHealthAddress = baseAddress + playerHealthOffset;
	playerArmorAddress = baseAddress + playerArmorOffset;
	
	arAmmoAddress = baseAddress + arAmmoOffset;
	smAmmoAddress = baseAddress + smAmmoOffset;
	snAmmoAddress = baseAddress + snAmmoOffset;
	sgAmmoAddress = baseAddress + sgAmmoOffset;
	cbAmmoAddress = baseAddress + cbAmmoOffset;
	psAmmoAddress = baseAddress + psAmmoOffset;
	gnAmmoAddress = baseAddress + gnAmmoOffset;

	arTimerAddress = baseAddress + arTimerOffset;
	smTimerAddress = baseAddress + smTimerOffset;
	snTimerAddress = baseAddress + snTimerOffset;
	sgTimerAddress = baseAddress + sgTimerOffset;
	cbTimerAddress = baseAddress + cbTimerOffset;
	psTimerAddress = baseAddress + psTimerOffset;
	gnTimerAddress = baseAddress + gnTimerOffset;
}

int main(){
	handle = attachFunc();
	retrieveAdresses(handle);
	
	Sleep(5000);

	for (;;) {
		teleportTo(enemySpawnX, enemySpawnY, enemySpawnZ);
		godMode();
		spin();
		infAmmo();
		rapidFire();
	}
	return 0;
}