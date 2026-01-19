#include "GainProcessor.h"
// Damit sagen wir:
// "Ich implementiere das, was im Header beschrieben ist."

#include <cmath>
// <cmath> enthält mathematische Funktionen wie pow()
// Die brauchen wir für die dB-Umrechnung (dB -> linear).

void GainProcessor::prepare(double sampleRate)
{
    // Wird EINMAL vor der Audioverarbeitung aufgerufen.
    // Wir speichern die Samplerate, weil Smoothing pro Sample arbeitet.
    sampleRate_ = sampleRate;

    // Wenn sich die Samplerate ändert, müssen wir unsere Schrittweite neu berechnen.
    updateStep();
}

void GainProcessor::setSmoothingTimeMs(float timeMs)
{
    // Schutz: 0 oder negative Werte würden zu Division durch 0 / Unsinn führen.
    // Also zwingen wir einen Minimalwert.
    if (timeMs < 1.0f)
        timeMs = 1.0f;

    smoothingTimeMs_ = timeMs;

    // Smoothing hängt von der Zeit ab -> Schrittweite neu berechnen.
    updateStep();
}

void GainProcessor::setGainDb(float gainDb)
{
    // Dezibel (dB) sind eine logarithmische Skala.
    // Computer rechnen aber linear.
    //
    // Formel:
    // linear = 10^(dB / 20)
    //
    // Beispiele:
    // 0 dB     -> 1.0
    // +6 dB    -> ~1.995
    // -6 dB    -> ~0.501

    // Früher hatten wir nur EINEN Gain-Wert (gainLinear_) und haben ihn sofort gesetzt.
    // Das ist für Audio schlecht, weil Sprünge im Gain "Klicks" verursachen.
    //
    // OBSOLET (nicht mehr benötigt):
    // gainLinear_ = std::pow(10.0f, gainDb / 20.0f);
    // -> Warum obsolet? Wir haben jetzt targetLinear_ und currentLinear_:
    //    setGainDb setzt nur das Ziel (target), und current läuft langsam dahin.

    targetLinear_ = std::pow(10.0f, gainDb / 20.0f);
}

void GainProcessor::updateStep()
{
    // Wir wollen, dass currentLinear_ innerhalb von smoothingTimeMs_ ms
    // "ungefähr" beim targetLinear_ ankommt.
    //
    // Dafür berechnen wir eine einfache Schrittweite pro Sample.
    //
    // Anzahl Samples in der Smoothing-Zeit:
    // samples = sampleRate * (ms / 1000)
    //
    // Und dann nutzen wir eine einfache Annäherung:
    // current += (target - current) * step
    // step = 1 / samples

    const double timeSeconds = smoothingTimeMs_ / 1000.0;
    const double samples = sampleRate_ * timeSeconds;

    if (samples <= 1.0)
    {
        // Extrem schnell -> quasi sofort.
        step_ = 1.0f;
        return;
    }

    step_ = static_cast<float>(1.0 / samples);
}

float GainProcessor::processSample(float input)
{
    // Früher war processSample() const und hat nur multipliziert.
    //
    // OBSOLET (nicht mehr benötigt):
    // float GainProcessor::processSample(float input) const
    // {
    //     return input * gainLinear_;
    // }
    //
    // -> Warum obsolet? Weil Smoothing den internen Zustand verändert (currentLinear_).
    //    Eine const-Funktion dürfte das nicht. Außerdem benutzen wir nicht mehr gainLinear_.

    // Smoothing: currentLinear_ bewegt sich pro Sample ein Stück Richtung targetLinear_.
    currentLinear_ += (targetLinear_ - currentLinear_) * step_;

    // Gain anwenden (mit dem geglätteten aktuellen Gain).
    return input * currentLinear_;
}
