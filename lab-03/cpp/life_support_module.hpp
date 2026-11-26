#pragma once

#include "oxygen_tank.hpp"
#include <memory>
#include <string>
#include <string_view>

namespace space_station
{

    class LifeSupportModule
    {
    private:
        std::string m_moduleName;
        bool m_isActive{ false };

        // Агрегация: модуль пользуется внешним баллоном, но не владеет им.
        // weak_ptr не продлевает баллону жизнь и позволяет проверить, жив ли он.
        std::weak_ptr<OxygenTank> m_oxygenTank{};

        static constexpr auto TAG = "life_support_module";

    public:
        explicit LifeSupportModule(std::string_view name);
        ~LifeSupportModule();

        // Метод агрегации: подключение внешнего баллона (владелец остаётся снаружи)
        void ConnectOxygenTank(const std::shared_ptr<OxygenTank>& tank);

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

        [[nodiscard]] bool HasOxygenTank() const
        {
            return !m_oxygenTank.expired();
        }
    };

} // namespace space_station
