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
            LogBox.Items.Add(message);
            LogBox.TopIndex = LogBox.Items.Count - 1;
        }

        public AnvilEditor()
        {
            InitializeComponent();

            Interop.InitEngineCore(Interop.SinkFlags.CallbackSink, OnLogReceived);
        }

        private void Button_Click(object sender, EventArgs e)
        {
            Interop.TestLoggingFunction();
        }

        private void ToggleConsoleLoggingCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            Interop.ToggleSinkLogs(Interop.SinkFlags.CallbackSink);
        }
    }
}
