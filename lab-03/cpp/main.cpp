#include <clocale>
#include <cstdlib>
#include <iostream>
#include <memory>
#include "oxygen_tank.hpp"
#include "life_support_module.hpp"
#include "space_station.hpp"

// Псевдоним пространства имен используется только в main.cpp
// (в .hpp файлах using namespace запрещен)
using namespace space_station;

int main()
{
#ifdef _WIN32
    // Установка кодовой страницы UTF-8 для корректного отображения кириллицы в консоли Windows
    std::system("chcp 65001 > nul");
#endif
    std::setlocale(LC_ALL, "Russian");

    std::cout << "=== СТАРТ ДЕМОНСТРАЦИОННОЙ ПРОГРАММЫ КОСМИЧЕСКОЙ СТАНЦИИ (ЛР 3, УМНЫЕ УКАЗАТЕЛИ) ===\n\n";

    // ==========================================
    // ПУНКТ 1: Агрегация через shared_ptr + weak_ptr
    // Баллоном владеет main (shared_ptr), модуль только наблюдает за ним (weak_ptr)
    // ==========================================
    std::cout << "--- 1. АГРЕГАЦИЯ: ВЛАДЕЛЕЦ SHARED_PTR, НАБЛЮДАТЕЛЬ WEAK_PTR ---\n";

    std::shared_ptr<OxygenTank> externalTank = std::make_shared<OxygenTank>(150, 100.0);
    std::cout << "externalTank.use_count() = " << externalTank.use_count() << "\n";

    LifeSupportModule manualModule("Вспомогательный отсек");
    manualModule.ConnectOxygenTank(externalTank);
    std::cout << "После подключения к модулю use_count() = " << externalTank.use_count()
        << " (weak_ptr не увеличивает счётчик)\n";

    manualModule.StartModule();
    manualModule.ConsumeModuleOxygen(30.0);

    std::cout << "\n";

    // ==========================================
    // ПУНКТ 2: Проверка правил (сначала успех, потом отказ)
    // ==========================================
    std::cout << "--- 2. ПРОВЕРКА ПРАВИЛ (УСПЕХ И ОТКАЗ) ---\n";

    externalTank->ConsumeOxygen(20.0);

    std::cout << "[Тест нарушения 1]: Попытка потратить 200% кислорода...\n";
    externalTank->ConsumeOxygen(200.0);

    LifeSupportModule emptyModule("Пустой отсек без баллона");
    std::cout << "[Тест нарушения 2]: Попытка запустить модуль без баллона...\n";
    emptyModule.StartModule();

    std::cout << "\n";

    // ==========================================
    // ПУНКТ 3: Композиция и weak_ptr после уничтожения объекта
    // ==========================================
    std::cout << "--- 3. КОМПОЗИЦИЯ И WEAK_PTR ПОСЛЕ УНИЧТОЖЕНИЯ БАЛЛОНА ---\n";
    {
        std::cout << "--> Вход во вложенный блок (создаем станцию 'Мир-2')...\n";

        // Модуль жизнеобеспечения создается внутри станции (композиция, поле по значению)
        SpaceStation station("Мир-2", "Центральный жизнеобеспечивающий узел");

        std::shared_ptr<OxygenTank> stationTank = std::make_shared<OxygenTank>(200, 100.0);
        station.ConnectOxygenTank(stationTank);
        station.ActivateStation();
        station.PerformLifeSupportCheck(40.0);

        // Вместо delete: последний владелец отказывается от баллона, и баллон уничтожается сразу
        std::cout << "--> stationTank.reset(): единственный владелец отказывается от баллона\n";
        stationTank.reset();

        // В ЛР 2 здесь модуль хранил бы висячий указатель. weak_ptr::lock() вернет пустой указатель.
        std::cout << "--> Повторная проверка жизнеобеспечения после уничтожения баллона:\n";
        station.PerformLifeSupportCheck(10.0);

        std::cout << "--> Выход из вложенного блока (станция сейчас уничтожится)...\n";
    }

    std::cout << "\n";

    // ==========================================
    // ПУНКТ 4: unique_ptr — единственный владелец, передача владения через std::move
    // ==========================================
    std::cout << "--- 4. UNIQUE_PTR: УНИЧТОЖЕНИЕ ПРИ ВЫХОДЕ ИЗ БЛОКА ---\n";
    {
        std::cout << "--> Вход в блок\n";
        std::unique_ptr<OxygenTank> spareTank = std::make_unique<OxygenTank>(80, 100.0);
        spareTank->ConsumeOxygen(15.0);
        std::cout << "--> Выход из блока (delete не вызывается)\n";
    }

    std::cout << "\n--- 4.1. UNIQUE_PTR: МАССИВ БАЛЛОНОВ И ПЕРЕДАЧА ВЛАДЕНИЯ ---\n";
    {
        constexpr int kTankCount = 2;
        std::unique_ptr<OxygenTank> tankArray[kTankCount] = {
            std::make_unique<OxygenTank>(100, 50.0),
            std::make_unique<OxygenTank>(120, 80.0)
        };

        std::cout << "Использование массива баллонов:\n";
        for (int i = 0; i < kTankCount; ++i)
        {
            std::cout << "Баллон #" << i + 1 << " уровень: " << tankArray[i]->GetOxygenLevel() << "%\n";
        }

        std::cout << "Передаем баллон #1 новому владельцу через std::move...\n";
        std::unique_ptr<OxygenTank> transferredTank = std::move(tankArray[0]);

        for (int i = 0; i < kTankCount; ++i)
        {
            if (tankArray[i])
            {
                std::cout << "tankArray[" << i << "] владеет баллоном емкостью " << tankArray[i]->GetCapacity() << "\n";
            }
            else
            {
                std::cout << "tankArray[" << i << "] пуст: владение передано\n";
            }
        }
        std::cout << "transferredTank владеет баллоном емкостью " << transferredTank->GetCapacity() << "\n";

        std::cout << "--> Выход из блока: баллоны уничтожаются в обратном порядке объявления\n";
    }

    std::cout << "\n";

    // ==========================================
    // ПУНКТ 5: shared_ptr — счётчик владельцев
    // ==========================================
    std::cout << "--- 5. SHARED_PTR: СЧЁТЧИК ВЛАДЕЛЬЦЕВ ---\n";
    std::cout << "externalTank.use_count() = " << externalTank.use_count() << "\n";
    {
        std::shared_ptr<OxygenTank> inspectorCopy = externalTank;
        std::cout << "После копирования указателя use_count() = " << externalTank.use_count() << "\n";
        std::cout << "--> Выход из блока: копия уничтожается\n";
    }
    std::cout << "После уничтожения копии use_count() = " << externalTank.use_count() << "\n\n";

    std::cout << "--- 5.1. ОБЪЕКТ ЖИВЕТ, ПОКА ЖИВ ХОТЯ БЫ ОДИН ВЛАДЕЛЕЦ ---\n";
    {
        std::shared_ptr<OxygenTank> backupOwner = externalTank;
        std::cout << "Владельцев: " << backupOwner.use_count() << "\n";

        externalTank.reset();
        std::cout << "externalTank.reset(): владельцев осталось " << backupOwner.use_count()
            << ", баллон еще жив\n";

        // Модуль уничтожается в конце main, но внешний баллон живет независимо от него
        manualModule.ConsumeModuleOxygen(10.0);
        std::cout << "Проверка баллона напрямую через backupOwner. Уровень кислорода: "
            << backupOwner->GetOxygenLevel() << "%\n";

        std::cout << "--> Выход из блока: уничтожается последний владелец backupOwner\n";
    }

    std::cout << "\n--- 5.2. WEAK_PTR: БАЛЛОН УЖЕ УНИЧТОЖЕН ---\n";
    std::cout << "Модуль manualModule пытается израсходовать кислород:\n";
    manualModule.ConsumeModuleOxygen(5.0);

    std::cout << "\n=== КОНЕЦ ПРОГРАММЫ ===\n";
    return 0;
}
