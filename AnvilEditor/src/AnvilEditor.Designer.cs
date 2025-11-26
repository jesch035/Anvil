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
            Console = new ListBox();
            ToggleConsoleLoggingCheckBox = new CheckBox();
            SDLViewport = new Panel();
            SuspendLayout();
            // 
            // Console
            // 
            Console.FormattingEnabled = true;
            Console.Location = new Point(14, 459);
            Console.Margin = new Padding(3, 4, 3, 4);
            Console.Name = "Console";
            Console.Size = new Size(886, 124);
            Console.TabIndex = 0;
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
            // SDLViewport
            // 
            SDLViewport.Location = new Point(12, 12);
            SDLViewport.Name = "SDLViewport";
            SDLViewport.Size = new Size(890, 410);
            SDLViewport.TabIndex = 4;
            // 
            // AnvilEditor
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(914, 600);
            Controls.Add(SDLViewport);
            Controls.Add(ToggleConsoleLoggingCheckBox);
            Controls.Add(Console);
            Margin = new Padding(3, 4, 3, 4);
            Name = "AnvilEditor";
            Text = "AnvilEditor";
            FormClosed += AnvilEditor_FormClosed;
            Load += AnvilEditor_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private ListBox Console;
        private CheckBox ToggleConsoleLoggingCheckBox;
        private Panel SDLViewport;
    }
}
