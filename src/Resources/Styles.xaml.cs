using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace GSEditor.Resources;

public partial class Styles
{
    public static ScrollViewer? FindScrollViewrRecursive(DependencyObject dependencyObject)
    {
        if (dependencyObject is ScrollViewer scrollViewer)
            return scrollViewer;

        for (int i = 0; i < VisualTreeHelper.GetChildrenCount(dependencyObject); i++)
        {
            var child = VisualTreeHelper.GetChild(dependencyObject, i);
            var result = FindScrollViewrRecursive(child);
            if (result != null)
                return result;
        }

        return null;
    }

    private void FlowDocumentScrollViewer_PreviewMouseWheel(object sender, MouseWheelEventArgs e)
    {
        var control = (sender as FlowDocumentScrollViewer)!;
        var scrollViewer = FindScrollViewrRecursive(control);
        if (scrollViewer != null)
        {
            double offset = scrollViewer.VerticalOffset - (e.Delta * 3 / 6);
            if (offset < 0)
                scrollViewer.ScrollToVerticalOffset(0);
            else if (offset > scrollViewer.ExtentHeight)
                scrollViewer.ScrollToVerticalOffset(scrollViewer.ExtentHeight);
            else
                scrollViewer.ScrollToVerticalOffset(offset);

            e.Handled = true;
        }
    }
}
