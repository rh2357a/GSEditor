using System;
using System.IO;
using System.IO.Compression;
using System.Reflection;

namespace GSEditor.Services;

public interface IEmbededService
{
    public byte[] RgbasmBinary { get; }
    public byte[] RgblinkBinary { get; }
    public byte[] RgbfixBinary { get; }

    public string OpenSourceLicenses { get; }
}

public sealed class DefaultEmbededService : IEmbededService
{
    public byte[] RgbasmBinary => EmbededHelpers.GetBytes("GSEditor.Embeds.Rgbds.rgbasm.exe");
    public byte[] RgblinkBinary => EmbededHelpers.GetBytes("GSEditor.Embeds.Rgbds.rgblink.exe");
    public byte[] RgbfixBinary => EmbededHelpers.GetBytes("GSEditor.Embeds.Rgbds.rgbfix.exe");

    public string OpenSourceLicenses => EmbededHelpers.GetString("GSEditor.Embeds.LICENSE.txt");
}

static class EmbededHelpers
{
    public static string GetString(string key)
    {
        var assembly = Assembly.GetExecutingAssembly();
        using var stream = assembly.GetManifestResourceStream(key)!;
        using var reader = new StreamReader(stream);
        return reader.ReadToEnd();
    }

    public static byte[] GetBytes(string key)
    {
        var assembly = Assembly.GetExecutingAssembly();
        using var stream = assembly.GetManifestResourceStream(key)!;
        using var memoryStream = new MemoryStream();
        stream.CopyTo(memoryStream);
        return memoryStream.ToArray();
    }

    public static void ForEachZipEntry(string key, Action<ZipArchiveEntry> archives)
    {
        var assembly = Assembly.GetExecutingAssembly();
        using var resourceStream = assembly.GetManifestResourceStream(key);
        using var archive = new ZipArchive(resourceStream!, ZipArchiveMode.Read);
        foreach (var entry in archive.Entries)
            archives(entry);
    }
}
