using System;
using System.IO;

namespace GSEditor.Core;

public static class AppPath
{
    public static string AppData => Path.Combine(
        Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData),
        "GSEditor"
    );

    public static string AppLegacyData => Path.Combine(
        Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData),
        "GSEditor"
    );
}
