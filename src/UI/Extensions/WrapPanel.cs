using System;
using System.Windows;
using System.Windows.Controls;

namespace GSEditor.UI.Extensions;

/// <see cref="https://github.com/sourcechord/GridExtra "/>
/// <see cref="https://github.com/sourcechord/GridExtra/blob/master/GridExtra.Wpf/WrapPanelEx.cs "/>
public static class WrapPanelEx
{
    public static readonly DependencyProperty OriginalSizeProperty = DependencyProperty.RegisterAttached(
        "OriginalSize",
        typeof(Size),
        typeof(WrapPanelEx),
        new PropertyMetadata(Size.Empty)
    );

    public static readonly DependencyProperty AdaptiveLayoutProperty = DependencyProperty.RegisterAttached(
        "AdaptiveLayout",
        typeof(bool),
        typeof(WrapPanelEx),
        new PropertyMetadata(false, OnAdaptiveLayoutChanged)
    );

    public static readonly DependencyProperty LayoutUpdatedCallbackProperty = DependencyProperty.RegisterAttached(
        "LayoutUpdatedCallback",
        typeof(EventHandler),
        typeof(WrapPanelEx),
        new PropertyMetadata(null)
    );

    public static Size GetOriginalSize(DependencyObject obj)
    {
        return (Size)obj.GetValue(OriginalSizeProperty);
    }

    private static void SetOriginalSize(DependencyObject obj, Size value)
    {
        obj.SetValue(OriginalSizeProperty, value);
    }

    public static bool GetAdaptiveLayout(DependencyObject obj)
    {
        return (bool)obj.GetValue(AdaptiveLayoutProperty);
    }

    public static void SetAdaptiveLayout(DependencyObject obj, bool value)
    {
        obj.SetValue(AdaptiveLayoutProperty, value);
    }

    private static void OnAdaptiveLayoutChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
    {
        var panel = d as WrapPanel;
        var isEnabled = (bool)e.NewValue;
        if (panel == null) { return; }

        if (isEnabled)
        {
            SetOriginalSize(panel, new Size(panel.ItemWidth, panel.ItemHeight));
            var layoutUpdateCallback = CreateLayoutUpdateHandler(panel);
            panel.LayoutUpdated += layoutUpdateCallback;
            SetLayoutUpdatedCallback(panel, layoutUpdateCallback);
        }
        else
        {
            var originalSize = GetOriginalSize(panel);

            panel.ItemWidth = originalSize.Width;
            panel.ItemHeight = originalSize.Height;

            panel.ClearValue(OriginalSizeProperty);

            var callback = GetLayoutUpdatedCallback(panel);
            panel.LayoutUpdated -= callback;
        }
    }

    private static EventHandler CreateLayoutUpdateHandler(WrapPanel panel)
    {
        var layoutUpdateCallback = new EventHandler((sender, args) =>
        {
            if (panel == null) return;
            var orientaion = panel.Orientation;
            var originalSize = GetOriginalSize(panel);

            if (orientaion == Orientation.Horizontal)
            {
                if (double.IsNaN(originalSize.Width)) return;

                var count = Math.Floor(panel.ActualWidth / originalSize.Width);
                var size = panel.ActualWidth / count;

                panel.ItemWidth = size;
            }
            else
            {
                if (double.IsNaN(originalSize.Width)) return;

                var count = Math.Floor(panel.ActualHeight / originalSize.Height);
                var size = panel.ActualHeight / count;

                panel.ItemHeight = size;
            }
        });

        return layoutUpdateCallback;
    }

    public static EventHandler GetLayoutUpdatedCallback(DependencyObject obj)
    {
        return (EventHandler)obj.GetValue(LayoutUpdatedCallbackProperty);
    }

    private static void SetLayoutUpdatedCallback(DependencyObject obj, EventHandler value)
    {
        obj.SetValue(LayoutUpdatedCallbackProperty, value);
    }
}
