#include <stdint.h>

#ifndef _MY_TIME_H
#define _MY_TIME_H

#define MY_TIME_HOURS    24U
#define MY_TIME_MINUTES  60U
#define MY_TIME_SECONDS  60U

#define MY_TIME_INC     0x01U
#define MY_TIME_DEC     0xFFU

#define MY_TIME_MODE_COUNT  0x11U
#define MY_TIME_MODE_EDIT   0x22U

typedef struct 
{
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
}clock_t;

class TimeOperation
{
private:
    clock_t _timevalue;
    uint32_t _timeInSecs;
public:
    TimeOperation(uint8_t inH, uint8_t inM, uint8_t inS);
    ~TimeOperation(void);

    clock_t GetTimeValue(void);
    void GetTimeValue(uint8_t* pH, uint8_t* pM, uint8_t* pS);
    uint32_t GetSeconds(void);

    void IncTime(clock_t inIncBy);
    void IncTime(uint8_t inH, uint8_t inM, uint8_t inS);
    void IncTime(uint32_t inSecs);
    
    void DecTime(clock_t inDecBy);
    void DecTime(uint8_t inH, uint8_t inM, uint8_t inS);
    void DecTime(uint32_t inSecs);

    void TimeConvertToSecs(clock_t inTime, uint32_t* pSecs);
    void TimeConvertToSecs(uint8_t inH, uint8_t inM, uint8_t inS, uint32_t* pSecs);

    void SecsConvertToTime(uint32_t inSecs, clock_t* pTime);
    void SecsConvertToTime(uint32_t inSecs, uint8_t* pH, uint8_t* pM, uint8_t* pS);

    void SetTimeValue(clock_t inTime);
    void SetTimeValue(uint8_t inH, uint8_t inM, uint8_t inS);
    void SetTimeValue(uint32_t inSecs);

    void CyclicalIncTime(uint8_t inPrescaler);
    void CyclicalDecTime(uint8_t inPrescaler);
};

#endif // _MY_LCD_H