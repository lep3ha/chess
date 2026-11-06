# Ubuntu

Инструкция для Ubuntu 24.04. Все команды сборки и запуска выполняются
из корня репозитория.

## Зависимости

Нужны компилятор C++17, CMake 3.16+, SFML 2.5–2.6 и графическая сессия
с доступом к X11/XWayland и OpenGL. SFML 3 не подходит.

```sh
sudo apt-get update
sudo apt-get install build-essential cmake libsfml-dev
```

Ubuntu 24.04 предоставляет [SFML 2.6.1](https://packages.ubuntu.com/noble/libsfml-dev).

## Сборка

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel 2
```

## Запуск

Из терминала графического рабочего стола:

```sh
./build/ChessGame
```

Левая кнопка мыши выводит координаты клетки в терминал. Закрытие окна
завершает приложение.

В SSH-сессии нужен локальный X-сервер на компьютере и подключение
`ssh -X user@server`. На сервере требуются `xauth` и разрешённое
`X11Forwarding`. SSH сам задаёт `DISPLAY`; вручную выставлять `DISPLAY=:0`
не нужно. Подробнее — [OpenSSH](https://man.openbsd.org/ssh#X).
При пустом `DISPLAY` приложение завершается с пояснением; при заданном,
но недоступном дисплее SFML может аварийно завершиться.

CMake копирует изображения в `build/assets/`; путь к ним записывается
в приложение. После переноса каталога сборки проект нужно пересобрать
с повторной настройкой CMake.

## Тесты

В графической сессии:

```sh
ctest --test-dir build --output-on-failure
```

На сервере без экрана:

```sh
sudo apt-get install xvfb xauth
xvfb-run -a ctest --test-dir build --output-on-failure
```

Xvfb создаёт виртуальный дисплей и не показывает окно на вашем компьютере.
Только тесты модели можно запускать без дисплея:

```sh
ctest --test-dir build -R '^model_tests$' --output-on-failure
```

Сборка и тесты проверены на Ubuntu 24.04 с GCC 13 и SFML 2.6.1.
