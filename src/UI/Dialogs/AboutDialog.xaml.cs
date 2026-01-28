using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using GSEditor.Services;
using System.Reflection;
using System.Windows;

namespace GSEditor.UI.Dialogs;

public partial class AboutDialog : Window
{
    public AboutDialog()
    {
        InitializeComponent();
    }
}

public partial class AboutDialogViewModel : ObservableObject
{
    private readonly IDialogService _dialogService;

    [ObservableProperty]
    private string _author = "-";

    [ObservableProperty]
    private string _version = "-";

    [ObservableProperty]
    private string _openSourceLicenses = "-";

    public AboutDialogViewModel(IDialogService dialogService, IEmbededService embededService)
    {
        _dialogService = dialogService;

        Author = "rh2357a (rh2357a@gmail.com)";
        Version = $"버전: {Assembly.GetEntryAssembly()!.GetName().Version!.ToString()}";

        OpenSourceLicenses = embededService.OpenSourceLicenses;
    }

    [RelayCommand]
    private void Close()
    {
        _dialogService.Close(this);
    }
}
