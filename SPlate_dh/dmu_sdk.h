/**
 * Copyright (c) 2014, 浙江大华系统工程有限公司 All rights reserved.
 * \file		dmu_sdk.h
 * \brief		dmu_sdk
 * \author		24997
 * \date		2014年12月19日
 * \note		DMU SDK 接口
 */
#ifndef IBP_DMU_SDK_H
#define IBP_DMU_SDK_H

#if !defined(t_uint32)
typedef unsigned int t_uint32;
#endif

#if !defined(t_int32)
typedef int t_int32;
#endif

#if !defined(t_float32)
typedef float t_float32;
#endif

#ifdef WIN32
#ifdef IBPDMUSDK_LIB_EXPORTS
#define DLIB_API __declspec(dllexport)
#else
#define DLIB_API __declspec(dllimport)
#endif  //DLIB_EXPORTS
#define CALLBACK __stdcall
#else
#define DLIB_API
#define CALLBACK
#endif   //WIN32

#ifdef __cplusplus
extern "C" 
{
#endif

/**
* @defgroup DMU_SDK函数
* @{
*/

#pragma region 通用功能



/**
* @defgroup DMU_SDK系统
* @{
*/

/**
@brief DMU_SDK初始化
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_Init();


/**
@brief DMU_SDK初始化,服务或者已经启动applicationBase的程序调用
@return 
@remarks
@see DMU_SC_InitNoApp
*/
DLIB_API t_int32 DMU_SC_InitNoApp();

/**
@brief DMU_SDK反初始化
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_Cleanup();

/** @} */

/**
* @defgroup DMU_SDK连接服务
* @{
*/

/**
@brief 连接DMU服务
@param [in]  timeout		超时时间
@param [in]  cmusession		CMU登陆句柄
@param [in]  ipinfo		    DMU服务的ip信息
@param [in]  svrdomid		DMU服务的域id
@param [in]  serverid		DMU服务id
@param [out] outxml			返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<handle></handle>		连接成功返回的句柄
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_AC_Connect(t_uint32 cmusession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
@brief 用户认证连接DMU服务
@param [in]  timeout		超时时间
@param [in]  usersession	用户认证
@param [in]  ipinfo		    DMU服务的ip信息
@param [in]  svrdomid		DMU服务的域id
@param [in]  serverid		DMU服务id
@param [out] outxml			返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<handle></handle>		连接成功返回的句柄
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_AC_ConnectNoCmu(t_uint32 usersession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
* @defgroup DMU_SDK同步连接
* @{
*/
/**
@brief 同步连接dmu
@param [in] cmuLoginHandle	cmu验证session
@param [in] timeout			超时时间
@param [in] ipInfo			dmu服务ip信息
@param [in] svrDomId		服务域id
@param [in] svrId			服务id
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<dmusession>2</dmusession>
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_Connect(t_uint32 cmuLoginHandle, t_int32 timeout, char *ipInfo, char *svrDomId, t_int32 svrId, char *outxml, t_uint32 maxlen);


/**
@brief 断开DMU服务
@param [in]  session		连接句柄
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_Disconn(t_uint32 session);

/** @} */

/**
* @defgroup DMU_SDK回调函数
* @{
*/

/**
@brief 消息回调函数
@param [in] session		连接句柄
@param [in] data		消息数据
@param [in] bufSize	    数据长度
@param [in] pUser		用户自定义数据
@return 
@remarks
@see 
*/
typedef t_int32 (*fIbpDmuMsgCallBack)(t_uint32 session, char *data, t_uint32 bufSize, void* pUser);

/**
@brief 设置消息回调函数
@param [in] session		连接句柄
@param [in] cb			回调函数
@param [in] pUser		用户数据
@return 
@remarks 回调消息示例
@verbatim
服务online消息通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="DMU" type="onlineNotify" cmd="onlineNotify" sequence="0" length="0">
	<server 
		servername="" 			服务名称
		session="" 				服务句柄
		status="" 				上下线状态
	/>
</root>
@endverbatim
@verbatim
报告master更新通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="reportMasterUpdate" sequence="" session="0">
	<domid></domid>				域ID
	<modulename></modulename>	模块名称
</root>
@endverbatim
@verbatim
告警数据通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="alarmData" sequence="">
	<item
		domid=""				域ID
		devcode=""				设备代码
		devname=""				设备名称
		subdevcode=""			子设备代码
		name=""					子设备名称
		chncode=""				资源或通道代码
		chnname=""				资源或通道名称
		chnidx=""				资源或通道索引
		type=""					告警类型
		subtype=""				告警子类型
		status=""				状态
		level=""				告警等级 0 无 1 严重 2 重要 3 一般 4 次要 5普通
		alarmtime=""			告警上报时间
		msgtxt=""				消息内容
		val=""					值
		unit=""					单位
		orgpath=""				组织设备路径
		title=""				组织设备路径名
		longitude=""            经度(单位是百万分之度，范围0-360度)
		latitude=""             纬度(单位是百万分之度，范围0-180度)
		phonedomid=""			话机域
		phonecode=""			话机编码
		phonenum=""				话机号码
		phonepass=""			话机密码
	/>
</root>
@endverbatim
@verbatim
实时数据通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="realData" sequence="">
	<item
		domid=""				域ID
		devcode=""				设备代码
		subdevcode=""			子设备代码
		chncode=""				通道代码
		chnidx=""				通道索引
		val=""					值
		unit=""					单位
		desc=""					描述
		time=""					时间
		isalarm=""				是否告警
		type=""					告警类型
		level=""				告警等级
		orgpath=""			
		title=""
		phonedomid=""			话机域
		phonecode=""			话机编码
		phonenum=""				话机号码
		phonepass=""			话机密码

		intparam1=""			gps定位星数
		intparam2=""			gps天线状态(true 好，false 坏)
		intparam3=""			gps定位状态(true 定位，false 不定位)
		strparam1=""
		strparam2=""
		strparam3=""
	>
		<expand					    pgs扩展信息
			longitude=""			经度(单位是百万分之度，范围0-360度)
			latitude=""				纬度(单位是百万分之度，范围0-180度)
			height=""				高度(米)
			angle=""				方向角(正北方向为原点，顺时针为正)
			speed=""				速度(单位是海里，speed/1000*1.852公里/小时)
		/>
	</item>
</root>
@endverbatim
@verbatim
修改预置点通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="modifyPrepointNotify" sequence="">
	<domid></domid>				域ID
	<devcode></devcode>			设备代码
	<index></index>				预置点号
	<name></name>				名称
	<operate></operate>			操作类型
	<userid></userid>			用户ID
	<username></username>		用户名称
	<level>1</level>			用户级别
	<updatetime></updatetime>	操作时间
</root>
@endverbatim
@verbatim
修改OSD通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="modifyOSDNotify" sequence="">
	<opt 
		domid="" 				域ID
		devcode="" 				设备代码
		userid="" 				用户ID
		operate="" 				操作类型
		count=""				操作数量
	>
		<info 
			type="" 			修改类型 1 修改OSD标签 2 修改OSD时间
			pointx="" 			原点X坐标
			pointy="" 			原点Y坐标
			width="" 			宽度
			length="" 			高度
			rgb="" 				RGB值
			alpha="" 			ALPHA值
			title=""			标签内容
		/>
	</opt>
</root>
@endverbatim
@verbatim
云台抢占通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="ptzArrange" sequence="">
	<domid></domid>				域ID
	<chncode></chncode>			通道代码
	<userid></userid>			用户ID
	<username>0</username>		用户名 
	<level></level>				用户级别
	<department></department>	部门
	<locktime></locktime>		锁定时间
</root>
@endverbatim
@verbatim
查询局域网设备结果通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="searchDevRetNotify" sequence="">
	<devcode>abc</devcode>
	<type>1</type>
	<ip></ip>
	<port>1</port>
	<mac></mac>
</root>
@endverbatim
@see 
*/
DLIB_API t_int32 DMU_SC_SetDmuMsg(t_uint32 session, fIbpDmuMsgCallBack cb, void* pUser);

/**
@brief 设置回调告警数据缓存配置
@param [in] session		连接句柄
@param [in] num			告警条数(默认设置100条)
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_SetAlarmDataCfg(t_uint32 session, t_int32 num);

/**
@brief 查询最新回调告警数据
@param [in] session		连接句柄
@param [out] outxml		返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		domid=""			域ID
		devcode=""			设备代码
		devname=""			设备名称
		subdevcode=""		子设备代码
		name=""				子设备名称
		chncode=""			资源或通道代码
		chnname=""			资源或通道名称
		chnidx=""			资源或通道索引
		type=""				告警类型
		subtype=""			告警子类型
		status=""			状态
		level=""			告警等级
		alarmtime=""		告警上报时间
		msgtxt=""			消息内容
		val=""				值
		unit=""				单位
		orgpath=""			组织设备路径
		title=""			组织设备路径名
	/>
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_QueryNewAlarmData(t_uint32 session, char *outxml, t_uint32 maxlen);

/**
@brief 设置回调非设备上下线的告警消息
@param [in] session		连接句柄
@param [in] flag		回调标识 0 默认不回调 1 回调
@return
@remarks 如果想实时回调告警消息，请调用此接口
@see 
*/
DLIB_API t_int32 DMU_SC_OpenCbAlarmData(t_uint32 session, t_int32 flag);

/** @} */

/**
* @defgroup DMU_SDK告警订阅
* @{
*/

/**
@brief 设置订阅全部告警或实时数据标识
@param [in] session				连接句柄
@param [in] subscribeflag		告警全部订阅标识 0 默认否 1 是
@param [in] distributeflag		分发设备授权标识 0 否 1 默认是
@return
@remarks 1、默认时，无须调用此接口 2、有需要，连接成功后立即调用
@see 
*/
DLIB_API t_int32 DMU_SC_SetSubAllAlarm(t_uint32 session, t_int32 subscribeflag = 0, t_int32 distributeflag = 1);

/**
@brief 操作告警或实时数据订阅
@param [in] session		连接句柄
@param [in] timeout		超时时间
@param [in] info		操作xml
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt
		type=""			子类型 0 告警订阅 1 实时数据订阅 2pgs信息 
		level=""		所有告警等级 -1 表示订阅告警 1~5表订阅等级统一修改位该等级
	>
		<item 
			operate=""	操作类型
			flag=""		0：订阅具体的设备；1：订阅组织；2:订阅通道
			devcode=""	设备代码(为组织时，填写路径)
			domid=""	设备域ID
			type=""		告警类型 -1 所有类型
			level=""	告警等级 5 高于等于该等级的告警都可以收到
		/>
		....

	</opt>
</root>
@endverbatim
@return
@remarks 订阅组织就是订阅组织及其下所有设备
@see 
*/
DLIB_API t_int32 DMU_SC_OptSubscribe(t_uint32 session, t_int32 timeout, char *info);


/**
@brief 操作告警或实时数据订阅（订阅用户）
@param [in] session		连接句柄
@param [in] timeout		超时时间
@param [in] info		操作xml
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt
		type=""			子类型 0 告警订阅 1 实时数据订阅 2pgs信息 3 订阅用户告警
		level=""		所有告警等级 -1 表示订阅告警 1~5表订阅等级统一修改为该等级
		userid=""       订阅用户的useid
	>
		<item 
			operate=""	操作类型
			flag=""		0：订阅具体的设备；1：订阅组织; 2 订阅通道; 
			flaguser=""	0 订阅用户 1 订阅用户组织
			devcode=""  设备编码（订阅组织时填组织路径）
			userid=""	被订阅用户id(为组织时不填，下面orgpath填写路径)
			orgpath=""  被订阅用户组织路径
			domid=""	域ID
			type=""		告警类型 -1 所有类型
			level=""	告警等级 5 高于等于该等级的告警都可以收到
		/>
		......
	</opt>
</root>
@endverbatim
@return
@remarks 订阅组织就是订阅组织及其下所有用户
@see 
*/
DLIB_API t_int32 DMU_SC_OptSubscribeUser(t_uint32 session, t_int32 timeout, char *info);

/**
@brief 查询用户告警或实时数据订阅
@param [in] session		连接句柄
@param [in] timeout		超时时间
@param [in] subtype		子类型 0 告警订阅 1 实时数据订阅 2 设备GPS告警 3 用户告警
@param [in] userid		订阅用户userid；userId=0 查所有用户，userId!=0查指定用户。
@param [out] outxml		返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		userid=""		用户ID
		devcode=""		设备代码
		domid=""		设备域ID
		type=""			告警类型
		level=""		告警等级
	/>
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_QuerySubscribe(t_uint32 session, t_int32 timeout, t_int32 subtype, t_int32 userid, char *outxml, t_uint32 maxlen);


/**
@brief 查询用户告警或实时数据订阅
@param [in] session		连接句柄
@param [in] timeout		超时时间
@param [in] subtype		子类型 0 告警订阅 1 实时数据订阅
@param [out] outxml		返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		userid=""		用户ID(阿里订阅查询)，userId=0 查所有用户，userId!=0查指定用户。
		devcode=""		设备代码
		domid=""		设备域ID
		type=""			告警类型
		level=""		告警等级
	/>
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return
@remarks
@see 
*/
//DLIB_API t_int32 DMU_SC_QueryUserSubscribe(t_uint32 session, t_int32 timeout, t_int32 subtype, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK视频OSD信息
* @{
*/

/**
@brief 操作OSD信息
@param [in] session		连接句柄
@param [in] timeout		超时时间
@param [in] info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt 
		domid=""		域ID
		devcode=""		设备代码
		operate=""		操作类型
		count=""		OSD数量
	>
		<item 
			type=""		OSD索引类型 1 名称OSD 2 时间OSD
			pointx=""	原点X坐标
			pointy=""	原点Y坐标
			width=""	宽度
			length=""	长度
			rgb=""		RGB值
			alapha=""	ALAPHA值
			title=""	标签
		/>
	</opt>
</root>
@endverbatim
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_OptOsdInfo(t_uint32 session, t_int32 timeout, char* info);

/**
@brief 获取OSD信息
@param [in]  session		连接句柄
@param [in]  timeout		超时时间
@param [in]  domainid		设备域id
@param [in]  chncode		通道编码
@param [in]  idx			信息索引 0 全部 1 名称OSD 2 时间OSD
@param [out] outxml			返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item type="" pointx="" pointy="" width="" length="" rgb="" alapha="" title="" />
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_QueryOsdInfo(t_uint32 session, t_int32 timeout, char* domainid, char* chncode, t_int32 idx, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK预置点
* @{
*/

/**
@brief 操作预置点
@param [in] session			连接句柄
@param [in] timeout			超时时间
@param [in] info			操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<srcdomid></srcdomid>	源发起域ID
	<domid></domid>			设备域ID
	<devcode></devcode>		通道设备代码
	<chnidx></chnidx>		通道序号(不填)
	<index></index>			预置点ID
	<name></name>			预置点名称
	<flag></flag>			是否为默认预置点，1 默认预置点，0 非默认预置点
	<interval></interval>	flag为1时，设备回归默认预置点时间间隔
	<operate></operate>		操作类型 0 添加，1修改，2删除
</root>
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptPrepoint(t_uint32 session, t_int32 timeout, char *info);

/**
@brief 获取预置点
@param [in] session			连接句柄
@param [in] timeout			超时时间
@param [in] domainid		设备域id
@param [in] chncode			通道编码
@param [out] outxml			返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<count></count>			数量
	<item 
		index=""			预置点编号
		name=""				预置点名称
		flag=""				标志，1 默认预置点，0 非默认预置点
		revered=""			保留
	/>
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_QueryPrepoint(t_uint32 session, t_int32 timeout, char* domainid, char* chncode, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK云台控制
* @{
*/

/**
@brief 云台控制
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] info				操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>				域ID
	<chncode></chncode>			通道代码
	<stop></stop>				停止位，1表示停止，0表示开启
	<cmd></cmd>					控制命令
	<intparam1></intparam1>		参数1
	<intparam2></intparam2>		参数2
	<intparam3></intparam3>		参数3
	<intparam4></intparam4>		参数4
	<intparam5></intparam5>		参数5
	<intparam6></intparam6>		参数6
	<intparam7></intparam7>		参数7
	<intparam8></intparam8>		参数8
	<strparam1></strparam1>		字符串参数1
	<strparam2></strparam2>		字符串参数2
</root>
@endverbatim
@param [out] outxml				错误码信息
@param [in]  maxlen				信息最大长度
@return
@remarks 
@verbatim
控制命令定义
	0 ePTZCmd_Unknown,			未知
	1 ePTZCmd_Up,               向上 
	2 ePTZCmd_Down,             向下
	3 ePTZCmd_Left,		        向左
	4 ePTZCmd_Right,		    向右
	5 ePTZCmd_LeftUp,           左上 
	6 ePTZCmd_RightUp,          右上 
	7 ePTZCmd_LeftDown,         左下 
	8 ePTZCmd_RightDown,        右下 
	9 ePTZCmd_GotoPreset,       转到预置点 
	10 ePTZCmd_SetPreset,       设置预置点
	11 ePTZCmd_ClearPreset,     清除预置点
	12 ePTZCmd_QuickOrient,     三维快速定位 
	13 ePTZCmd_Zoom_Tele,       焦距拉进 
	14 ePTZCmd_Zoom_Wide,       焦距拉远 
	15 ePTZCmd_Focus_Near,      焦点调进 
	16 ePTZCmd_Focus_Far,       焦点调远 
	17 ePTZCmd_Iris_Auto,       光圈自动调整 
	18 ePTZCmd_Iris_Large,      光圈增大 
	19 ePTZCmd_Iris_Small,      光圈缩小
	20 ePTZCmd_Aux_On,          擦拭启动
	21 ePTZCmd_Aux_Off,         擦拭停止
	22 ePTZCmd_Light_On ,       灯光开启 
	23 ePTZCmd_Light_Off,       灯光关闭
	24 ePTZCmd_StartTour,       开始自动巡航
	25 ePTZCmd_StopTour,        停止自动巡航 
	26 ePTZCmd_AutoPan_On,      水平巡航启动 
	27 ePTZCmd_AutoPan_Off      水平巡航停止 
	39 ePTZCmd_IOControl		IO状态控制(报警输出控制)
	40 ePTZCmd_LockPtz			云台加解锁控制(stop:1 解锁 0 锁定)
针对不同命令参数说明（未说明参数不填或者默认）
1、3D定位命令
	intparam1					顶点X坐标
	intparam2					底点X坐标
	intparam3					顶点Y坐标
	intparam4					底点Y坐标
2、预置点命令
	intparam2					预置点索引
3、其它命令
	intparam1					垂直速度
	intparam2					水平速度
@endverbatim
@see 
*/
DLIB_API t_int32 DMU_SC_PTZControl(t_uint32 session, t_int32 timeout, char *info, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK查询告警数据
* @{
*/

/**
@brief 查询历史告警信息
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]	 info				条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<srcdomid />		发起域ID
	<starttime />		开始时间
	<endtime />			结束时间
	<type />			告警类型 -1 查询全部 其它查询指定
	<domid />			设备域ID
	<devcode />			通道设备代码，比如"'chn0','chn1','chn2'"
	<chnidx />			通道序号
	<domdevcode />		设备域ID+设备代码，比如"'chn0','chn1','chn2'@domid1; 'chn0','chn1','chn2'@domid2"
	<size />			每页大小
	<curpage />			查询第几页
	<orgcode />		    组织编码(orgcode跟devcode只能存在一个)
</root>
@endverbatim
@param [out] outxml				返回信息

// 注意devcode，如果是设备告警，devcode就是设备编码
// 如果是通道告警，devcode就是通道编码

@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>				总数
	<item 
		id=""					告警记录ID
		domid=""				域ID
		devcode=""				设备代码
		devname=""				设备名称
		chnidx=""				通道索引
		devtype=""				设备类型
		type=""					告警类型
		status=""				状态
		level=""				告警等级
		alarmtime=""			告警时间
		length=""				数据长度
		msgtxt=""				消息文本
		confirmor=""			确认人
		confirmtime=""			确认时间
		confirmmsg=""			确认消息
		confirmstatus=""		确认状态
	/>
	...
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryHistoryAlarmInfo(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 操作告警确认信息
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]	 info				操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<confirmtime></confirmtime>	告警消息日期(处理告警时间)
	<item 
		id=""					告警记录ID
		confirmmsg=""			确认信息
		confirmstatus=""		确认状态 0 未确认 1 已确认
	/>
</root>
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptAlarmConfirm(t_uint32 session, t_int32 timeout, char *info);


/**
@brief 操作批量用户告警确认信息
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]	 info				操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total><total>                 		总数
	<confirmmsg><confirmmsg>			确认消警意见
	<item
		revalarmusername=""				消警用户名称
		revalarmuserid=""				消警用户id
		username=""						告警用户名称（服务查DB）
		userid=""						告警用户id
		domid=""                        告警域ID
		devcode=""                      告警设备编码
		chncode=""						告警通道编码
		orgpath=""                      组织路径（服务查DB）
		devtype=""                      设备类型
		type=""							告警类型
		guid=""							告警guid                     
	/>
	......
</root>
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptBatchPhoneAlarmConfirm(t_uint32 session, t_int32 timeout, char *info);

/**
@brief 查询案件告警信息
@param [in]  session                       连接句柄
@param [in]  timeout                      超时时间
@param [in]    info                                     条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
         <srcdomid />             发起域ID
         <starttime />            开始时间：2016-05-10 00:00:00
         <endtime />              结束时间
         <type />                 告警类型 -1 查询全部 其它查询指定4,201
         <domid />                设备域ID
         <status />               状态（查询告警状态,0是未处理，1是处理）
         <size />                 每页大小
         <curpage />              查询第几页,1表示第一页
		 <confirmstatus />        告警用户确认状态
		 <flaguser  />            1:subuserid就是告警用户的userid,查alarm_log表，查已经发送的告警状态，0：查询订阅用户subuserid的告警
		 <subuserid />            订阅用户ID,根据订阅用户的ID来查，subuserid<=0 就按照原先的普通查询，subuserid>0根据订阅查询
		 <devtype />              设备类型 -1 查询全部 其它查询指定几种，格式如：27,111,102,301
		 <flag />                 0:用下面的时间条件查询，1查询服务器过去24小时的数据
		 <flagtime />             0:按照等级时间排序查询，1、按照等级排序查询,2按照时间排序查询，3按照时间等级排序    备注：默认时间升序，等级升序排列
</root>
@endverbatim
@param [out] outxml                                  返回信息

// 注意devcode，如果是设备告警，devcode就是设备编码
// 如果是通道告警，devcode就是通道编码

@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
         <total></total>                                    总数
         <item 
                    id=""                                   告警记录ID
                   domid=""                                域ID
                   devcode=""                              设备代码
                   devname=""                              设备名称
                   chnidx=""                               通道索引
                   devtype=""                              设备类型
                   type=""                                 告警类型
                   status=""                               状态
                   level=""                                告警等级
                   alarmtime=""                            告警时间
                   length=""                               数据长度
                   msgtxt=""                               消息文本
                   confirmor=""                            确认人
                   confirmtime=""                          确认时间
                   confirmmsg=""                           确认消息
                   comfirmstatus=""                        确认状态
				   guid=""                                 告警guid
				   alarmstatus=""                          告警状态确认   
         />
</root>
@endverbatim
@param [in]  maxlen                                 信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryAlarmCaseInfo(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);


/**
@brief 查询历史实时数据信息
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]  inxml				条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<srcdomid />		发起域ID
	<starttime />		开始时间
	<endtime />			结束时间
	<domid />			设备域ID
	<devcode />			通道设备代码，比如"'chn0';'chn1';'chn2'"
	<size />			每页大小
	<curpage />			查询第几页
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>				总数
	<item 
		domid=""				域ID
		devcode=""				设备代码
		devname=""				设备名称
		devtype=""				设备类型
		time=""					上报时间
		val=""					实时数据值
		unit=""					实时数据单位
	/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryHistoryRealData(t_uint32 session, t_int32 timeout, char* inxml, char* outxml, t_uint32 maxlen);


/**
@brief 查询历史实时数据的平均值
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]  inxml				条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<starttime />		开始时间
	<endtime />			结束时间
	<domid />			设备域ID
	<devcode />			设备编码
	<interval />		间隔的时间，单位秒
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		domid=""				域ID
		devcode=""				设备代码
		devname=""				设备名称
		devtype=""				设备类型
		starttime=""			时间段开始时间
		endtime=""			    时间段结束时间
		val=""					时间段的平均值
		unit=""					实时数据单位
	/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryHistoryRealData_AVG(t_uint32 session, t_int32 timeout, char* inxml, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK告警等级
* @{
*/

/**
@brief 操作告警优先级
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] info				操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt 
		operate=""				操作类型
	>
		<item 
			devcode=""			设备代码
			domid=""			域ID
			type=""				告警类型
			level=""			告警等级
			updatetime=""		更新时间
		/>
	</opt>
</root>
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptAlarmPriority( t_uint32 session, t_int32 timeout, char *info);

/**
@brief 查询告警优先级
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] alarmcategory		告警大类型 0表示非大类条件
@param [in] info				非大类条件
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		devcode=""				设备代码
		domid=""				域ID
		type=""					告警类型
		level=""				告警等级(不填)
		udatetime=""			更新时间(不填)
	/>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		devcode=""				设备代码
		domid=""				域ID
		type=""					告警类型
		level=""				告警等级
		udatetime=""			更新时间
	/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryAlarmPriority( t_uint32 session, t_int32 timeout, t_int32 alarmcategory, char* info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK保存策略
* @{
*/

/**
@brief 操作告警或实时数据保存策略
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] info				操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt 
		operate=""				操作类型 0 增加 1 修改 2 删除
	>
		<item 
			domId=""			设备域
			devcode=""			设备代码（为空表示所有设备）
			type=""				告警类型 具体类型 比如 1 （一种告警类型一个item）
			interval=""			间隔时间（间隔内重复告警不处理）
			autodisappear=""	告警自动消失时间（-1表示不自动消失，否则模拟自动消失）
			stop=""				发起告警停止 暂时无用
			enable==""			是否启用
			msgtxt=""			告警描述
		/>
	</opt>
</root>
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptSaveStrategy( t_uint32 session, t_int32 timeout, char* info);

/**
@brief 查询告警或实时数据保存策略
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] info				条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<category></category>		组别                          
	<size />					每页大小
	<curpage />					查询第几页
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>				总数
	<item domId="" devcode="" type="" interval="" autodisappear="" stop="" enable=="" msgtxt="" />
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see DMU_SC_OptSaveStrategy
*/
DLIB_API t_int32 DMU_SC_QuerySaveStrategy( t_uint32 session, t_int32 timeout, char* info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK动力环境
* @{
*/

/**
@brief 动环控制
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] domid				域ID
@param [in] scsid				动环ID
@param [in] scsdevid			动环设备ID
@param [in] scslabel			类别 0 资产 1 资源
@param [in] scsopt				操作 如 1 开灯 0 关灯
@param [in] scspram				操作参数，用户自定义
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_ScsControl(t_uint32 session, t_int32 timeout, char *domid, char *scsid, char *scsdevid, t_int32 scslabel, t_int32 scsopt, char *scspram);

/**
@brief 查询动环信息
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] domid				域ID
@param [in] scsid				动环ID
@param [in] scsdevid			动环设备ID
@param [in] scslabel			类别 0 资产 1 资源
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<id/>						SCS资产或资源ID
	<res/>0						获取成功 1 获取失败
	<time/>						时间
	<devtype/>					资产资源类型
	<val/>						值
	<desc/>						描述
	<errmsg/>
	<errcode/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return  错误码查看 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryScsInfo(t_uint32 session, t_int32 timeout, char *domid, char *scsid, char *scsdevid, t_int32 scslabel, char *outxml, t_uint32 maxlen);

/**
@brief 查询动环上下限阀值
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] domainid			域ID
@param [in] resourceid			资源ID
@param [in] info				条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<alarmtype />                告警类型（必填）
</root>
@verbatim
@param [out] outxml				 返回信息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<alarmtype />                告警类型
	<x_top1 />				     上限
	<y_but1 />					 下限
	<width_top2 />				 宽度上限
	<height_but2 />				 高度下限
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return  错误码查看 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryScsAlarmCfg( t_uint32 session, t_int32 timeout, char* domainid, char* resourceid,char* info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK设备状态
* @{
*/

/**
@brief 查询设备状态
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的设备
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="CLIENT">
<device domid="2000" devcode="123" status="0"/>
...
</root>
@endverbatim
@param [out] outxml				返回的设备状态
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="CLIENT">
<device domid="2000" devcode="123" status="1"/> 1:在线 2:离线
...
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryDevStatus(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK红外热图
* @{
*/

/**
@brief 获取红外设备的能力
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] domid				域ID
@param [in] chnCode				通道ID
@param [in] type				能力标识（哪一种能力）
0: NET_DEV_CAP_SEQPOWER     // 电源时序器能力 
1: NET_ENCODE_CFG_CAPS      // 设备编码配置对应能力 
2: NET_VIDEOIN_FISHEYE_CAPS // 鱼眼能力 
3: NET_THERMO_GRAPHY_CAPS	// 热成像能力 
4: NET_RADIOMETRY_CAPS	    // 热成像测温能力 
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' ?>
<root>
<size>3435973836</size>
<modes>14</modes>
<colorization>30</colorization>
<roimodes>495</roimodes>
<brightness max="100.000000" min="0.000000" isstep="1" step="1.000000" isdefault="0" default="0.000000" reserved=""/>
<sharpness max="100.000000" min="0.000000" isstep="1" step="5.000000" isdefault="0" default="0.000000" reserved=""/>
<ezoom max="16.000000" min="0.000000" isstep="1" step="1.000000" isdefault="0" default="0.000000" reserved=""/>
<thermographygamma max="8.000000" min="-8.000000" isstep="1" step="1.000000" isdefault="0" default="0.000000" reserved=""/>
<smartoptimizer max="100.000000" min="0.000000" isstep="1" step="5.000000" isdefault="0" default="0.000000" reserved=""/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return  错误码查看 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_GetThermoDevCaps(t_uint32 session, t_int32 timeout,char* domId,char* chnCode,int type,char* outxml, t_uint32 maxlen);


/**
@brief 获取红外设备的信息
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] domid				域ID
@param [in] chnCode				通道ID
@param [in] type				查询哪一种信息
9: NET_QUERY_DEV_THERMO_GRAPHY_PRESET		// 查询热成像预设信息		
10: NET_QUERY_DEV_THERMO_GRAPHY_OPTREGION	// 查询热成像优化区域信息	
11: NET_QUERY_DEV_THERMO_GRAPHY_EXTSYSINFO	// 查询热成像外部系统信息	
12: NET_QUERY_DEV_RADIOMETRY_POINT_TEMPER	// 查询测温点的参数值		
13:NET_QUERY_DEV_RADIOMETRY_TEMPER 			// 查询测温项温度的参数值
@param [in] inxml				对于测温点和测温区的查询，还需要其他的参数
测温点
<root>
<x>200</x>
<y>120</y>
</root>
测温项
<root>
<presetid>1</presetid>
<ruleid>2</ruleid>
<metertype>3</metertype>
<itemname>4</itemname>
</root>
@param [out] outxml				返回信息
测温返回结果
<?xml version='1.0' encoding='utf-8' ?>
<root>
<size></size>
<radiometryinfo>
<metertype></metertype>
<temperaver></temperaver>
<tempermax></tempermax>
<tempermin></tempermin>
<tempermid></tempermid>
<temperstd></temperstd>
<reserved></reserved>
</radiometryinfo>
</root>
@param [in]  maxlen				信息最大长度
@return  错误码查看 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryThermoDevInfo(t_uint32 session, t_int32 timeout,char* domId,char* chnCode,int type,char* inxml,char* outxml, t_uint32 maxlen);


/**
@brief 获取红外设备的信息
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] domid				域ID
@param [in] chnCode				通道ID
@param [in] type				控制类型
0: NET_CTRL_DEV_THERMO_GRAPHY_ENSHUTTER, // 热成像开关
1: NET_CTRL_DEV_RADIOMETRY_SETOSDMARK,	 // 设置测温项的osd为高亮
@param [in] inxml				需要其他的参数
热成像开关
<root>
<enable>1</enable>
</root>
 设置测温项的osd为高亮
<root>
<presetid>1</presetid>
<ruleid>2</ruleid>
<metertype>3</metertype>
<itemname>4</itemname>
</root>
@param [out] outxml				返回信息


@param [in]  maxlen				信息最大长度
@return  错误码查看 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_ControlThermoDevEx(t_uint32 session, t_int32 timeout,char* domId,char* chnCode,int type,char* inxml);


/**
@brief 获取红外设备的配置
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] domid				域ID
@param [in] chnCode				通道ID
@param [in] type				配置标识（哪一种配置）
0: CFG_CMD_THERMO_GRAPHY	// 热成像配置
1: CFG_CMD_THERMOMETRY_RULE	// 热成像规则配置
2: CFG_CMD_TEMP_STATISTICS	// 温度统计配置
3: CFG_CMD_THERMOMETRY		// 热成像测温配置
@param [out] outxml				返回信息

@param [in]  maxlen				信息最大长度
@return  错误码查看 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_GetThermoDevConfig(t_uint32 session, t_int32 timeout,char* domId,char* chnCode,int type,char* outxml, t_uint32 maxlen);

/**
@brief 获取红外设备的配置
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] domid				通道的域
@param [in] chnCode				通道编码
@param [in] type				配置标识（哪一种配置）
0: CFG_CMD_THERMO_GRAPHY	// 热成像配置
1: CFG_CMD_THERMOMETRY_RULE	// 热成像规则配置
2: CFG_CMD_TEMP_STATISTICS	// 温度统计配置
3: CFG_CMD_THERMOMETRY		// 热成像测温配置
@param [in] isSaveDB			是否保存到数据库
@param [in] inxml				返回信息

@return  错误码查看 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_SetThermoDevConfig(t_uint32 session, t_int32 timeout,
	char* domId,char* chnCode,int type,int isSaveDB,char* inxml);


/**
@brief 根据一次设备或者通道的预置位，查询测温对象
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] qryFlg				查询标识
1: 根据eleDom+eleCode,查询
2: 根据chnDom+chnCode,查询
3: 根据eleDom+eleCode+chnDom+chnCode+prepointId,查询
@param [in] eleDom				一次设备的域
@param [in] eleCode				一次设备的编码
@param [in] chnDom				通道的域
@param [in] chnCode				通道的编码
@param [in] prepointId			通道的预置位
@param [out] outxml				返回信息
@param [in]  maxlen				信息最大长度
@return  错误码查看 IBP_Error.h
@remarks 如果eleDom和eleCode为空字符串，按照通道和预置位查询
@see
*/
DLIB_API t_int32 DMU_SC_GetIrArea_ByElecDev_ChnPrepoint(t_uint32 session, t_int32 timeout,int qryFlag,char* eleDom,char* eleCode,
	char* chnDom,char* chnCode,int prepointId,char* outxml, t_uint32 maxlen);


/**
@brief 抓取红外热图
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]	 chnDom				通道的域
@param [in]	 chnCode			通道的编码
@param [out] outxml				返回信息
@param [in]  maxlen				信息最大长度
@return  错误码查看 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_FetchThermoGraphy(t_uint32 session, t_int32 timeout,char* chnDom,char* chnCode,char* outxml,t_uint32 maxlen);

/** @} */


/**
* @defgroup DMU_SDK解码器通道信息
* @{
*/

/**
@brief 查询解码器通道信息
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的解码器
@verbatim
<root>
	<ip>1</ip>
	<port>1</port>
	<username>1</username>
	<password>1</password>
</root>
@endverbatim
@param [out] outxml				返回的解码器通道信息
@verbatim
<root>
	<chn seq=xxx maxsplit=xxx />
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryDecorderChnInfo(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK开始局域网设备搜索
* @{
*/

/**
@brief 查询局域网内设备
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的IP范围(一个网段)
@verbatim
<root>
	<startip>1</startip>
	<endip>1</endip>
	<searchtime>1</searchtime>
</root>
@endverbatim
@param [in] cb					回调函数
@param [in] pUser				用户自定义数据
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_StartSearchLanDev(t_uint32 session, t_int32 timeout,char* inxml);

/** @} */


/**
* @defgroup DMU_SDK停止局域网设备搜索
* @{
*/

/**
@brief 查询局域网内设备
@param [in] session				连接句柄
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_StopSearchLanDev(t_uint32 session);

/** @} */


/**
* @defgroup DMU_SDK查询设备信息
* @{
*/

/**
@brief 查询局域网内设备
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的解码器
@verbatim
<root>
	<device devtype="" loginname="" loginpwd="" ipaddr="" portdev="" />
</root>
@endverbatim
@param [out] outxml				返回的设备信息
@verbatim
<root>
	<device ipaddr="" portdev="" errcode="" devcode="id" maxchn="16" manufid="1">
		<channel title="通道1" devtype="22" manufid="1"/>	现有通道信息
		<channel title="通道2" devtype="22" manufid="1"/>	现有通道信息
	</device>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryLanDevInfo(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK客户端告警
* @{
*/
/**
@brief 客户端向dmu发送客户端告警
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的解码器
@verbatim
见DMU_SC_SetDmuMsg中的告警数据通知
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_SendClientAlarm(t_uint32 session, t_int32 timeout,char* inxml);

/**
@brief 手机告警上报（阿里项目）
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的解码器
@param [out] outguid			告警ID
@param [in]  maxlen				信息最大长度
@verbatim
见DMU_SC_SetDmuMsg中的告警数据通知
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_SendPhoneClientAlarm(t_uint32 session, t_int32 timeout,char* inxml,char* outguid,t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK实时数据
* @{
*/
/**
@brief 客户端向dmu发送客户端实时数据
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				gps信息
@verbatim
见DMU_SC_SetDmuMsg中的实时数据通知
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_SendClientRealData(t_uint32 session, t_int32 timeout,char* inxml);

/**
@brief 查询门禁卡片信息
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的条件
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>
	<deptid></deptid>
	<cardnum></cardnum>
	<startindex></startindex>
	<pagecount></pagecount>
</root>
@endverbatim
@param [out] outxml				查询的卡信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<count></count>
	<item id="" userid="" domid="" username=""
		 deptid=""  deptname=""  cardnum=""  cardtype=""  
		 password="" startdate="" enddate="" worktype="" />
	<item id="" userid="" domid="" username=""
	deptid=""  deptname=""  cardnum=""  cardtype=""  
	password="" startdate="" enddate="" doorpwd="" worktype=""/>
</root>
@endverbatim
@param [in] maxlen				信息最大长度
*/
DLIB_API t_int32 DMU_SC_QueryAcOwnerInfo(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/**
@brief 门禁卡信息操作
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				操作内容
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<acowner userid="" domid="" username="" deptid="" deptname="" cardnum="" cardtype="" password="" startdate="" enddate="" doorpwd="" worktype=""/>
</root>
@endverbatim
@param [in] maxlen				信息最大长度
*/
DLIB_API t_int32 DMU_SC_OptAcOwnerInfo(t_uint32 session, t_int32 timeout,char* inxml,t_uint32 maxlen);

/**
@brief 查询门禁日志信息
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的条件
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<starttime></starttime>
	<endtime></endtime>
	<startindex></startindex>
	<pagecount></pagecount>
	<domid></domid>
	<userid></userid>
	<username></username>
	<cardnum></cardnum>
	<doorcode></doorcode>
	<orgcode></orgcode>		   查组织必填，此时门编码为空
</root>
@endverbatim
@param [out] outxml				查询的日志信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<count></count>
	<item id="" domid="" doorcode=""  doorname="" doorindex="" devcode=""  cardnum=""  
	userid="" username="" time="" opentype="" result=""
	/>
</root>
@endverbatim
@param [in] maxlen				信息最大长度
*/
DLIB_API t_int32 DMU_SC_QueryAcLogInfo(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/**
@brief 查询门禁权限信息
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的条件
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>
	<cardnum></cardnum>
	<startindex></startindex>
	<pagecount></pagecount>
</root>
@param [out] outxml				查询的门禁权限信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<count></count>
	<item domid="" cardnum="" devcode="" devname="" doorcode="" doorname="" doorindex="" recnum="" />
</root>
@endverbatim
@param [in] maxlen				信息最大长度
*/
DLIB_API t_int32 DMU_SC_QueryAcRightInfo(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/**
@brief 门禁权限信息操作
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				操作内容
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>
	<cardnum></cardnum>
	<devcode></devcode>
	<devname></devname>
	<recnum></recnum>
	<acright opt="" doorcode="" doorindex="" doorname="" />
	<acright opt="" doorcode="" doorindex="" doorname="" />
	<cardtype></cardtype>
	<password></password>
	<startdate></startdate>
	<enddate></enddate>
	<doorpwd></doorpwd>
</root>
@param [out] outxml				查询的门禁权限信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<recnum></recnum>
</root>
@endverbatim
@param [in] maxlen				信息最大长度
*/
DLIB_API t_int32 DMU_SC_OptAcRightInfo(t_uint32 session, t_int32 timeout,char* inxml,char* outxml,t_uint32 maxlen);

/**
@brief 门控制操作(开门、关门、查询门状态)
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的条件
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<domid></domid>
	<devcode></devcode>
	<doorcode></doorcode>
	<doorindex></doorindex>
</root>
@param [out] outxml				查询的门禁权限信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<domid></domid>
	<devcode></devcode>
	<doorcode></doorcode>
	<doorindex></doorindex>
	<status></status>
</root>
@endverbatim
@param [in] maxlen				信息最大长度
*/
DLIB_API t_int32 DMU_SC_OptAcControlInfo(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/**
@brief 开、关门操作通知上报
@param [in] session				连接句柄
@param [in] inxml				操作内容
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<notify domid="" doorcode=""  doorname="" doorindex="" devcode="" cardnum=""  
	userid="" username="" time="" opentype="" result=""
	/>
</root>
@endverbatim
*/
DLIB_API t_int32 DMU_SC_AcEventNotify(t_uint32 session,char* inxml);

/**
@brief 向门禁控制器查询门参数
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的条件
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>
	<devcode></devcode>
	<doorcode></doorcode>
	<doorindex></doorindex>
</root>
@param [out] outxml				向门禁控制器查询的门参数
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<acparam domid="" devcode="" doorcode="" doorindex="" openmode="" duration="" timeout="" openmethod="" />
</root>
@endverbatim
@param [in] maxlen				信息最大长度
*/
DLIB_API t_int32 DMU_SC_QueryAcParamInfo(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/**
@brief 门参数设置
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				操作内容
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<acparam domid="" devcode="" doorcode="" doorindex="" openmode="" 
	cardtype="" password="" startdate="" enddate="" />
</root>
@endverbatim
@param [in] maxlen				信息最大长度
*/
DLIB_API t_int32 DMU_SC_OptAcParamInfo(t_uint32 session, t_int32 timeout,char* inxml,t_uint32 maxlen);

/**
@brief 多人开门参数设置
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				操作内容
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>
	<devcode></devcode>
	<doorcode></doorcode>
	<doorindex></doorindex>
	<person></person>
	<item cardnum="" />
	<item cardnum="" />
</root>
@endverbatim
@param [in] maxlen				信息最大长度
*/
DLIB_API t_int32 DMU_SC_SetAcMultiPersonOpen(t_uint32 session, t_int32 timeout,char* inxml,t_uint32 maxlen);


/**
@brief 设置设备时间
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				操作内容
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>
	<devcode></devcode>
	<time></time>
</root>
@endverbatim
@param [in] maxlen				信息最大长度
*/
DLIB_API t_int32 DMU_SC_SetDeviceTime(t_uint32 session, t_int32 timeout, char* inxml, t_uint32 maxlen);


/**
@brief 更新门禁控制器信息
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				操作内容
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<item domid="" devcode="" devname="" doorcode="" doorname="" />
<item domid="" devcode="" devname="" doorcode="" doorname="" />
</root>
@endverbatim
@param [in] maxlen				信息最大长度
*/
DLIB_API t_int32 DMU_SC_UpdateACDevice(t_uint32 session, t_int32 timeout, char* inxml, t_uint32 maxlen);

/**
@brief 删除门禁控制器(dmu需要清理数据库，然后删除所有权限)
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				操作内容
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<domid></domid>
<devcode></devcode>
</root>
@endverbatim
@param [in] maxlen				信息最大长度
*/
DLIB_API t_int32 DMU_SC_DeleteACDevice(t_uint32 session, t_int32 timeout, char* inxml, t_uint32 maxlen);


/**
@brief 获取设备抓图信息
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的条件
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<srcdomid></srcdomid>			源设备域ID
	<srcdevcode></srcdevcode>		源设备代码
	<domid></domid>					视频设备域ID
	<devcode></devcode>				视频设备代码
	<alarmtype>0</alarmtype>		告警类型
	<alarmsubtype>0</alarmsubtype>	告警子类型
	<flag>0</flag>					抓图通知触发源标识 0 不通知 1 通知 
</root>
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<guid></guid>					图片guid
	<filesize>0</filesize>			图片文件大小
	<filename/>						文件名
</root>
@endverbatim
@param [in] maxlen				信息最大长度
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_GetSnapshot(t_uint32 session, t_int32 timeout, char* inxml, char* outxml, t_uint32 maxlen);

#pragma endregion


#pragma region 广播接口

/**
* @defgroup 广播接口
* @{
*/

/**
@brief 查询所有终端信息
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]	 info				条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid />			域ID
	<size />			每页大小 默认100条
	<curpage />			查询第几页
	<parentorgcode />   父节点编码(父节点为空查询全部，不为空查询该节点下的所有终端)
	<name />            终端名称(根据终端名称左匹配模糊查询，为空查询全部)
	<status />          终端状态(0表示查询全部)
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>				总数
	<item 
		domid=""				域ID
		id=""					终端编号
		parentorgcode=""        父组织编码
		name=""				    终端名称
		status=""				状态 1:登录 2. 未登录 (广播主机和终端之间的状态)
	/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_NBSQueryTerminalInfo(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);


/**
@brief 修改终端信息(修改终端的名称、父节点)
@param [in] session		   连接句柄
@param [in] timeout	 	   超时时间
@param [in] terminalId	   终端id
@param [in] opt	           修改类型(1.修改名称，2.修改父节点，3.名称和父节点同时修改)
@param [in] terminalName   新的终端名称
@param [in] parentcode     父组织编码
@param [in] groupname      父组织名称
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSModifyTerminalInfo(t_uint32 session, t_int32 timeout, int terminalId, int opt, char *terminalName, char *parentcode, char *groupname);

/**
@brief 查询更新终端信息
@param [in] session		   连接句柄
@param [in] timeout	 	   超时时间
@param [in] Flag	       标志位等于1
@param [in] domId          域ID
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSQryAllTerminalInfo(t_uint32 session, t_int32 timeout, int Flag, char *domId);

/**
@brief 查询节目列表信息
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]  inxml				条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid />		    域ID
	<size />			每页大小
	<curpage />			查询第几页
	<parentcode />      所属节目分组编码(如果编码不为空，则查询该编码下的所有节目)
	<name />            节目名称(根据名称左匹配模糊查询，为空查询全部)
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>			总数
	<item 
		domid=""			域ID
		name=""				文件名称(abc.mp3)
		guid=""				文件的guid
		parentcode=""       所属节目组编码
	/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_NBSQueryProgramInfo(t_uint32 session, t_int32 timeout, char* inxml, char* outxml, t_uint32 maxlen);


/**
@brief 节目操作
@param [in] session		   连接句柄
@param [in] timeout	 	   超时时间
@param [in]  inxml		   条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item
		opt=""              1:增加节目, 2:修改节目, 3:删除节目
		domid=""			域ID
		name=""				节目名称(如: abc.mp3)
		guid=""				文件的guid(通过FS服务上传节目获取到guid)
		parentcode=""       所属节目组编码
	/>
</root>
@endverbatim
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSOptProgramInfo(t_uint32 session, t_int32 timeout, char* inxml);

/**
@brief 操作节目分组信息
@param [in] session		登录成功后返回的值
@param [in] timeout		超时时间
@param [in] info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org opt=""            操作类型 0 增加 1 修改 2 删除
		domid=""		   域ID
		orgcode=""	 	   分组编码
		parentdomid=""	   父域ID
		parentorgcode=""   父编码(当父节点编码为空表示根节点)
		name=""            分组名称
	/>
</root>
@endverbatim
@return 
@remarks 一次可以操作多个组织节点
@see
*/
DLIB_API t_int32 DMU_SC_NBSOptProgramOrg(t_uint32 session, t_int32 timeout, char *info);

/**
@brief 查询指定节目分组详细信息
@param [in]  session	
@param [in]  timeout	超时时间
@param [in]  domid		域ID
@param [in]  orgcode	节目分组编码
@param [out] outxml		查询信息(详见DMU_SC_NBSOptOrg注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" name="" />
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return 
@remarks
@see DMU_SC_NBSOptProgramOrg
*/
DLIB_API t_int32 DMU_SC_NBSQueryProgramOrg(t_uint32 session, t_int32 timeout, char *domid, char *orgcode, char *outxml, t_uint32 maxlen);

/**
@brief 查询所有节目分组
@param [in]  session	
@param [in]  timeout	超时时间
@param [out] outxml		查询信息(详见DMU_SC_NBSOptOrg注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" name="" />
	    <org domid="" orgcode="" parentdomid="" parentorgcode="" name="" />
		<org domid="" orgcode="" parentdomid="" parentorgcode="" name=""  />
			<org domid="" orgcode="" parentdomid="" parentorgcode="" name="" />
			<org domid="" orgcode="" parentdomid="" parentorgcode="" name="" />
		</org>
	</org>
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return 
@remarks
@see DMU_SC_NBSOptProgramOrg
*/
DLIB_API t_int32 DMU_SC_NBSQueryAllProgramOrg(t_uint32 session, t_int32 timeout, char *outxml, t_uint32 maxlen);

/*
@brief 操作时间模板
@param [in] session    登录成功后返回的值
@param [in] timeout	   超时时间
@param [in] xmlInput   信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<opt 
	operatetype="0"   //操作类型 0 增加 1 修改 2 删除
>
	<timetemplate 
		id=""; //模板id
		title="";//模板名
		type="";//模板类型 1:按天; 2:按周; 3:按月;4:单次执行（按天解析）
		config="";//模板配置，以xml形式，格式如下
	/>
</opt>
</root>
@endverbatim

@模板配置格式
@verbatim
//按天进行
<Config>
<Day>
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
</Config>

//某天单次进行,有效期起始跟终止一样
<Config>
<Day>//一号
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
</Config>


//按周进行
<Config>
<Week>
<Day Num="1"> //周一
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
<Day Num="5">//周五
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
</Week>
</Config>

//按月进行
<Config>
<Month>
<Day Num="1">//一号
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
<Day Num="5">//五号
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
<Day Num="28">//二十八号
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
</Month>
</Config>
@endverbatim

@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<templateid></templateid>
</root>
@endverbatim
@return  错误码查看 ibp_error_enum.h
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSOptTimeTemplate(t_uint32 session, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);


/*
@brief 查询时间模板
@param [in] session    登录成功后返回的值
@param [in] timeout	   超时时间
@param [in] xmlInput   信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<id />             时间模板id(如果id不为0，则查询该id的模板内容,id不为0则下面的参数不起作用;为0则查询全部)
	<size />		   每页大小 默认100条
	<curpage />		   查询第几页
</root>
@endverbatim

@param [in]  maxLen			xmlOutput长度
@param [out] xmlOutput信息  参见DMU_SC_NBSOptTimeTemplate中的格式
@return  错误码查看 ibp_error_enum.h
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSQueryTimeTemplate(t_uint32 session, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);


/**
@brief 操作广播组织结构
@param [in] session		登录成功后返回的值
@param [in] timeout		超时时间
@param [in] info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org
	    opt=""             操作类型 0 增加 1 修改 2 删除
		domid=""		   域ID
		orgcode=""	 	   组织编码
		olddomid=""		   旧域ID(此两字段修改时有效)
		oldorgcode=""	   旧组织编码
		parentdomid=""	   父域ID
		parentorgcode=""   父组织编码(当父节点编码为空表示根节点)
		name=""            组织名称
		desc=""			   描述
	/>
</root>
@endverbatim
@return 
@remarks 一次可以操作多个组织节点
@see
*/
DLIB_API t_int32 DMU_SC_NBSOptOrg(t_uint32 session, t_int32 timeout, char *info);

/**
@brief 查询指定组织详细信息
@param [in]  session	
@param [in]  timeout	超时时间
@param [in]  domid		组织域ID
@param [in]  orgcode	组织编码
@param [out] outxml		查询信息(详见DMU_SC_NBSOptOrg注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" name=""  desc="" updatetime=""/>
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return 
@remarks
@see DMU_SC_OptOrg
*/
DLIB_API t_int32 DMU_SC_NBSQueryOrg(t_uint32 session, t_int32 timeout, char *domid, char *orgcode, char *outxml, t_uint32 maxlen);

/**
@brief 查询所有广播组织
@param [in]  session	
@param [in]  timeout	超时时间
@param [out] outxml		查询信息(详见DMU_SC_NBSOptOrg注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" name="" updatetime="" desc="" >
		<org domid="" orgcode="" parentdomid="" parentorgcode="" name="" updatetime="" desc="" >
			<org domid="" orgcode="" parentdomid="" parentorgcode="" name="" updatetime="" desc="" />
		</org>
	</org>
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return 
@remarks
@see DMU_SC_NBSOptOrg
*/
DLIB_API t_int32 DMU_SC_NBSQueryAllOrg(t_uint32 session, t_int32 timeout, char *outxml, t_uint32 maxlen);

/**
@brief 查询子组织
@param [in]  session		
@param [in]  timeout	超时时间
@param [in]  domid		域ID
@param [in]  parentorgcode	父组织代码(为空字符串返回根组织信息)
@param [out] outxml		查询信息(详见DMU_SC_NBSOptOrg注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" name="" updatetime="" desc="" />
	<org domid="" orgcode="" parentdomid="" parentorgcode="" name="" updatetime="" desc="" />
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return 
@remarks
@see DMU_SC_NBSOptOrg
*/
DLIB_API t_int32 DMU_SC_NBSQuerySubOrg(t_uint32 session, t_int32 timeout, char* domid, char* parentorgcode, char*outxml, t_uint32 maxlen);

/**
@brief 操作广播任务
@param [in] session		登录成功后返回的值
@param [in] timeout		超时时间
@param [in] info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<task opt="" domid="" id="" name="" desc="" >
		<terminal id="" name=""  parentorgcode="" />
		<terminal id="" name=""  parentorgcode="" />
		<program  name="" guid=""  parentcode="" />
		<program  name="" guid=""  parentcode="" />
	</task>
</root>
参数描述:
opt			//操作类型 0 增加 1 修改 2 删除
domid       //域ID
id          //任务id(增加操作的时候不需要填写，由服务操作后返回; 删除任务根据id，下面其它参数可以忽略)
name        //任务名称
desc        //任务描述
terminal: id    //终端id 
		  name //终端名称
          parentorgcode 父组织编码  
program:   name        //节目名称
           guid        //节目文件的guid
		   parentcode  //所属节目分组编码

@endverbatim
@param [in] maxLen		xmlOutput长度
@param [out] xmlOutput信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<id></id>
</root>
@endverbatim
@return  错误码查看 ibp_error_enum.h
@remarks 只有增加操作信息的时候会返回任务id
@see 
*/
DLIB_API t_int32 DMU_SC_NBSOptTask(t_uint32 session, t_int32 timeout, char *info, char *xmlOutput, t_uint32 maxLen);


/*
@brief 查询广播任务信息
@param [in] session    登录成功后返回的值
@param [in] timeout	   超时时间
@param [in] xmlInput   信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<id />            任务id(如果id不为0，则查询该id的内容,id不为0则下面的参数不起作用;为0则查询全部)
	<size />		  每页大小 默认100条
	<curpage />		  查询第几页
	<name />          任务名称(根据名称左匹配模糊查询，为空查询全部)
</root>
@endverbatim

@param [in]  maxLen			xmlOutput长度
@param [out] xmlOutput信息  参见DMU_SC_NBSOptTask中的格式
@return  错误码查看 ibp_error_enum.h
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSQueryTask(t_uint32 session, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);


/**
@brief 操作广播计划
@param [in] session		登录成功后返回的值
@param [in] timeout		超时时间
@param [in] info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>总数
	<item opt="" domid="" id="" name="" name="" desc="" enable="" startdate="", enddate="", timeid="", config="", taskid="", taskname="", status="" title="" type="" updatetime=""/>
	<item opt="" domid="" id="" name="" name="" desc="" enable="" startdate="", enddate="", timeid="", config="", taskid="", taskname="", status="" title="" type="" updatetime="" />
	参数说明:
	opt		    //操作类型 0 增加 1 修改 2 删除
	domid       //域ID
	id          //计划id(增加操作的时候不需要填写，由服务操作后返回; 删除操作时根据id删除，下面其它参数可以忽略)
	name        //计划名称
	desc        //计划描述
	enable      //计划使能 1.启用 2. 停用
	startdate   //有效期开始时间 格式:2015-10-21  
	enddate     //有效期结束时间 格式:2016-10-21
	timeid      //时间模板id(如果id为0表示需要服务帮忙生成一个时间模板，需要填写下的timecontent, title type)
	config      //时间模板内容(timeid不为0的时候这里不需要填写，该字段在查询计划时用)
	title       //参数见时间模板描述
	type        //参数见时间模板描述
	taskid      //任务id
	taskname    //任务名称
	status      //计划状态 0:未执行 1:正在执行(该字段为查询计划的时候用)
</root>
@endverbatim
@param [in] maxLen		xmlOutput长度
@param [out] xmlOutput信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<id></id>
</root>
@endverbatim
@return  错误码查看 ibp_error_enum.h
@remarks 只有增加操作的时候会返回计划id
@see 
*/
DLIB_API t_int32 DMU_SC_NBSOptPlan(t_uint32 session, t_int32 timeout, char *info, char *xmlOutput, t_uint32 maxLen);


/*
@brief 查询广播计划信息
@param [in] session    登录成功后返回的值
@param [in] timeout	   超时时间
@param [in] xmlInput   信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<id />            计划id(如果id不为0，则查询该id的内容,id不为0则下面的参数不起作用;为0则查询全部)
	<size />		  每页大小 默认100条
	<curpage />		  查询第几页
	<name />          计划名称(根据名称左匹配模糊查询，为空查询全部)
	<enable />        使能，0表示查询全部
	<startdate />     起始时间，0表示全部
	<enddate />       结束时间，0表示全部
</root>
@endverbatim

@param [in]  maxLen			xmlOutput长度
@param [out] xmlOutput信息  参见DMU_SC_NBSOptPlan中的格式
@return  错误码查看 ibp_error_enum.h
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSQueryPlan(t_uint32 session, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/*
@brief 手动执行广播计划
@param [in] session    登录成功后返回的值
@param [in] timeout	   超时时间
@param [in] taskId     任务id
@param [in] opt        操作类型：1.立即执行计划  2.立即停止计划 3.普通执行（使能）
@return  错误码查看 ibp_error_enum.h
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSRunTask(t_uint32 session, t_int32 timeout, t_uint32 taskId, t_uint32 opt);

/*
@brief 查询终端正在播放节目信息
@param [in] session    登录成功后返回的值
@param [in] timeout	   超时时间
@param [in] Id		   终端id
@return  错误码查看 ibp_error_enum.h

@endverbatim
@param [in] maxLen		xmlOutput长度
@param [out] xmlOutput信息
@verbatim

<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>	
	<name></name>    节目名称
	<time></time>	 播放起始时间
	<totle></totle>	 总时间
</root>
@endverbatim

@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSQueryTerminalProgram(t_uint32 session, t_int32 timeout, t_uint32 Id, char *xmlOutput, t_uint32 maxLen);


/** @} */

#pragma endregion


#pragma region 车辆识别功能

/**
* @defgroup 车辆识别功能
* @{
*/

/**
@brief 操作停车场
@param [in] session			连接句柄
@param [in] timeout			超时时间
@param [in] inxml			输入信息
@verbatim
opt: 0 add 1 modify 2 del
<root>
	<carpark opt="0" //操作码 parentid="0" //所属组织的id domid="" //所属组织的域id name="" //停车场的名称
		totalnum="100" //停车场总数 />
</root>
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptCarPark(t_uint32 session,t_int32 timeout,char* inxml);

/**
@brief 查询停车场
@param [in] session			连接句柄
@param [in] timeout			超时时间
@param [in] inxml			输入信息
@verbatim
opt: 3 查询一个 4 查询全部
<root> 
	<carpark opt="3" id="0" parentid="0" curpage="0" size="0" />
</root>
@param [out] outxml			输出信息
	<carpark opt="3" id="0" parentid="0"  domid="" parentorgcode="" //所属组织的编码
		name="" totalnum="100" unusednum="50" />
@param [in]  maxlen			最大长度
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QryCarPark(t_uint32 session,t_int32 timeout,char* inxml,char* outxml,t_uint32 maxlen);

/**
@brief 操作卡口
@param [in] session			连接句柄
@param [in] timeout			超时时间
@param [in] inxml			输入信息
@verbatim
opt: 0 add 1 modify 2 del
<root>
	<cargate opt="0" id="7" name="" carparkid="0">
		<chn flag=0 domainid="" chncode=""> // flag 0 进入抓拍摄像机 1 出去抓拍摄像机
        <chn flag=1 domainid="" chncode="">
	</cargate>
</root>
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptCarGate(t_uint32 session,t_int32 timeout,char* inxml);

/**
@brief 查询停车场卡口
@param [in] session			连接句柄
@param [in] timeout			超时时间
@param [in] inxml			输入信息
@verbatim
opt: 3 查询一个 4 查询全部
<root>
	<cargate opt="3" id="0"//卡口id  carparkid="0" //停车场id curpage="0" size="0" />
</root>
@param [out] outxml			输出信息
<root>
	<cargate opt="3" id="0" carparkid="" //停车场id name="" //卡口名称 />
		<chn flag="" domainid="" chncode="">
	</cargate>
</root>
@param [in]  maxlen			最大长度
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QryCarGate(t_uint32 session,t_int32 timeout,char* inxml,char* outxml,t_uint32 maxlen);

/**
@brief 操作车辆信息
@param [in] session			连接句柄
@param [in] timeout			超时时间
@param [in] inxml			输入信息
@verbatim
opt: 0 add 1 modify 2 del
<root>
	<cargate opt="0" id="7" //车牌 cartype="" //车辆类型 owner="" //车辆所有人 ownerid="" //身份证号码
		ownertype="" //名单状态 reason="" //理由 remark=""//备注 /> 
</root>
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptCarInfo(t_uint32 session,t_int32 timeout,char* inxml);

/**
@brief 查询车辆信息
@param [in] session			连接句柄
@param [in] timeout			超时时间
@param [in] inxml			输入信息
@verbatim
opt: 3 查询一个 4 查询全部
<root>
	<cargate opt="3" id="7" curpage="0" size="0" />
</root>
@param [in]  maxlen			最大长度
@param [out] outxml			输出信息
<root>
	<cargate opt="3" id="7" cartype="" owner="" ownerid="" ownertype="" reason="" remark=""/>
</root>
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QryCarInfo(t_uint32 session,t_int32 timeout,char* inxml,char* outxml,t_uint32 maxlen);

/**
@brief 查询历史车辆信息
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]  inxml				条件信息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<carid></carid>
	<cardomid></cardomid>
	<cartype></cartype>
	<owner></owner>
	<carcolor></carcolor>
	<carpark></carpark>
	<cargate></cargate>
	<starttime></starttime>
	<endtime></endtime>
	<carhasid></carhasid>
	<curpage></curpage>
	<size></size>
</root>
@param [out] outxml				返回信息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<total>2</total>
	<carlog id="1" carid="" carpark="" carcolor="BB22DD" cartype="MPV" owner="" indomid="111" inchncode="chn1" ineventtype="1" intime="2017-03-11 09:28:51" infile="" inplace="" outdomid="" outchncode="" outeventtype="0" outtime="" outfile="" outplace=""/>
	<carlog id="2" carid="" carpark="" carcolor="" cartype="" owner="" indomid="" inchncode="" ineventtype="" intime="" infile="" inplace="" outdomid="" outchncode="" outeventtype="0"	outtime="" outfile="" outplace=""/>
</root>
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QryCarLog(t_uint32 session, t_int32 timeout, char* inxml, char* outxml, t_uint32 maxlen);

/**
@brief 客户排行（月排行）查询
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]  inxml				条件信息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<carparkid></carparkid>		//停车场ID
	<starttime></starttime>     //开始时间,年月:2016-3
	<endtime></endtime>			//结束时间,年月:2016-5
	<carid></carid>      		//车牌号,如果为空,查全部
</root>
@param [out] outxml				返回信息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<count time="2016-3" num="60"/>		(根据time从小到大排列)
	<count time="2016-4" num="80"/>
   	<count time="2016-5" num="50"/>
</root>
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QryCusMonthRank(t_uint32 session,t_int32 timeout,char* inxml,char* outxml,t_uint32 maxlen);

/**
@brief 客户排行（月排行）明细查询
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]  inxml				条件信息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<carparkid></carparkid>		//停车场ID
	<searchtime></searchtime>   //具体的月份:2016-3
	<carid></carid>      		//车牌号,如果为空,查全部
	<curpage></curpage>
	<size></size>
</root>
@param [out] outxml				返回信息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total>3</total>
	<count carid="" num="20"/>		(根据num从多到少排列)
	<count carid="" num="10"/>
    <count carid="" num="5"/>
</root>
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QryCusMonthDetailRank(t_uint32 session,t_int32 timeout,char* inxml,char* outxml,t_uint32 maxlen);

/**
@brief 客户排行（车型排行）查询
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]  inxml				条件信息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<carparkid></carparkid>		//停车场ID
	<searchtime></searchtime>   //具体的月份:2016-3
</root>
@param [out] outxml				返回信息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<count cartype=""   num="60"  ratio="30.51"/>
	<count cartype=""   num="80"  ratio="40.31"/>
    <count cartype=""   num="50"  ratio="29.31"/>
</root>
@param [in]  maxlen			    信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QryCusCartypeRank(t_uint32 session,t_int32 timeout,char* inxml,char* outxml,t_uint32 maxlen);

/**
@brief 客户排行（车型排行）明细查询
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]  inxml				条件信息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<carparkid></carparkid>		//停车场ID
	<searchtime></searchtime>   //具体的月份:2016-3
	<cartype></cartype>         //车型，如果为空，查全部
	<curpage></curpage>
	<size></size>
</root>
@param [out] outxml				返回信息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total>3</total>
	<count cartype="" carid="" num="20"/>	(先根据cartype排序，再根据num从多到少排列)
	<count cartype="" carid="" num="10"/>
	<count cartype="" carid="" num="5" />
</root>
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QryCusCartypeDetailRank(t_uint32 session,t_int32 timeout,char* inxml,char* outxml,t_uint32 maxlen);

/**
@brief 车流量分析
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]  inxml				条件信息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>				 //查询方式：0 按时、1 按日、2 按月
	<carparkid></carparkid>  //停车场ID
	<starttime></starttime>
	<endtime></endtime>
	<curpage></curpage>
	<size></size>
</root>
@param [out] outxml				返回信息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total>10</total>
	<carflow time="2016-1-1"  incarnum="" >  (根据time从小到大排列)
		<detail cartype="" ratio="" />
		<detail cartype="" ratio="" />
		<detail cartype="" ratio="" />
	</carflow>	
	<carflow time="2016-1-2"  incarnum="" >
		<detail cartype="" ratio="" />
		<detail cartype="" ratio="" />
		<detail cartype="" ratio="" />
	</carflow>
</root>
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QryCusCarflowRank(t_uint32 session,t_int32 timeout,char* inxml,char* outxml,t_uint32 maxlen);

/**
@brief 操作摄像头使能上报
@param [in] session			连接句柄
@param [in] timeout			超时时间
@param [in] opt				操作类型 0 使能   1 去使能 
@param [in] chnlane			摄像头划区编号
@param [in] chncode			摄像头编号
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptChnEnableReport(t_uint32 session, t_int32 timeout, int opt, int chnlane, char *chncode);

/**
@brief 获取设备抓图信息
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的条件
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<channelid></channelid>		 // 通道号
	<times></time>               // 连拍次数, 0表示停止抓拍,正数表示连续抓拍的张数
</root>
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<alarmtype></alarmtype>			//事件类型（交通卡口事件）
	<carcolor></carcolor>			// 车辆颜色
	<cargate></cargate>				// 卡口名称
	<carid></carid>					// 表示车牌号
	<carplatetype></carplatetype>	//类型，其值为轿车或者SUV等
	<cartype></cartype>				// 车辆类型
	<chnid></chnid>					//摄像头通道ID
	<devcode></devcode>				// 表示摄像头通道编号
	<eventtime></eventtime>			//事件发生时间
	<filename></filename>			//抓拍的图片名称
	<lane></lane>					//分区编号，其取值为0、1、2等
	<cararea></cararea>				//车头还是车尾，其值为head或者tail
	<carlogo></carlogo>				//品牌，其取值为奥迪、宝马、福特等
	<carseries></carseries>			//车系，其值为A4L或者X5等
	<carlable></carlable>			//年款，其取值为A4L-20092012-中高配版或者X5-20112013-M运动型等
	<piccontent></piccontent>		//图片数据
</root>
@endverbatim
@param [in] maxlen				信息最大长度
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_GetCarSnapshot( t_uint32 session, t_int32 timeout, char* inxml, char* outxml, t_uint32 maxlen);
/** @} */

#pragma endregion


/** @} */


#ifdef __cplusplus
}
#endif

#endif


