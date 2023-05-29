#include "UniversalFuns.h"

void ClearStructure(uint8_t* pBaseAddr, uint8_t sizeInByte)
{
    uint8_t i;
    for (i = 0; i < sizeInByte; i++)
    {
        *(pBaseAddr + i) = 0x00;
    }
    return;
}

void CopyStruct(uint8_t* pBasefrom, uint8_t* pBaseTo, uint8_t insizeof)
{
    uint8_t i;
    for (i=0; i<insizeof; i++)
    {
        *(pBaseTo + i) = *(pBasefrom + i);
    }
    return;
}

uint8_t ConvertToBCD(uint8_t number)
{
    uint8_t tBCT_H, tBCT_L;

    tBCT_H = (number / 10);
    tBCT_H = (tBCT_H << 4);
    
    tBCT_L = (number % 10);
    tBCT_L = (tBCT_L << 0);

    return (tBCT_H | tBCT_L);
}