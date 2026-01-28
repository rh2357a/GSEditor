using GSEditor.Core;
using GSEditor.Core.ExtensionMethods;
using GSEditor.Services;
using Microsoft.Extensions.DependencyInjection;
using System;
using System.IO;
using System.Windows;

namespace GSEditor;

public static class Program
{
    private static readonly IServiceProvider _serviceProvider = new ServiceCollection()
        .AddSingleton<IEmbededService, DefaultEmbededService>()
        .AddSingleton<ISidecarService, DefaultSidecarService>()
        .AddSingleton<IDialogService, DefaultDialogService>()
        .BuildServiceProvider();

    [STAThread]
    public static int Main(string[] args)
    {
        var app = new App();
        app.InitializeComponent();

        app.Startup += OnAppStartup;
        app.Exit += OnAppExit;

        return app.Run();
    }

    private static void OnAppStartup(object sender, StartupEventArgs e)
    {
        var app = (sender as App)!;

        // 구버전 앱 데이터 제거
        if (Directory.Exists(AppPath.AppLegacyData))
            Directory.Delete(AppPath.AppLegacyData, true);

        var sidecarService = _serviceProvider.GetOrCreate<ISidecarService>();
        var dialogService = _serviceProvider.GetOrCreate<IDialogService>();

        sidecarService.Init();
        dialogService.ShowMain();
        app.Shutdown();
    }

    private static void OnAppExit(object sender, ExitEventArgs e)
    {
        var sidecarService = _serviceProvider.GetOrCreate<ISidecarService>();
        sidecarService.Dispose();
    }
}
