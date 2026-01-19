#pragma once
// "pragma once" sagt dem Compiler:
// "Wenn diese Datei schon einmal eingebunden wurde, nimm sie nicht nochmal."
// Damit vermeiden wir doppelte Definitionen.

class GainProcessor
{
public:
    GainProcessor() = default;
    // Konstruktor: wird aufgerufen, wenn wir ein Objekt erstellen.
    // "= default" heißt: "nimm die Standard-Version, ich brauche nichts Besonderes."

    void prepare(double sampleRate);
    // Wird EINMAL vor der Audioverarbeitung aufgerufen.
    // Wir speichern die Samplerate, weil Smoothing "pro Sample" arbeitet.

    void setGainDb(float gainDb);
    // Wir setzen den Gain in dB (Decibel), weil Menschen in dB denken.
    // Intern speichern wir aber später die lineare Zahl (weil der Computer so rechnet).

    void setSmoothingTimeMs(float timeMs);
    // Wie lange (in Millisekunden) soll es dauern,
    // bis der aktuelle Gain den Ziel-Gain erreicht?
    // Größer = sanfter, kleiner = schneller.

    float processSample(float input);
    // Nimmt EIN Sample (eine Zahl) und gibt das veränderte Sample zurück.
    // "const" heißt: diese FUnktion verändert das Objekt NICHT.
    // Das ist wichtig für Audio-Denken: process darf keine überraschenden Nebenwirkungen haben.

private:
    // === Gain-Zustand (linear, nicht dB!) ===

    float targetLinear_ = 1.0f;
    // Wohin wir wollen (Zielwert).

    float currentLinear_ = 1.0f;
    // Wo wir gerade sind (aktueller Wert).

    // === Smoothing-Parameter ===
    
    double sampleRate_ = 44100.0; 
    // Wird in prepare() gesetzt.
    float smoothingTimeMs_ = 20.0f;
    // Standard: 20 ms -> kurzer, aber hörbar weicher Übergang.
    float step_ = 0.0f;
    // Wie viel wir pro Sample Richtung ziel gehen.

    void updateStep();
    //Berechnet step_ neu, wenn sich Samplerate
    // oder Smoothing-Zeit ändern.
};