using System;


namespace wcvlib
{
    public interface IClipboardData<T>
    {
        [Validate(true)]
        IntPtr GetClipboardDataPointer();
        [Validate(true)]
        long GetClipboardDataSize(T clipboardDataType);
        [Validate(true)]
        IClipboardDataObject<T> GetClipboardDataObject();
        [Validate(false)]
        bool IsClipboardDataEmpty();
        [Validate(false)]
        T GetClipboardDataType();
        [Validate(false)]
        string ToString();
    }


}


