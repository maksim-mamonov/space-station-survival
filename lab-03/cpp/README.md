# ЛР 3, часть 2. Умные указатели в C++

Проект ЛР 2 (космическая станция), в котором все обычные указатели заменены на
`std::unique_ptr`, `std::shared_ptr` и `std::weak_ptr`. В проекте нет ни одного `new` и `delete`.

## Файлы

- `oxygen_tank.hpp` / `oxygen_tank.cpp` — кислородный баллон.
- `life_support_module.hpp` / `life_support_module.cpp` — модуль жизнеобеспечения; баллон хранится как `std::weak_ptr` (агрегация).
- `space_station.hpp` / `space_station.cpp` — станция; модуль хранится полем по значению (композиция).
- `main.cpp` — демонстрация `unique_ptr`, `shared_ptr`, `weak_ptr`.

## Таблица владения

| Где был указатель | На что указывает | Кто владеет | Заменяется на | Почему |
|---|---|---|---|---|
| `LifeSupportModule::m_oxygenTank` (`OxygenTank*`) | внешний кислородный баллон | не модуль (агрегация), а тот, кто создал баллон | `std::weak_ptr<OxygenTank>` | модуль пользуется баллоном, но не владеет им; баллон может быть уничтожен раньше модуля, и `weak_ptr` позволяет это проверить через `lock()` |
| `main`: `externalTank` (`new OxygenTank(150, 100)`) | баллон вспомогательного отсека | `main`; временно ещё одна копия-владелец | `std::shared_ptr<OxygenTank>` | за баллоном наблюдает модуль, а `weak_ptr` можно получить только из `shared_ptr`; баллон должен жить, пока жив хотя бы один владелец |
| `main`: `stationTank` (`new OxygenTank(200, 100)`) | баллон станции «Мир-2» | `main` (вложенный блок) | `std::shared_ptr<OxygenTank>` | к нему подключён модуль станции через `weak_ptr`; вместо `delete` вызывается `reset()` |
| `main`: `tankArray[]` (`OxygenTank*[2]`) | массив баллонов | только `main` | `std::unique_ptr<OxygenTank>[2]` | один владелец, никто больше на баллоны не ссылается; освобождение автоматическое |
| `LifeSupportModule::ConnectOxygenTank(OxygenTank*)` (параметр) | передаваемый баллон | вызывающий код | `const std::shared_ptr<OxygenTank>&` | модуль сохраняет баллон в поле, поэтому обычный указатель здесь недопустим |
| `SpaceStation::m_lifeSupport` (поле по значению) | модуль жизнеобеспечения | станция (композиция) | не меняется | поле по значению — самый надёжный вид владения |

## Сборка и запуск (из папки `lab-03/cpp`)

GCC / MinGW:

```
g++ -std=c++17 -Wall -Wextra *.cpp -o lab03
./lab03
```

MSVC (Developer Command Prompt for Visual Studio):

```
cl /std:c++17 /EHsc /utf-8 *.cpp /Fe:lab03.exe
lab03.exe
```
