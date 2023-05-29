#include <stdint.h>
#include <stdlib.h>

#ifndef _UNIVERSAL_FUNS_H
#define _UNIVERSAL_FUNS_H

void ClearStructure(uint8_t* pBaseAddr, uint8_t sizeInByte);
void CopyStruct(uint8_t* pBasefrom, uint8_t* pBaseTo, uint8_t insizeof);
uint8_t ConvertToBCD(uint8_t number);


#endif // _UNIVERSAL_FUNS_H