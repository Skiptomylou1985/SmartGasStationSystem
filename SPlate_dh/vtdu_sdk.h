/**
 * Copyright (c) 2014, 浙江大华系统工程有限公司 All rights reserved.
 * \file		vtdu_sdk.h
 * \brief		vtdu_sdk
 * \author		17400
 * \date		2014年12月19日
 * \note		VTDU SDK 接口
 */
#ifndef _IBP_VTDU_SDK_I_H_
#define _IBP_VTDU_SDK_I_H_

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
#ifdef IBPVTDUSDK_LIB_EXPORTS
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
* @defgroup VTDU_SDK函数
* @{
*/

/**
* @defgroup VTDU_SDK系统
* @{
*/

/**
@brief VTDU_SDK初始化
@return 
@remarks
@see VTDU_C_Init
*/
DLIB_API t_int32 VTDU_SC_Init();
/**
@brief VTDU_SDK初始化,服务或者已经启动applicationBase的程序调用
@return 
@remarks
@see VTDU_SC_InitNoApp
*/
DLIB_API t_int32 VTDU_SC_InitNoApp();

/**
@brief VTDU_SDK反初始化
@return 
@remarks
@see VTDU_C_Cleanup
*/
DLIB_API t_int32 VTDU_SC_Cleanup();

/** @} */

/**
* @defgroup VTDU_SDK码流回调函数
* @{
*/

/**
@brief 码流回调接口
@param [out] realHandle 句柄
@param [out] buffer	码流
@param [out] dwBufSize 长度
@param [out] pUser 用户信息
@return 
@see 
*/
typedef t_int32 (*fVtdu_C_RealDataCallBack)(t_uint32 realHandle, char *buffer, t_uint32 dwBufSize, void *pUser);


/**
@brief 设置码流回调函数
@param [in] realHandle 视频句柄号
@param [in] cb 回调函数
@param [in] pUser 用户数据
@return 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_SetRealDataCallBack(t_uint32 realHandle, fVtdu_C_RealDataCallBack cb, void *pUser);

/**
@brief 码流缓存回调函数
@param [out] realHandle	句柄
@param [out] buffer	码流
@param [out] dwBufSize 长度
@param [out] cacheLen 内部缓存长度
@param [out] pUser 用户信息
@see 
*/
typedef t_int32 (*fVtdu_C_RealDataCallBackByCache)(t_uint32 realHandle, char *buffer, t_uint32 dwBufSize, t_uint32 cacheLen, void *pUser);

/**
@brief 设置码流缓存回调函数,开启内部缓存
@param [in] realHandle 视频句柄号
@param [in] cb 回调函数
@param [in] pUser 用户数据
@return  
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_SetRealDataCallBackByCache(t_uint32 realHandle, fVtdu_C_RealDataCallBackByCache cb, void *pUser);

/** @} */

/**
* @defgroup VTDU_SDK回调函数
* @{
*/

/**
@brief 异步消息回调函数
@param [out] vtduSession 消息句柄
@param [out] buffer		回调内容
@param [out] buffLen	数据长度
@param [out] pUser		用户数据
@return  
@remarks
@see 
*/
typedef t_int32 (*fVtdu_C_CallBack)(t_uint32 vtduSession, char *buffer, t_uint32 buffLen, void *pUser);

/**
@brief 设置异步消息回调函数
@param [out] vtduSession 消息句柄
@param [in] cb 回调函数
@param [in] pUser 用户数据
@return  
@remarks
@see
@verbatim
服务online消息通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="SDK" type="onlineNotify" cmd="onlineNotify" sequence="0" length="0">
<server
	servername="VTDU"	服务名称
	session="1"			服务句柄
	status="1"			上下线状态
/>
</root>
@endverbatim

rtsp announce消息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="SDK" type="request" cmd="announce" sequence="0" length="0"/>

<state>200</state>			状态：200表示在线，其他详见错误码
<realhandle>5</realhandle>	视频句柄
</root>
@endverbatim
*/
DLIB_API t_int32 VTDU_SC_SetCallBack(t_uint32 vtduSession, fVtdu_C_CallBack cb, void *pUser);

/** @} */

/**
* @defgroup VTDU_SDK异步连接
* @{
*/

/**
@brief 异步连接vtdu
@param [in] cmuLoginHandle	cmu的登录句柄
@param [in] ipInfo			服务ip信息，格式"ip|port;ip|port;"
@param [in] svrDomId		服务域id
@param [in] svrId			服务id
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<vtdusession>2</vtdusession>
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_Connect(t_uint32 cmuLoginHandle, char *ipInfo, char *svrDomId, t_int32 svrId, char *xmlOutput, t_uint32 maxLen);

/**
@brief 用户认证异步连接vtdu
@param [in] usersession		用户认证
@param [in] ipInfo			服务ip信息，格式"ip|port;ip|port;"
@param [in] svrDomId		服务域id
@param [in] svrId			服务id
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<vtdusession>2</vtdusession>
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_ConnectNoCmu(t_uint32 usersession, char *ipInfo, char *svrDomId, t_int32 svrId, char *xmlOutput, t_uint32 maxLen);

/**
@brief 异步断开连接
@param [in] vtduSession		服务句柄
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_Disconnect(t_uint32 vtduSession);

/** @} */

/**
* @defgroup VTDU_SDK异步录像
* @{
*/

/**
@brief 异步录像查询
@param [in] vtduSession		服务句柄
@param [in] xmlInput		录像查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<domid></domid>				设备域id
<chncode></chncode>			通道代码
<svrid></svrid>				服务器ID
<ipinfo></ipinfo>			IP、端口信息
<sourcetype></sourcetype>	1:中心录像，2:前端录像
<recordtype></recordtype>	录像类型 0:未知录像类型, 1:手动录像, (1<<1):定时录像, (1<<2):全天候录像, (1<<3):告警录像, 1<<4):视频丢失, (1<<5):视频遮挡, (1<<6):移动侦测, 0xFFFFFFFF:所有文件
<vruid></vruid>				录像存储服务ID
<diskid></diskid>			录像存储磁盘ID
<filehandle></filehandle>	录像存储文件句柄
<starttime></starttime>		开始时间
<endtime></endtime>			结束时间
<size></size>				每页大小
<curpage></curpage>			当前页从1开始
<videofiletype></videofiletype>	录像文件类型 0原始录像 1浓缩录像
<synopsisstate></synopsisstate>	录像浓缩状态 0浓缩过程中 1浓缩完成
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_QueryRecordFile(t_uint32 vtduSession, char *xmlInput);

/**
@brief 异步录像查询,修正接口 (保证输入xml可以与vrusdk接口共用)
@param [in] vtduSession		服务句柄
@param [in] xmlInput		录像查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<IBP domid="123" chncode="chad" />
<svrid></svrid>				服务器ID
<ipinfo></ipinfo>			IP、端口信息
<sourcetype></sourcetype>	1:中心录像，2:前端录像
<recordtype></recordtype>	录像类型 0:未知录像类型, 1:手动录像, (1<<1):定时录像, (1<<2):全天候录像, (1<<3):告警录像, 1<<4):视频丢失, (1<<5):视频遮挡, (1<<6):移动侦测, 0xFFFFFFFF:所有文件
<vruid></vruid>				录像存储服务ID
<diskid></diskid>			录像存储磁盘ID
<filehandle></filehandle>	录像存储文件句柄
<starttime></starttime>		开始时间
<endtime></endtime>			结束时间
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_QueryRecordFile_Modify(t_uint32 vtduSession, char *xmlInput);

/** @} */

/**
* @defgroup VTDU_SDK异步实时视频
* @{
*/

/**
@brief 异步获取视频（包括实时,录像,语音等），集成rtsp流程
@param [in] vtduSession					服务句柄
@param [in] xmlInput							视频请求信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<domid></domid>							设备域id
<chncode></chncode>						通道代码
<playvideotype></playvideotype>			0:实时视频, 1:录像回放, 2:语音对讲
<talktype></talktype>					0:通道对讲，1:设备对讲
<playtype></playtype>					1:按文件回放,  2:按时间回放
<transproto></transproto>				0:TCP, 1:UDP
<streamtype></streamtype>				0:主码流, 1:辅码流
<streampacktype></streampacktype>		码流包类型 //-1 其他 0 用对于的制造商sdk来解码 1 rpt h264 裸码流 2 rpt h264 nal打包 3 pg  pss流 
<sourcetype></sourcetype>				1:中心录像，2:前端录像
<filename></filename>					录像文件名
<vruid></vruid>							录像存储服务ID
<diskid></diskid>						录像存储磁盘ID
<filehandle></filehandle>				录像存储文件句柄
<starttime></starttime>					开始时间
<endtime></endtime>						结束时间
</root>
@endverbatim
@param [in] maxLen						xmlOutput长度
@param [out] xmlOutput					xml输出
@verbatim
<root version="1.0" unit="Unknown" type="Response" cmd="startRVideo" sequence="16" session="0">
<token>1</token>
<playvideotype>0</playvideotype>
<svrid>4</svrid>
<ipinfo>10.36.65.112|8513;</ipinfo>		服务端rtsp ip、port信息
<transproto>1</transproto>
<substream>0</substream>
<rtspurl>rtsp://10.36.65.112:8513/realplay/1?token=1</rtspurl>
<sessionid>0</sessionid>
<errmsg/>
<errcode>200</errcode>
<streamportfrom>0</streamportfrom>
<streampacktype>0</streampacktype>
<version>0</version>
<realhandle>3</realhandle>
</root>
@endverbatim
@return									200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_StartVideo_I(t_uint32 vtduSession, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/**
@brief 异步获取实时视频，集成rtsp流程
@param [in] vtduSession		服务句柄
@param [in] domainId		设备域id
@param [in] channelCode		通道代码
@param [in] streamType		码流类型 0主码流, 1辅码流
@param [in] transType		码流传输协议0:TCP 1:UDP
@param [in] streamPackType  码流包类型 //-1 其他 0 用对于的制造商sdk来解码 1 rpt h264 裸码流 2 rpt h264 nal打包 3 pg  pss流 
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出 格式同VTDU_AC_StartVideo_I
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_RealPlay_I(t_uint32 vtduSession, char *domainId, char *channelCode, t_int32 streamType, t_int32 transType, t_int32 streamPackType, char *xmlOutput, t_uint32 maxLen);

/**
@brief 异步获取视频
@param [in] vtduSession		服务句柄
@param [in] xmlInput		请求内容
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<domid></domid>							设备域id
<chncode></chncode>						通道代码
<playvideotype></playvideotype>			0:实时视频, 1:录像回放, 2:语音对讲
<talktype></talktype>					0:通道对讲，1:设备对讲
<playtype></playtype>					1:按文件回放,  2:按时间回放
<transproto></transproto>				0:TCP, 1:UDP
<streamtype></streamtype>				0:主码流, 1:辅码流
<streampacktype></streampacktype>		0:用对于的制造商sdk来解码 (设备排序RTP码流)	
										1:rpt h264 裸码流 	(H264RTP裸码流)
										2:rpt h264 nal打包 (H264RTP标准码流)
										3:pg  pss流 	(南方电网PG码流)	
topacktype>3</topacktype>				码流打包转换类型	 0:默认 1:pg转RTMP 2:大华2Rtmp 3:大华2RTPH264Nal
<blocalrecv>1</blocalrecv>				非0:码流直接发送给sdk,0:发送给其他机器
<sourcetype></sourcetype>				1:中心录像，2:前端录像
<filename></filename>					录像文件名
<vruid></vruid>							录像存储服务ID
<diskid></diskid>						录像存储磁盘ID
<filehandle></filehandle>				录像存储文件句柄
<starttime></starttime>					开始时间
<endtime></endtime>						结束时间
</root>
@endverbatim
@param [in] maxLen						xmlOutput长度
@param [out] xmlOutput					xml输出 格式同VTDU_AC_StartVideo_I
@return									200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_StartVideo(t_uint32 vtduSession, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/** @} */

/**
* @defgroup VTDU_SDK异步RTSP流程
* @{
*/

/**
@brief 异步Rtsp连接
@param [in] realHandle		服务句柄
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_RtspConnect(t_uint32 realHandle);

/**
@brief 异步rtsp Describe
@param [in] realHandle		播放句柄
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_VideoDescribe(t_uint32 realHandle);

/**
@brief 异步rtsp Setup
@param [in] realHandle		播放句柄
@param [in] clientIpInfo	请求端ip信息，格式"ip|port;ip|port;"
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_VideoSetup(t_uint32 realhandle, char *clientIpInfo);

/**
@brief 异步rtsp Play，相关接口 VTDU_SC_SeekPlay
@param [in] realHandle		播放句柄
@param [in] rang			请求端ip信息，格式"ip|port;ip|port;"
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_VideoPlay(t_uint32 realHandle);

/**
@brief 异步录像拖动,如果播放的时间也需要带range 和 scale可以使用这个接口
@param [in] realHandle		播放句柄
@param [in] timeout			超时时间
@param [in] range			定位位置,按时间拖动格式:clock=19000101T000000Z-，按文件大小拖动格式:byte=12333-
@param [in] scale			播放速度 
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_SeekPlay(t_uint32 realHandle, char *range, t_float32 scale);

/**
@brief 异步录像暂停
@param [in] realHandle		播放句柄
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_VideoPause(t_uint32 realHandle);

/**
@brief 视频停止
@param [in] realHandle		播放句柄
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_Stop(t_uint32 realHandle);

/** @} */

/**
* @defgroup VTDU_SDK同步连接
* @{
*/

/**
@brief 同步连接vtdu
@param [in] cmuLoginHandle	cmu验证session
@param [in] timeout			超时时间
@param [in] ipInfo			vtdu服务ip信息
@param [in] svrDomId		服务域id
@param [in] svrId			服务id
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<vtdusession>2</vtdusession>
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_Connect(t_uint32 cmuLoginHandle, t_int32 timeout, char *ipInfo, char *svrDomId, t_int32 svrId, char *xmlOutput, t_uint32 maxLen);

/**
@brief 同步断开连接
@param [in] vtduSession		服务句柄
@param [in] timeout			超时时间
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_Disconnect(t_uint32 vtduSession, t_int32 timeout);

/** @} */

/**
* @defgroup VTDU_SDK同步录像
* @{
*/

/**
@brief 同步录像查询
@param [in] vtduSession		服务句柄
@param [in] timeout			超时时间
@param [in] xmlInput		录像查询信息，格式同VTDU_AC_QueryRecordFile
@param [in] maxLen			对应的最大长度
@param [out] xmlOutput		查询结果输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<info>
<count>2</count>
<item sourcetype="2" recordtype="1" starttime="20141229T160000Z" endtime="20141229T170000Z" filename="0|0|77036|682394|0|5|20141229T160000Z|20141229T170000Z" length="682394" title="" planid="0" vruid="0" diskid="0" filehandle="0" devcode="" rtspurl=""/>
<item sourcetype="2" recordtype="1" starttime="20141229T170000Z" endtime="20141229T175534Z" filename="0|0|77631|603136|0|15|20141229T170000Z|20141229T175534Z" length="603136" title="" planid="0" vruid="0" diskid="0" filehandle="0" devcode="" rtspurl=""/>
</info>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_QueryRecordFile(t_uint32 vtduSession, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/**
@brief 同步录像查询,修正接口（保证输入xml可以与vrusdk接口共用）
@param [in] vtduSession		服务句柄
@param [in] timeout			超时时间
@param [in] xmlInput		录像查询信息，格式同VTDU_AC_QueryRecordFile_Modify
@param [in] maxLen			对应的最大长度
@param [out] xmlOutput		查询结果输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<info>
<count>2</count>
<item sourcetype="2" recordtype="1" starttime="20141229T160000Z" endtime="20141229T170000Z" filename="0|0|77036|682394|0|5|20141229T160000Z|20141229T170000Z" length="682394" title="" planid="0" vruid="0" diskid="0" filehandle="0" devcode="" rtspurl=""/>
<item sourcetype="2" recordtype="1" starttime="20141229T170000Z" endtime="20141229T175534Z" filename="0|0|77631|603136|0|15|20141229T170000Z|20141229T175534Z" length="603136" title="" planid="0" vruid="0" diskid="0" filehandle="0" devcode="" rtspurl=""/>
</info>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_QueryRecordFile_Modify(t_uint32 vtduSession, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/** @} */

/**
* @defgroup VTDU_SDK同步视频语音
* @{
*/

/**
@brief 同步获取视频（包括实时,录像,语音等），集成rtsp流程
@param [in] vtduSession		服务句柄
@param [in] timeout			超时时间
@param [in] xmlInput		视频请求信息，格式同VTDU_AC_StartVideo_I
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<realhandle>3</realhandle>
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_StartVideo_I(t_uint32 vtduSession, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/**
@brief 同步获取实时视频，集成rtsp流程
@param [in] vtduSession		服务句柄
@param [in] timeout			超时时间
@param [in] domainId		设备域id
@param [in] channelCode		通道代码
@param [in] streamType		码流类型 0主码流, 1辅码流
@param [in] transType		码流传输协议0:TCP 1:UDP
@param [in] streamPackType  码流包类型 //-1 其他 0 用对于的制造商sdk来解码 1 rpt h264 裸码流 2 rpt h264 nal打包 3 pg  pss流 
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<realhandle>3</realhandle>
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_RealPlay_I(t_uint32 vtduSession, t_int32 timeout, char *domainId, char *channelCode, t_int32 streamType, t_int32 transType, t_int32 streamPackType, char *xmlOutput, t_uint32 maxLen);

/**
@brief 同步语音对讲，集成rtsp流程
@param [in] vtduSession		服务句柄
@param [in] timeout			超时时间
@param [in] domainId		请求的视频所在域
@param [in] channelCode		通道代码
@param [in] talkType		对讲类型 0通道对讲, 1设备对讲
@param [in] transType		码流传输协议0:TCP 1:UDP
@param [in] streamPackType  码流包类型 //-1 其他 0 用对于的制造商sdk来解码 1 rpt h264 裸码流 2 rpt h264 nal打包 3 pg  pss流 
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<realhandle>3</realhandle>
</root>
@endverbatim
@return						200 成功,其他详见错误码文档  
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_RealTalking_I(t_uint32 vtduSession, t_int32 timeout, char *domainId, char *channelCode, t_int32 talkType, t_int32 transType, t_int32 streamPackType, char *xmlOutput, t_uint32 maxLen);

/**
@brief 扩展同步语音对讲，集成rtsp流程
@param [in] vtduSession		服务句柄
@param [in] timeout			超时时间
@param [in] domainId		请求的视频所在域
@param [in] channelCode		通道代码
@param [in] talkType		对讲类型 0通道对讲, 1设备对讲
@param [in] transType		码流传输协议0:TCP 1:UDP
@param [in] streamPackType  码流包类型 //-1 其他 0 用对于的制造商sdk来解码 1 rpt h264 裸码流 2 rpt h264 nal打包 3 pg  pss流 
@param [in] convType        码流转换类型 0不转换 3 G711A转大华
@param [in] audioEncodeType 语音编码类型
@param [in] audioSamplingRate 音频采样率
@param [in] audioChannelNum   声道数
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<realhandle>3</realhandle>
</root>
@endverbatim
@return						200 成功,其他详见错误码文档  
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_RealTalkingEx_I(t_uint32 vtduSession, t_int32 timeout,
										 char *domainId, char *channelCode, 
										 t_int32 talkType, t_int32 transType,
										 t_int32 streamPackType, t_int32 convType,
										 t_int32 audioEncodeType, t_int32 audioSamplingRate, t_int32 audioChannelNum,
										 char *xmlOutput, t_uint32 maxLen);

/**
@brief 同步发送对讲数据
@param [in] realHandle		播放句柄
@param [in] buffer			数据
@param [in] bufferLen		数据长度
@return						200 成功,其他详见错误码 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_SendTalkData(t_uint32 realHandle, char* buffer, t_uint32 bufferLen);

/**
@brief 同步获取视频
@param [in] vtduSession		服务句柄
@param [in] timeout			超时时间
@param [in] xmlInput		请求内容，格式同VTDU_AC_StartVideo
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<realhandle>3</realhandle>
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_StartVideo(t_uint32 vtduSession, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/** @} */

/**
* @defgroup VTDU_SDK同步RTSP流程
* @{
*/

/**
@brief 同步Rtsp连接
@param [in] realHandle		服务句柄
@param [in] timeout			超时时间
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_RtspConnect(t_uint32 realHandle, t_int32 timeout);

/**
@brief 同步rtsp Describe
@param [in] realHandle		播放句柄
@param [in] timeout			超时时间
@return						200 成功,其他详见错误码文档  
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_VideoDescribe(t_uint32 realHandle, t_int32 timeout);

/**
@brief 同步rtsp Setup
@param [in] realHandle		播放句柄
@param [in] timeout			超时时间
@param [in] clientIpInfo	请求端ip信息，格式"ip|port;ip|port;"
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<serverIp>10.36.65.112</serverIp>
<serverPort>20000</serverPort>
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_VideoSetup(t_uint32 realHandle, t_int32 timeout, char *clientIpInfo, char *xmlOutput, t_uint32 maxLen);

/**
@brief 同步rtsp Play 相关接口 VTDU_SC_SeekPlay
@param [in] realHandle		播放句柄
@param [in] timeout			超时时间
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_VideoPlay(t_uint32 realHandle, t_int32 timeout);

/**
@brief 同步rtsp Play 相关接口 VTDU_SC_SeekPlay
@param [in] realHandle		播放句柄
@param [in] timeout			超时时间
@return						200 成功,其他详见错误码文档 
@remarks					播放并马上暂停
@see 
*/
DLIB_API t_int32 VTDU_SC_VideoPlayAndPause(t_uint32 realHandle, t_int32 timeout);

/**
@brief 同步录像拖动,如果播放的时间也需要带range 和 scale可以使用这个接口
@param [in] realHandle		播放句柄
@param [in] timeout			超时时间
@param [in] range			定位位置,按时间拖动格式:clock=19000101T000000Z-，按文件大小拖动格式:byte=12333-
@param [in] scale			播放速度 
@return						200 成功,其他详见错误码文档   
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_SeekPlay(t_uint32 realHandle, t_int32 timeout, char *range, t_float32 scale);

/**
@brief 同步录像暂停
@param [in] realHandle		播放句柄
@param [in] timeout			超时时间
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_VideoPause(t_uint32 realHandle, t_int32 timeout);

/**
@brief 同步视频关闭
@param [in] realHandle		播放句柄
@param [in] timeout			超时时间
@return						200 成功,其他详见错误码文档  
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_Stop(t_uint32 realhandle, t_int32 timeout);

/**
@brief 同步码流切换        
@param [in] timeout			超时时间
@param [in] chnCode			通道code
@param [in] domainId		设备域id
@param [in] streamType		码流类型：0主码流， 1辅码流
@return						200 成功,其他详见错误码文档  
@remarks					仅供广东电网使用
@see 
*/
DLIB_API t_int32 VTDU_SC_StreamChange(t_uint32 vtduSession, t_int32 timeout, char *chnCode, char *domainId, t_int32 streamType);


/** @} */

/** @} */

#ifdef __cplusplus
}
#endif


#endif
