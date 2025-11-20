namespace AnvilEditor
{
    public partial class AnvilEditor : Form
    {
        private Interop.LogCallback logCallback;
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
        }

        public AnvilEditor()
        {
            InitializeComponent();
            Interop.SetLogCallback(logCallback);
        }

        private void Button_Click(object sender, EventArgs e)
        {
            Interop.TestLoggingFunction();
        }
    }
}
