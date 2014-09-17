using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;
using APKStudio.Resource;

namespace APKStudio.Controller
{
    public class Explorer
    {
        private readonly Dictionary<string, string> _Nodes;
        private readonly TreeView _TreeExplorer;
        private readonly IFileSelection _Listener;
        private const int    IconFileApk = 0,
                             IconFileJava = 1,
                             IconFilePng = 2,
                             IconFileRaw = 3,
                             IconFileRsa = 4,
                             IconFileSmali = 5,
                             IconFileXml = 6;
        private const int    IconFolderAsset = 7,
                             IconFolderBinary = 8,
                             IconFolderCertificate = 9,
                             IconFolderDrawable = 10,
                             IconFolderEmpty = 11,
                             IconFolderLayout = 12,
                             IconFolderRaw = 13,
                             IconFolderResource = 14,
                             IconFolderRoot = 15,
                             IconFolderSmali = 16,
                             IconFolderSource = 17,
                             IconFolderValues = 18,
                             IconPackageClose = 19,
                             IconPackageOpen = 20;
        public enum Selection
        {
            Delete,
            Open,
            Properties,
            Rename
        }
        public interface IFileSelection
        {
            void OnFileSelected(Selection SelectionType, string Path);
        }
        public Explorer(IFileSelection Listener, ref TreeView TreeExplorer)
        {
            this._Listener = Listener;
            this._TreeExplorer = TreeExplorer;
            this._Nodes = new Dictionary<string, string>();
            this._TreeExplorer.ImageList = new ImageList();
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFileApk);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFileJava);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFilePng);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFileRaw);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFileRsa);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFileSmali);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFileXml);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFolderAsset);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFolderBinary);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFolderCertificate);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFolderDrawable);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFolderEmpty);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFolderLayout);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFolderRaw);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFolderResource);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFolderRoot);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFolderSmali);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFolderSource);
            this._TreeExplorer.ImageList.Images.Add(Images.TreeFolderValues);
            this._TreeExplorer.ImageList.Images.Add(Images.TreePackageClose);
            this._TreeExplorer.ImageList.Images.Add(Images.TreePackageOpen);
        }
        private enum Nature
        {
            Asset,
            Binary,
            Certificate,
            Drawable,
            Empty,
            Layout,
            Raw,
            Resource,
            Smali,
            Source,
            Values
        }
        private static bool CheckIfFolder(string Path)
        {
            var Attributes = File.GetAttributes(Path);
            return (Attributes & FileAttributes.Directory) == FileAttributes.Directory;
        }
        private static bool CheckIfFileIsRequired(string Path)
        {
            var File = new FileInfo(Path);
            return File.Name.Equals("AndroidManifest.xml") || File.Name.Equals("apktool.yml");
        }
        private static bool CheckIfFolderUnderSmali(TreeNode CurrentNode)
        {
            var LoopNode = CurrentNode;
            while (LoopNode.Parent != null)
            {
                if (LoopNode.Parent.Text.Equals(@"smali"))
                    return true;
                LoopNode = LoopNode.Parent;
            }
            return false;
        }
        private static bool CheckIfFolderUnderSource(TreeNode CurrentNode)
        {
            var LoopNode = CurrentNode;
            while (LoopNode.Parent != null)
            {
                if (LoopNode.Parent.Text.Equals(@"source"))
                    return true;
                LoopNode = LoopNode.Parent;
            }
            return false;
        }
        public void ExpandDist()
        {
            var RootNode = GetRootNode();
            if (RootNode != null)
            {
                var DistNode = GetNodeUnderNode("dist", RootNode.Nodes);
                if (DistNode != null && DistNode.Length > 0)
                    DistNode[0].Expand();
            }
        }
        public void ExpandRoot()
        {
            var RootNode = this._TreeExplorer.Nodes[0];
            while (RootNode.Parent != null)
                RootNode = RootNode.Parent;
            if (RootNode != null)
                RootNode.Expand();
        }
        private ContextMenuStrip GetContextMenu(string Path)
        {
            var ContextStrip = new ContextMenuStrip();
            var DeleteItem = new ToolStripMenuItem("Delete", Images.TreeContextDelete) { Enabled = (!CheckIfFolder(Path) && !CheckIfFileIsRequired(Path)) };
            DeleteItem.Click += OnContextDeleteClick;
            var OpenItem = new ToolStripMenuItem("Open", Images.TreeContextOpen) { Enabled = !CheckIfFolder(Path) };
            OpenItem.Click += OnContextOpenClick;
            var PropertiesItem = new ToolStripMenuItem("Properties", Images.TreeContextProperties);
            PropertiesItem.Click += OnContextPropertiesClick;
            var RenameItem = new ToolStripMenuItem("Rename", Images.TreeContextRename) { Enabled = (!CheckIfFolder(Path) && !CheckIfFileIsRequired(Path)) };
            RenameItem.Click += OnContextRenameClick;
            ContextStrip.Items.Add(OpenItem);
            ContextStrip.Items.Add("-");
            ContextStrip.Items.Add(RenameItem);
            ContextStrip.Items.Add(DeleteItem);
            ContextStrip.Items.Add("-");
            ContextStrip.Items.Add(PropertiesItem);
            return ContextStrip;
        }
        private static TreeNode GetFileNode(FileInfo File)
        {
            var CurrentNode = new TreeNode(File.Name);
            if (!String.IsNullOrEmpty(File.Extension.ToLower()))
            {
                switch (File.Extension.ToLower())
                {
                    case @".apk":
                        CurrentNode.ImageIndex = IconFileApk;
                        CurrentNode.SelectedImageIndex = IconFileApk;
                        break;
                    case @".jad":
                        CurrentNode.ImageIndex = IconFileJava;
                        CurrentNode.SelectedImageIndex = IconFileJava;
                        break;
                    case @".java":
                        CurrentNode.ImageIndex = IconFileJava;
                        CurrentNode.SelectedImageIndex = IconFileJava;
                        break;
                    case @".png":
                        CurrentNode.ImageIndex = IconFilePng;
                        CurrentNode.SelectedImageIndex = IconFilePng;
                        break;
                    case @".rsa":
                        CurrentNode.ImageIndex = IconFileRsa;
                        CurrentNode.SelectedImageIndex = IconFileRsa;
                        break;
                    case @".smali":
                        CurrentNode.ImageIndex = IconFileSmali;
                        CurrentNode.SelectedImageIndex = IconFileSmali;
                        break;
                    case @".xml":
                        CurrentNode.ImageIndex = IconFileXml;
                        CurrentNode.SelectedImageIndex = IconFileXml;
                        break;
                    default:
                        CurrentNode.ImageIndex = IconFileRaw;
                        CurrentNode.SelectedImageIndex = IconFileRaw;
                        break;
                }
            }
            else
            {
                CurrentNode.ImageIndex = IconFileRaw;
                CurrentNode.SelectedImageIndex = IconFileRaw;
            }
            return CurrentNode;
        }
        private static Nature GetFolderNature(DirectoryInfo Directory)
        {
            if (!System.IO.Directory.EnumerateFileSystemEntries(Directory.ToString()).Any())
                return Nature.Empty;
            switch (Directory.Name)
            {
                case @"asset":
                    return Nature.Asset;
                case @"dist":
                    return Nature.Binary;
                case @"META-INF":
                    return Nature.Certificate;
                case @"res":
                    return Nature.Resource;
                case @"smali":
                    return Nature.Smali;
                case @"source":
                    return Nature.Source;
                default:
                    if (Directory.Name.StartsWith(@"layout"))
                        return Nature.Layout;
                    if (Directory.Name.StartsWith(@"drawable"))
                        return Nature.Drawable;
                    return Directory.Name.StartsWith(@"values") ? Nature.Values : Nature.Raw;
            }
        }
        private static TreeNode GetFolderNode(DirectoryInfo Directory)
        {
            var CurrentNode = new TreeNode(Directory.Name);
            switch (GetFolderNature(Directory))
            {
                case Nature.Asset:
                    CurrentNode.ImageIndex = IconFolderAsset;
                    CurrentNode.SelectedImageIndex = IconFolderAsset;
                    break;
                case Nature.Binary:
                    CurrentNode.ImageIndex = IconFolderBinary;
                    CurrentNode.SelectedImageIndex = IconFolderBinary;
                    break;
                case Nature.Certificate:
                    CurrentNode.ImageIndex = IconFolderCertificate;
                    CurrentNode.SelectedImageIndex = IconFolderCertificate;
                    break;
                case Nature.Drawable:
                    CurrentNode.ImageIndex = IconFolderDrawable;
                    CurrentNode.SelectedImageIndex = IconFolderDrawable;
                    break;
                case Nature.Empty:
                    CurrentNode.ImageIndex = IconFolderEmpty;
                    CurrentNode.SelectedImageIndex = IconFolderEmpty;
                    break;
                case Nature.Layout:
                    CurrentNode.ImageIndex = IconFolderLayout;
                    CurrentNode.SelectedImageIndex = IconFolderLayout;
                    break;
                case Nature.Resource:
                    CurrentNode.ImageIndex = IconFolderResource;
                    CurrentNode.SelectedImageIndex = IconFolderResource;
                    break;
                case Nature.Smali:
                    CurrentNode.ImageIndex = IconFolderSmali;
                    CurrentNode.SelectedImageIndex = IconFolderSmali;
                    break;
                case Nature.Source:
                    CurrentNode.ImageIndex = IconFolderSource;
                    CurrentNode.SelectedImageIndex = IconFolderSource;
                    break;
                case Nature.Values:
                    CurrentNode.ImageIndex = IconFolderValues;
                    CurrentNode.SelectedImageIndex = IconFolderValues;
                    break;
                default:
                    CurrentNode.ImageIndex = IconFolderRaw;
                    CurrentNode.SelectedImageIndex = IconFolderRaw;
                    break;
            }
            return CurrentNode;
        }
        private static TreeNode[] GetNodeUnderNode(string Key, IEnumerable Nodes)
        {
            return Nodes.Cast<TreeNode>().Where(Recusrion => Recusrion.Text == Key).ToArray();
        }
        public TreeNode GetRootNode()
        {
            var RootNode = this._TreeExplorer.Nodes[0];
            while (RootNode.Parent != null)
                RootNode = RootNode.Parent;
            return RootNode;
        }
        public string GetRootPath()
        {
            var RootNode = GetRootNode();
            if (RootNode != null)
            {
                if (this._Nodes.ContainsKey(RootNode.FullPath))
                    return this._Nodes[RootNode.FullPath];
            }
            return null;
        }
        public void InitializeWorkingDirectory(string Path)
        {
            this._TreeExplorer.Nodes.Clear();
            this._Nodes.Clear();
            this._TreeExplorer.NodeMouseDoubleClick += this.OnNodeDoubleClick;
            this._TreeExplorer.NodeMouseClick += this.OnNodeRightClick;
            var CurrentNode = new TreeNode(new DirectoryInfo(Path).Name) { ImageIndex = IconFolderRoot, SelectedImageIndex = IconFolderRoot };
            this._TreeExplorer.Nodes.Add(CurrentNode);
            this._Nodes.Add(CurrentNode.FullPath, Path);
            RecursiveScan(Path, ref CurrentNode);
        }
        private void OnContextDeleteClick(object Sender, EventArgs Arguments)
        {
            this._Listener.OnFileSelected(Selection.Delete, this._Nodes[this._TreeExplorer.SelectedNode.FullPath]);
        }
        private void OnContextOpenClick(object Sender, EventArgs Arguments)
        {
            this._Listener.OnFileSelected(Selection.Open, this._Nodes[this._TreeExplorer.SelectedNode.FullPath]);
        }
        private void OnContextPropertiesClick(object Sender, EventArgs Arguments)
        {
            this._Listener.OnFileSelected(Selection.Properties, this._Nodes[this._TreeExplorer.SelectedNode.FullPath]);
        }
        private void OnContextRenameClick(object Sender, EventArgs Arguments)
        {
            this._Listener.OnFileSelected(Selection.Rename, this._Nodes[this._TreeExplorer.SelectedNode.FullPath]);
        }
        private void OnNodeRightClick(object Sender, TreeNodeMouseClickEventArgs Event)
        {
            if (Event.Button == MouseButtons.Right)
            {
                this._TreeExplorer.SelectedNode = Event.Node;
                if (this._Nodes != null && this._Nodes.ContainsKey(Event.Node.FullPath))
                {
                    var NodePath = this._Nodes[Event.Node.FullPath];
                    if (NodePath != null)
                    {
                        var ContextStrip = this.GetContextMenu(NodePath);
                        var ClickPoint = new Point(Event.X, Event.Y);
                        ContextStrip.Show(this._TreeExplorer, ClickPoint);
                    }
                }
            }
        }
        private void OnNodeDoubleClick(object Sender, TreeNodeMouseClickEventArgs Event)
        {
            try
            {
                if (this._Nodes != null && this._Nodes.ContainsKey(Event.Node.FullPath))
                {
                    var FilePath = this._Nodes[Event.Node.FullPath];
                    if (FilePath != null && !CheckIfFolder(FilePath))
                        this._Listener.OnFileSelected(Selection.Open, FilePath);
                }
            }
            catch (Win32Exception)
            {
                MessageBox.Show(@"File may have been moved or deleted");
            }
        }
        private void RecursiveScan(string DirectoryPath, ref TreeNode ParentNode)
        {
            foreach (var FoundDirectory in Directory.GetDirectories(DirectoryPath))
            {
                var DirectoryHandle = new DirectoryInfo(FoundDirectory);
                var CurrentNode = GetFolderNode(DirectoryHandle);
                ParentNode.Nodes.Add(CurrentNode);
                this._Nodes.Add(CurrentNode.FullPath, DirectoryHandle.ToString());
                if (CheckIfFolderUnderSmali(CurrentNode))
                {
                    CurrentNode.ImageIndex = IconPackageClose;
                    CurrentNode.SelectedImageIndex = IconPackageClose;
                }
                else if (CheckIfFolderUnderSource(CurrentNode))
                {
                    CurrentNode.ImageIndex = IconPackageClose;
                    CurrentNode.SelectedImageIndex = IconPackageClose;
                }
                RecursiveScan(FoundDirectory, ref CurrentNode);
            }
            foreach (var FoundFile in Directory.GetFiles(DirectoryPath))
            {
                var FileHandle = new FileInfo(FoundFile);
                var CurrentNode = GetFileNode(FileHandle);
                ParentNode.Nodes.Add(CurrentNode);
                this._Nodes.Add(CurrentNode.FullPath, FileHandle.ToString());
            }
        }
        public void RemoveNode(string Path)
        {
            var KeyPath = this._Nodes.FirstOrDefault(Pair => Pair.Value.Equals(Path)).Key;
            if (string.IsNullOrEmpty(KeyPath))
                return;
            /**
            var Node = this.GetNodeFromPath(GetRootNode(), KeyPath);
             */
            var Node = this._TreeExplorer.SelectedNode;
            if (Node == null)
                return;
            Node.Remove();
            this._Nodes.Remove(KeyPath);
        }
        public void RenameNode(string Path, string NewName, string NewPath)
        {
            var KeyPath = this._Nodes.FirstOrDefault(Pair => Pair.Value.Equals(Path)).Key;
            if (string.IsNullOrEmpty(KeyPath))
                return;
            /**
            var Node = this.GetNodeFromPath(GetRootNode(), KeyPath);
             */
            var Node = this._TreeExplorer.SelectedNode;
            if (Node == null)
                return;
            Node.Text = NewName;
            this._Nodes[KeyPath] = NewPath;
        }
        public TreeNode GetNodeFromPath(TreeNode Node, string Path)
        {
            TreeNode FoundNode = null;
            foreach (TreeNode Tn in Node.Nodes)
            {
                if (Tn.FullPath == Path)
                    return Tn;
                else if (Tn.Nodes.Count > 0)
                    FoundNode = this.GetNodeFromPath(Tn, Path);
                if (FoundNode != null)
                    return FoundNode;
            }
            return null;
        }
        public void SelectRebuiltBinary(string BinaryName)
        {
            var RootNode = GetRootNode();
            if (RootNode == null || RootNode.Nodes.Count < 1)
                return;
            var DistNode = GetNodeUnderNode("dist", RootNode.Nodes);
            if (DistNode == null || DistNode.Length < 1)
                return;
            for (var _ = 0; _ < DistNode[0].Nodes.Count; _++)
            {
                var Node = DistNode[0].Nodes[_];
                if (!Node.Text.Equals(BinaryName))
                    continue;
                this._TreeExplorer.SelectedNode = Node;
                this._TreeExplorer.Focus();
                break;
            }
        }
    }
}