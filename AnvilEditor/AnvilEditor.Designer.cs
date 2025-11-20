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
            SuspendLayout();
            // 
            // LogBox
            // 
            LogBox.FormattingEnabled = true;
            LogBox.Location = new Point(114, 270);
            LogBox.Name = "LogBox";
            LogBox.Size = new Size(494, 94);
            LogBox.TabIndex = 0;
            // 
            // Button
            // 
            Button.Location = new Point(302, 121);
            Button.Name = "Button";
            Button.Size = new Size(126, 23);
            Button.TabIndex = 1;
            Button.Text = "Click for message";
            Button.UseVisualStyleBackColor = true;
            Button.Click += Button_Click;
            // 
            // AnvilEditor
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(Button);
            Controls.Add(LogBox);
            Name = "AnvilEditor";
            Text = "AnvilEditor";
            ResumeLayout(false);
        }

        #endregion

        private ListBox LogBox;
        private Button Button;
    }
}
