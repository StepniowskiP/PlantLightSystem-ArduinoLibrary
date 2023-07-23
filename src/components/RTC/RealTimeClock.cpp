#include "RealTimeClock.h"

RealTimeClock::RealTimeClock() {}
RealTimeClock::~RealTimeClock() {}

bool RealTimeClock::_get_compiler_time(const char *time_string)
{
    uint8_t Hour;
    uint8_t Minutes;
    uint8_t Seconds;

    if (sscanf(time_string, "%hhu:%hhu:%hhu", &Hour, &Minutes, &Seconds) != 3)
    {
        return false;
    }

    tm.Hour = Hour;
    tm.Minute = Minutes;
    tm.Second = Seconds;

    return true;
}

bool RealTimeClock::_get_compiler_date(const char *date_string)
{
    char Month[12];
    uint8_t Day;
    uint16_t Year;
    uint8_t month_index;

    const char *MONTH_NAME[12] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    if (sscanf(date_string, "%s %hhu %d", Month, &Day, (int*)&Year) != 3)
    {
        return false;
    }

    for (month_index = 0; month_index < 12; month_index++)
    {
        if (!strcmp(Month, MONTH_NAME[month_index]))
        {
            break;
        }
    }
    if (month_index >= 12)
    {
        return false;
    }

    tm.Day = Day;
    tm.Month = month_index + 1;
    tm.Year = CalendarYrToTm(Year);

    return true;
}

bool RealTimeClock::_get_rtc_data()
{
    if (!RTC.read(tm))
    {
        if (PLS::LOGGING)
        {
            if (RTC.chipPresent())
            {
                Serial.println(F("The DS1307 is stopped. Set time and date."));
            }
            else
            {
                Serial.println(F("DS1307 read error!  Please check the circuitry."));
            }
        }
        return false;
    }
    return true;
}

String RealTimeClock::_format_number(uint8_t number)
{
    String str_number = (String)number;
    if (number >= 0 && number < 10)
    {
        str_number = "0" + (String)number;
    }

    return str_number;
}

void RealTimeClock::initialize_real_time_clock()
{
    if (PLS::LOGGING)
    {
        Serial.println(F("Initializing Real Time Clock module..."));
    }

    if (!_get_rtc_data())
    {
        set_time_based_on_compiler_clock();
    }
}

bool RealTimeClock::set_time_based_on_compiler_clock()
{

    const char *time = __TIME__;
    const char *date = __DATE__;

    bool time_parse_flag = false;
    bool date_parse_flag = false;
    bool write_flag = false;

    if (_get_compiler_time(time))
    {
        if (PLS::LOGGING)
        {
            Serial.print(F("Parsed time from compiler, Time= "));
            Serial.println(time);
        }
        time_parse_flag = true;
    }

    if (_get_compiler_date(date))
    {
        if (PLS::LOGGING)
        {
            Serial.print(F("Parsed date from compiler, Date= "));
            Serial.println(date);
        }
        date_parse_flag = true;
    }

    if (!time_parse_flag || !date_parse_flag)
    {
        if (PLS::LOGGING)
        {
            Serial.print(F("Could not parse info from the compiler, Time=\""));
            Serial.print(time);
            Serial.print(F("\", Date=\""));
            Serial.println(date);
        }
        return false;
    }

    if (RTC.write(tm))
    {
        write_flag = true;
        return true;
    }

    if (!write_flag)
    {
        if (PLS::LOGGING)
        {
            Serial.println(F("DS1307 Communication Error"));
            Serial.println(F("Please check your circuitry"));
        }
    }

    return false;
}

bool RealTimeClock::set_time(uint8_t hour, uint8_t minute, uint8_t second)
{
    if (!_get_rtc_data())
    {
        return false;
    }

    tm.Hour = hour;
    tm.Minute = minute;
    tm.Second = second;

    if (RTC.write(tm))
    {
        return true;
    }
    else
    {
        if (PLS::LOGGING)
        {
            Serial.println(F("DS1307 Communication Error"));
            Serial.println(F("Please check your circuitry"));
        }
        return false;
    }
}

bool RealTimeClock::set_date(uint8_t wday, uint8_t day, uint8_t month, uint16_t year)
{
    if (!_get_rtc_data())
    {
        return false;
    }

    tm.Wday = wday;
    tm.Day = day;
    tm.Month = month;
    tm.Year = year-1970;

    if (RTC.write(tm))
    {
        return true;
    }
    else
    {
        if (PLS::LOGGING)
        {
            Serial.println(F("DS1307 Communication Error"));
            Serial.println(F("Please check your circuitry"));
        }
        return false;
    }
}

bool RealTimeClock::set_time_and_date(uint8_t hour, uint8_t minute, uint8_t second, uint8_t wday, uint8_t day, uint8_t month, uint16_t year)
{

    if (!set_time(hour, minute, second) || !set_date(wday, day, month, year))
    {
        return false;
    }
    return true;
}

String RealTimeClock::get_time()
{
    if (!_get_rtc_data())
    {
        return "Error getting data from RTC module.";
    }

    String time = _format_number(tm.Hour) + ":" + _format_number(tm.Minute) + ":" + _format_number(tm.Second);
    return time;
}

String RealTimeClock::get_date()
{
    if (!_get_rtc_data())
    {
        return "Error getting data from RTC module.";
    }

    String date = _format_number(tm.Day) + "/" + _format_number(tm.Month) + "/" + (String)(1970 + tm.Year);
    return date;
}