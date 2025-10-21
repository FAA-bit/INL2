# INL2
# Inlämningsuppgift 2.

Detta program är en vidareutveckling av inlämningsuppgift 1. Det samlar in, analyserar och presenterar temperaturvärden, nu med förbättrad struktur och funktionalitet.

## Funktioner
- Mata in mätvärden manuellt
- Simulera sensorvärden (slumpmässiga temperaturer)
- Visa statistik: medelvärde, min, max, standardavvikelse
- Sortera och söka efter värden
- Läsa och spara mätvärden till fil (`temperatures.csv`)

## Programstruktur
- `measurement.h`: innehåller `Measurement`-structen med `value` och `timestamp`
- `data_manager.h`: deklarerar klassen `DataManager` och dess metoder
- `data_manager.cpp`: implementerar all logik för datainsamling, analys och filhantering
- `INL2.cpp`: innehåller meny och styr programflödet

## Hur de arbetar tillsammans
INL2.cpp
 └── uses → DataManager (data_manager.h + .cpp)
         └── uses → Measurement (measurement.h)


  FAID ABSHIR ABDILE
