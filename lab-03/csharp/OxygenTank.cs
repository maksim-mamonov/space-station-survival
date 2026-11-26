namespace SpaceStationLab;

/// <summary>
/// Кислородный баллон: хранит текущий запас кислорода и управляет его расходом и пополнением.
/// </summary>
public class OxygenTank
{
    private const double MaxLevel = 100.0;

    public OxygenTank(int capacity, double initialLevel)
    {
        Capacity = capacity;
        OxygenLevel = initialLevel;
        Console.WriteLine($"[OxygenTank] Создан баллон емкостью {Capacity} с уровнем кислорода {OxygenLevel}%");
    }

    /// <summary>Максимальная емкость баллона. Задается при создании и не меняется.</summary>
    public int Capacity { get; }

    /// <summary>Текущий уровень кислорода в процентах. Изменить его может только сам баллон.</summary>
    public double OxygenLevel { get; private set; }

    /// <summary>
    /// Расходует кислород. Правило: нельзя израсходовать отрицательное количество
    /// или больше, чем осталось в баллоне.
    /// </summary>
    public void ConsumeOxygen(double amount)
    {
        if (amount < 0)
        {
            Console.WriteLine("[OxygenTank Error] Ошибка: нельзя потратить отрицательное количество кислорода!");
            return;
        }

        if (OxygenLevel - amount < 0)
        {
            Console.WriteLine(
                $"[OxygenTank Error] Ошибка: Недостаточно кислорода в баллоне! Доступно: {OxygenLevel}%, запрошено: {amount}%");
            return;
        }

        OxygenLevel -= amount;
        Console.WriteLine($"[OxygenTank] Израсходовано {amount}%. Остаток: {OxygenLevel}%");
    }

    public void Refill()
    {
        OxygenLevel = MaxLevel;
        Console.WriteLine($"[OxygenTank] Баллон полностью заправлен. Уровень: {OxygenLevel}%");
    }

    public override string ToString() => $"Баллон (емкость {Capacity}, уровень {OxygenLevel}%)";
}
