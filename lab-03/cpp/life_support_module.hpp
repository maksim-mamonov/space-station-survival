#pragma once

#include "oxygen_tank.hpp"
#include <string>

namespace space_station
{

    class LifeSupportModule
    {
    private:
        std::string m_moduleName;
        bool m_isActive{ false };

        // Агрегация: модуль хранит указатель на внешний кислородный баллон
        OxygenTank* m_oxygenTank{ nullptr };

        static constexpr auto TAG = "life_support_module";

    public:
        LifeSupportModule(std::string_view name);
        ~LifeSupportModule();

        // Метод для реализации агрегации: подключение внешнего баллона
        void ConnectOxygenTank(OxygenTank* tank);

        // Содержательные методы
        void StartModule();
        void ConsumeModuleOxygen(double amount);

        // Геттеры
        [[nodiscard]] std::string_view GetModuleName() const
        {
            return m_moduleName;
        }

        [[nodiscard]] bool IsActive() const
        {
            return m_isActive;
        }
    };

} // namespace space_station