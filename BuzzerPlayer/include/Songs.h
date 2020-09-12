#pragma once

#include "Sound.h"

namespace Buzzer
{
    constexpr const Note IN_CHRIST_ALONE_NOTES[]
    {
        // Verse One
        // In Christ Alone
        {NOTE_D3, BPS::Two},
        {NOTE_E3, BPS::Two},
        {NOTE_G3, BPS::Four},
        {NOTE_G3, BPS::Four},
        {NOTE_G3, BPS::One},
        {NOTE_G3, BPS::Two},

        // My hope is found
        {NOTE_D3, BPS::Two},
        {NOTE_E3, BPS::Two},
        {NOTE_G3, BPS::Two},
        {NOTE_A3, BPS::One},
        {NOTE_A3, BPS::One},

        // He is my light, my strength, my song
        {NOTE_B3, BPS::Two},
        {NOTE_A3, BPS::Four},
        {NOTE_G3, BPS::Four},
        {NOTE_E3, BPS::Two},
        {NOTE_B3, BPS::Two},
        {NOTE_A3, BPS::One},
        {NOTE_A3, BPS::Two},
        {NOTE_G3, BPS::Two},
        {NOTE_G3, BPS::One},
        {NOTE_G3, BPS::Two},

        // This cornerstone, this solid ground
        {NOTE_D3, BPS::Two},
        {NOTE_E3, BPS::Two},
        {NOTE_G3, BPS::Four},
        {NOTE_G3, BPS::Four},
        {NOTE_G3, BPS::One},
        {NOTE_G3, BPS::Two},

        {NOTE_D3, BPS::Two},
        {NOTE_E3, BPS::Two},
        {NOTE_G3, BPS::Two},
        {NOTE_A3, BPS::One},
        {NOTE_A3, BPS::One},

        // Firm through the fiercest drought and storm
        {NOTE_B3, BPS::Two},
        {NOTE_A3, BPS::Four},
        {NOTE_G3, BPS::Four},
        {NOTE_E3, BPS::Two},
        {NOTE_B3, BPS::Two},
        {NOTE_A3, BPS::One},
        {NOTE_A3, BPS::Two},
        {NOTE_G3, BPS::Two},
        {NOTE_G3, BPS::One},
        {NOTE_G3, BPS::Two},

        // // Chorus: What heights of love, What depths of peace
        // { NOTE_G3, BPS::Two },
        // { NOTE_B3, BPS::Two },
        // { NOTE_D4, BPS::Two },
        // { NOTE_E4, BPS::One }, { NOTE_E4, BPS::Two },
        // { NOTE_E4, BPS::Two },
        // { NOTE_D4, BPS::Two },
        // { NOTE_B3, BPS::Two },
        // { NOTE_A3, BPS::Two },
        // { NOTE_A3, BPS::One }, { NOTE_A3, BPS::Two },

        // { NOTE_G3, BPS::Two },
        // { NOTE_G4, BPS::Two },
        // { NOTE_FS4, BPS::Two },
        // { NOTE_E4, BPS::One }, { NOTE_E4, BPS::Two },
        // { NOTE_E4, BPS::Two },
        // { NOTE_D4, BPS::Two },
        // { NOTE_B3, BPS::Two },
        // { NOTE_A3, BPS::Two },
        // { NOTE_A3, BPS::One }, { NOTE_A3, BPS::Two },

        // // My Comforter, My All in All
        // { NOTE_D3, BPS::Two },
        // { NOTE_E3, BPS::Two },
        // { NOTE_G3, BPS::Four },
        // { NOTE_G3, BPS::Four },
        // { NOTE_G3, BPS::One }, { NOTE_G3, BPS::Two },

        // { NOTE_D3, BPS::Two },
        // { NOTE_E3, BPS::Two },
        // { NOTE_G3, BPS::Two },
        // { NOTE_A3, BPS::One }, { NOTE_A3, BPS::One },

        // { NOTE_B3, BPS::Two },
        // { NOTE_A3, BPS::Four },
        // { NOTE_G3, BPS::Four },
        // { NOTE_E3, BPS::Two },
        // { NOTE_B3, BPS::Two },
        // { NOTE_A3, BPS::One }, { NOTE_A3, BPS::Two },
        // { NOTE_G3, BPS::Two },
        // { NOTE_G3, BPS::One }, { NOTE_G3, BPS::Two },
    };

    constexpr const Song InChristAlone{IN_CHRIST_ALONE_NOTES, sizeof(IN_CHRIST_ALONE_NOTES) / sizeof(Note), 80, 0};

    // constexpr const Note BEFORE_THE_THRONE_NOTES[]
    // {
    //     // Verse One: Before the throne of God above
    //     { NOTE_A3, BPS::Two },
    //     { NOTE_D4, BPS::Two },
    //     { NOTE_E4, BPS::Two },
    //     { NOTE_F4, BPS::One },
    //     { NOTE_D4, BPS::One },
    //     { NOTE_B3, BPS::Two },
    //     { NOTE_D4, BPS::Two },
    //     { NOTE_D4, BPS::One }, { NOTE_D4, BPS::Two },

    //     // I have a strong and perfect plea
    //     { NOTE_A3, BPS::Two },
    //     { NOTE_D4, BPS::Two },
    //     { NOTE_E4, BPS::Two },
    //     { NOTE_F4, BPS::One },
    //     { NOTE_D4, BPS::One },
    //     { NOTE_F4, BPS::Two },
    //     { NOTE_A4, BPS::Two },
    //     { NOTE_A4, BPS::One }, { NOTE_A4, BPS::Two },

    //     //
    //     { NOTE_D4, BPS::Two },
    //     { NOTE_F4, BPS::Two },
    //     { NOTE_A4, BPS::Two },
    //     { NOTE_B4, BPS::One },
    //     { NOTE_A4, BPS::One },
    //     { NOTE_A4, BPS::One },
    //     { NOTE_E4, BPS::Two },
    //     { NOTE_F4, BPS::Two },
    //     { NOTE_D4, BPS::One }, { NOTE_D4, BPS::Two },
    //     { NOTE_D4, BPS::One }, // la care

    // };

    // constexpr const Song BeforeTheThrone { BEFORE_THE_THRONE_NOTES, sizeof(BEFORE_THE_THRONE_NOTES)/sizeof(Note), 68, 0 };

} // namespace Buzzer