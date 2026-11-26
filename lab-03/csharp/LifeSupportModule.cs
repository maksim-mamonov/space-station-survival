namespace SpaceStationLab;

/// <summary>
/// Модуль жизнеобеспечения: управляет состоянием отсека и расходует кислород
/// через подключенный внешний баллон.
/// </summary>
public class LifeSupportModule
{
    // Агрегация: баллон создается снаружи и передается готовым.
    private OxygenTank? _oxygenTank;

    public LifeSupportModule(string name)
    {
        Name = name;
        Console.WriteLine($"[LifeSupportModule] Создан модуль жизнеобеспечения: \"{Name}\"");
    }

    public string Name { get; }

    public bool IsActive { get; private set; }

    public bool HasOxygenTank => _oxygenTank is not null;

    public void ConnectOxygenTank(OxygenTank tank)
    {
        _oxygenTank = tank;
        Console.WriteLine($"[LifeSupportModule] К модулю \"{Name}\" успешно подключен кислородный баллон.");
    }

    /// <summary>
    /// Запускает модуль. Правило: нельзя запустить модуль без подключенного баллона.
    /// </summary>
    public void StartModule()
    {
        if (_oxygenTank is null)
        {
            Console.WriteLine(
                $"[LifeSupportModule Error] Ошибка запуска \"{Name}\": Отсутствует подключенный кислородный баллон!");
            IsActive = false;
            return;
        }

        IsActive = true;
        Console.WriteLine($"[LifeSupportModule] Модуль \"{Name}\" успешно запущен и функционирует.");
    }

    public void ConsumeModuleOxygen(double amount)
    {
        if (!IsActive)
        {
            Console.WriteLine($"[LifeSupportModule Error] Нельзя расходовать кислород: модуль \"{Name}\" выключен!");
            return;
        }

        if (_oxygenTank is null)
        {
            Console.WriteLine("[LifeSupportModule Error] Нет баллона для расхода кислорода!");
            return;
        }

        Console.WriteLine($"[LifeSupportModule] Подача команды баллону на расход {amount}% кислорода...");
        _oxygenTank.ConsumeOxygen(amount);
    }

    public override string ToString()
    {
        string state = IsActive ? "работает" : "выключен";
        string tank = _oxygenTank?.ToString() ?? "баллон не подключен";
        return $"Модуль \"{Name}\" [{state}], {tank}";
    }
}
