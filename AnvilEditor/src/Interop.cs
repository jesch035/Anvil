using System;
using System.Runtime.InteropServices;

namespace AnvilEditor.src
{
    public static class Interop
    {
        [Flags]
        public enum SinkFlags : uint
        {
            None = 0,
            CallbackSink = 1 << 0,
        }

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void LogCallbackFn(string message);

        [DllImport("AnvilCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void InitEngineCore(SinkFlags sinkFlags, LogCallbackFn callback);

        [DllImport("AnvilCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void TestLoggingFunction();
    }
}
