using GSEditor.Core;
using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Windows.Controls;

namespace GSEditor.UI.Extensions;

public static class StackPanelEx
{
    public static readonly DependencyProperty HorizontalSpacingProperty = DependencyProperty.RegisterAttached(
        "HorizontalSpacing",
        typeof(double),
        typeof(StackPanelEx),
        new UIPropertyMetadata(0d, HorizontalSpacingChangedCallback)
    );

    public static readonly DependencyProperty VerticalSpacingProperty = DependencyProperty.RegisterAttached(
        "VerticalSpacing",
        typeof(double),
        typeof(StackPanelEx),
        new UIPropertyMetadata(0d, VerticalSpacingChangedCallback)
    );

    public static double GetHorizontalSpacing(DependencyObject obj)
    {
        return (double)obj.GetValue(HorizontalSpacingProperty);
    }

    public static void SetHorizontalSpacing(DependencyObject obj, double space)
    {
        obj.SetValue(HorizontalSpacingProperty, space);
    }

    private static void HorizontalSpacingChangedCallback(object sender, DependencyPropertyChangedEventArgs e)
    {
        if (sender is StackPanel stackPanel)
        {
            if (DesignerProperties.GetIsInDesignMode(stackPanel))
                stackPanel.LayoutUpdated += (_, __) => StackPanelExHorizontalSpacing_Loaded(stackPanel, EventArgs.Empty);

            stackPanel.Loaded -= StackPanelExHorizontalSpacing_Loaded;
            stackPanel.Loaded += StackPanelExHorizontalSpacing_Loaded;

            if (stackPanel.IsLoaded)
                StackPanelExHorizontalSpacing_Loaded(stackPanel, EventArgs.Empty);
        }
    }

    private static void StackPanelExHorizontalSpacing_Loaded(object? sender, EventArgs ev)
    {
        if (sender is StackPanel stackPanel)
        {
            var space = GetHorizontalSpacing(stackPanel);

            for (int i = 0; i < stackPanel.Children.Count; i++)
            {
                var child = stackPanel.Children[i];
                if (child is FrameworkElement childElement)
                {
                    var childMargin = ChildMarginManager.GetMargin(childElement);
                    var newMargin = new Thickness
                    {
                        Left = childMargin.Left,
                        Top = childMargin.Top,
                        Right = childMargin.Right + ((i < stackPanel.Children.Count - 1) ? space : 0),
                        Bottom = childMargin.Bottom,
                    };

                    ChildMarginManager.Freeze(childElement);
                    childElement.Margin = newMargin;
                    ChildMarginManager.Thaw(childElement);
                }
            }
        }
    }

    public static double GetVerticalSpacing(DependencyObject obj)
    {
        return (double)obj.GetValue(VerticalSpacingProperty);
    }

    public static void SetVerticalSpacing(DependencyObject obj, double value)
    {
        obj.SetValue(VerticalSpacingProperty, value);
    }

    private static void VerticalSpacingChangedCallback(object sender, DependencyPropertyChangedEventArgs e)
    {
        if (sender is StackPanel stackPanel)
        {
            if (DesignerProperties.GetIsInDesignMode(stackPanel))
                stackPanel.LayoutUpdated += (_, __) => StackPanelExVerticalSpacing_Loaded(stackPanel, EventArgs.Empty);

            stackPanel.Loaded -= StackPanelExVerticalSpacing_Loaded;
            stackPanel.Loaded += StackPanelExVerticalSpacing_Loaded;

            if (stackPanel.IsLoaded)
                StackPanelExVerticalSpacing_Loaded(stackPanel, EventArgs.Empty);
        }
    }

    private static void StackPanelExVerticalSpacing_Loaded(object? sender, EventArgs ev)
    {
        if (sender is StackPanel stackPanel)
        {
            var space = GetVerticalSpacing(stackPanel);

            for (int i = 0; i < stackPanel.Children.Count; i++)
            {
                var child = stackPanel.Children[i];
                if (child is FrameworkElement childElement)
                {
                    var childMargin = ChildMarginManager.GetMargin(childElement);
                    var newMargin = new Thickness
                    {
                        Left = childMargin.Left,
                        Top = childMargin.Top,
                        Right = childMargin.Right,
                        Bottom = childMargin.Bottom + ((i < stackPanel.Children.Count - 1) ? space : 0),
                    };

                    ChildMarginManager.Freeze(childElement);
                    childElement.Margin = newMargin;
                    ChildMarginManager.Thaw(childElement);
                }
            }
        }
    }

    static class ChildMarginManager
    {
        private static readonly ConditionalWeakTable<FrameworkElement, Holder<Thickness>> _thicknesses = [];
        private static readonly ConditionalWeakTable<FrameworkElement, Holder<bool>> _dirtyflags = [];

        public static Thickness GetMargin(FrameworkElement childElement)
        {
            if (!_thicknesses.TryGetValue(childElement, out var result))
            {
                var marginPropertyDesc = DependencyPropertyDescriptor.FromProperty(FrameworkElement.MarginProperty, typeof(FrameworkElement));
                childElement.Loaded += (_, __) => marginPropertyDesc.AddValueChanged(childElement, MarginPropertyChanged);
                childElement.Unloaded += (_, __) => marginPropertyDesc.RemoveValueChanged(childElement, MarginPropertyChanged);

                var newHolder = new Holder<Thickness>(childElement.Margin);
                _thicknesses.Add(childElement, newHolder);
                return newHolder.Value;
            }

            return result.Value;
        }

        private static void MarginPropertyChanged(object? sender, EventArgs ev)
        {
            if (sender is FrameworkElement element)
            {
                if (!IsGuarded(element))
                {
                    var newHolder = new Holder<Thickness>(element.Margin);
                    _thicknesses.Remove(element);
                    _thicknesses.Add(element, newHolder);
                }
            }
        }

        public static void Freeze(FrameworkElement childElement)
        {
            if (!_dirtyflags.TryGetValue(childElement, out var result))
            {
                var newHolder = new Holder<bool>(true);
                _dirtyflags.Add(childElement, newHolder);
                return;
            }

            result.Value = true;
        }

        public static void Thaw(FrameworkElement childElement)
        {
            if (!_dirtyflags.TryGetValue(childElement, out var result))
            {
                var newHolder = new Holder<bool>(false);
                _dirtyflags.Add(childElement, newHolder);
                return;
            }

            result.Value = false;
        }

        public static bool IsGuarded(FrameworkElement childElement)
        {
            if (!_dirtyflags.TryGetValue(childElement, out var result))
            {
                var newHolder = new Holder<bool>(false);
                _dirtyflags.Add(childElement, newHolder);
                return false;
            }

            return result.Value;
        }
    }
}
