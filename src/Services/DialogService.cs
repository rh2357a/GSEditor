using GSEditor.Core.ExtensionMethods;
using GSEditor.Services.Models.Pokegold;
using GSEditor.UI.Dialogs;
using System;
using System.Collections.Generic;
using System.Windows;

namespace GSEditor.Services;

public interface IDialogService
{
    /// <summary>
    /// 창 닫기
    /// </summary>
    /// <param name="dataContext">닫을 창의 뷰 모델</param>
    /// <param name="result">결과 전달</param>
    void Close(object dataContext, object? result = null);

    void ShowMessage(string title, string message);
    void ShowWarning(string title, string message);
    void ShowError(string title, string message);
    MessageDialogResult ShowYesNo(string title, string message);
    MessageDialogResult ShowYesNoCancel(string title, string message);

    void ShowMain();
    void ShowAbout(object ownerDataContext);
    void ShowBadData(object ownerDataContext, List<BadData> badDataList);
}

public enum MessageDialogResult
{
    Yes,
    No,
    Cancel,
}

public sealed class DefaultDialogService : IDialogService
{
    private readonly IServiceProvider _serviceProvider;
    private readonly Dictionary<object, Window?> _windows = [];
    private readonly Dictionary<Window, object?> _results = [];

    public DefaultDialogService(IServiceProvider serviceProvider)
    {
        _serviceProvider = serviceProvider;
    }

    private W CreateDialog<W, VM>()
        where W : Window, new()
        where VM : class
    {
        var dialog = new W();
        dialog.DataContext = _serviceProvider.GetOrCreate<VM>();
        _windows[dialog.DataContext] = dialog;
        return dialog;
    }

    private VM? GetViewModelByWindow<VM>(Window window)
    {
        foreach (var entry in _windows)
        {
            if (entry.Value == window && entry.Key is VM viewModel)
                return viewModel;
        }
        return default;
    }

    private T? GetResult<T>(Window dialog)
    {
        if (_results.TryGetValue(dialog, out object? value))
        {
            _results.Remove(dialog);
            return (T?)value;
        }
        return default;
    }

    public void Close(object dataContext, object? result = null)
    {
        var window = _windows[dataContext];
        if (window != null)
        {
            window.Close();

            if (result != null)
                _results[window] = result;

            _windows.Remove(dataContext);
        }
    }

    public void ShowMessage(string title, string message)
    {
        MessageBox.Show(message, title, MessageBoxButton.OK, MessageBoxImage.Information);
    }

    public void ShowWarning(string title, string message)
    {
        MessageBox.Show(message, title, MessageBoxButton.OK, MessageBoxImage.Warning);
    }

    public void ShowError(string title, string message)
    {
        MessageBox.Show(message, title, MessageBoxButton.OK, MessageBoxImage.Error);
    }

    public MessageDialogResult ShowYesNo(string title, string message)
    {
        var result = MessageBox.Show(message, title, MessageBoxButton.YesNo, MessageBoxImage.Warning);
        return result switch
        {
            MessageBoxResult.Yes => MessageDialogResult.Yes,
            _ => MessageDialogResult.No,
        };
    }

    public MessageDialogResult ShowYesNoCancel(string title, string message)
    {
        var result = MessageBox.Show(message, title, MessageBoxButton.YesNo, MessageBoxImage.Warning);
        return result switch
        {
            MessageBoxResult.Yes => MessageDialogResult.Yes,
            MessageBoxResult.No => MessageDialogResult.No,
            _ => MessageDialogResult.Cancel,
        };
    }

    public void ShowMain()
    {
        var dialog = CreateDialog<MainDialog, MainDialogViewModel>();
        dialog.ShowDialog();
    }

    public void ShowAbout(object ownerDataContext)
    {
        var dialog = CreateDialog<AboutDialog, AboutDialogViewModel>();
        dialog.Owner = _windows[ownerDataContext];
        dialog.ShowDialog();
    }

    public void ShowBadData(object ownerDataContext, List<BadData> badDataList)
    {
        var dialog = CreateDialog<BadDataDialog, BadDataDialogViewModel>();
        dialog.Owner = _windows[ownerDataContext];

        var viewModel = GetViewModelByWindow<BadDataDialogViewModel>(dialog)!;
        viewModel.SetBadDataList(badDataList);

        dialog.ShowDialog();
    }
}
