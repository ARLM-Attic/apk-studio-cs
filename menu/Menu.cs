using System;
using System.Windows.Forms;

namespace APKStudio.Controller
{
    public class Menu
    {
        public enum Items
        {
            ItemAbout,
            ItemBuildRepackage,
            ItemEditCopy,
            ItemEditCut,
            ItemEditFind,
            ItemEditGoto,
            ItemEditPaste,
            ItemEditPreferences,
            ItemEditRedo,
            ItemEditReplace,
            ItemEditUndo,
            ItemFileClose,
            ItemFileExit,
            ItemFileOpen,
            ItemFileOpenDirectory,
            ItemFileSave
        }
        public interface IMainItemClick
        {
            void OnMainItemClick(Items ItemType);
        }
        private readonly IMainItemClick _ItemClickListener;
        private ToolStripMenuItem _ItemBuildRepackage;
        private ToolStripMenuItem _ItemEditCut, _ItemEditCopy, _ItemEditFind, _ItemEditGoto, _ItemEditPaste, _ItemEditPreferences, _ItemEditRedo, _ItemEditReplace, _ItemEditUndo;
        private ToolStripMenuItem _ItemFileClose, _ItemFileExit, _ItemFileOpen, _ItemFileOpenDirectory, _ItemFileSave;
        private ToolStripMenuItem _MenuAbout, _MenuEdit, _MenuFile, _MenuProperties;
        public Menu(IMainItemClick ItemClickListener)
        {
            this._ItemClickListener = ItemClickListener;
        }
        private void DisabeBetaOptions()
        {
            this.SetItemEditFindEnabled(false);
            this.SetItemEditGotoEnabled(false);
            this.SetItemEditPreferencesEnabled(false);
            this.SetItemEditReplaceEnabled(false);
        }
        public void Inflate(ref MenuStrip Menu)
        {
            Menu.Items.AddRange(new ToolStripItem[]
            {
                this.InflateFileItem(),
                this.InflateEditItem(),
                this.InflateBuildItem(),
                this.InflateAboutItem()
            });
        }
        private ToolStripMenuItem InflateAboutItem()
        {
            this._MenuAbout = new ToolStripMenuItem("About");
            this._MenuAbout.Click += OnMainItemClick;
            return this._MenuAbout;
        }
        private ToolStripMenuItem InflateBuildItem()
        {
            this._MenuProperties = new ToolStripMenuItem("Build");
            this._ItemBuildRepackage = new ToolStripMenuItem("Repackage") { Image = Resource.Images.MenuBuildRepackage };
            this._ItemBuildRepackage.Click += OnMainItemClick;
            this._MenuProperties.DropDownItems.AddRange(new ToolStripItem[]
            {
                this._ItemBuildRepackage
            });
            return this._MenuProperties;
        }
        private ToolStripMenuItem InflateEditItem()
        {
            this._MenuEdit = new ToolStripMenuItem("Edit");
            this._ItemEditCut = new ToolStripMenuItem("Cut") { Image = Resource.Images.MenuEditCut };
            this._ItemEditCut.Click += OnMainItemClick;
            this._ItemEditCopy = new ToolStripMenuItem("Copy") { Image = Resource.Images.MenuEditCopy };
            this._ItemEditCopy.Click += OnMainItemClick;
            this._ItemEditFind = new ToolStripMenuItem("Find") { Image = Resource.Images.MenuEditFind };
            this._ItemEditFind.Click += OnMainItemClick;
            this._ItemEditGoto = new ToolStripMenuItem("Goto") { Image = Resource.Images.MenuEditGoto };
            this._ItemEditGoto.Click += OnMainItemClick;
            this._ItemEditPaste = new ToolStripMenuItem("Paste") { Image = Resource.Images.MenuEditPaste };
            this._ItemEditPaste.Click += OnMainItemClick;
            this._ItemEditPreferences = new ToolStripMenuItem("Preferences") { Image = Resource.Images.MenuEditPreferences };
            this._ItemEditPreferences.Click += OnMainItemClick;
            this._ItemEditRedo = new ToolStripMenuItem("Redo") { Image = Resource.Images.MenuEditRedo };
            this._ItemEditRedo.Click += OnMainItemClick;
            this._ItemEditReplace = new ToolStripMenuItem("Replace") { Image = Resource.Images.MenuEditReplace };
            this._ItemEditReplace.Click += OnMainItemClick;
            this._ItemEditUndo = new ToolStripMenuItem("Undo") { Image = Resource.Images.MenuEditUndo };
            this._ItemEditUndo.Click += OnMainItemClick;
            this._MenuEdit.DropDownItems.AddRange(new ToolStripItem[]
            {
                this._ItemEditUndo,
                this._ItemEditRedo,
                new ToolStripSeparator(),
                this._ItemEditCut,
                this._ItemEditCopy,
                this._ItemEditPaste,
                new ToolStripSeparator(),
                this._ItemEditGoto,
                this._ItemEditFind,
                this._ItemEditReplace,
                new ToolStripSeparator(),
                this._ItemEditPreferences
            });
            return this._MenuEdit;
        }
        private ToolStripMenuItem InflateFileItem()
        {
            this._MenuFile = new ToolStripMenuItem("File");
            this._ItemFileClose = new ToolStripMenuItem("Close");
            this._ItemFileClose.Click += OnMainItemClick;
            this._ItemFileExit = new ToolStripMenuItem("Exit") { Image = Resource.Images.MenuFileExit };
            this._ItemFileExit.Click += OnMainItemClick;
            this._ItemFileOpen = new ToolStripMenuItem("Open APK") { Image = Resource.Images.MenuFileOpen };
            this._ItemFileOpen.Click += OnMainItemClick;
            this._ItemFileOpenDirectory = new ToolStripMenuItem("Open Directory") { Image = Resource.Images.MenuFileOpenDirectory };
            this._ItemFileOpenDirectory.Click += OnMainItemClick;
            this._ItemFileSave = new ToolStripMenuItem("Save") { Image = Resource.Images.MenuFileSave };
            this._ItemFileSave.Click += OnMainItemClick;
            this._MenuFile.DropDownItems.AddRange(new ToolStripItem[]
            {
                this._ItemFileOpen,
                this._ItemFileOpenDirectory,
                new ToolStripSeparator(),
                this._ItemFileSave,
                this._ItemFileClose,
                new ToolStripSeparator(),
                this._ItemFileExit
            });
            return this._MenuFile;
        }
        public void OnApkLoaded()
        {
            this.SetItemBuildRepackageEnabled(true);
        }
        public void OnApkUnloaded()
        {
            this.SetItemBuildRepackageEnabled(false);
        }
        public void OnFileLoaded()
        {
            this.SetItemEditCopyEnabled(true);
            this.SetItemEditCutEnabled(true);
            this.SetItemEditFindEnabled(true);
            this.SetItemEditGotoEnabled(true);
            this.SetItemEditPasteEnabled(true);
            this.SetItemEditPreferencesEnabled(true);
            this.SetItemEditRedoEnabled(true);
            this.SetItemEditReplaceEnabled(true);
            this.SetItemEditUndoEnabled(true);
            this.SetItemFileCloseEnabled(true);
            this.SetItemFileSaveEnabled(true);
            this.DisabeBetaOptions();
        }
        public void OnFileUnloaded()
        {
            this.SetItemEditCopyEnabled(false);
            this.SetItemEditCutEnabled(false);
            this.SetItemEditFindEnabled(false);
            this.SetItemEditGotoEnabled(false);
            this.SetItemEditPasteEnabled(false);
            this.SetItemEditPreferencesEnabled(false);
            this.SetItemEditRedoEnabled(false);
            this.SetItemEditReplaceEnabled(false);
            this.SetItemEditUndoEnabled(false);
            this.SetItemFileCloseEnabled(false);
            this.SetItemFileSaveEnabled(false);
        }
        private void OnMainItemClick(object Sender, EventArgs Event)
        {
            if ((Sender != null) && (Sender.GetType() == typeof(ToolStripMenuItem)))
            {
                if (Sender.Equals(this._MenuAbout))
                    this._ItemClickListener.OnMainItemClick(Items.ItemAbout);
                if (Sender.Equals(this._ItemBuildRepackage))
                    this._ItemClickListener.OnMainItemClick(Items.ItemBuildRepackage);
                if (Sender.Equals(this._ItemFileClose))
                    this._ItemClickListener.OnMainItemClick(Items.ItemFileClose);
                else if (Sender.Equals(this._ItemFileExit))
                    this._ItemClickListener.OnMainItemClick(Items.ItemFileExit);
                else if (Sender.Equals(this._ItemFileOpen))
                    this._ItemClickListener.OnMainItemClick(Items.ItemFileOpen);
                else if (Sender.Equals(this._ItemFileOpenDirectory))
                    this._ItemClickListener.OnMainItemClick(Items.ItemFileOpenDirectory);
                else if (Sender.Equals(this._ItemFileSave))
                    this._ItemClickListener.OnMainItemClick(Items.ItemFileSave);
                else if (Sender.Equals(this._ItemEditCut))
                    this._ItemClickListener.OnMainItemClick(Items.ItemEditCut);
                else if (Sender.Equals(this._ItemEditCopy))
                    this._ItemClickListener.OnMainItemClick(Items.ItemEditCopy);
                else if (Sender.Equals(this._ItemEditFind))
                    this._ItemClickListener.OnMainItemClick(Items.ItemEditFind);
                else if (Sender.Equals(this._ItemEditGoto))
                    this._ItemClickListener.OnMainItemClick(Items.ItemEditGoto);
                else if (Sender.Equals(this._ItemEditPaste))
                    this._ItemClickListener.OnMainItemClick(Items.ItemEditPaste);
                else if (Sender.Equals(this._ItemEditPreferences))
                    this._ItemClickListener.OnMainItemClick(Items.ItemEditPreferences);
                else if (Sender.Equals(this._ItemEditRedo))
                    this._ItemClickListener.OnMainItemClick(Items.ItemEditRedo);
                else if (Sender.Equals(this._ItemEditUndo))
                    this._ItemClickListener.OnMainItemClick(Items.ItemEditUndo);
            }
        }
        public void SetItemEditCopyEnabled(bool Enabled)
        {
            this._ItemEditCopy.Enabled = Enabled;
        }
        public void SetItemEditCutEnabled(bool Enabled)
        {
            this._ItemEditCut.Enabled = Enabled;
        }
        public void SetItemEditFindEnabled(bool Enabled)
        {
            this._ItemEditFind.Enabled = Enabled;
        }
        public void SetItemEditGotoEnabled(bool Enabled)
        {
            this._ItemEditGoto.Enabled = Enabled;
        }
        public void SetItemEditPasteEnabled(bool Enabled)
        {
            this._ItemEditPaste.Enabled = Enabled;
        }
        public void SetItemEditPreferencesEnabled(bool Enabled)
        {
            this._ItemEditPreferences.Enabled = Enabled;
        }
        public void SetItemEditRedoEnabled(bool Enabled)
        {
            this._ItemEditRedo.Enabled = Enabled;
        }
        public void SetItemEditReplaceEnabled(bool Enabled)
        {
            this._ItemEditReplace.Enabled = Enabled;
        }
        public void SetItemEditUndoEnabled(bool Enabled)
        {
            this._ItemEditUndo.Enabled = Enabled;
        }
        public void SetItemFileCloseEnabled(bool Enabled)
        {
            this._ItemFileClose.Enabled = Enabled;
        }
        public void SetItemFileSaveEnabled(bool Enabled)
        {
            this._ItemFileSave.Enabled = Enabled;
        }
        public void SetItemBuildRepackageEnabled(bool Enabled)
        {
            this._ItemBuildRepackage.Enabled = Enabled;
        }
    }
}
