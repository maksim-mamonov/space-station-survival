#include "space_station.hpp"
#include <iostream>

namespace space_station
{

    SpaceStation::SpaceStation(std::string_view stationName, std::string_view moduleName)
        : m_stationName{ stationName }
        , m_lifeSupport{ moduleName } // Создаем часть (композиция) в списке инициализации
    {
        std::cout << "[SpaceStation] Космическая станция \"" << m_stationName << "\" построена.\n";
    }

    SpaceStation::~SpaceStation()
    {
        std::cout << "[SpaceStation] Космическая станция \"" << m_stationName << "\" уничтожена (сдано на утилизацию).\n";
        // При вызове этого деструктора автоматически вызовется деструктор m_lifeSupport (композиция).
    }

    void SpaceStation::ActivateStation()
    {
        std::cout << "[SpaceStation] Инициирован запуск систем станции \"" << m_stationName << "\"...\n";
        m_lifeSupport.StartModule();
    }

    void SpaceStation::PerformLifeSupportCheck(double oxygenAmount)
    {
        std::cout << "[SpaceStation] Запрос отчета жизнеобеспечения станции \"" << m_stationName << "\":\n";
        m_lifeSupport.ConsumeModuleOxygen(oxygenAmount);
    }

} // namespace space_station