#pragma hdrstop
#pragma argsused
#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include "FAT32.h"

using namespace std;

#pragma pack(push, 1)
typedef struct 
{
    BYTE BS_jmpBoot[3];       // 0x00 переход в начало описания
    char BS_OEMName[8];       // 0x03 OEM Name
    UINT16 BS_BytsPerSec;    // 0x0b количество байт в секторе
    UINT8 BS_SecPerClus;     // 0x0d кластерный множитель
    UINT16 BS_RsvdSecCnt;    // 0x0e размер зарезервированной области (в секторах)
    UINT8 BS_NumFATs;        // 0x10 количество копий FAT
    UINT16 BS_RootEntCnt;    // 0x11 (не используется для FAT32)
    UINT16 BS_TotSec16;      // 0x13 (не используется для FAT32)
    UINT8 BS_Media;          // 0x15 тип носителя
    UINT16 BS_FATSz16;       // 0x16 (не используется для FAT32)
    UINT16 BS_SecPerTrk;     // 0x18 количество секторов в дорожке
    UINT16 BS_NumHeads;      // 0x1a количество головок
    UINT32 BS_HiddSec;       // 0x1c количество секторов перед началом раздела
    UINT32 BS_TotSec32;      // 0x20 (32-разрядное количество секторов в файловой системе)
    UINT32 BS_FATSz32;       // 0x24 32-разрядный размер в секторах
    UINT16 BS_ExtFlags;      // 0x28 режим обновления нескольких структур
    UINT16 BS_FSVer;         // 0x2a основной и дополнительный номер версии
    UINT32 BS_RootClus;      // 0x2c номер кластера корневого каталога
    UINT16 BS_FSInfo;        // 0x30 сектор, в котором находится структура FSINFO
    UINT16 BS_BkBootSec;     // 0x32 сектор, в котором находится резервная копия загрузочного диска
    UINT8 BS_Reserved[12];   // 0x34 зарезервировано
    UINT8 BS_DrvNum;          // 0x40 номер диска BIOS INT13H
    UINT8 BS_Reserved1;       // 0x41 не используется
    UINT8 BS_BootSig;         // 0x42 расширенная сигнатура = 0x29
    UINT32 BS_VolID;          // 0x43 серийный номер тома
    char BS_VolLab[11];       // 0x47 метка тома в кодировке ASCII
    char BS_FilSysType[8];    // 0x52 метка типа ФС "FAT32"
}  FAT32_BootRecord;
#pragma pack(pop)


void FAT32::getDisk(string diskname) 
{
    string prep_name("\\\\.\\");
	prep_name += diskname;
	wstring wname = wstring(prep_name.begin(), prep_name.end());
    const wchar_t* fileName = wname.c_str();
    // L"\\\\.\\PhysicalDrive0"
    // либо просто имя файла

    HANDLE fileHandle = CreateFileW(
        fileName, // имя файла
        GENERIC_READ,         // режим доступа-чтение
        FILE_SHARE_READ | FILE_SHARE_WRITE, // режим совместной работы
        NULL,    // атрибуты безопасности
        OPEN_EXISTING,    // способ открытия
        FILE_ATTRIBUTE_NORMAL,  // флаги и атрибуты
        NULL    // описатель (идентификатор) файла шаблона с правами доступа GENERIC_READ
    );
    if(fileHandle == INVALID_HANDLE_VALUE)   // обработка ошибки открытия файла
    {
        cout << "Invalid file handle!" << endl;
    }

    LARGE_INTEGER sectorOffset; // определение смещения
    sectorOffset.QuadPart = 0;  // так как чтение с диска

    // позиционируемся на диске-задаем позицию
    unsigned long currentPosition = SetFilePointer( // если успешно
        fileHandle,  // дескриптор файла
        sectorOffset.LowPart, // младшая часть смещения
        &sectorOffset.HighPart,  // указатель нас старшую часть смещения
        FILE_BEGIN // точка в файле относительно которой надо позиционироваться-начало файла
    );
    if (currentPosition != sectorOffset.LowPart)   // проверка успешного позиционирования
    {
        cout << "Current position is wrong!" << endl;
    }
    BYTE dataBuffer[1024];  // выделение памяти в стеке // буфер для хранения загрузочной записи
    DWORD bytesToRead = 1024; // сколько надо считать
    DWORD bytesRead;  // сколько реально прочиталось

    bool readResult = ReadFile(  // чтение данных
        fileHandle, // дескриптор файла
        dataBuffer,  //указатель на буфер
        bytesToRead,  //сколько хотим прочитать //четырехбайтовое число
        &bytesRead,   //указатель на переменную в которую записывваеться сколько считалось
        NULL
    );
    if (!readResult || bytesRead != bytesToRead)  // обработка ошибки
    {
       cout << "Read error!" << endl;
    }

    FAT32_BootRecord *pBootRecord = reinterpret_cast<FAT32_BootRecord*>(dataBuffer);  // считываем данные в буфер
    //инициализируем указатель преобразуем тип
    // работа с данными
    cout << "OEM Name: " << pBootRecord->BS_OEMName << endl;
    cout << "Bytes per sector: " << pBootRecord->BS_BytsPerSec << endl;
    cout << "Reserved sectors count: " << pBootRecord->BS_RsvdSecCnt << endl;
    cin.get();
    CloseHandle (fileHandle); // закрытие файла
}


