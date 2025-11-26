using AnvilEditor.src;

namespace AnvilEditor
{
    public partial class AnvilEditor : Form
    {
        private void OnLogReceived(string message)
        {
            if (InvokeRequired)
            {
                BeginInvoke(new Action(() => AddLog(message)));
                return;
            }

            AddLog(message);
        }

        private void AddLog(string message)
        {
            Console.Items.Add(message);
            Console.TopIndex = Console.Items.Count - 1;
        }

        public AnvilEditor()
        {
            InitializeComponent();
        }

        private void AnvilEditor_Load(object sender, EventArgs e)
        {
            Interop.InitCoreLogger(Interop.SinkFlags.CallbackSink, OnLogReceived);
            Interop.InitEditorSDL(SDLViewport.Handle, SDLViewport.Width, SDLViewport.Height);
        }

        private void ToggleConsoleLoggingCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            Interop.ToggleSinkLogs(Interop.SinkFlags.CallbackSink);
        }

        private void AnvilEditor_FormClosed(object sender, FormClosedEventArgs e)
        {
            Interop.QuitSDL();
        }
    }
}
