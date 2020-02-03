using System;
using System.IO;
using System.Security.Cryptography;

namespace iCore
{
    class clsCrypto
    {
        public string SHA1CheckSum(string sFile)
        {
            using (FileStream stream = File.OpenRead(sFile))
            {
                SHA1Managed sha = new SHA1Managed();
                byte[] checksum = sha.ComputeHash(stream);
                return BitConverter.ToString(checksum).Replace("-", String.Empty);
            }
        }

        public string SHA256CheckSum(string sFile)
        {
            using (FileStream stream = File.OpenRead(sFile))
            {
                SHA256Managed sha = new SHA256Managed();
                byte[] checksum = sha.ComputeHash(stream);
                return BitConverter.ToString(checksum).Replace("-", String.Empty);
            }
        }
        public string SHA384CheckSum(string sFile)
        {
            using (FileStream stream = File.OpenRead(sFile))
            {
                SHA384Managed sha = new SHA384Managed();
                byte[] checksum = sha.ComputeHash(stream);
                return BitConverter.ToString(checksum).Replace("-", String.Empty);
            }
        }

        public string SHA512CheckSum(string sFile)
        {
            using (FileStream stream = File.OpenRead(sFile))
            {
                SHA512Managed sha = new SHA512Managed();
                byte[] checksum = sha.ComputeHash(stream);
                return BitConverter.ToString(checksum).Replace("-", String.Empty);
            }
        }
    }
}
