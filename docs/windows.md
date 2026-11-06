# Windows

Инструкция для Windows x64 с Visual Studio 2022. Команды выполняются
в PowerShell из корня репозитория.

## Зависимости

- Visual Studio 2022 или Build Tools 2022 с компонентами «Разработка классических
  приложений на C++», MSVC v143 и Windows SDK.
- CMake 3.21+ в `PATH` — эта версия нужна для генератора Visual Studio 2022.
- [SFML 2.6.2](https://www.sfml-dev.org/download/sfml/2.6.2/): пакет
  **Visual C++ 17 (2022), 64-bit**. SFML 3 не подходит.
- Графическая сессия и драйвер с поддержкой OpenGL.

Распакуйте SFML, например в `C:/Libraries/SFML-2.6.2`. В этой папке должны
находиться `bin/`, `include/` и `lib/`. Компилятор и архитектура пакета должны
соответствовать сборке проекта; подробнее — [инструкция SFML](https://www.sfml-dev.org/tutorials/2.6/getting-started/visual-studio/).

## Сборка

При другом расположении SFML измените значение `$sfml`:

```powershell
$sfml = "C:/Libraries/SFML-2.6.2"
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 "-DSFML_DIR=$sfml/lib/cmake/SFML"
cmake --build build --config Release --parallel 2
Copy-Item "$sfml/bin/*.dll" -Destination "./build/Release/"
```

DLL нужны рядом с исполняемыми файлами при запуске приложения и тестов.
Если `build/` уже создан другим генератором, используйте новый каталог сборки.

## Запуск

```powershell
./build/Release/ChessGame.exe
```

Левая кнопка мыши выводит координаты клетки в терминал. Закрытие окна
завершает приложение.

Изображения копируются в `build/assets/`, а абсолютный путь к ним записывается
в приложение. Один `.exe` без каталога ресурсов не является переносимой сборкой;
после переноса каталога сборки повторите настройку и сборку CMake.

## Тесты

```powershell
ctest --test-dir build -C Release --output-on-failure
```

Инструкция составлена по документации SFML и CMake; локально на Windows
сборка не проверялась.
