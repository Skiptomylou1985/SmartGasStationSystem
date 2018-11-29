using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JsonDemo
{
    public static class Global
    {
        public static List<PumpInfo> pumpList = new List<PumpInfo>();
    }
    public class PumpInfo
    {
        public string PumpID { set; get; }

        public string PumpFlag { set; get; }

        public string GradeID { set; get; }

        public string Volume { set; get; }

        public string Value { set; get; }

        public string Time { set; get; }
    }
    public class PumpBackInfo
    {
        public string VehicleNo { set; get; }
        public string VehicleBrand { set; get; }
        public string SubBrand { set; get; }
        public string VehicleModel { set; get; }
        public string VehicleColor { set; get; }
        public string BodyColor { set; get; }
    }

    public class VehicelInfo
    {
        public string Flag { set; get; }
        public string Time { set; get; }
        public string VehicleNo { set; get; }
        public string VehicleBrand { set; get; }
        public string SubBrand { set; get; }
        public string VehicleModel { set; get; }
        public string VehicleColor { set; get; }
        public string BodyColor { set; get; }
    }
}
