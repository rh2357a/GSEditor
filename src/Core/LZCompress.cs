using System;
using System.Runtime.InteropServices;

namespace GSEditor.Core;

public static class LzCompress
{
    public static int GetLzSize(ReadOnlySpan<byte> src)
    {
        unsafe
        {
            fixed (byte* srcPtr = src)
                return Natives.lzcomp_lzsize(srcPtr, src.Length);
        }
    }

    public static int Compress(Span<byte> dst, ReadOnlySpan<byte> src)
    {
        unsafe
        {
            fixed (byte* dstPtr = dst)
            {
                fixed (byte* srcPtr = src)
                    return Natives.lzcomp_compress(dstPtr, srcPtr, src.Length, 0);
            }
        }
    }

    public static int Uncompress(Span<byte> dst, ReadOnlySpan<byte> src)
    {
        unsafe
        {
            fixed (byte* dstPtr = dst)
            {
                fixed (byte* srcPtr = src)
                    return Natives.lzcomp_uncompress(dstPtr, srcPtr, src.Length);
            }
        }
    }

    private static unsafe class Natives
    {
        [DllImport("lzcomp.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "lzcomp_lzsize")]
        public static extern int lzcomp_lzsize(byte* src, int size);

        [DllImport("lzcomp.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "lzcomp_compress")]
        public static extern int lzcomp_compress(byte* dst, byte* src, int size, int method);

        [DllImport("lzcomp.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "lzcomp_uncompress")]
        public static extern int lzcomp_uncompress(byte* dst, byte* src, int size);
    }
}
