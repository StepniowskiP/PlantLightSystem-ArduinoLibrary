/*
author: PStepniowski
description: PLS example with RTC module

To enable RTC change in constants.h file:
PLS::COMPONENTS::RTC -> true

Tested on Arduino Nano:
RAM:   [=====     ]  47.5% (used 973 bytes from 2048 bytes)
Flash: [=====     ]  47.3% (used 14516 bytes from 30720 bytes)

Sample output from Serial Monitor (PLS::LOGGING = 1):

Initializing Real Time Clock module...
Parsed time from compiler, Time= 15:01:21
Parsed date from compiler, Date= Jul 23 2023
Date from compiler: Jul 23 2023
Date from RTC module: 23/07/2023
Time from compiler: 15:00:04
Time from RTC module: 15:01:21
Setting time to 12:00:00
Time from RTC module: 12:00:00
Setting date to Sunday 01/01/2023
Date from RTC module: 01/01/2023
Setting date to Monday 02/02/2023 and time to 15:15:00
Date ant time from RTC module: 02/02/2023 , 15:15:00
...
*/

#include <Arduino.h>
#include <PlantLightSystem.h>

PlantLightSystem pls;

void setup()
{
    Serial.begin(9600);
    pls.init_components();
}

void loop()
{

    // Set date and time from compiler
    pls._RealTimeClock.set_time_based_on_compiler_clock();
    Serial.println("Date from compiler: " + (String)__DATE__);
    Serial.println("Date from RTC module: " + pls._RealTimeClock.get_date());

    Serial.println("Time from compiler: " + (String)__TIME__);
    Serial.println("Time from RTC module: " + pls._RealTimeClock.get_time());
    delay(1000);

    // Set time manually
    Serial.println(F("Setting time to 12:00:00"));
    pls._RealTimeClock.set_time(12, 0, 0);
    Serial.println("Time from RTC module: " + pls._RealTimeClock.get_time());
    delay(1000);

    // Set date manually
    Serial.println(F("Setting date to Sunday 01/01/2023"));
    pls._RealTimeClock.set_date(1, 1, 1, 2023);
    Serial.println("Date from RTC module: " + pls._RealTimeClock.get_date());
    delay(1000);

    // Set time and date manually
    Serial.println(F("Setting date to Monday 02/02/2023 and time to 15:15:00"));
    pls._RealTimeClock.set_time_and_date(15, 15, 0, 2, 2, 2, 2023);
    Serial.println("Date ant time from RTC module: " + pls._RealTimeClock.get_date() + " , " + pls._RealTimeClock.get_time());

    delay(2000);
}