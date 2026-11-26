#pragma once

#include <string>

namespace space_station
{

    class OxygenTank
    {
    private:
        double m_oxygenLevel{ 100.0 };
        int m_capacity{ 100 };
        static constexpr auto TAG = "oxygen_tank";

    public:
        OxygenTank(int capacity, double initialLevel);

        OxygenTank() = delete; // баллон всегда создается с осмысленной емкостью и уровнем
        ~OxygenTank();

        // Содержательные методы
        void ConsumeOxygen(double amount);
        void Refill();

        // Геттеры
        [[nodiscard]] double GetOxygenLevel() const
        {
            return m_oxygenLevel;
        }

        [[nodiscard]] int GetCapacity() const
        {
            return m_capacity;
        }
    };

} // namespace space_station