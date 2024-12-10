
Сборка (перевод предоставлен локально):
- `autoreconf -fisv && ./configure --localedir=$PWD && make`

Запуск http-сервера с doxygen (после сборки):
- `make http`

Просмотр man-страницы (после сборки):
- `man ./doxygen-doc/man/man1/guess.1`

Поддерживается запуск игры с римскими цифрами (`./guess -r`) и/или на русском языке (`LANG=ru_RU.utf8 ./guess ...`).