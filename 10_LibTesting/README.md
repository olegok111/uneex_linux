Библиотека [growable-buf](https://github.com/skeeto/growable-buf) с обвязкой для autotools, libtool и тестирования с libcheck.

Сборка без сбора покрытия:
- `autoreconf -fisv && ./configure && make`

Сборка со сбором покрытия:
- `autoreconf -fisv && ./configure --enable-gcov && make`

Запуск тестов:
- После сборки, в директории tests `make check`

Просмотр покрытия:
- После запуска тестов, в директории src `make gcov`

Сделано по аналогии с [примером namegen](https://git.sr.ht/~frbrgeorge/namegen)
