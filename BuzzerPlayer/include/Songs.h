#pragma once

#include "Sound.h"

namespace Buzzer
{
    // In Christ Alone
    constexpr const Note IN_CHRIST_ALONE_NOTES[]
    {
        // Verse One
        // In Christ Alone
        { NoteFrequency::NOTE_D3, BPS::Two },
        { NoteFrequency::NOTE_E3, BPS::Two },
        { NoteFrequency::NOTE_G3, BPS::Four },
        { NoteFrequency::NOTE_G3, BPS::Four },
        { NoteFrequency::NOTE_G3, BPS::One },
        { NoteFrequency::NOTE_G3, BPS::Two },

        // My hope is found
        { NoteFrequency::NOTE_D3, BPS::Two },
        { NoteFrequency::NOTE_E3, BPS::Two },
        { NoteFrequency::NOTE_G3, BPS::Two },
        { NoteFrequency::NOTE_A3, BPS::One },
        { NoteFrequency::NOTE_A3, BPS::One },

        // He is my light, my strength, my song
        { NoteFrequency::NOTE_B3, BPS::Two },
        { NoteFrequency::NOTE_A3, BPS::Four },
        { NoteFrequency::NOTE_G3, BPS::Four },
        { NoteFrequency::NOTE_E3, BPS::Two },
        { NoteFrequency::NOTE_B3, BPS::Two },
        { NoteFrequency::NOTE_A3, BPS::One },
        { NoteFrequency::NOTE_A3, BPS::Two },
        { NoteFrequency::NOTE_G3, BPS::Two },
        { NoteFrequency::NOTE_G3, BPS::One },
        { NoteFrequency::NOTE_G3, BPS::Two },

        // This cornerstone, this solid ground
        { NoteFrequency::NOTE_D3, BPS::Two },
        { NoteFrequency::NOTE_E3, BPS::Two },
        { NoteFrequency::NOTE_G3, BPS::Four },
        { NoteFrequency::NOTE_G3, BPS::Four },
        { NoteFrequency::NOTE_G3, BPS::One },
        { NoteFrequency::NOTE_G3, BPS::Two },

        { NoteFrequency::NOTE_D3, BPS::Two },
        { NoteFrequency::NOTE_E3, BPS::Two },
        { NoteFrequency::NOTE_G3, BPS::Two },
        { NoteFrequency::NOTE_A3, BPS::One },
        { NoteFrequency::NOTE_A3, BPS::One },

        // Firm through the fiercest drought and storm
        { NoteFrequency::NOTE_B3, BPS::Two },
        { NoteFrequency::NOTE_A3, BPS::Four },
        { NoteFrequency::NOTE_G3, BPS::Four },
        { NoteFrequency::NOTE_E3, BPS::Two },
        { NoteFrequency::NOTE_B3, BPS::Two },
        { NoteFrequency::NOTE_A3, BPS::One },
        { NoteFrequency::NOTE_A3, BPS::Two },
        { NoteFrequency::NOTE_G3, BPS::Two },
        { NoteFrequency::NOTE_G3, BPS::One },
        { NoteFrequency::NOTE_G3, BPS::Two },

        /*
        // Chorus: What heights of love, What depths of peace
        { NoteFrequency::NOTE_G3, BPS::Two },
        { NoteFrequency::NOTE_B3, BPS::Two },
        { NoteFrequency::NOTE_D4, BPS::Two },
        { NoteFrequency::NOTE_E4, BPS::One }, { NOTE_E4, BPS::Two },
        { NoteFrequency::NOTE_E4, BPS::Two },
        { NoteFrequency::NOTE_D4, BPS::Two },
        { NoteFrequency::NOTE_B3, BPS::Two },
        { NoteFrequency::NOTE_A3, BPS::Two },
        { NoteFrequency::NOTE_A3, BPS::One }, { NOTE_A3, BPS::Two },

        { NoteFrequency::NOTE_G3, BPS::Two },
        { NoteFrequency::NOTE_G4, BPS::Two },
        { NoteFrequency::NOTE_FS4, BPS::Two },
        { NoteFrequency::NOTE_E4, BPS::One }, { NOTE_E4, BPS::Two },
        { NoteFrequency::NOTE_E4, BPS::Two },
        { NoteFrequency::NOTE_D4, BPS::Two },
        { NoteFrequency::NOTE_B3, BPS::Two },
        { NoteFrequency::NOTE_A3, BPS::Two },
        { NoteFrequency::NOTE_A3, BPS::One }, { NOTE_A3, BPS::Two },

        // My Comforter, My All in All
        { NoteFrequency::NOTE_D3, BPS::Two },
        { NoteFrequency::NOTE_E3, BPS::Two },
        { NoteFrequency::NOTE_G3, BPS::Four },
        { NoteFrequency::NOTE_G3, BPS::Four },
        { NoteFrequency::NOTE_G3, BPS::One }, { NOTE_G3, BPS::Two },

        { NoteFrequency::NOTE_D3, BPS::Two },
        { NoteFrequency::NOTE_E3, BPS::Two },
        { NoteFrequency::NOTE_G3, BPS::Two },
        { NoteFrequency::NOTE_A3, BPS::One }, { NOTE_A3, BPS::One },

        { NoteFrequency::NOTE_B3, BPS::Two },
        { NoteFrequency::NOTE_A3, BPS::Four },
        { NoteFrequency::NOTE_G3, BPS::Four },
        { NoteFrequency::NOTE_E3, BPS::Two },
        { NoteFrequency::NOTE_B3, BPS::Two },
        { NoteFrequency::NOTE_A3, BPS::One }, { NOTE_A3, BPS::Two },
        { NoteFrequency::NOTE_G3, BPS::Two },
        { NoteFrequency::NOTE_G3, BPS::One }, { NOTE_G3, BPS::Two },
        */
    };

    constexpr const Song InChristAlone{ IN_CHRIST_ALONE_NOTES, sizeof(IN_CHRIST_ALONE_NOTES) / sizeof(Note), 80, 0 };

    /* // Before the Throne of God Above
    constexpr const Note BEFORE_THE_THRONE_NOTES[]
    {
        // Verse One: Before the throne of God above
        { NoteFrequency::NOTE_A3, BPS::Two },
        { NoteFrequency::NOTE_D4, BPS::Two },
        { NoteFrequency::NOTE_E4, BPS::Two },
        { NoteFrequency::NOTE_F4, BPS::One },
        { NoteFrequency::NOTE_D4, BPS::One },
        { NoteFrequency::NOTE_B3, BPS::Two },
        { NoteFrequency::NOTE_D4, BPS::Two },
        { NoteFrequency::NOTE_D4, BPS::One }, { NoteFrequency::NOTE_D4, BPS::Two },

        // I have a strong and perfect plea
        { NoteFrequency::NOTE_A3, BPS::Two },
        { NoteFrequency::NOTE_D4, BPS::Two },
        { NoteFrequency::NOTE_E4, BPS::Two },
        { NoteFrequency::NOTE_F4, BPS::One },
        { NoteFrequency::NOTE_D4, BPS::One },
        { NoteFrequency::NOTE_F4, BPS::Two },
        { NoteFrequency::NOTE_A4, BPS::Two },
        { NoteFrequency::NOTE_A4, BPS::One }, { NoteFrequency::NOTE_A4, BPS::Two },

    
        { NoteFrequency::NOTE_D4, BPS::Two },
        { NoteFrequency::NOTE_F4, BPS::Two },
        { NoteFrequency::NOTE_A4, BPS::Two },
        { NoteFrequency::NOTE_B4, BPS::One },
        { NoteFrequency::NOTE_A4, BPS::One },
        { NoteFrequency::NOTE_A4, BPS::One },
        { NoteFrequency::NOTE_E4, BPS::Two },
        { NoteFrequency::NOTE_F4, BPS::Two },
        { NoteFrequency::NOTE_D4, BPS::One }, { NoteFrequency::NOTE_D4, BPS::Two },
        { NoteFrequency::NOTE_D4, BPS::One }, // la care

    };

    constexpr const Song BeforeTheThrone { BEFORE_THE_THRONE_NOTES, sizeof(BEFORE_THE_THRONE_NOTES)/sizeof(Note), 68, 0 };
    */
} // namespace Buzzer