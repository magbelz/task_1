#ifdef _WIN32
#include <tchar.h>
#endif

#pragma pack(push, 1)
typedef struct {
  BYTE BS_jmpBoot[3];       // 0x00 ������� � ������ ��������
  char BS_OEMName[8];       // 0x03 OEM Name
  UINT16 BS_BytsPerSec;    // 0x0b ���������� ���� � �������
  UINT8 BS_SecPerClus;     // 0x0d ���������� ���������
  UINT16 BS_RsvdSecCnt;    // 0x0e ������ ����������������� ������� (� ��������)
  UINT8 BS_NumFATs;        // 0x10 ���������� ����� FAT
  UINT16 BS_RootEntCnt;    // 0x11 (�� ������������ ��� FAT32)
  UINT16 BS_TotSec16;      // 0x13 (�� ������������ ��� FAT32)
  UINT8 BS_Media;          // 0x15 ��� ��������
  UINT16 BS_FATSz16;       // 0x16 (�� ������������ ��� FAT32)
  UINT16 BS_SecPerTrk;     // 0x18 ���������� �������� � �������
  UINT16 BS_NumHeads;      // 0x1a ���������� �������
  UINT32 BS_HiddSec;       // 0x1c ���������� �������� ����� ������� �������
  UINT32 BS_TotSec32;      // 0x20 (32-��������� ���������� �������� � �������� �������)
  UINT32 BS_FATSz32;       // 0x24 32-��������� ������ � ��������
  UINT16 BS_ExtFlags;      // 0x28 ����� ���������� ���������� ��������
  UINT16 BS_FSVer;         // 0x2a �������� � �������������� ����� ������
  UINT32 BS_RootClus;      // 0x2c ����� �������� ��������� ��������
  UINT16 BS_FSInfo;        // 0x30 ������, � ������� ��������� ��������� FSINFO
  UINT16 BS_BkBootSec;     // 0x32 ������, � ������� ��������� ��������� ����� ������������ �����
  UINT8 BS_Reserved[12];   // 0x34 ���������������
  UINT8 BS_DrvNum;          // 0x40 ����� ����� BIOS INT13H
  UINT8 BS_Reserved1;       // 0x41 �� ������������
  UINT8 BS_BootSig;         // 0x42 ����������� ��������� = 0x29
  UINT32 BS_VolID;          // 0x43 �������� ����� ����
  char BS_VolLab[11];       // 0x47 ����� ���� � ��������� ASCII
  char BS_FilSysType[8];    // 0x52 ����� ���� �� "FAT32"
}  FAT32_BootRecord;
#pragma pack(pop)

extern "C" int __declspec(dllexport) __stdcall getDisk(FAT32_BootRecord* pBootRecord);
