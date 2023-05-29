#include "MyTime.h"

/*********************************************************************************
* @brief    Class constructor
* @param    inH start hour
* @param    inMin start minutes
* @param    inSec start seconds
* @return   void
**********************************************************************************/
TimeOperation::TimeOperation(uint8_t inH, uint8_t inM, uint8_t inS)
{
    _timevalue.hours = inH;
    _timevalue.minutes = inM;
    _timevalue.seconds = inS;
    TimeConvertToSecs(_timevalue, &_timeInSecs);
}
//=================================================================================

/*********************************************************************************
*   @brief  Class deconstructor
*   @return void
**********************************************************************************/
TimeOperation::~TimeOperation(void)
{;}
//=================================================================================

/*********************************************************************************
 * @name    IncTime
 * @brief   Increase time value by value
 * @param   inIncBy Increment time by value
 * @note    void
**********************************************************************************/
void TimeOperation::IncTime(clock_t inIncBy)
{
    uint32_t tAddBy;
    TimeConvertToSecs(inIncBy, &tAddBy); // inIncBy => &tAddBy
    _timeInSecs = _timeInSecs + tAddBy;
    SecsConvertToTime(_timeInSecs, &_timevalue); // timeInSecs => &timevalue
}
void TimeOperation::IncTime(uint8_t inH, uint8_t inM, uint8_t inS)
{
    uint32_t tAddBy;
    TimeConvertToSecs(inH, inM, inS, &tAddBy); // inIncBy => &tAddBy
    _timeInSecs = _timeInSecs + tAddBy;
    SecsConvertToTime(_timeInSecs, &_timevalue); // timeInSecs => &timevalue
}
void TimeOperation::IncTime(uint32_t inSecs)
{
    _timeInSecs = _timeInSecs + inSecs;
    SecsConvertToTime(_timeInSecs, &_timevalue); // timeInSecs => &timevalue
}
//=================================================================================

/*********************************************************************************
 * @name    DecTime
 * @brief   Decrease time value by value
 * @param   inDecBy Decrement time by value
 * @return  void
 * @note    void
**********************************************************************************/
void TimeOperation::DecTime(clock_t inDecBy)
{
    uint32_t tDecBy;
    TimeConvertToSecs(inDecBy, &tDecBy);
    _timeInSecs = _timeInSecs - tDecBy;
    SecsConvertToTime(_timeInSecs, &_timevalue);
}
void TimeOperation::DecTime(uint8_t inH, uint8_t inM, uint8_t inS)
{
    uint32_t tDecBy;
    TimeConvertToSecs(inH, inM, inS, &tDecBy);
    _timeInSecs = _timeInSecs - tDecBy;
    SecsConvertToTime(_timeInSecs, &_timevalue);
}
void TimeOperation::DecTime(uint32_t inSecs)
{
    _timeInSecs = _timeInSecs - inSecs;
    SecsConvertToTime(_timeInSecs, &_timevalue);
}
//=================================================================================

/*********************************************************************************
 * @name    TimeConvertToSecs
 * @brief   Convert time sormat to seconds
 * @param   inTime Convert time to amount of seconds
 * @return  void
 * @note    void
**********************************************************************************/
void TimeOperation::TimeConvertToSecs(clock_t inTime, uint32_t* pSecs)
{
    uint32_t tSeconds;

    // Convert hours to seconds
    tSeconds = inTime.hours * 3600;   // Hours to seconds

    // Convert minutes to seconds
    tSeconds = tSeconds + (inTime.minutes * 60);

    // Add seconds
    tSeconds = tSeconds + inTime.seconds;

    *pSecs = tSeconds;
}
void TimeOperation::TimeConvertToSecs(uint8_t inH, uint8_t inM, uint8_t inS, uint32_t* pSecs)
{
    uint32_t tSeconds;

    // Convert hours to seconds
    tSeconds = inH * 3600;   // Hours to seconds

    // Convert minutes to seconds
    tSeconds = tSeconds + (inM * 60);

    // Add seconds
    tSeconds = tSeconds + inS;

    *pSecs = tSeconds;
}
//=================================================================================

/*********************************************************************************
 * @name    SecsConvertToTime
 * @brief   Convert time sormat to seconds
 * @param   inSecs Convert time to amount of seconds
 * @param   pTime Destination time structure
 * @return  void
 * @note    void
**********************************************************************************/
void TimeOperation::SecsConvertToTime(uint32_t inSecs, clock_t* pTime)
{
    uint32_t rest;

    pTime->hours = inSecs / 3600;
    rest = inSecs % 3600;

    pTime->minutes = rest / 60;
    rest = rest % 60;

    pTime->seconds = rest;
}
void TimeOperation::SecsConvertToTime(uint32_t inSecs, uint8_t* pH, uint8_t* pM, uint8_t* pS)
{
    uint32_t rest;

    *pH = inSecs / 3600;
    rest = inSecs % 3600;

    *pM = rest / 60;
    rest = rest % 60;

    *pS = rest;
}
//=================================================================================

/*********************************************************************************
 * @name    GetTimeValue
 * @brief   Return current value of time
 * @param   void
 * @return  clock_t Structure with time values
 * @note    This is public method
*/
clock_t TimeOperation::GetTimeValue(void)
{
    clock_t tTime;

    tTime.hours = _timevalue.hours;
    tTime.minutes = _timevalue.minutes;
    tTime.seconds = _timevalue.seconds;

    return tTime;
}
void TimeOperation::GetTimeValue(uint8_t* pH, uint8_t* pM, uint8_t* pS)
{
    *pH = _timevalue.hours;
    *pM = _timevalue.minutes;
    *pS = _timevalue.seconds;
}
uint32_t TimeOperation::GetSeconds(void)
{
    return _timeInSecs;
}
//=================================================================================

/*********************************************************************************
 * @name    SetTimeValue
 * @brief   Set time variable to some value
 * @param   inTime Time to set in clock_t format
 * @return  void
 * @note    void 
*/
void TimeOperation::SetTimeValue(clock_t inTime)
{
    _timevalue = inTime;
    TimeConvertToSecs(_timevalue, &_timeInSecs);
}
/*********************************************************************************
 * @name    SetTimeValue
 * @brief   Set time variable to some value
 * @param   inH Input hours value 
 * @param   inM Input minutes value
 * @param   inS Input seconds value
 * @return  void
 * @note    void 
*/
void TimeOperation::SetTimeValue(uint8_t inH, uint8_t inM, uint8_t inS)
{
    _timevalue.hours = inH;
    _timevalue.minutes = inM;
    _timevalue.seconds = inS;
    TimeConvertToSecs(_timevalue, &_timeInSecs);
}
/*********************************************************************************
 * @name    SetTimeValue
 * @brief   Set time variable to some value
 * @param   inSecs Amount of seconds to set 
 * @return  void
 * @note    void 
*/
void TimeOperation::SetTimeValue(uint32_t inSecs)
{
    _timeInSecs = inSecs;
    SecsConvertToTime(_timeInSecs, &_timevalue);
}
//=================================================================================

/*********************************************************************************
 * @name    CyclicalIncTime
 * @brief   This call need to be place in timer interrupt 
 * @param   inPrescaler Cyclical call devider
 * @return  void
 * @note    void
*/
void TimeOperation::CyclicalIncTime(uint8_t inPrescaler)
{
    static uint8_t sCounter = 0;
    sCounter++;
    if(sCounter >= inPrescaler)
    {
        sCounter = 0x00;
        IncTime(0x01);
    }
}
/*********************************************************************************
 * @name    CyclicalDecTime
 * @brief   This call need to be place in timer interrupt 
 * @param   inPrescaler Cyclical call devider
 * @return  void
 * @note    void
*/
void TimeOperation::CyclicalDecTime(uint8_t inPrescaler)
{
    static uint8_t sCounter = 0;
    sCounter++;
    if(sCounter >= inPrescaler)
    {
        sCounter = 0x00;
        DecTime(0x01);
    }
}
//=================================================================================