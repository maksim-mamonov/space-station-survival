#include "life_support_module.hpp"
#include <iostream>

namespace space_station
{

    LifeSupportModule::LifeSupportModule(std::string_view name)
        : m_moduleName{ name }
    {
        std::cout << "[LifeSupportModule] Создан модуль жизнеобеспечения: \"" << m_moduleName << "\"\n";
    }

    LifeSupportModule::~LifeSupportModule()
    {
        std::cout << "[LifeSupportModule] Уничтожен модуль жизнеобеспечения: \"" << m_moduleName << "\"\n";
        // Важно для агрегации: мы НЕ удаляем m_oxygenTank здесь, 
        // потому что модуль не владеет им (его уничтожит тот, кто создал — main).
    }

    void LifeSupportModule::ConnectOxygenTank(OxygenTank* tank)
    {
        m_oxygenTank = tank;
        std::cout << "[LifeSupportModule] К модулю \"" << m_moduleName << "\" успешно подключен кислородный баллон.\n";
    }

    void LifeSupportModule::StartModule()
    {
        // Проверка правила: нельзя запустить модуль, если к нему не подключен кислородный баллон
        if (m_oxygenTank == nullptr)
        {
            std::cout << "[LifeSupportModule Error] Ошибка запуска \"" << m_moduleName
                << "\": Отсутствует подключенный кислородный баллон!\n";
            m_isActive = false;
            return; // Отказ выполнить действие
        }

        m_isActive = true;
        std::cout << "[LifeSupportModule] Модуль \"" << m_moduleName << "\" успешно запущен и функционирует.\n";
    }

    void LifeSupportModule::ConsumeModuleOxygen(double amount)
    {
        if (!m_isActive)
        {
            std::cout << "[LifeSupportModule Error] Нельзя расходовать кислород: модуль \"" << m_moduleName << "\" выключен!\n";
            return;
        }

        if (m_oxygenTank == nullptr)
        {
            std::cout << "[LifeSupportModule Error] Нет баллона для расхода кислорода!\n";
            return;
        }

        // Делегируем работу баллону
        std::cout << "[LifeSupportModule] Подача команды баллону на расход " << amount << "% кислорода...\n";
        m_oxygenTank->ConsumeOxygen(amount);
    }

} // namespace space_station