# macOS

Команды выполняются в Terminal из корня репозитория.

## Зависимости

Нужны Apple Clang с поддержкой C++17, CMake 3.16+, SFML 2.5–2.6
и графическая сессия macOS.

Установите Command Line Tools и дождитесь завершения установки:

```sh
xcode-select --install
```

Установите [Homebrew](https://brew.sh/), затем CMake и
[SFML 2](https://formulae.brew.sh/formula/sfml@2):

```sh
brew install cmake sfml@2
```

Нужен именно `sfml@2`: проект не совместим с SFML 3.
Homebrew, компилятор и библиотека должны использовать одну архитектуру:
arm64 на Apple Silicon или x86_64 на Intel.

## Сборка

Версия `sfml@2` устанавливается отдельно от основной версии, поэтому путь
к её CMake-пакету передаётся явно:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release "-DSFML_DIR=$(brew --prefix sfml@2)/lib/cmake/SFML"
cmake --build build --parallel 2
```

## Запуск

Запускайте из Terminal в графической сессии macOS:

```sh
./build/ChessGame
```

Левая кнопка мыши выводит координаты клетки в терминал. Закрытие окна
завершает приложение.

CMake копирует изображения в `build/assets/`; путь к ним записывается
в приложение. После переноса каталога сборки повторите настройку и сборку CMake.
Приложение использует установленные библиотеки Homebrew; `.app`-пакет не создаётся.

## Тесты

```sh
ctest --test-dir build --output-on-failure
```

Инструкция составлена по документации Homebrew и SFML; локально на macOS
сборка не проверялась.
