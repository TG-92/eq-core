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

    void setGainDb(float gainDb);
    // Wir setzen den Gain in dB (Decibel), weil Menschen in dB denken.
    // Intern speichern wir aber später die lineare Zahl (weil der Computer so rechnet).

    float processSample(float input) const;
    // Nimmt EIN Sample (eine Zahl) und gibt das veränderte Sample zurück.
    // "const" heißt: diese FUnktion verändert das Objekt NICHT.
    // Das ist wichtig für Audio-Denken: process darf keine überraschenden Nebenwirkungen haben.

private:
    float gainLinear_= 1.0f;
    // Das ist der interne Zustand:
    // 1.0 bedeutet "keine Änderung".
    // Wenn wir +6 dB setzen, wird daraus ungefähr 1.995.
};