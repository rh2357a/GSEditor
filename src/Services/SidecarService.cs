using GSEditor.Core;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;

namespace GSEditor.Services;

public interface ISidecarService
{
    void Init();
    void Dispose();

    SidecarResult Rgbasm(string args, string cwd);
    SidecarResult Rgblink(string args, string cwd);
    SidecarResult Rgbfix(string args, string cwd);
}

public sealed class SidecarResult(int exitCode, string output)
{
    public int ExitCode => exitCode;
    public string Output => output;
}

public sealed class DefaultSidecarService : ISidecarService
{
    private readonly IEmbededService _embededService;

    private readonly string _sidecarPath = Path.Combine(AppPath.AppData, "bin");
    private readonly List<FileStream> _sidecarBinaryLockings = [];

    public DefaultSidecarService(IEmbededService embededService)
    {
        _embededService = embededService;
    }

    public void Init()
    {
        if (!Path.Exists(_sidecarPath))
            Directory.CreateDirectory(_sidecarPath);

        InitSidecar("rgbasm.exe", _embededService.RgbasmBinary);
        InitSidecar("rgblink.exe", _embededService.RgblinkBinary);
        InitSidecar("rgbfix.exe", _embededService.RgbfixBinary);
    }

    private void InitSidecar(string name, Span<byte> bytes)
    {
        var sidecarPath = Path.Combine(_sidecarPath, name);
        File.WriteAllBytes(sidecarPath, bytes);

        var fs = new FileStream(sidecarPath, FileMode.OpenOrCreate, FileAccess.Read, FileShare.None);
        _sidecarBinaryLockings.Add(fs);
    }

    public void Dispose()
    {
        foreach (var e in _sidecarBinaryLockings)
            e.Dispose();
        _sidecarBinaryLockings.Clear();
    }

    public SidecarResult Rgbasm(string args, string cwd)
    {
        return new SidecarRunner(Path.Combine(_sidecarPath, "rgbasm.exe"), args, cwd).Run();
    }

    public SidecarResult Rgblink(string args, string cwd)
    {
        return new SidecarRunner(Path.Combine(_sidecarPath, "rgblink.exe"), args, cwd).Run();
    }

    public SidecarResult Rgbfix(string args, string cwd)
    {
        return new SidecarRunner(Path.Combine(_sidecarPath, "rgbfix.exe"), args, cwd).Run();
    }

    internal sealed class SidecarRunner
    {
        private readonly string _path;
        private readonly string _args;
        private readonly string _cwd;

        public SidecarRunner(string path, string args, string cwd)
        {
            _path = path;
            _args = args;
            _cwd = cwd;
        }

        public SidecarResult Run()
        {
            using var process = new Process
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = _path,
                    Arguments = _args,
                    UseShellExecute = false,
                    RedirectStandardOutput = true,
                    RedirectStandardError = true,
                    CreateNoWindow = true,
                    WorkingDirectory = _cwd,
                }
            };

            var output = new StringBuilder();
            process.OutputDataReceived += (s, e) => { if (e.Data != null) output.AppendLine(e.Data); };
            process.ErrorDataReceived += (s, e) => { if (e.Data != null) output.AppendLine(e.Data); };

            process.Start();
            process.BeginOutputReadLine();
            process.BeginErrorReadLine();
            process.WaitForExit();

            return new SidecarResult(process.ExitCode, output.ToString());
        }
    }
}
