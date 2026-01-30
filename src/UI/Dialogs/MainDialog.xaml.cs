using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using GSEditor.Services;

namespace GSEditor.UI.Dialogs;

public partial class MainDialog
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
    public void TestAbout()
    {
        _dialogService.ShowAbout(this);
    }

    [RelayCommand]
    public void TestBad()
    {
        _dialogService.ShowBadData(this, [
            new(),
            new(),
            new(),
            new(),
            new(),
            ]);
    }
}
