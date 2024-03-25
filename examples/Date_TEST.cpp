/* Tests for Date class

    Tests:
    Invalid date
    SetDay
    SetMonth
    SetYear
    GetDateFormatted
*/

#include <DateTM.h>

void setup()
{
    Serial.begin(115200);

    Serial.println("Tests: DateTM class");

    uint8_t failsCount = 0;

    // 30 April 2019
    DateTM testDate(30, 4, 19);
    Serial.println(testDate.GetDateFormatted());
    if (!testDate || testDate.GetDateFormatted() != "30/04/2019")
    {
        Serial.println("FAILED: Initial Date should be valid");
        failsCount++;
    }

    // validity
    {
        // there is no 31st of April, just 30th
        Serial.println(testDate.GetDateFormatted());
        testDate.SetDate(31, 4, 19);
        Serial.println(testDate.GetDateFormatted());
        if (!testDate)
        {
            Serial.println("FAILED: Date should be valid");
            failsCount++;
        }
    }

    // day
    {
        Serial.println(testDate.GetDateFormatted());
        testDate.SetDay(19);
        Serial.println(testDate.GetDateFormatted());
        if (testDate.GetDay() != 19)
        {
            Serial.println("FAILED: Day should be set");
            failsCount++;
        }
    }

    // month
    {
        Serial.println(testDate.GetDateFormatted());
        testDate.SetMonth(10);
        Serial.println(testDate.GetDateFormatted());
        if (testDate.GetMonth() != 10)
        {
            Serial.println("FAILED: Month should be set");
            failsCount++;
        }
    }

    // year
    {
        Serial.println(testDate.GetDateFormatted());
        testDate.SetYear(19);
        Serial.println(testDate.GetDateFormatted());
        if (testDate.GetYear() != 2019)
        {
            Serial.println("FAILED: Year should be set");
            failsCount++;
        }
    }

    // date: day, month, year
    {
        Serial.println(testDate.GetDateFormatted());
        testDate.SetDate(19, 10, 19);
        Serial.println(testDate.GetDateFormatted());
        if (testDate.GetDay() != 19 || testDate.GetMonth() != 10 || testDate.GetYear() != 2019)
        {
            Serial.println("FAILED: Date should be set");
            failsCount++;
        }
    }

    // compare dates
    {
        DateTM date1(12, 2, 24);
        DateTM date2(12, 2, 24);

        if (!(date1 >= date2))
        {
            Serial.println("FAILED: Dates should be greater or equal.");
            failsCount++;
        }

        date1.AddDays(2);
        if (!(date1 >= date2))
        {
            Serial.println("FAILED: Dates should be greater or equal.");
            failsCount++;
        }

        date2.AddDays(3);
        if (date1 >= date2)
        {
            Serial.println("FAILED: Date1 should be less than date2.");
            failsCount++;
        }
    }

    // invalid cases
    {
        // date not set
        {
            DateTM date;
            if (date)
            {
                Serial.println("FAILED: Date should be invalid because was not set.");
                failsCount++;
            }
        }

        // set a day when the current month does not support that day
        {
            DateTM date(28, 2, 1);
            Serial.println(date.GetDateFormatted());
            if (date.SetDay(29))
            {
                Serial.println("FAILED: Date should remain valid after trying to set a wrong day.");
                failsCount++;
            }
        }

        // set a month when the current day does not support that month
        {
            DateTM date(30, 3, 0);
            Serial.println(date.GetDateFormatted());
            if (date.SetMonth(2) || !date)
            {
                Serial.println("FAILED: Date should remain valid after trying to set a wrong month.");
                failsCount++;
            }
        }

        // set a year when the current day does not support that year
        {
            DateTM date(29, 2, 0);
            Serial.println(date.GetDateFormatted());
            if (date.SetYear(1) || !date)
            {
                Serial.println("FAILED: Date should remain valid after trying to set a wrong year.");
                failsCount++;
            }
        }
    }

    // formatted date
    {  
        // "<DD>/<MM>/<YYYY>"
        String dateFormatted = testDate.GetDateFormatted();
        if (dateFormatted != "19/10/2019")
        {
            Serial.println("FAILED: Date should be formatted");
            failsCount++;
        }
    }

    // add days tests
    {
        /*
            21/04/2024, add 2 days = 23 April
            21/04/2024, add 10 days = 1 May
            21/04/2024, add 50 days = 10 June
            21/04/2024, add 255 = 1 January 2025
        */
        {
            DateTM date(21, 4, 24);
            Serial.println(date.GetDateFormatted());
            if (!date.AddDays(2) || !date || date.GetDateFormatted() != "23/04/2024")
            {
                Serial.println("FAILED: Date should be 23/04/2024.");
                failsCount++;
            }
        }

        {
            DateTM date(21, 4, 24);
            Serial.println(date.GetDateFormatted());
            if (!date.AddDays(10) || !date || date.GetDateFormatted() != "01/05/2024")
            {
                Serial.println("FAILED: Date should be 01/05/2024.");
                failsCount++;
            }
        }

        {
            DateTM date(21, 4, 24);
            Serial.println(date.GetDateFormatted());
            if (!date.AddDays(50) || !date || date.GetDateFormatted() != "10/06/2024")
            {
                Serial.println("FAILED: Date should be 10/06/2024.");
                failsCount++;
            }
        }

        {
            DateTM date(21, 4, 24);
            Serial.println(date.GetDateFormatted());
            if (!date.AddDays(255) || !date || date.GetDateFormatted() != "01/01/2025")
            {
                Serial.println("FAILED: Date should be 01/01/2025.");
                failsCount++;
            }
        }
    }


    if (failsCount == 0)
        Serial.println((failsCount == 0) ? "PASSED" : "FAILED");
}

void loop()
{
    // dummy wait 10s
    delay(10000);
}