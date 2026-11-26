using System.Text;

namespace SpaceStationLab;

public static class Program
{
    public static void Main()
    {
        Console.OutputEncoding = Encoding.UTF8;

        Console.WriteLine("=== СТАРТ ДЕМОНСТРАЦИОННОЙ ПРОГРАММЫ КОСМИЧЕСКОЙ СТАНЦИИ (ЛР 3, C#) ===");
        Console.WriteLine();

        Console.WriteLine("--- 1. АГРЕГАЦИЯ: БАЛЛОН СОЗДАН СНАРУЖИ И ПЕРЕДАН ГОТОВЫМ ---");
        var externalTank = new OxygenTank(150, 100);
        var manualModule = new LifeSupportModule("Вспомогательный отсек");
        manualModule.ConnectOxygenTank(externalTank);
        manualModule.StartModule();
        manualModule.ConsumeModuleOxygen(30);
        Console.WriteLine(manualModule);
        Console.WriteLine();

        Console.WriteLine("--- 2. ПРОВЕРКА ПРАВИЛ (УСПЕХ И ОТКАЗ) ---");
        externalTank.ConsumeOxygen(20);
        Console.WriteLine("[Тест нарушения 1]: Попытка потратить 200% кислорода...");
        externalTank.ConsumeOxygen(200);
        var emptyModule = new LifeSupportModule("Пустой отсек без баллона");
        Console.WriteLine("[Тест нарушения 2]: Попытка запустить модуль без баллона...");
        emptyModule.StartModule();
        Console.WriteLine();

        Console.WriteLine("--- 3. КОМПОЗИЦИЯ: СТАНЦИЯ САМА СОЗДАЕТ СВОЙ МОДУЛЬ ---");
        var station = new SpaceStation("Мир-2", "Центральный жизнеобеспечивающий узел");
        var stationTank = new OxygenTank(200, 100);
        station.ConnectOxygenTank(stationTank);
        station.ActivateStation();
        station.PerformLifeSupportCheck(40);
        Console.WriteLine(station);
        Console.WriteLine();

        Console.WriteLine("--- 4. ПРОВЕРКА АГРЕГАЦИИ: БАЛЛОН НЕЗАВИСИМ ОТ МОДУЛЯ ---");
        manualModule.ConsumeModuleOxygen(10);
        Console.WriteLine($"Проверка externalTank напрямую: {externalTank}");
        Console.WriteLine();

        MemoryDemo.ShowReferenceCopy();
        MemoryDemo.ShowValueCopy();
        MemoryDemo.ShowResourceRelease(externalTank);
        MemoryDemo.ShowGarbageCollection();

        Console.WriteLine();
        Console.WriteLine("=== КОНЕЦ ПРОГРАММЫ ===");
    }
}
