#include "GainProcessor.h"
// GainProcessor wird getestet, also muss er eingebunden werden.

#include <cassert>
// assert(...) ist eine einfache "Stopp, das stimmt nicht!" -Funktion.
// Wenn die Bedingung false ist, bricht das Programm ab.

#include <cmath>
// Für std::abs(), damit wir Unterschiede vergleichen können.

int main()
{
    // 1) Bauen des Test Objekts.
    GainProcessor gain;

    // 2) Wir setzen +6 dB.
    // In der Praxis bedeutet +6 dB ungefähr "fast doppelt so laut" (Amplitude ~*2).
    gain.setGainDb(6.0f);
    
    // 3) Wir geben ein Sample rein: 1.0
    float input = 1.0f;

    // 4) Wir verarbeiten es.
    float output = gain.processSample(input);

    // 5) Was erwarten wir?
    // +6 dB ist NICHT exakt 2.0, sondern ca. 1995.
    // Wir erlauben deshalb eine kleine Toleranz (0.05).
    float expected = 1.995f;
    float tolerance = 0.05f;

    // 6) Wenn das hier fehlschlägt, ist unsere dB->linear Formel falsch.
    assert(std::abs(output - expected) < tolerance);

    return 0;
}