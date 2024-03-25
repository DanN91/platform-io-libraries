/* Tests for Time class

    Tests:
    Invalid time
    SetHour24
    SetMinute
    SetTime
    GetTimeFormatted
*/

#include <TimeTM.h>

// invalid time
TimeTM testTime(32, 60, 60);

void setup()
{
    Serial.begin(115200);

    Serial.println("Tests: Time class");

    static byte failsCount = 0;

    // validity
    {
        if (testTime)
        {
            Serial.println("FAILED: Time should be invalid.");
            failsCount++;
        }
    }

    // setting hour
    {
        testTime.SetHour24(14);
        if (testTime.GetHour24() != 14)
        {
            Serial.println("FAILED: Hour should be set.");
            failsCount++;
        }
    }

    // setting minute
    {
        testTime.SetMinute(30);
        if (testTime.GetMinute() != 30)
        {
            Serial.println("FAILED: Minute should be set.");
            failsCount++;
        }
    }

    // setting second
    {
        testTime.SetSecond(13);
        if (testTime.GetSecond() != 13)
        {
            Serial.println("FAILED: Second should be set.");
            failsCount++;
        }
    }

    // setting time: hour, minute, second
    {
        testTime.SetTime(14, 30, 29);
        if (testTime.GetHour24() != 14 || testTime.GetMinute() != 30 || testTime.GetSecond() != 29)
        {
            Serial.println("FAILED: Time should be set.");
            failsCount++;
        }
    }

    // getting formatted time
    {  
        // "<HH>:<MM>:<SS>"
        String timeFormatted = testTime.GetTimeFormatted();
        if (timeFormatted != "14:30:29")
        {
            Serial.println("FAILED: Time should be formatted.");
            failsCount++;
        }
    }

    // compare time
    {
        TimeTM time1(12, 5, 30);
        TimeTM time2(12, 5, 30);

        if (!(time1 >= time2))
        {
            Serial.println("FAILED: Times should be greater or equal.");
            failsCount++;
        }

        time1.SetMinute(6);
        if (!(time1 >= time2))
        {
            Serial.println("FAILED: Times should be greater or equal.");
            failsCount++;
        }

        time1.SetMinute(4);
        if (time1 >= time2)
        {
            Serial.println("FAILED: Time1 should be less than time2.");
            failsCount++;
        }
    }

    // time not set
    {
        TimeTM time;
        if (time)
        {
            Serial.println("FAILED: Time should be invalid because it was not set.");
            failsCount++;
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