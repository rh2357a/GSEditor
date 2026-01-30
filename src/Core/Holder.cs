namespace GSEditor.Core;

public class Holder<T>
{
    public T Value { get; set; }

    public Holder(T value)
    {
        Value = value;
    }
}
