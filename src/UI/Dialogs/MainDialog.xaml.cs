using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using GSEditor.Services;
using System.Windows;

namespace GSEditor.UI.Dialogs;

public partial class MainDialog : Window
{
    public MainDialog()
    {
        InitializeComponent();
    }
}

public partial class MainDialogViewModel : ObservableObject
{
    private readonly IDialogService _dialogService;

    [ObservableProperty]
    private string _title = "-";

    public MainDialogViewModel(IDialogService dialogService)
    {
        _dialogService = dialogService;
    }

    [RelayCommand]
    public void Test()
    {
        Title = "test!!";

        _dialogService.ShowAbout(this);
    }
}
