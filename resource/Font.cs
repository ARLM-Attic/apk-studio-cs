using System.Drawing;
using System.Drawing.Text;
using System.Runtime.InteropServices;

namespace APKStudio.Resource
{
    class Font
    {
        private static FontFamily LoadFontFamily(byte[] Buffer, out PrivateFontCollection FontCollection)
        {
            var Handle = GCHandle.Alloc(Buffer, GCHandleType.Pinned);
            try
            {
                var Pointer = Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0);
                FontCollection = new PrivateFontCollection();
                FontCollection.AddMemoryFont(Pointer, Buffer.Length);
                return FontCollection.Families[0];
            }
            finally
            {
                Handle.Free();
            }
        }
    }
}
