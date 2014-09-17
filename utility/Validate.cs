using System;
using System.IO;

namespace APKStudio.Utility
{
    public class Validate
    {
        public static bool IfValidDisassembly(string Path)
        {
            bool HasAndroidManifest = false, HasApkToolYaml = false, HasSmaliFolder = false;
            try
            {
                var Attributes = File.GetAttributes(System.IO.Path.GetFullPath(Path));
                if ((Attributes & FileAttributes.Directory) == FileAttributes.Directory)
                {
                    var Directory = new DirectoryInfo(Path);
                    foreach (var FoundDirectory in Directory.GetDirectories())
                    {
                        if (FoundDirectory.Name.Equals("smali"))
                            HasSmaliFolder = true;
                    }
                    foreach (var FoundFile in Directory.GetFiles())
                    {
                        if (FoundFile.Name.Equals("AndroidManifest.xml"))
                            HasAndroidManifest = true;
                        else if (FoundFile.Name.Equals("apktool.yml"))
                            HasApkToolYaml = true;
                    }
                }
            }
            catch (Exception Error)
            {
                //
            }
            return HasAndroidManifest && HasApkToolYaml && HasSmaliFolder;
        }
    }
}
