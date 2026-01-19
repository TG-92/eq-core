#include "GainProcessor.h"
// GainProcessor wird getestet, also muss er eingebunden werden.

#include <cassert>
// assert(...) ist eine einfache "Stopp, das stimmt nicht!"-Funktion.
// Wenn die Bedingung false ist, bricht das Programm ab.

#include <cmath>
// Für std::abs(), damit wir Unterschiede vergleichen können.

int main()
{
    // 1) Bauen des Test-Objekts.
    GainProcessor gain;

    // NEU: Wir müssen prepare() aufrufen, weil Smoothing von der Samplerate abhängt.
    gain.prepare(44100.0);

    // Optional: Wir machen das Smoothing hier sehr schnell,
    // damit der Test nicht lange "warten" muss, bis er am Ziel ist.
    gain.setSmoothingTimeMs(1.0f);

    // 2) Wir setzen +6 dB (ZIELwert).
    // In der Praxis bedeutet +6 dB ungefähr "fast doppelt so laut" (Amplitude ~*2).
    gain.setGainDb(6.0f);

    // 3) Wir geben ein Sample rein: 1.0
    float input = 1.0f;

    // Früher (ohne Smoothing) hat EIN Sample gereicht, weil der Gain sofort gesprungen ist.
    //
    // OBSOLET (nicht mehr benötigt):
    // float output = gain.processSample(input);
    //
    // -> Warum obsolet? Mit Smoothing nähert sich currentLinear_ langsam an targetLinear_ an.
    //    Deshalb lassen wir mehrere Samples "durchlaufen", damit er am Ziel ankommt.

    float output = 0.0f;
    for (int i = 0; i < 5000; ++i)
    {
        output = gain.processSample(input);
    }

    // 5) Was erwarten wir?
    // +6 dB ist NICHT exakt 2.0, sondern ca. 1.995.
    // Wir erlauben deshalb eine kleine Toleranz.
    float expected = 1.995f;
    float tolerance = 0.05f;

    // 6) Wenn das hier fehlschlägt, stimmt dB->linear nicht ODER smoothing läuft nie ans Ziel.
    assert(std::abs(output - expected) < tolerance);

    return 0;
}
