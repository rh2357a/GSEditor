using Microsoft.Extensions.DependencyInjection;
using System;

namespace GSEditor.Core.ExtensionMethods;

public static class ServiceProvider
{
    /// <summary>
    /// 타입에 해당하는 서비스를 반환, 없을 경우 생성하여 반환 함
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="serviceProvider"></param>
    /// <returns></returns>
    public static T GetOrCreate<T>(this IServiceProvider serviceProvider)
    {
        var service = serviceProvider.GetService<T>();
        return service ?? ActivatorUtilities.CreateInstance<T>(serviceProvider);
    }
}
