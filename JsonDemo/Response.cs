using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JsonDemo
{
    class Response
    {
        //返回结果，成功 or 失败
        public bool Result { get; set; }

        /*
         * Cmd:操作类型
         * 0x01: 下发新工单
         */
        public int Cmd { get; set; }

        /*
         * ErrorCode:常见错误类型，返回结果Result为fasle时生效
         * 0: 未知错误
         * -1:数据格式错误
         * -2：数据重复
         * -3：参数异常
         */
        public int ErrorCode { get; set; }

        //备注
        public string Remark { get; set; }

    }
}
