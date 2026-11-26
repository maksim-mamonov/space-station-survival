using System.Runtime.CompilerServices;

namespace SpaceStationLab;

/// <summary>
/// Демонстрации того, как C# работает с памятью: ссылки и копии,
/// освобождение ресурса без деструктора, сборщик мусора.
/// </summary>
public static class MemoryDemo
{
    /// <summary>Класс — ссылочный тип: присваивание копирует ссылку, а не объект.</summary>
    public static void ShowReferenceCopy()
    {
        Console.WriteLine("--- 5. ССЫЛКИ И КОПИИ: КЛАСС (ССЫЛОЧНЫЙ ТИП) ---");

        var firstTank = new OxygenTank(100, 90);
        OxygenTank secondTank = firstTank;

        Console.WriteLine("Расходуем 25% через вторую переменную secondTank:");
        secondTank.ConsumeOxygen(25);

        Console.WriteLine($"firstTank:  {firstTank}");
        Console.WriteLine($"secondTank: {secondTank}");
        Console.WriteLine($"ReferenceEquals(firstTank, secondTank) = {ReferenceEquals(firstTank, secondTank)}");
        Console.WriteLine();
    }

    /// <summary>Структура — тип-значение: присваивание копирует значение целиком.</summary>
    public static void ShowValueCopy()
    {
        Console.WriteLine("--- 5.1. ССЫЛКИ И КОПИИ: СТРУКТУРА (ТИП-ЗНАЧЕНИЕ) ---");

        var firstReading = new OxygenReading("A-1", 70);
        OxygenReading secondReading = firstReading;

        Console.WriteLine("Меняем Level через вторую переменную secondReading на 10%:");
        secondReading.Level = 10;

        Console.WriteLine($"firstReading:  {firstReading}");
        Console.WriteLine($"secondReading: {secondReading}");
        Console.WriteLine();
    }

    /// <summary>Ресурс освобождается в Dispose() при выходе из блока using, а не деструктором.</summary>
    public static void ShowResourceRelease(OxygenTank tank)
    {
        Console.WriteLine("--- 6. ОСВОБОЖДЕНИЕ РЕСУРСА: IDisposable И using ---");

        var log = new OxygenLog("Смена 1");
        using (log)
        {
            log.Record(tank, 5);
            log.Record(tank, 5);
            Console.WriteLine("--> Выход из блока using");
        }

        Console.WriteLine("--> После блока using объект журнала еще существует, но ресурс закрыт:");
        log.Record(tank, 5);
        Console.WriteLine();
    }

    /// <summary>Объект без ссылок уничтожается не при выходе из блока, а после сборки мусора.</summary>
    public static void ShowGarbageCollection()
    {
        Console.WriteLine("--- 7. СБОРЩИК МУСОРА ---");

        WeakReference<OxygenTank> watcher = CreateTemporaryTank();
        Console.WriteLine($"После выхода из метода объект жив: {IsAlive(watcher)}");

        Console.WriteLine("Вызываем GC.Collect()...");
        GC.Collect();
        GC.WaitForPendingFinalizers();

        Console.WriteLine($"После сборки мусора объект жив: {IsAlive(watcher)}");
    }

    // Объект создается в отдельном методе: в отладочной сборке локальная переменная
    // могла бы удерживать его до конца метода, даже если ей присвоили null.
    [MethodImpl(MethodImplOptions.NoInlining)]
    private static WeakReference<OxygenTank> CreateTemporaryTank()
    {
        var temporaryTank = new OxygenTank(50, 100);
        temporaryTank.ConsumeOxygen(10);
        Console.WriteLine("--> Выход из метода: последняя обычная ссылка temporaryTank исчезает");
        return new WeakReference<OxygenTank>(temporaryTank);
    }

    // Проверка тоже в отдельном методе, чтобы временная ссылка из TryGetTarget не удерживала объект.
    [MethodImpl(MethodImplOptions.NoInlining)]
    private static bool IsAlive(WeakReference<OxygenTank> watcher) => watcher.TryGetTarget(out _);
}
