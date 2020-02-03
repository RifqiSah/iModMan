using System.Threading;

namespace iCore
{
    class clsMutext
    {
        public bool IsAppAplreadyRunning()
        {
            bool createdNew;
            Mutex m = new Mutex(true, "INFLauncher_Mutex", out createdNew);
            return !createdNew;
        }
    }
}
