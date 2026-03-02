# IZP Projekt 1 – keyfilter

Nástroj, ktorý filtruje názvy miest podľa prefixu (reťazca zadaného ako argument programu) a:
- ak nájde presne jeden záznam, vypíše `Found: <MESTO>`,
- ak nájde viac záznamov, vypíše zoznam povolených znakov (`Enable: ...`) na ďalšej pozícii po zadanom prefixe,
- ak nenájde nič, vypíše `Not found`.

Projekt vznikol v rámci predmetu IZP (FIT VUT), akademický rok 2023/2024.

## Vstup a výstup
- **Vstup:** každý riadok na štandardnom vstupe obsahuje jeden názov mesta (max. 100 znakov). Diakritika sa neočakáva. Súbor `adresy.txt` obsahuje ukážkový zoznam slovenských miest.
- **Argument programu:** voliteľný reťazec predstavujúci hľadaný prefix. Bez argumentu sa použije prázdny reťazec, takže sa vyhodnocuje prvý znak každej položky.
- **Výstup:** jedna z troch hlášok:
  - `Found: <MESTO>` – ak existuje presne jedna zhoda, vypíše sa celé mesto veľkými písmenami.
  - `Enable: <ZNÁKY>` – ak zodpovedá viacero miest, vypíšu sa povolené znaky na nasledujúcej pozícii po prefixe (zjednotenie znakov všetkých zhôd).
  - `Not found` – ak žiadne mesto nevyhovuje.

Program je case‑insensitive: interné spracovanie konvertuje vstup aj argument na veľké písmená.

## Požiadavky
- GCC 11+ alebo iný C11 kompatibilný prekladač.
- Bash (na spustenie testovacieho skriptu).
- Voliteľne CMake 3.26+ pre pohodlnejšie zostavenie.

## Preloženie
Rýchly preklad priamo z príkazovej riadky:
```bash
gcc -std=c11 -Wall -Wextra -Werror keyfilter.c -o keyfilter
```

Alebo pomocou CMake:
```bash
cmake -S . -B build
cmake --build build
./build/IZP_Projekt1        # spustiteľný súbor
```

## Spustenie
```bash
./keyfilter <adresy.txt             # bez prefixu – vyhodnotí prvý znak
./keyfilter br <adresy.txt          # prefix "br"
./keyfilter "NIT" < adresy.txt      # prefix "NIT"
```

### Rýchle príklady
Pri vstupe:
```
Praha
Brno
Bratislava
Bruntal
```

- `./keyfilter br < vstup.txt` → `Enable: ANU`
- `./keyfilter brn < vstup.txt` → `Found: BRNO`
- `./keyfilter z < vstup.txt`   → `Not found`

## Testy
K dispozícii je jednoduchý Bash skript `test_keyfilter.sh`, ktorý generuje testovacie vstupy a porovnáva očakávané výstupy.

Spustenie:
```bash
chmod +x test_keyfilter.sh
./test_keyfilter.sh
```

Skript prekladá binárku pomocou GCC, spúšťa sériu testov (vrátane prázdneho argumentu a špeciálnych znakov) a zobrazí **PASSED** alebo **FAILED** pre každú kombináciu.

## Štruktúra repozitára
- `keyfilter.c` – zdrojový kód programu.
- `CMakeLists.txt` – konfigurácia pre CMake build.
- `adresy.txt` – ukážkový vstup s mestami.
- `test_keyfilter.sh` – automatizované testy.

## Obmedzenia a poznámky
- Konštanty `MAX_CITIES` (1000) a `MAX_LINE_LENGTH` (101) limitujú počet riadkov a dĺžku názvu; pri väčších vstupoch upravte hodnoty v zdrojáku.
- Program pracuje iba s ASCII znakmi; prípadné diakritické znaky sa neprevádzajú.

