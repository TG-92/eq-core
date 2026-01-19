cmake_minimum_required(VERSION 3.20)
# Mindestversion: damit moderne Features sicher funtionieren.

project(eq_core LANGUAGES CXX)
# Projektname: eq_core
# Ausdrückliche Beschreibung als C++ Projekt.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Wir nutzen C++20. "REQUIRED" heißt: bitte nicht auf älteres runterfallen.

# 1) Unsere Library (das ist der "DSP-Core")
add_library(eq_core
    src/GainProcessor.cpp
)
# add_library baut eine wiederverwendbare Code-Einheit.
# Momentan nur GainProcessor vorhanden, später werden Filter hinzugefügt.

target_include_directories(eq_core PUBLIC src)
# Damit dürfen andere Targets (z.B. Tests) "GainProcessor.h" finden.
# PUBLIC heißt: "auch für Nutzer sichtbar".

# 2) Unser Test-Programm (eine kleine EXE)
add_executable(eq_core_tests
    tests/test_gain.cpp
)
# add_executable baut ein Programm, das wir ausführen können.

target_link_libraries(eq_core_tests PRIVATE eq_core)
# Unser Test-Programm benutzt die Library eq_core.
# PRIVATE heißt: nur dieses Target braucht das Linken.