using System;
using System.Windows.Forms;

namespace APKStudio.Window
{
    public partial class Rename : Form
    {
        public string Result { get; set; }
        // private readonly TextEditorControl _Editor;
        public Rename(string OldName)
        {
            InitializeComponent();
            if (!string.IsNullOrEmpty(OldName))
                this.DesignTextboxNewname.Text = OldName;
        }
        private void OnFindButtonClick(object Sender, EventArgs Event)
        {
            if (!string.IsNullOrEmpty(this.DesignTextboxNewname.Text))
                this.Result = this.DesignTextboxNewname.Text;
            // this._Editor.ActiveTextAreaControl.ScrollToCaret();
            // this.Focus();
            this.Close();
        }
        /**
        void Some()
        {
            this._Find(this.DesignTextboxNewname.Text, this._Editor.Text);
        }
        private int _LastLine = 0;
        private int _LastIndex = 0;
        private void _Find(string Needle, string Haystack)
        {
            this.DesignButtonCommit.Enabled = false;
            var Found = false;
            var CurrentLine = 0;
            foreach (var Line in Haystack.Split(new string[] { Environment.NewLine }, StringSplitOptions.None))
            {
                if (CurrentLine == _LastLine && _LastIndex < Line.Length)
                {
                    var CurrentText = _LastIndex > 0 ? Line.Substring((this._LastIndex - 1)) : Line;
                    var CurrentIndex = Strings.InStr(1, CurrentText, this.DesignTextboxNewname.Text, SearchType);
                    if (CurrentIndex > 0)
                    {
                        _LastIndex += CurrentIndex;
                        _LastLine = CurrentLine;
                        Found = true;
                        break;
                    }
                    _LastIndex = 0;
                    CurrentLine++;
                }
                else if (CurrentLine > _LastLine)
                {
                    var CurrentIndex = Strings.InStr(1, Line, this.DesignTextboxNewname.Text, SearchType);
                    if (CurrentIndex > 0)
                    {
                        _LastIndex = CurrentIndex;
                        _LastLine = CurrentLine;
                        Found = true;
                        break;
                    }
                }
                else
                    CurrentLine++;
            }
            if (Found && _LastIndex > 0 && _LastLine > 0)
            {
                this.HighlighText((_LastIndex - 1), ((_LastIndex - 1) + Needle.Length), _LastLine);
            }
            else
            {
                MessageBox.Show(@"SearchText: " + this.DesignTextboxNewname.Text + @" not found in active editor", @"No Matches", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                _LastLine = 0;
                _LastIndex = 0;
            }
            this.DesignButtonCommit.Enabled = true;
        }
        private void HighlighText(int StartLocation, int StopLocation, int Line)
        {
            ISelection Selection = new DefaultSelection(this._Editor.Document, new TextLocation(StartLocation, Line), new TextLocation(StopLocation, Line));
            this._Editor.ActiveTextAreaControl.SelectionManager.SetSelection(Selection);
            this._Editor.ActiveTextAreaControl.ScrollTo(Line, StartLocation);
        }
        **/
    }
}
