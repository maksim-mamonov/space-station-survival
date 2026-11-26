namespace SpaceStationLab;

/// <summary>
/// Журнал расхода кислорода за смену. Это ресурс, который нужно закрыть вовремя,
/// поэтому класс реализует IDisposable и используется в блоке using.
/// </summary>
public sealed class OxygenLog : IDisposable
{
    private readonly string _title;
    private bool _isClosed;

    public OxygenLog(string title)
    {
        _title = title;
        Console.WriteLine($"[OxygenLog] [+] Журнал расхода открыт: {_title}");
    }

    /// <summary>Списывает кислород из баллона и записывает операцию в журнал.</summary>
    public void Record(OxygenTank tank, double amount)
    {
        if (_isClosed)
        {
            Console.WriteLine($"[OxygenLog Error] Журнал \"{_title}\" уже закрыт, запись невозможна!");
            return;
        }

        Console.WriteLine($"[OxygenLog] Запись: списание {amount}% из баллона емкостью {tank.Capacity}");
        tank.ConsumeOxygen(amount);
    }

    public void Dispose()
    {
        if (_isClosed)
        {
            return;
        }

        _isClosed = true;
        Console.WriteLine($"[OxygenLog] [-] Журнал расхода закрыт: {_title}");
    }
}
