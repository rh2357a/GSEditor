namespace GSEditor.Services.Models.Pokegold;

public enum BadDataReason
{
    Unknown,
}

public sealed class BadData
{
    public BadDataReason Reason { get; set; } = BadDataReason.Unknown;
    public int Index { get; set; } = -1;
}
