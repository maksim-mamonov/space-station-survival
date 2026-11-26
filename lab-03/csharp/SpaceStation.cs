namespace SpaceStationLab;

/// <summary>
/// Космическая станция: координирует работу систем и сама создает свой модуль жизнеобеспечения.
/// </summary>
public class SpaceStation
{
    // Композиция: модуль создается в конструкторе станции и наружу не отдается.
    private readonly LifeSupportModule _lifeSupport;

    public SpaceStation(string name, string moduleName)
    {
        Name = name;
        _lifeSupport = new LifeSupportModule(moduleName);
        Console.WriteLine($"[SpaceStation] Космическая станция \"{Name}\" построена.");
    }

    public string Name { get; }

    /// <summary>
    /// Подключает внешний баллон к встроенному модулю. Станция делегирует вызов своей части,
    /// поэтому ссылка на модуль наружу не выдается.
    /// </summary>
    public void ConnectOxygenTank(OxygenTank tank) => _lifeSupport.ConnectOxygenTank(tank);

    public void ActivateStation()
    {
        Console.WriteLine($"[SpaceStation] Инициирован запуск систем станции \"{Name}\"...");
        _lifeSupport.StartModule();
    }

    public void PerformLifeSupportCheck(double oxygenAmount)
    {
        Console.WriteLine($"[SpaceStation] Запрос отчета жизнеобеспечения станции \"{Name}\":");
        _lifeSupport.ConsumeModuleOxygen(oxygenAmount);
    }

    public override string ToString() => $"Станция \"{Name}\": {_lifeSupport}";
}
