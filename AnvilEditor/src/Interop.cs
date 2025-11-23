using System;
using System.Runtime.InteropServices;

namespace AnvilEditor.src
{
    public static class Interop
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void LogCallbackFn(string message);

        [DllImport("AnvilCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void InitEngineCore(LogCallbackFn callback);

        [DllImport("AnvilCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void TestLoggingFunction();
    }
}
