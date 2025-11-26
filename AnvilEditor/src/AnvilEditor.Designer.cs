namespace AnvilEditor
{
    partial class AnvilEditor
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            LogBox = new ListBox();
            Button = new Button();
            ToggleConsoleLoggingCheckBox = new CheckBox();
            SuspendLayout();
            // 
            // LogBox
            // 
            LogBox.FormattingEnabled = true;
            LogBox.Location = new Point(14, 459);
            LogBox.Margin = new Padding(3, 4, 3, 4);
            LogBox.Name = "LogBox";
            LogBox.Size = new Size(886, 124);
            LogBox.TabIndex = 0;
            // 
            // Button
            // 
            Button.Location = new Point(345, 161);
            Button.Margin = new Padding(3, 4, 3, 4);
            Button.Name = "Button";
            Button.Size = new Size(144, 31);
            Button.TabIndex = 1;
            Button.Text = "Click for message";
            Button.UseVisualStyleBackColor = true;
            Button.Click += Button_Click;
            // 
            // ToggleConsoleLoggingCheckBox
            // 
            ToggleConsoleLoggingCheckBox.AutoSize = true;
            ToggleConsoleLoggingCheckBox.Checked = true;
            ToggleConsoleLoggingCheckBox.CheckState = CheckState.Checked;
            ToggleConsoleLoggingCheckBox.Location = new Point(14, 428);
            ToggleConsoleLoggingCheckBox.Name = "ToggleConsoleLoggingCheckBox";
            ToggleConsoleLoggingCheckBox.Size = new Size(136, 24);
            ToggleConsoleLoggingCheckBox.TabIndex = 3;
            ToggleConsoleLoggingCheckBox.Text = "Toggle Logging";
            ToggleConsoleLoggingCheckBox.UseVisualStyleBackColor = true;
            ToggleConsoleLoggingCheckBox.CheckedChanged += ToggleConsoleLoggingCheckBox_CheckedChanged;
            // 
            // AnvilEditor
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(914, 600);
            Controls.Add(ToggleConsoleLoggingCheckBox);
            Controls.Add(Button);
            Controls.Add(LogBox);
            Margin = new Padding(3, 4, 3, 4);
            Name = "AnvilEditor";
            Text = "AnvilEditor";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private ListBox LogBox;
        private Button Button;
        private CheckBox ToggleConsoleLoggingCheckBox;
    }
}
