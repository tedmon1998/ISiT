using System;

namespace Lab1
{
    internal class NewListEntryEventArgs : EventArgs
    {
        private string text;

        public NewListEntryEventArgs(string text)
        {
            this.text = text;
        }
    }
}