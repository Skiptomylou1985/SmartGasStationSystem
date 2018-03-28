using System;
using System.Collections.Generic;
using System.Text;

namespace SPServer
{
    class StationInfo
    {
        public string StationName { set; get; }

        public string StationCode { set; get;}

        public string IP { set; get; }

        public int Status { set; get; }

        public DateTime UpdateTime { set; get; }

        public int CurrentRatio { set; get; }

        public int TotalRatio { set; get; }
        public int CurrentCount { set; get; }

        public int TotalCount { set; get; }

        public string SoftVersion { set; get; }

    }
}
