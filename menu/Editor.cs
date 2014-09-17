using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;
using APKStudio.Resource;
using APKStudio.Window;
using ICSharpCode.TextEditor;

namespace APKStudio.Controller
{
    public class Editor
    {
        public enum Selection
        {
            Save,
            Close,
            Copy,
            Cut,
            Paste
        }
        private readonly OrderedDictionary _Tabs;
        private String[] _Keys;
        private readonly TabControl _DesignTabsetEditor;
        private const int   IconFileJava = 0,
                            IconFilePng = 1,
                            IconFileRaw = 2,
                            IconFileRsa = 3,
                            IconFileSmali = 4,
                            IconFileXml = 5;

        private readonly Menu.IMainItemClick _Listener;
        public Editor(Menu.IMainItemClick Listener, TabControl DesignTabsetEditor)
        {
            this._Listener = Listener;
            this._DesignTabsetEditor = DesignTabsetEditor;
            this._DesignTabsetEditor.ImageList = new ImageList();
            this._DesignTabsetEditor.ImageList.Images.Add(Images.TreeFileJava);
            this._DesignTabsetEditor.ImageList.Images.Add(Images.TreeFilePng);
            this._DesignTabsetEditor.ImageList.Images.Add(Images.TreeFileRaw);
            this._DesignTabsetEditor.ImageList.Images.Add(Images.TreeFileRsa);
            this._DesignTabsetEditor.ImageList.Images.Add(Images.TreeFileSmali);
            this._DesignTabsetEditor.ImageList.Images.Add(Images.TreeFileXml);
            this._Tabs = new OrderedDictionary();
        }
        public void Close()
        {
            if (this._DesignTabsetEditor.Controls.Count > 0)
            {
                this._Tabs.RemoveAt(this._DesignTabsetEditor.SelectedIndex);
                this._DesignTabsetEditor.Controls.Remove(this._DesignTabsetEditor.SelectedTab);
            }
        }
        private ContextMenuStrip GetContextMenu()
        {
            var ContextStrip = new ContextMenuStrip();
            var CloseItem = new ToolStripMenuItem("Close");
            CloseItem.Click += OnContextCloseClick;
            var CopyItem = new ToolStripMenuItem("Copy", Images.MenuEditCopy);
            CopyItem.Click += OnContextCopyClick;
            var CutItem = new ToolStripMenuItem("Cut", Images.MenuEditCut);
            CutItem.Click += OnContextCutClick;
            var PasteItem = new ToolStripMenuItem("Paste", Images.MenuEditPaste);
            PasteItem.Click += OnContextPasteClick;
            var SaveItem = new ToolStripMenuItem("Save", Images.MenuFileSave);
            SaveItem.Click += OnContextSaveClick;
            ContextStrip.Items.Add(SaveItem);
            ContextStrip.Items.Add("-");
            ContextStrip.Items.Add(CutItem);
            ContextStrip.Items.Add(CopyItem);
            ContextStrip.Items.Add(PasteItem);
            ContextStrip.Items.Add("-");
            ContextStrip.Items.Add(CloseItem);
            return ContextStrip;
        }
        private int GetFileIconIndex(string Extension)
        {
            switch (Extension)
            {
                case ".java":
                    return IconFileJava;
                case ".png":
                    return IconFilePng;
                case ".rsa":
                    return IconFileRsa;
                case ".smali":
                    return IconFileSmali;
                case ".xml":
                    return IconFileXml;
                default:
                    return IconFileRaw;
            }
        }
        private int GetIndex(string Key)
        {
            for (var _ = 0; _ < this._Tabs.Count; _++)
            {
                if (this._Tabs[_] == this._Tabs[Key])
                    return _;
            }
            return -1;
        }
        private void OnContextCloseClick(object Sender, EventArgs Arguments)
        {
            this._Listener.OnMainItemClick(Menu.Items.ItemFileClose);
        }
        private void OnContextCopyClick(object Sender, EventArgs Arguments)
        {
            this._Listener.OnMainItemClick(Menu.Items.ItemEditCopy);
        }
        private void OnContextCutClick(object Sender, EventArgs Arguments)
        {
            this._Listener.OnMainItemClick(Menu.Items.ItemEditCut);
        }
        private void OnContextPasteClick(object Sender, EventArgs Arguments)
        {
            this._Listener.OnMainItemClick(Menu.Items.ItemEditPaste);
        }
        private void OnContextSaveClick(object Sender, EventArgs Arguments)
        {
            this._Listener.OnMainItemClick(Menu.Items.ItemFileSave);
        }
        private void OnMouseClick(object Sender, MouseEventArgs Event)
        {
            if (Event.Button == MouseButtons.Right)
            {
                var ContextStrip = this.GetContextMenu();
                var ClickPoint = new Point(Event.X, Event.Y);
                ContextStrip.Show((TextArea)Sender, ClickPoint);
            }
        }
        public void Open(string Path)
        {
            if (this._Tabs.Contains(Path))
            {
                var Index = GetIndex(Path);
                if (Index > -1)
                    this._DesignTabsetEditor.SelectTab(Index);
            }
            else if (File.Exists(Path))
            {
                var SourceInfo = new FileInfo(Path);
                var Extension = SourceInfo.Extension;
                var CodeEditor = new TextEditorControl
                    {
                        BorderStyle = BorderStyle.None,
                        Dock = DockStyle.Fill,
                        EnableFolding = true,
                        TextEditorProperties = {EnableFolding = true}
                    };
                CodeEditor.ActiveTextAreaControl.TextArea.MouseClick += this.OnMouseClick;
                bool Continue = false;
                if (!string.IsNullOrEmpty(SourceInfo.Extension))
                {
                    switch (Extension.ToLower())
                    {
                        case ".java":
                            CodeEditor.SetHighlighting("Java");
                            Continue = true;
                            break;
                        case ".smali":
                            CodeEditor.SetHighlighting("Smali");
                            Continue = true;
                            break;
                        case ".xml":
                            CodeEditor.SetHighlighting("XML");
                            Continue = true;
                            break;
                    }
                }
                if (Continue)
                {
                    try
                    {
                        CodeEditor.LoadFile(@Path);
                        var NewTab = new TabPage { Text = SourceInfo.Name, ImageIndex = GetFileIconIndex(SourceInfo.Extension.ToLower()) };
                        NewTab.Controls.Add(CodeEditor);
                        this._Tabs.Add(Path, NewTab);
                        this._DesignTabsetEditor.Controls.Add(NewTab);
                        this._DesignTabsetEditor.SelectTab(NewTab);
                        this._DesignTabsetEditor.Focus();
                        this._Keys = new string[this._Tabs.Count + 1];
                        var Collection = this._Tabs.Keys;
                        Collection.CopyTo(this._Keys, 0);
                    }
                    catch (Exception Error)
                    {
                        //
                    }
                }
            }
        }
        public void Find()
        {
            /**
            if (this._DesignTabsetEditor.Controls.Count > 0)
            {
                foreach (var Editor in this._DesignTabsetEditor.SelectedTab.Controls.OfType<TextEditorControl>())
                {
                    var FindForm = new Rename(Editor);
                    FindForm.ShowDialog();
                }
            }
            **/
        }
        public void Redo()
        {
            if (this._DesignTabsetEditor.Controls.Count > 0)
            {
                foreach (var Editor in this._DesignTabsetEditor.SelectedTab.Controls.OfType<TextEditorControl>())
                    Editor.Redo();
            }
        }
        public void Save()
        {
            if (this._DesignTabsetEditor.Controls.Count > 0)
            {
                foreach (var Editor in this._DesignTabsetEditor.SelectedTab.Controls.OfType<TextEditorControl>())
                    Editor.SaveFile(this._Keys[this._DesignTabsetEditor.SelectedTab.TabIndex]);
            }
        }
        public void Undo()
        {
            if (this._DesignTabsetEditor.Controls.Count > 0)
            {
                foreach (var Editor in this._DesignTabsetEditor.SelectedTab.Controls.OfType<TextEditorControl>())
                {
                    Editor.FindForm();
                    Editor.Undo();
                }
            }
        }
    }
}