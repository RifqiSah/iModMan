using System.Windows.Forms;

namespace iCore
{
    public class clsModule
    {
        public void InitModule()
        {
            MessageBox.Show(Form.ActiveForm, "Module loaded!", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

    }
}
