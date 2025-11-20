using System;
using System.Runtime.InteropServices;

namespace AnvilEditor
{
    public static class Interop
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void LogCallback(string message);

        [DllImport("AnvilCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetLogCallback(LogCallback callback);

        [DllImport("AnvilCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void TestLoggingFunction();
    }
}
