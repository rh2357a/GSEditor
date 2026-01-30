using CommunityToolkit.Mvvm.ComponentModel;
using GSEditor.Services;
using GSEditor.Services.Models.Pokegold;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Media;

namespace GSEditor.UI.Dialogs;

public partial class BadDataDialog
{
    public BadDataDialog()
    {
        InitializeComponent();
        SystemSounds.Asterisk.Play();
    }
}

public partial class BadDataDialogViewModel : ObservableObject
{
    private readonly IDialogService _dialogService;

    [ObservableProperty]
    private ObservableCollection<BadDataRowViewModel> _badDataList = [];

    public BadDataDialogViewModel(IDialogService dialogService)
    {
        _dialogService = dialogService;
    }

    public void SetBadDataList(List<BadData> data)
    {
        for (int i = 0; i < data.Count; i++)
            BadDataList.Add(new BadDataRowViewModel(i + 1, data[i]));
    }

    public partial class BadDataRowViewModel(int index, BadData data) : ObservableObject
    {
        public string Index => index.ToString();
        public string Reason => "testtesttesttesttest";
        public string Result => "testtesttesttesttesttesttest";
    }
}
