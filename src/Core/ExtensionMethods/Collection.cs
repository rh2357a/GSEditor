using System.Collections.Generic;

namespace GSEditor.Core.ExtensionMethods;

public static class Collection
{
    public static void AddRange<T>(this IList<T> list, IList<T> another)
    {
        foreach (var e in another)
            list.Add(e);
    }
}
