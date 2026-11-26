#include "oxygen_tank.hpp"
#include <iostream>

namespace space_station
{

    OxygenTank::OxygenTank(int capacity, double initialLevel)
        : m_oxygenLevel{ initialLevel }
        , m_capacity{ capacity }
    {
        std::cout << "[OxygenTank] Создан баллон емкостью " << m_capacity
            << " с уровнем кислорода " << m_oxygenLevel << "%\n";
    }

    OxygenTank::~OxygenTank()
    {
        std::cout << "[OxygenTank] Уничтожен баллон (емкость: " << m_capacity << ")\n";
    }

    void OxygenTank::ConsumeOxygen(double amount)
    {
        // Проверка правила: нельзя расходовать отрицательное количество или больше, чем осталось
        if (amount < 0)
        {
            std::cout << "[OxygenTank Error] Ошибка: нельзя потратить отрицательное количество кислорода!\n";
            return;
        }

        if (m_oxygenLevel - amount < 0)
        {
            std::cout << "[OxygenTank Error] Ошибка: Недостаточно кислорода в баллоне! Доступно: "
                << m_oxygenLevel << "%, запрошено: " << amount << "%\n";
            return; // Отказ выполнить действие
        }

        m_oxygenLevel -= amount;
        std::cout << "[OxygenTank] Израсходовано " << amount << "%. Остаток: " << m_oxygenLevel << "%\n";
    }

    void OxygenTank::Refill()
    {
        m_oxygenLevel = kMaxLevel; // уровень хранится в процентах, поэтому полный баллон — 100%
        std::cout << "[OxygenTank] Баллон полностью заправлен. Уровень: " << m_oxygenLevel << "%\n";
    }

} // namespace space_station