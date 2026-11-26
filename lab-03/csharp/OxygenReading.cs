namespace SpaceStationLab;

/// <summary>
/// Показание датчика кислорода. Маленькое значение без собственной «личности»,
/// поэтому это структура (тип-значение), а не класс.
/// </summary>
public struct OxygenReading
{
    public OxygenReading(string sensor, double level)
    {
        Sensor = sensor;
        Level = level;
    }

    public string Sensor { get; set; }

    public double Level { get; set; }

    public override string ToString() => $"Датчик {Sensor}: {Level}%";
}
