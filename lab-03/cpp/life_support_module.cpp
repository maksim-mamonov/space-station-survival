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
        // Баллон здесь не уничтожается: weak_ptr им не владеет.
    }

    void LifeSupportModule::ConnectOxygenTank(const std::shared_ptr<OxygenTank>& tank)
    {
        m_oxygenTank = tank; // счётчик владельцев баллона при этом не растёт
        std::cout << "[LifeSupportModule] К модулю \"" << m_moduleName << "\" успешно подключен кислородный баллон.\n";
    }

    void LifeSupportModule::StartModule()
    {
        // Проверка правила: нельзя запустить модуль, если к нему не подключен
        // кислородный баллон (или подключенный баллон уже уничтожен)
        if (m_oxygenTank.expired())
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

        // lock() даёт временного владельца: непустой, если баллон жив, и пустой, если уже уничтожен
        const std::shared_ptr<OxygenTank> tank = m_oxygenTank.lock();
        if (!tank)
        {
            std::cout << "[LifeSupportModule Error] Баллон модуля \"" << m_moduleName
                << "\" уже уничтожен, расход кислорода невозможен!\n";
            m_isActive = false;
            return;
        }

        // Делегируем работу баллону
        std::cout << "[LifeSupportModule] Подача команды баллону на расход " << amount << "% кислорода...\n";
        tank->ConsumeOxygen(amount);
    }

} // namespace space_station
