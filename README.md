# Projekt MES 2025 — Symulacja przewodzenia ciepła (C++17 + Qt6)

Symulator przewodzenia ciepła metodą elementów skończonych (MES) na siatkach czworokątnych. Aplikacja desktopowa z GUI w Qt6; część numeryczna w czystym C++17.

**Język:** C++17
**Framework:** Qt 6 (Widgets)
**System:** Windows (MinGW-w64)

## Funkcje
- Obliczenia MES dla elementów 4‑węzłowych: funkcje kształtu, macierz Jacobiego, lokalne macierze `H`, `Hbc`, `C` oraz wektor `P`.
- Całkowanie Gaussa w 2D (np. 2×2, 3×3, 4×4 punkty) — wybór przez parametr `NPC` (kompilacyjnie).
- Montaż macierzy globalnych i rozwiązywanie iteracyjne `SystemOfEquation::solveSimulation()` po krokach czasowych. Wyniki widoczne w konsoli.
- GUI do wyboru siatki: gotowe testy oraz przycisk „Własna” (plik `.txt`).
- Podgląd podstawowych danych globalnych (czas symulacji, krok, własności materiału, `nE`, `nN`, `npc`).

## Struktura projektu
- forms/
	- `mainwindow.ui` — interfejs Qt (Qt Designer)
- grids/
	- `Test1_4_4.txt`, `Test2_4_4_MixGrid.txt`, `Test3_31_31_kwadrat.txt` — przykładowe siatki
- include/
	- `mainwindow.h`, `grid.h`, `functions.h`, `GaussTable.h`, `readFromFile.h` — nagłówki
- src/
	- `main.cpp`, `mainwindow.cpp` — start aplikacji i GUI
	- `grid.cpp` — implementacja struktur MES i montaż globalny
	- `GaussTable.cpp` — tablice i całkowanie Gaussa
	- `functions.cpp` — funkcje podcałkowe i pomocnicze
	- `readFromFile.cpp` — wczytywanie siatek/parametrów z pliku
- `projekt-MES-2025.pro` — plik projektu qmake

## Uruchomienie
- Wyodrębnij zawartość `app.zip`. Uruchom aplikację `app/release/app.exe`. W panelu „WCZYTAJ SIATKĘ” wybierz jedną z siatek testowych lub „Własna”, aby wskazać własny plik `.txt`.
- Po wczytaniu wypełniane są pola „DANE GLOBALNE” (czas, krok, `nE`, `nN`, `npc`, itd.).
- Symulacja uruchamia się po wyborze siatki; wartości są aktualizowane w UI, a rozwiązanie symulacji jest wyświetlane w konsoli.

## Format pliku siatki
- Pliki w folderze `grids/` są przykładami wejścia. Zawierają parametry globalne oraz węzły i elementy.
- Własny plik powinien odwzorowywać strukturę tych testów (ten sam porządek pól; patrz implementacja `readFromFile.cpp`).