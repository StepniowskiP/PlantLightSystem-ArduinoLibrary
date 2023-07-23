#ifndef REALTIMECLOCK_H
#define REALTIMECLOCK_H

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include "../../constants.h"

class RealTimeClock
{
private:
    tmElements_t tm;

    bool _get_compiler_time(const char *time_string);
    bool _get_compiler_date(const char *date_string);
    bool _get_rtc_data();
    String _format_number(uint8_t number);

public:
    RealTimeClock();
    ~RealTimeClock();

    void initialize_real_time_clock();

    bool set_time_based_on_compiler_clock();
    bool set_time_and_date(uint8_t hour, uint8_t minute, uint8_t second, uint8_t wday, uint8_t day, uint8_t month, uint16_t year);
    bool set_time(uint8_t hour, uint8_t minute, uint8_t second);
    bool set_date(uint8_t wday, uint8_t day, uint8_t month, uint16_t year);

    String get_time();
    String get_date();
};

#endif /* REALTIMECLOCK_H */