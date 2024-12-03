
Сборка (перевод предоставлен локально):
- `autoreconf -fisv && ./configure --localedir=$PWD && make`

Запуск:
- `./guess` или `LANG=ru_RU.utf8 ./guess` на русском языке

Обновление перевода:
- `make -C po update-po`, затем `make` после исправления перевода (т.е. удаления fuzzy).

Сделано на основе [примера с gettext](https://git.sr.ht/~frbrgeorge/simple-gettext/tree/master)
