using System;

namespace wcvlib
{
    public interface IClipboardOwnerInfo
    {
        string ClipboardOwnerProcessName { get; }
        IntPtr ClipboardOwnerProcessHandle { get; }
        int ClipboardOwnerProcessId { get; }
        int ClipboardOwnerThreadId { get; }
        IntPtr ClipboardOwnerWindowHandle { get; }
        string ClipboardOwnerWindowName { get; }

        bool Equals(object obj);
        int GetHashCode();
    }
}