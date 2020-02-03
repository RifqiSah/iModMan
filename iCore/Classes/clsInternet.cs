using System;
using System.Net.NetworkInformation;

namespace iCore
{
    class clsInternet
    {
        public static bool CheckConnection()
        {
            Ping ping = new Ping();
            PingOptions pingOptions = new PingOptions();

            String host = "google.com";
            byte[] buffer = new byte[32];
            int timeout = 1000;

            
            try
            {
                var reply = ping.Send(host, timeout, buffer, pingOptions);
                return (reply != null && reply.Status == IPStatus.Success);
            }
            catch (Exception)
            {
                return false;
            }
        }
    }
}
