#include "GainProcessor.h"
// Damit sagen wir:
// "Ich implementiere das, was im Header beschrieben ist."

#include <cmath>
// <cmath> enthält mathematische Funktionen wie pow()
// Die brauchen wir gleich für die dB-Umrechnung.

void GainProcessor::setGainDb(float gainDb)
{
    // Dezibel (dB) sind eine logarithmische Skala.
    // Computer rechnen aber linear.
    // Formel:
    // linear = 10^(dB / 20)
    // 
    // Beispiele:
    // 0 dB     -> 1.0
    // +6 dB    -> ~1.995
    // -6 dB    -> ~0.501

    gainLinear_= std::pow(10.0f, gainDb / 20.0f);
}

float GainProcessor::processSample(float input) const
{
    // Ein Audio-Sample ist einfach eine Zahl.
    // Gain anwenden heißt: Zahl * Verstärkung.

    return input * gainLinear_;
}