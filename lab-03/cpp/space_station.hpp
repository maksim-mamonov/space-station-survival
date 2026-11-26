#pragma once

#include "life_support_module.hpp"
#include <memory>
#include <string>
#include <string_view>

namespace space_station
{

    class SpaceStation
    {
    private:
        std::string m_stationName;

        // Композиция: модуль жизнеобеспечения — поле по значению.
        // Он создаётся и уничтожается вместе со станцией, указатель не нужен.
        LifeSupportModule m_lifeSupport;

        static constexpr auto TAG = "space_station";

    public:
        // Конструктор принимает имя станции и имя для ее модуля (чтобы создать его внутри)
        SpaceStation(std::string_view stationName, std::string_view moduleName);
        ~SpaceStation();

        // Подключение внешнего баллона к встроенному модулю.
        // Часть наружу не отдаётся: станция сама делегирует вызов своему модулю.
        void ConnectOxygenTank(const std::shared_ptr<OxygenTank>& tank);

        // Содержательные методы
        void ActivateStation();
        void PerformLifeSupportCheck(double oxygenAmount);

        // Геттеры
        [[nodiscard]] std::string_view GetStationName() const
        {
            return m_stationName;
        }
    };

} // namespace space_station
