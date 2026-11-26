#pragma once

#include "life_support_module.hpp"
#include <string>

namespace space_station
{

    class SpaceStation
    {
    private:
        std::string m_stationName;

        // Композиция: модуль жизнеобеспечения создается внутри станции и является ее частью.
        // Он не существует отдельно от станции.
        LifeSupportModule m_lifeSupport;

        static constexpr auto TAG = "space_station";

    public:
        // Конструктор принимает имя станции и имя для ее модуля (чтобы создать его внутри)
        SpaceStation(std::string_view stationName, std::string_view moduleName);
        ~SpaceStation();

        // Содержательные методы
        void ActivateStation();
        void PerformLifeSupportCheck(double oxygenAmount);

        // Доступ к части (через методы целого, как требует задание)
        [[nodiscard]] LifeSupportModule& GetLifeSupportModule()
        {
            return m_lifeSupport;
        }

        // Геттеры
        [[nodiscard]] std::string_view GetStationName() const
        {
            return m_stationName;
        }
    };

} // namespace space_station