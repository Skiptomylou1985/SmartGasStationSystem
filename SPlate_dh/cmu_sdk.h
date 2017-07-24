/**
 * Copyright (c) 2014~2015, 浙江大华系统工程有限公司 All rights reserved.
 * \file		cmu_sdk.h
 * \brief		cmu_sdk
 * \author		24997
 * \date		2014年12月19日
 * \note		CMU SDK 接口
 */
#ifndef IBP_CMU_SDK_H
#define IBP_CMU_SDK_H

#if !defined(t_uint32)
typedef unsigned int t_uint32;
#endif

#if !defined(t_int32)
typedef int t_int32;
#endif

#if !defined(t_int64)
typedef long long t_int64;
#endif

#if !defined(t_float32)
typedef float t_float32;
#endif

#ifdef WIN32
#ifdef IBPCMUSDK_LIB_EXPORTS
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
* @defgroup CMU_SDK函数
* @{
*/

/**
* @defgroup CMU_SDK系统
* @{
*/

/**
@brief CMU_SDK初始化
@return 
@remarks 如果和其它SDK一起使用，需要最先调用此接口
@see CMU_SC_Cleanup
*/
DLIB_API t_int32 CMU_SC_Init();

/**
@brief CMU_SDK初始化
@return 
@remarks 如果和其它SDK一起使用，需要最先调用此接口
@see CMU_SC_Cleanup
*/
DLIB_API t_int32 CMU_SC_InitNoApp();

/**
@brief CMU_SDK反初始化
@return 
@remarks 如果和其它SDK一起使用，需要最后调用此接口
@see CMU_SC_Init
*/
DLIB_API t_int32 CMU_SC_Cleanup();

/**
@brief 设置日志配置文件路径
@param [in] path		配置文件路径
@return 
@remarks
@see
*/
DLIB_API t_int32 CMU_SC_SetLogCfgPath(char* path);

/**
@brief 客户端记录日志
@param [in] level		日志等级
@verbatim
	0	调试日志
	1	信息日志
	2	接口日志
	3	警告日志
	4	错误日志
	5	致命日志
@endverbatim
@param [in] info		日志信息
@return 
@remarks
@see
*/
DLIB_API t_int32 CMU_SC_Log(t_uint32 level, char* info);

/**
@brief 客户端记录trace
@param [in] info		trace信息
@return 
@remarks
@see
*/
DLIB_API t_int32 CMU_SC_Trace(char* info);

/**
@brief 日志级别开关
@param [in] level		日志等级
@verbatim
	0	调试日志
	1	信息日志
	2	接口日志
	3	警告日志
	4	错误日志
	5	致命日志
@endverbatim
@param [in] flag		开关
@verbatim
0	关闭
1	开启
@endverbatim
@return 
@remarks
@see
*/
DLIB_API t_int32 CMU_SC_LogEnabled(t_uint32 level, t_int32 flag);

/**
@brief 查询字典表
@param [in]	 timeout		超时时间
@param [in]  ip				服务IP
@param [in]  port			服务端口
@param [in]	 tabletype		字典表类型
@verbatim
	0	制造商
	1	设备类型
	2	位置类型
	3	告警类型
	4	码流类型
@endverbatim
@param [out] outxml			查询信息
@verbatim
制造商
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		id=""			ID
		domid=""		域ID
		title=""		名称
		dllname=""		DLL名称
		fast=""			是否有效
		updatetime=""		更新时间
	/>
</root>
@endverbatim
@verbatim
设备类型
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		typeid=""		类型ID
		typename=""		类型名称
		fast=""			是否有效
		updatetime=""		更新时间
	/>
</root>
@endverbatim
@verbatim
位置类型
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		typeid=""		类型名称
		domid=""		域ID
		title=""		名称
		fast=""			是否有效
		updatetime=""		更新时间
	/>
</root>
@endverbatim
@verbatim
告警类型
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		categoryid=""		目录ID
		typeid=""		类型ID
		title=""		名称
		fast=""			是否有效
		updatetime=""		更新时间
	/>
</root>
@endverbatim
@verbatim
码流类型
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		id=""			ID
		typeid=""		类型ID
		desc=""			描述
		fast=""			是否有效
		updatetime=""		更新时间
	/>
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryDictTable(t_int32 timeout, char* ip, t_uint32 port, t_int32 tabletype, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK回调函数
* @{
*/

/**
@brief CMU SDK 消息回调函数定义
@param [in] handle		用户登录句柄
@param [in] data		消息数据
@param [in] dwBufSize		数据长度
@param [in] pUser		用户数据
@return 
@remarks
@see CMU_SC_SetMsg
*/
typedef t_int32 (*fIbpCmuMsgCallBack)(t_uint32 handle, char *data, t_uint32 bufSize, void* pUser);

/**
@brief 设置CMU SDK 回调函数
@param [in] cb		设置的回调函数
@param [in] pUser	用户数据
@return 
@remarks 回调消息示例
@verbatim
报告master信息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="CMU" type="Request" cmd="reportMasterInfo" sequence="" session="0">
	<modulename></modulename>		模块名 比如 DMU, VTDU
	<domid></domid>				域ID
	<ipinfo></ipinfo>			IP信息10.36.65.89|9858;
	<svrid></svrid>				服务ID
	<accnum></accnum>			接入能力
	<adapnum></adapnum>			转发能力
</root>
@endverbatim
@verbatim
用户被踢掉
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="CMU" type="Request" cmd="logout" sequence="" session="0">
	<domid></domid>				域ID
	<userid></userid>			用户ID
	<username></username>			用户名称
	<strdata></strdata>			字符串数据
	<intdata></intdata>			数字数据
</root>
@endverbatim
@verbatim
服务online消息通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="CMU" type="onlineNotify" cmd="onlineNotify" sequence="0" length="0">
	<server 
		servername="" 			服务名称
		session="" 			服务句柄
		status="" 			上下线状态
	/>
</root>
@endverbatim
@verbatim
设备信息通知消息
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="CMU" type="Notify" cmd="sharedDeviceNotify" sequence="">
	<user userid="1" username="admin"/>
	<device domid="" devcode=""  title=""/>
</root>
@endverbatim
@see fIbpCmuMsgCallBack
*/
DLIB_API t_int32 CMU_SC_SetMsg(t_uint32 handle, fIbpCmuMsgCallBack cb, void* pUser);

/** @} */

/**
* @defgroup CMU_SDK登陆登出
* @{
*/

/**
@brief 用户登录
@param [in]  timeout		超时时间
@param [in]  domainId		域ID
@param [in]  ip			服务IP
@param [in]  port		服务端口
@param [in]  username		用户名
@param [in]  userpass		用户密码
@param [out] outxml		返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<handle></handle>		登陆成功返回的句柄
	<userid></userid>		返回的用户ID
	<domid></domid>			返回的用户域ID
	<handle></handle>		返回的用户handle
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return 200 成功 其它 失败
@remarks
@see CMU_SC_Logout
*/
DLIB_API t_int32 CMU_SC_Login(t_int32 timeout, char* domainId, char* ip, t_uint32 port, char *username, char *userpass, char* outxml, t_uint32 maxlen);

/**
@brief 用户登录接口（增加了登录用户类型）
@param [in]  timeout		超时时间
@param [in]  info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<ip>CMU的IP地址</ip>
	<port>CMU的端口，一般是9800</port>
	<username>登录用户名</username>
	<userpass>登录用户名</userpass>
	<type>登录类型，0:调度台 1:Web客户端登录 2:手机客户端登录 3:PC客户端登录</type>
	<imei>手机客户端登录需填写imei以启用手机绑定功能，不填写则不启用该功能</imei>
</root>
@endverbatim
@param [out] outxml		返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<handle></handle>		登陆成功返回的句柄
	<userid></userid>		返回的用户ID
	<domid></domid>			返回的用户域ID
	<session></session>		返回的用户handle
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_Logout
*/
DLIB_API t_int32 CMU_SC_LoginEx(t_int32 timeout, char* info, char* outxml, t_uint32 maxlen);

/**
@brief 用户是否已经登录
@param [in] handle		登陆句柄
@return 0 未登录 1 已登录
@remarks
@see CMU_SC_Login
*/
DLIB_API t_int32 CMU_SC_IsLogin(t_uint32 handle);

/**
@brief 用户登出
@param [in] handle		登陆句柄
@return 
@remarks
@see CMU_SC_Login
*/
DLIB_API t_int32 CMU_SC_Logout(t_uint32 handle);

/**
@brief 校验用户名密码
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [in]  username		用户名
@param [in]  userpass		用户密码
@param [out] outxml		返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<val>1</val>			校验结果 0 不是同一用户 1 同一用户 
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_CheckUserPwd(t_uint32 handle, t_int32 timeout, char *username, char *userpass, char *outxml, t_uint32 maxlen );

/**
@brief 加解锁用户
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [in]  domid		域ID
@param [in]  userid		用户ID
@param [in]  flag		标识 0 解锁 1 锁定
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_LockUser(t_uint32 handle, t_int32 timeout, char* domid, t_int32 userid, t_int32 flag);

/**
@brief 修改密码
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [in]  domid		域id
@param [in]  userid		用户id
@param [in]  oldpwd		老密码
@param [in]  newpwd		新密码
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_ModifyUserPwd(t_uint32 handle, t_int32 timeout, char* domid, t_int32 userid, char* oldpwd, char* newpwd);

/**
@brief 操作用户登陆负载
@param [in]  handle		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 userid			用户ID
@param [in]	 num			登陆登出增量数（正负增量表示）
@return 
@remarks
@see CMU_SC_QueryUserWithVideoDev
*/
DLIB_API t_int32 CMU_SC_OptUserLoad(t_uint32 handle, t_int32 timeout, t_int32 userid, t_int32 num);

/** @} */

/**
* @defgroup CMU_SDK组织管理
* @{
*/

/**
@brief 操作组织
@param [in] handle		登陆句柄
@param [in] timeout		超时时间
@param [in] info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			//操作类型 0 增加 1 修改 2 删除
	<org 
		domid=""		域ID
		orgcode=""		组织代码
		olddomid=""		旧域ID(此两字段修改时有效)
		oldorgcode=""		旧组织代码
		parentdomid=""		父域ID
		parentorgcode=""	父组织代码
		orgpath=""		组织路径
		orgposidx=""		组织位置索引
		title=""		标签
		updatetime=""		更新时间
		desc=""			描述
		orgtype=""			组织类型（新增字段）1:组织 2:区域 3:部门
	/>
</root>
@endverbatim
@return 
@remarks 一次可以操作多个组织节点（并排方式）
@see CMU_SC_QueryOrg
*/
DLIB_API t_int32 CMU_SC_OptOrg(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief 查询指定组织详细信息
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [in]  domid		组织域ID
@param [in]  orgcode		组织代码
@param [out] outxml		查询信息(详见CMU_SC_OptOrg注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" />
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptOrg
*/
DLIB_API t_int32 CMU_SC_QueryOrg(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode, char*outxml, t_uint32 maxlen);

/**
@brief 查询所有组织
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [out] outxml		查询信息(详见CMU_SC_OptOrg注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" >
		<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" >
			<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" />
		</org>
	</org>
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptOrg
*/
DLIB_API t_int32 CMU_SC_QueryAllOrg(t_uint32 handle, t_int32 timeout, char*outxml, t_uint32 maxlen);

/**
@brief 查询所有组织(增加权限功能)
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<funid></funid>
</root>
@endverbatim
@param [out] outxml		查询信息(详见CMU_SC_OptOrg注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" >
		<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" >
			<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" />
		</org>
	</org>
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptOrg
*/
DLIB_API t_int32 CMU_SC_QueryAllOrgEx(t_uint32 handle, t_int32 timeout, char *info, char*outxml, t_uint32 maxlen);

/**
@brief 按照条件查询所有组织
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [in] info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<orgdomid></orgdomid>空:全部
	<orgcode></orgcode>空:全部
	<orgtype></orgtype>-1:全部 1:组织 2:区域 3:部门，多种类型用逗号(",")分隔
</root>
@endverbatim
@param [out] outxml		查询信息(详见CMU_SC_OptOrg注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" orgtype=""/>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" orgtype=""/>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" orgtype=""/>
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptOrg
*/
DLIB_API t_int32 CMU_SC_QueryOrgEx(t_uint32 handle, t_int32 timeout, char *info, char*outxml, t_uint32 maxlen);

/**
@brief 查询子组织
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [in]  domid		域ID
@param [in]  parentorgcode	父组织代码(为空字符串返回根组织信息)
@param [out] outxml		查询信息(详见CMU_SC_OptOrg注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" />
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" />
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" />
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptOrg
*/
DLIB_API t_int32 CMU_SC_QuerySubOrg(t_uint32 handle, t_int32 timeout, char* domid, char* parentorgcode, char*outxml, t_uint32 maxlen);

/**
@brief 查询子组织（需要释放返回对象内存）
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [in]  domid		域ID
@param [in]  parentorgcode	父组织代码(为空字符串返回根组织信息)
@param [out] errorcode		错误码
@param [out]  reallen		信息实际长度
@return 
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" />
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" />
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" />
</root>
@endverbatim
@remarks 请释放返回对象内存！请释放返回对象内存！请释放返回对象内存！
@see CMU_SC_OptOrg
*/
DLIB_API char* CMU_SC_QuerySubOrgXXXX(t_uint32 handle, t_int32 timeout, char* domid, char* parentorgcode, t_int32 *errorcode, t_uint32 *reallen);

/**
@brief 配置自定义分组
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0添加 1修改 2删除</opt>
	<group id="分组id，修改、删除有效"
		parentid="分组父节点ID, 0为根节点"
		name="分组名称，64字节，添加、修改有效"
		type="分组类型，通讯录分组:1,调度台分组:2"
		userid="分组所属用户ID"
	>
		<device domid="" devcode=""/>
		<user domid="" userid=""/>
		<contact domid="" contactid=""/>
	</group>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<group id=""/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptGroup(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 查询自定义分组
@param [in]	session			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<!--userid，parentid，id三个字段同时只能填一个，其他两个字段填-1-->
	<userid>分组所属用户id</userid>
	<parentid>分组父节点id</parentid>
	<id>分组id</id>
	<size>每页返回记录的数量</size>
	<curpage>第几页，从0开始</curpage>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<group id="分组id"
		parentid="分组父节点ID"
		name="分组名称，64字节，添加、修改有效"
		type="分组类型，通讯录分组:1"
	>
		<group id="" parentid="" name="" type="">
			<group id="" parentid="" name="" type=""/>
		</group>
	</group>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks 未分组的查不到
@see 
*/
DLIB_API t_int32 CMU_SC_QueryGroup(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 查询自定义分组下面的对象
@param [in]	session			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<groupid></groupid>
	<size>每页返回记录的数量</size>
	<curpage>第几页，从0开始</curpage>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<group id="分组id"
		parentid="分组父节点ID"
		name="分组名称，64字节，添加、修改有效"
		type="分组类型，通讯录分组:1"
	>
		<device devid="3844" domid="73807" devcode="88888channel1" devtype="31" manufid="1" title="閫氶亾1" status="2" orgdomid="73807" orgcode="1" devpath="0-3772-" orgpath="0-1-522" devlinktype="0" updatetime="2016-09-01 20:16:56"/>
		<user id="3" userid="3" name="fz" domid="66404">
			<phone number="">
			<phone number="">
		</user>
		<contact domid="66404" id="4" userid="1" name="001">
			<telephone id="4" number="22005" desc=""/>
		</contact>
	</group>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks 未分组的查不到
@see 
*/
DLIB_API t_int32 CMU_SC_QueryGroupObject(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 查询子组织
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [in] info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<funid></funid>
	<domid></domid>
	<parentorgdomid></parentorgdomid>
	<parentorgcode></parentorgcode>
	<orgtype></orgtype>-1:全部 1:组织 2:区域 3:部门，多种类型用逗号(",")分隔
</root>
@endverbatim
@param [out] outxml		查询信息(详见CMU_SC_OptOrg注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" orgtype=""/>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" orgtype=""/>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" orgtype=""/>
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptOrg
*/
DLIB_API t_int32 CMU_SC_QuerySubOrgEx(t_uint32 handle, t_int32 timeout, char *info, char*outxml, t_uint32 maxlen);

/**
@brief 添加支队（山西武警项目专用）
@param [in]	session			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0:新增 1:修改 2:删除</opt>
	<detachment 
		id="支队编号，修改删除有效，新增不需要填写"
		name="支队名称" 
		dbip="支队数据库IP" 
		dbport="支队数据库port"
		dbuser="支队数据库用户名" 
		dbpass="支队数据库密码" 
		dbname="支队数据库名称" 
		desc="支队描述信息"
	/>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<detachment id="/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks 
@see 
*/
DLIB_API t_int32 CMU_SC_OptDetachment(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 查询支队（山西武警项目专用）
@param [in]	session			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<detachmentid>支队编号，-1查询全部</detachmentid>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<detachment id="" name="" dbip="" dbuser="" dbpass="" dbname="" desc="">
		<sentinel id="岗哨编号" name="岗哨名称" number="岗哨号码"/>
		<sentinel id="" name="" number=""/>
	</detachment>
	<detachment id="" name="" dbip="" dbuser="" dbpass="" dbname="" desc="">
		<sentinel id="" name="" number=""/>
		<sentinel id="" name="" number=""/>
	</detachment>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks 
@see 
*/
DLIB_API t_int32 CMU_SC_QueryDetachment(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 配置岗哨额外信息（山西武警项目专用）
@param [in]	session			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<detachmentid>支队编号，配置必填</detachmentid>
	<sentinelid>岗哨编号，配置必填</sentinelid>
	<number>岗哨号码，没有为空</number>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root/>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks 
@see 
*/
DLIB_API t_int32 CMU_SC_OptSentinelExInfo(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 查询岗哨查岗信息（山西武警项目专用）
@param [in]	session			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<number>岗哨号码</number>
	<checktime>查岗时间，以天为最小单位，格式：yyyy-mm-dd</checktime>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<sentinel id="" name="岗哨名称" number="岗哨号码" dutycheck="查岗人姓名"/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks 
@see 
*/
DLIB_API t_int32 CMU_SC_QuerySentinelDutyCheck(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);


/** @} */

/**
* @defgroup CMU_SDK设备管理
* @{
*/


/**
@brief 操作设备
@param [in] handle		登陆句柄
@param [in] timeout		超时时间
@param [in] info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			//操作类型 0 增加 1 修改 2 删除
	<device 
		domid=""		域ID
		devcode=""		设备代码
		olddomid=""		旧域ID（此两字段修改时有效）
		olddevcode=""		旧设备代码
		parentdomid=""		父域ID
		parentdevcode=""	父设备代码
		orgdomid=""		组织域ID
		orgcode=""		组织代码
		devpath=""		设备路径
		orgpath=""		组织路径
		devtype=""		设备类型
		manufid=""		厂商ID
		title=""		标签
		status=""		状态
		devposidx=""		设备位置索引
		devlinktype=""
		display=""			是否显示
		updatetime=""		更新时间
		extend=""			扩展信息（话机设备用）
		loginname=""		登陆用户名
		loginpwd=""		登陆密码
		ipaddr=""		设备IP
		portdev=""		设备端口
		streamtype=""		码流类型
		contrator=""		承包商/工程商
		locationid=""		场所
		installspot=""		安装地点
		installtime=""		安装时间
		maintainer=""		制造商
		phone=""		电话
		model=""		模块
		visible=""		是否可见
		longitude=""		经度
		latitude=""		纬度
		desc=""			描述
	>
		<channel 
			domid=""		域ID
			devcode=""		设备代码
			olddomid=""		旧域ID（此两字段修改时有效）
			olddevcode=""		旧设备代码
			parentdomid=""		父域ID
			parentdevcode=""	父设备代码
			orgdomid=""		组织域ID
			orgcode=""		组织代码
			devpath=""		设备路径
			orgpath=""		组织路径
			devtype=""		设备类型
			manufid=""		厂商ID
			title=""		标签
			status=""		状态
			devposidx=""		设备位置索引
			updatetime=""		更新时间
			chnidx=""		通道索引
			accesory=""		附加信息
		>
			<item domid="" devcode="" slavedomid="" slavedevcode="" />
			<item domid="" devcode="" slavedomid="" slavedevcode="" />
		</channel>
		//可选绑定信息
		<item domid="" devcode="" slavedomid="" slavedevcode="" />
		<item domid="" devcode="" slavedomid="" slavedevcode="" />
	</device>
	<device ...></device>	//支持多设备添加
</root>
@endverbatim
@verbatim
//增加一次设备XML信息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			//操作类型 0 增加 1 修改 2 删除
	<device 
		domid=""			域ID
		devcode=""			设备代码
		olddomid=""			旧域ID（此两字段修改时有效）
		olddevcode=""		旧设备代码
		parentdomid=""		父域ID
		parentdevcode=""	父设备代码
		orgdomid=""			组织域ID
		orgcode=""			组织代码
		devpath=""			设备路径
		orgpath=""			组织路径
		devtype=""			设备类型
		manufid=""			厂商ID
		title=""			标签
		status=""			状态
		devposidx=""		设备位置索引
		updatetime=""		更新时间
		devlinktype=""
		
		detecttype=""		分析类型
		detectpart=""		检测部位
		targettype=""		一次设备类别
		typedesc=""			类型描述
		ratedcurrent=""		额定电流
		heatfeature=""		热像特征
		faultdesc=""		缺陷描述
		sequence=""			序列号
		time=""				出厂日期

		installspot=""		安装地点
		installtime=""		安装时间
		maintainer=""		制造商
		model=""			设备型号
		visible=""			是否可见
		desc=""				描述
	>
	</device>
	<device ...></device>	//支持多设备添加
</root>
@endverbatim
@verbatim
//增加解码器设备XML信息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			//操作类型 0 增加 1 修改 2 删除
	<device 
		domid=""		域ID
		devcode=""		设备代码
		olddomid=""		旧域ID（此两字段修改时有效）
		olddevcode=""		旧设备代码
		parentdomid=""		父域ID
		parentdevcode=""	父设备代码
		orgdomid=""		组织域ID
		orgcode=""		组织代码
		devpath=""		设备路径
		orgpath=""		组织路径
		devtype=""		设备类型
		manufid=""		厂商ID
		title=""		标签
		status=""		状态
		devposidx=""		设备位置索引
		devlinktype=""
		display=""			是否显示
		updatetime=""		更新时间
		extend=""			扩展信息（话机设备用）
		loginname=""		登陆用户名
		loginpwd=""		登陆密码
		ipaddr=""		设备IP
		portdev=""		设备端口
		streamtype=""		码流类型
		contrator=""		承包商
		locationid=""		场所
		installspot=""		安装地点
		installtime=""		安装时间
		maintainer=""		制造商
		phone=""		电话
		model=""		模块
		visible=""		是否可见
		longitude=""		经度
		latitude=""		纬度
		desc=""			描述
		
		uintseq=""				解码单元序号
		decodemode=""		解码模式
		streammode=""		流处理模式
		sort=""						排序码
		combinestatus=""	电视墙融合状态，1表示支持融合，0表示不支持融合
	>
		<channel 
				domid=""		域ID
				devcode=""		设备代码
				olddomid=""		旧域ID（此两字段修改时有效）
				olddevcode=""		旧设备代码
				parentdomid=""		父域ID
				parentdevcode=""	父设备代码
				orgdomid=""		组织域ID
				orgcode=""		组织代码
				devpath=""		设备路径
				orgpath=""		组织路径
				devtype=""		设备类型
				manufid=""		厂商ID
				title=""		标签
				status=""		状态
				devposidx=""		设备位置索引
				updatetime=""		更新时间
				chnidx=""		通道索引
				accesory=""		附加信息
				lighttype=""		灯光类型 0:无灯光 1:ipc自带灯光 2:灯光控制器灯光
				guardtype=""  门禁类型 0:无门禁 1:普通门禁
				uintseq=""				解码单元序号
				splitscreenmax=""	最大分屏数
			>
			</channel>
	</device>
	<device ...></device>	//支持多设备添加
</root>
@endverbatim
@verbatim
//增加门禁控制器器设备XML信息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			//操作类型 0 增加 1 修改 2 删除
	<device 
		domid=""		域ID
		devcode=""		设备代码
		olddomid=""		旧域ID（此两字段修改时有效）
		olddevcode=""		旧设备代码
		parentdomid=""		父域ID
		parentdevcode=""	父设备代码
		orgdomid=""		组织域ID
		orgcode=""		组织代码
		devpath=""		设备路径
		orgpath=""		组织路径
		devtype=""		设备类型
		manufid=""		厂商ID
		title=""		标签
		status=""		状态
		devposidx=""		设备位置索引
		devlinktype=""
		display=""			是否显示
		updatetime=""		更新时间
		extend=""			扩展信息（话机设备用）
		loginname=""		登陆用户名
		loginpwd=""		登陆密码
		ipaddr=""		设备IP
		portdev=""		设备端口
		streamtype=""		码流类型
		contrator=""		承包商
		locationid=""		场所
		installspot=""		安装地点
		installtime=""		安装时间
		maintainer=""		制造商
		phone=""		电话
		model=""		模块
		visible=""		是否可见
		longitude=""		经度
		latitude=""		纬度
		desc=""			描述
	>
		<channel 
				domid=""		域ID
				devcode=""		设备代码
				olddomid=""		旧域ID（此两字段修改时有效）
				olddevcode=""		旧设备代码
				parentdomid=""		父域ID
				parentdevcode=""	父设备代码
				orgdomid=""		组织域ID
				orgcode=""		组织代码
				devpath=""		设备路径
				orgpath=""		组织路径
				devtype=""		设备类型
				manufid=""		厂商ID
				title=""		标签
				status=""		状态
				devposidx=""		设备位置索引
				updatetime=""		更新时间
				chnidx=""		通道索引
				accesory=""		附加信息

				doorenable="1"
				entercardreaderenable="1"
				entercardreadername=""
				entercardreadertype="2323"
				exitcardreaderenable="1"
				exitcardreadername=""
				exitcardreadertype="234"
				lockholdingtime="45345"
				notlockouttime="56756"
			>
			</channel>
	</device>
	<device ...></device>	//支持多设备添加
</root>
@endverbatim
@return 
@remarks
@see CMU_SC_QueryDevice CMU_SC_QueryDevDetail CMU_SC_QueryDevByChn
*/
DLIB_API t_int32 CMU_SC_OptDevice(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief 通过组织查询设备主要信息
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [in]  domid		组织域ID
@param [in]  orgcode		组织代码
@param [out] outxml		查询信息(详见CMU_SC_OptDevice注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode=""  orgpath="" title="" updatetime="" desc="" >
		<device devid="2324" domid="30824" devcode="IMDS_1000" olddomid="" olddevcode="" 
			parentdevid="0" parentdomid="" parentdevcode="" orgid="1" orgdomid="30824" 
			orgcode="1" devpath="0-" orgpath="0-1" devtype="26" manufid="1" title="test_1000" 
			status="1" devposidx="0" updatetime="2017-03-04 11:23:22" devlinktype="0" 
			extend='&lt;extension deviceType="26" extensionName="test_1000" extensionNumber="1000" extensionPassword="dahua1187!" alternateNumber="" extensionLevel="1" interposeLevel="0" transferNumber="" callTransfer="0" dialPlan="255" DTMFMode="0" recordMode="1" chargeMode="0" advancePayment="1" callHold="0" dnd="0" limitOutIn="0" extensionType="3" /&gt;' 
			relatedomid="" relatedevcode="" relatedevtitle="" loginname="" loginpwd="" ipaddr="" 
			portdev="0" streamtype="0" contrator="" locationid="0" installspot="" installtime="0000-00-00 00:00:00" 
			maintainer="" phone="" model="" visible="0" longitude="0" latitude="0" desc="" orgname="test"/>
			//可选绑定信息
			<item domid="" devcode="" slavedomid="" slavedevcode="" />
			<item domid="" devcode="" slavedomid="" slavedevcode="" />
		</device>
	</org>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDevice(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode, char*outxml, t_uint32 maxlen);

/**
@brief 通过组织查询设备信息(根据设备类型)
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [in]  domid			组织域ID
@param [in]  orgcode		组织代码
@param [in]  devtype		设备类型(""全部, 多个条件用逗号分隔，如"1,2,3")
@param [out] outxml			查询信息(详见CMU_SC_OptDevice注释)
@verbatim
//具体根据设备类型决定返回信息，主要信息如下：
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode=""  orgpath="" title="" updatetime="" desc="" >
		<device domid="" devcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" devlinktype="" display="" updatetime="" />
	</org>
</root>
//一次设备
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode=""  orgpath="" title="" updatetime="" desc="" >
		<device domid="" devcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" devlinktype="" detecttype="" detectpart="" targettype="" typedesc="" ratedcurrent="" heatfeature="" faultdesc="" sequence="" time="" installspot="" installtime="" maintainer="" model="" visible="" desc="" />
		<device domid="" devcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" devlinktype="" detecttype="" detectpart="" targettype="" typedesc="" ratedcurrent="" heatfeature="" faultdesc="" sequence="" time="" installspot="" installtime="" maintainer="" model="" visible="" desc="" />
	</org>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDeviceEx(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode, char *devtype, char*outxml, t_uint32 maxlen);

/**
@brief 通过组织和功能权限查询设备主要信息
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [in]  domid		组织域ID
@param [in]  orgcode		组织代码
@param [in]  funcid			功能权限ID
@param [out] outxml		查询信息(详见CMU_SC_OptDevice注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode=""  orgpath="" title="" updatetime="" desc="" >
		<device domid="" devcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" />
	</org>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDeviceByFuncId(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode, t_int32 funcid, char*outxml, t_uint32 maxlen);

/**
@brief 通过组织和功能权限查询设备主要信息(根据设备类型)
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [in]  domid		组织域ID
@param [in]  orgcode		组织代码
@param [in]  devtype		设备类型(""全部, 多个条件用逗号分隔，如"1,2,3")
@param [in]  funcid			功能权限ID
@param [out] outxml		查询信息(详见CMU_SC_OptDevice注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode=""  orgpath="" title="" updatetime="" desc="" >
		<device domid="" devcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" />
	</org>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDeviceByFuncIdEx(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode, char* devtype, t_int32 funcid, char*outxml, t_uint32 maxlen);

/**
@brief 根据设备查询设备详细信息
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 domid		设备域ID
@param [in]	 devcode	设备代码
@param [in]	 devtype	设备类型(未知类型填0)
@param [out] outxml		查询信息(详见CMU_SC_OptDevice注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<device domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" display="" devlinktype="" updatetime="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" >
		<channel domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" chnidx="" accesory="" lighttype="" guardtype="">
			//可选绑定信息
			<item domid="" devcode="" slavedomid="" slavedevcode="" />
			<item domid="" devcode="" slavedomid="" slavedevcode="" />
		</channel>
		//可选绑定信息
		<item domid="" devcode="" slavedomid="" slavedevcode="" />
		<item domid="" devcode="" slavedomid="" slavedevcode="" />
	</device>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDevDetail(t_uint32 handle, t_int32 timeout, char* domid, char* devcode, t_int32 devtype, char*outxml, t_uint32 maxlen);

/**
@brief 根据设备和功能权限查询设备详细信息
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 domid		设备域ID
@param [in]	 devcode	设备代码
@param [in]	 devtype	设备类型(未知类型填0)
@param [in]  funcid			功能权限ID
@param [out] outxml		查询信息(详见CMU_SC_OptDevice注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<device domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" >
		<channel domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" chnidx="" accesory="" />
	</device>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDevDetailByFuncId(t_uint32 handle, t_int32 timeout, char* domid, char* devcode, t_int32 devtype, t_int32 funcid, char* outxml, t_uint32 maxlen);

/**
@brief 根据通道查询设备详细信息
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 domid		通道域ID
@param [in]	 chncode	通道代码
@param [out] outxml		查询信息(详见CMU_SC_OptDevice注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<device domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" >
		<channel domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" chnidx="" accesory="" />
	</device>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDevByChn(t_uint32 handle, t_int32 timeout, char* domid, char* chncode, char* outxml, t_uint32 maxlen);

/**
@brief 通过组织查询设备列表详细信息(分页)
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [in]  domid			组织域ID
@param [in]  code			组织代码
@param [in]	 size			页大小
@param [in]	 curpage		当前页(从0开始)
@param [out] outxml			查询信息(详见CMU_SC_OptDevice注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>			总条数
	<item domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" extend="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" orgname="" />
	<item domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" extend="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" orgname="" />
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDevDetailByCode(t_uint32 handle, t_int32 timeout, char* domid, char* code, t_int32 size, t_int32 curpage, char* outxml, t_uint32 maxlen);

/**
@brief 通过组织和设备类型查询设备列表详细信息(分页)
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [in]  domid			组织域ID
@param [in]  code			组织代码
@param [in]  devtype		设备类型(""全部, 多个条件用逗号分隔，如"1,2,3")
@param [in]	 size			页大小
@param [in]	 curpage		当前页(从0开始)
@param [out] outxml			查询信息(详见CMU_SC_OptDevice注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>			总条数
	<item domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" extend="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" orgname="" />
	<item domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" extend="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" orgname="" />
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDevDetailByCodeEx(t_uint32 handle, t_int32 timeout, char* domid, char* code, char *devtype, t_int32 size, t_int32 curpage, char* outxml, t_uint32 maxlen);

/**
@brief 根据条件查询设备主要（详细）信息
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [in]  domid			组织域ID（""全部）
@param [in]  code			组织代码（""全部）
@param [in]	 devname		设备名称（""全部）
@param [in]	 devtype		设备类型(0全部)
@param [in]	 manuftype		厂商类型(-1全部)
@param [in]	 status			在线状态(0全部 1 在线 2 不在线)
@param [in]	 size			页大小
@param [in]	 curpage		当前页(从0开始)
@param [out] outxml			查询信息(详见CMU_SC_OptDevice注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>			总条数
	<item domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" extend="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" orgname="" />
	<item domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" extend="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" orgname="" />
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDevBrief(t_uint32 handle, t_int32 timeout, char* domid, char* code, char *devname, t_int32 devtype, t_int32 manuftype, t_int32 status, t_int32 size, t_int32 curpage, char* outxml, t_uint32 maxlen);

/**
@brief 根据条件查询设备主要（详细）信息
@param [in]  handle		登陆句柄
@param [in]  timeout		超时时间
@param [in]  info			条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid />				组织域ID（""全部）
	<code />				组织代码（""全部）
	<devname />				设备名称（""全部）
	<devtype />				设备类型(""全部, 多个条件用逗号分隔，如"1,2,3")
	<manuftype />			厂商类型(-1全部)
	<status />				在线状态(0全部 1 在线 2 不在线)
	<size />				页大小
	<curpage />				当前页(从0开始)
</root>
@endverbatim		
@param [out] outxml			查询信息(详见CMU_SC_OptDevice注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>			总条数
	<item domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" extend="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" orgname="" />
	<item domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" extend="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" orgname="" />
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDevBriefEx(t_uint32 handle, t_int32 timeout, char *info, char* outxml, t_uint32 maxlen);

/**
@brief 操作设备绑定关系
@param [in]  handle			登陆句柄
@param [in]	 timeout		超时时间
@param [in]  info			条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<relation 
		devcode="" 主绑定设备code
		domid="" 主绑定设备域id
		bind="" 0:解绑 1:绑定 (解绑的时候，如果relation下面没有device节点，就解绑全部)
	>
		<device 
			devcode="" 
			domid="" 
			preposindex="预置位编号preset postion index"/>绑定的设备
		<device devcode="" domid="" preposindex=""/>
	</relation>
	<relation>
		...
	</relation>
</root>
@endverbatim		
@param [out] outxml	
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptDevRelation(t_uint32 handle, t_int32 timeout, char *info, char* outxml, t_uint32 maxlen);

/**
@brief 查询设备绑定关系
@param [in]  handle			登陆句柄
@param [in]	 timeout		超时时间
@param [in]  info			条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<relation 
		devcode="" 被查询设备code
		domid="" 被查询设备域id
	/>
</root>
@endverbatim		
@param [out] outxml	
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<relation 
		devcode="" 被查询设备code
		domid="" 被查询备域id
	>
		<device 
			devcode="" 
			domid=""
			preposindex="预置位编号preset postion index"
		/> 绑定的设备
		<device devcode="" domid=""/>
	</relation>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryDevRelation(t_uint32 handle, t_int32 timeout, char *info, char* outxml, t_uint32 maxlen);

/**
@brief 配置下级域设备组织结构
@param [in]  handle			登陆句柄
@param [in]	 timeout		超时时间
@param [in]  info			操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="">
		<device domid="" devcode=""/>
		<device domid="" devcode=""/>
	</org>
</root>
@endverbatim
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptSubRegionDevOrg(t_uint32 handle, t_int32 timeout, char *info);

/**
@brief 查询组织或设备并返回它们的组织结构
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<title></title>
	<curpage></curpage>
	<size></size>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<org domid="" orgcode="" title=""> 根节点
		<org domid="" orgcode="" title="">
			<org domid="" orgcode="" title=""/>要查找的节点
		</org>
	</org>
	<org domid="" orgcode="" title="">根节点
		<org domid="" orgcode="" title="">
			<device domid="" devcode="" title=""/>要查找的节点
		</org>
	</org>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryOrgDevByTitle(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 查询设备故障信息
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息（暂时为空）
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<upper title="" 省级名称
			devtotalnum="" 设备总数
			devfaultnum="" 设备故障数
			devfaultrate="" 设备故障率
			chntotalnum=""  通道总数
			chnfaultnum="" 通道故障数
			chnfaultrate="" 通道故障率
	>
		<level title="" 名称（500kV、220kV、110kV、其他）省级统计数据
			devtotalnum="" 设备总数
			devfaultnum="" 设备故障数
			devfaultrate="" 设备故障率
			chntotalnum=""  通道总数
			chnfaultnum="" 通道故障数
			chnfaultrate="" 通道故障率
		/>
		<region title="" 地区级名称
				devtotalnum="" 设备总数
				devfaultnum="" 设备故障数
				devfaultrate="" 设备故障率
				chntotalnum="" 通道总数
				chnfaultnum=""  通道故障数
				chnfaultrate=""通道故障率
		>
			<center title="" 巡维中心名称
					devtotalnum="" 设备总数
					devfaultnum="" 设备故障数
					devfaultrate="" 设备故障率
					chntotalnum="" 通道总数
					chnfaultnum=""  通道故障数
					chnfaultrate=""通道故障率
			/>
		</region>
	</upper>
	<level title="" 名称（500kV、220kV、110kV、其他）全网统计数据
		devtotalnum="" 设备总数
		devfaultnum="" 设备故障数
		devfaultrate="" 设备故障率
		chntotalnum=""  通道总数
		chnfaultnum="" 通道故障数
		chnfaultrate="" 通道故障率
	/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryDevFaultInfo(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK区域管理
* @{
*/

/**
@brief 操作区域对象关系信息
@param [in]  handle		登陆句柄
@param [in]	 timeout		超时时间
@param [in]  info			操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			操作类型 0 增加 1 修改 2 删除
	<item 
		id="",				区域ID
		srcdomid="",		区域域ID
		areacode=""			区域代码
		title=""			区域名称
		rpudomid=""			RPU域ID
		rpucode=""			RPU代码
		domid=""			区域下对象域ID
		code=""				区域下对象代码
		type=""				区域下对象类型
		index=""			区域下对象索引
		name=""				索引名称
		fast=""				是否启用
		updatetime=""		更新时间
		<!--红外一次设备通道专属字段-->
		analysetype="" 通道分析类型 
									0:不分析, 
									1:红外测温分析, 
									2:红外对比分析, 
									3:仪表分析, 
									4:刀闸分析
	/>
</root>
@endverbatim
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptAreaWithObj(t_uint32 handle, t_int32 timeout, char *info);

/**
@brief 根据站端RPU ID查询区域对象关系信息（只支持广东网际）
@param [in]  handle		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 rpudomid		RPU域ID
@param [in]	 rpucode		RPU代码
@param [out] outxml			查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		id="",				区域ID
		srcdomid="",		区域域ID
		areacode=""			区域代码
		rpudomid=""			RPU域ID
		rpucode=""			RPU代码
		domid=""			区域下对象域ID
		code=""				区域下对象代码
		type=""				区域下对象类型
		index=""			区域下对象索引
		fast=""				是否启用
		updatetime=""		更新时间
	/>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryAreaWithObjByRpu(t_uint32 handle, t_int32 timeout, char *rpudomid, char *rpucode, char *outxml, t_uint32 maxlen);

/**
@brief 根据条件查询区域对象关系信息
@param [in]  handle		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 domid			域ID
@param [in]	 code			代码
@param [in]	 flag			查询标识 0 根据站端RPU查询（只支持广东网际） 1 根据原设备查询
@param [out] outxml			查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		id="",				区域ID
		srcdomid="",		区域域ID
		areacode=""			区域代码
		title=""			区域名称
		rpudomid=""			RPU域ID
		rpucode=""			RPU代码
		domid=""			区域下对象域ID
		code=""				区域下对象代码
		type=""				区域下对象类型
		index=""			区域下对象索引
		name=""				索引名称
		fast=""				是否启用
		updatetime=""		更新时间
	/>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryAreaWithObj(t_uint32 handle, t_int32 timeout, char *domid, char *code, t_int32 flag, char *outxml, t_uint32 maxlen);

 /**
 @brief 根据话机号码查询绑定的视频设备
 @param [in]  handle		登陆句柄
 @param [in]	 timeout		超时时间
 @param [in]  info			操作信息
 @verbatim
 <?xml version='1.0' encoding='utf-8' standalone='no' ?>
 <root>
 	<item number="123"/>
	<item number="456"/>
 </root>
 @endverbatim
 @param [out] outxml			查询信息
 @verbatim
 <?xml version='1.0' encoding='utf-8' standalone='no' ?>
 <root>
 	<item number="123" domid="" devcode="" devtype="" name="" binddomid="绑定的视频通道域ID" binddevcode="绑定的视频通道编码"/>
	<item number="456" domid="" devcode="" devtype="" name="" binddomid="" binddevcode=""/>
 </root>
 @endverbatim
 @param [in]	 maxlen		信息最大长度
 @return 
 @remarks 如果是可视话机，绑定的视频通道返回可视话机自己的通道；如果是IPC话机，绑定的视频通道返回IPC的通道。
 @see 
 */
 DLIB_API t_int32 CMU_SC_QueryPhonInfo(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 根据话机号码查询绑定的设备
@param [in]  handle		登陆句柄
@param [in]	 timeout		超时时间
@param [in]  info			操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<telephone number=""/>
	<telephone number=""/>
	......
</root>
@endverbatim
@param [out] outxml			查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<telephone number="">
		<device domid="" devcode=""/>
		<device domid="" devcode=""/>
		......
	</telephone>
	......
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryBindDeviceByNumber(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK用户角色管理
* @{
*/

/**
@brief 操作用户
@param [in]  handle			登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 info			操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>		操作类型 0 增加 1 修改 2 删除
	<user 
		userid=""		用户ID
		usertype=""		用户类型
		treeid=""		树ID
		username=""		用户名称
		creatorid=""	创建者ID
		loginname=""	登陆用户名
		loginpwd=""		登陆密码
		telephone=""	电话号码
		status=""		状态
		ip=""			IP
		updatetime=""	更新时间
		begindate=""	开始日期
		enddate=""		结束日志
		lockstatus=""	锁定状态
		orgdomid=""		组织域ID(用户必须挂到组织下)
		orgcode=""		组织代码
		medianum=""		媒体数
		email=""		电子邮件
		multi=""		可支持的最大重复登陆数
		flag=""			扩展标识 0 默认不使用 1 用于VOIP视频会议系统
		groupid=""		组号
		grouptype=""	组类型 0：逐个拨打，1：并行拨打，2：并行拨打,一个接了其它挂断
		groupmember=""  终端对应的号码，分别为LoginFrom:MultiLoginNum:PhoneNum，格式如下：1:1:65001;2:1:65002;3:1:65003;-1:1:18957130405
		imgguid=""		头像的guid, 这个guid是上传给fs返回的guid
		extradata=""	扩展信息（XML表示：<extend><pname1></pname1><pname2></pname2></extend>）
	/>
</root>
@endverbatim
@param [out] outxml			登陆句柄
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<userid></userid>		用户ID
	<treeid></treeid>		树ID
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return 
@remarks
@see CMU_SC_QueryUser
*/
DLIB_API t_int32 CMU_SC_OptUser(t_uint32 handle, t_int32 timeout, char* info, char* outxml, t_uint32 maxlen);

/**
@brief 查询本级域用户信息
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 userid		用户ID
@param [out] outxml		查询信息(详见CMU_SC_OptUser注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<user userid="" usertype="" treeid="" username="" creatorid="" loginname="" loginpwd="" telephone="" status="" ip="" updatetime="" begindate="" enddate="" lockstatus="" orgdomid="" orgcode=""  medianum="" email="" multi="" flag="" extradata="" imei=""/>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptUser
*/
DLIB_API t_int32 CMU_SC_QueryUser(t_uint32 handle, t_int32 timeout, t_int32 userid, char*outxml, t_uint32 maxlen);

/**
@brief 按域查询用户信息
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 domid		域编码
@param [in]	 userid		用户ID
@param [out] outxml		查询信息(详见CMU_SC_OptUser注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<user userid="" usertype="" treeid="" username="" creatorid="" loginname="" loginpwd="" telephone="" status="" ip="" updatetime="" begindate="" enddate="" lockstatus="" orgdomid="" orgcode=""  medianum="" email="" multi="" flag="" extradata=""	/>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptUser
*/
DLIB_API t_int32 CMU_SC_QueryDomUser(t_uint32 handle, t_int32 timeout, char *domid, t_int32 userid, char*outxml, t_uint32 maxlen);

/**
@brief 查询组织下用户
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 domid		组织域ID
@param [in]	 orgcode	组织代码
@param [out] outxml		查询信息(详见CMU_SC_OptUser注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<user userid="" usertype="" treeid="" username="" creatorid="" loginname="" loginpwd="" telephone="" status="" ip="" updatetime="" begindate="" enddate="" lockstatus="" orgdomid="" orgcode=""  medianum="" email="" multi="" flag="" extradata="" imei=""/>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptUser
*/
DLIB_API t_int32 CMU_SC_QueryUserByOrg(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode, char*outxml, t_uint32 maxlen);

/**
@brief 查询所有用户
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [out] outxml		查询信息(详见CMU_SC_OptUser注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<user domid="" userid="" usertype="" treeid="" username="" creatorid="" loginname="" loginpwd="" telephone="" status="" ip="" updatetime="" begindate="" enddate="" lockstatus="" orgdomid="" orgcode=""  medianum="" email="" multi="" flag="" extradata="" />
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptUser
*/
DLIB_API t_int32 CMU_SC_QueryAllUser(t_uint32 handle, t_int32 timeout, char*outxml, t_uint32 maxlen);

/**
@brief 操作用户视频设备关系（用于VOIP视频会议系统）
@param [in]  handle		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 info			操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			操作类型(不填，信息直接替换)
	<userid></userid>		用户ID
	<item 
		domid=""			设备域ID
		chncode=""			设备通道代码
	/>
	<item domid="" chncode="" />
</root>
@endverbatim
@return 
@remarks
@see CMU_SC_QueryUserWithVideoDev
*/
DLIB_API t_int32 CMU_SC_OptUserWithVideoDev(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief 查询用户视频设备关系（用于VOIP视频会议系统）
@param [in]  handle	登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 userid		用户ID
@param [out] outxml		查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item domid="" chncode="" chnname="" />
	<item domid="" chncode="" chnname="" />
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptUserWithVideoDev
*/
DLIB_API t_int32 CMU_SC_QueryUserWithVideoDev(t_uint32 handle, t_int32 timeout, t_int32 userid, char*outxml, t_uint32 maxlen);

/**
@brief 查询用户密码
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<ip></ip>
	<port></port>
	<username></username>
	<key1></key1>
	<key2></key2>
</root>
@endverbatim
@param [out] outxml
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<password></password>
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return 
@remarks
*/
DLIB_API t_int32 CMU_SC_QueryUserPassword(t_int32 timeout, char* info, char* outxml, t_uint32 maxlen);

/**
@brief 操作用户角色关系
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>		操作类型 0 增加 2 删除
	<userid></userid>	用户ID
	<roleid></roleid>	角色ID
	<roleid></roleid>	角色ID
</root>
@endverbatim
@return 
@remarks
@see CMU_SC_QueryUserWithRole
*/
DLIB_API t_int32 CMU_SC_OptUserWithRole(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief 查询用户角色关系
@param [in]  handle	登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 userid		用户ID
@param [out] outxml		查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<roleid></roleid>	角色ID
	<roleid></roleid>	角色ID
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptUserWithRole
*/
DLIB_API t_int32 CMU_SC_QueryUserWithRole(t_uint32 handle, t_int32 timeout, t_int32 userid, char*outxml, t_uint32 maxlen);

/**
@brief 查询当前在线用户
@param [in]  handle	登陆句柄
@param [in]	 timeout	超时时间
@param [out] outxml		查询信息
@verbatim
<root>
	<user userid="1" username="admin" loginname="admin" status="1" domid="65008">
		<device domid="65008" devcode="MCU_936805" devtype="20001" streamtype="0" sessionid="111" loginfrom="1" virtualnumber="ppppp" extension='&lt;extension deviceType="20001" extensionName="ext_936805" extensionNumber="936805" extensionPassword="dahua1187!" alternateNumber="" extensionLevel="2" interposeLevel="0" transferNumber="" callTransfer="0" dialPlan="255" DTMFMode="1" recordMode="0" chargeMode="1" advancePayment="1" callHold="1" dnd="0" limitOutIn="0" extensionType="1" /&gt;'/>
	</user>
	<user userid="2" username="rpu" loginname="rpu" status="1" domid="65008"/>
	<user userid="3" username="invisibleadmin" loginname="2de25ec97b45ea2f74bf91799bcadc80" status="1" domid="65008"/>
	<user userid="7" username="niu102" loginname="niu104" status="1" domid="65008"/>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
*/
DLIB_API t_int32 CMU_SC_QueryOnlineUser(t_uint32 handle, t_int32 timeout, char*outxml, t_uint32 maxlen);


/**
@brief 查当前在线用户的扩展接口
@param [in]  handle	登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 imxml		操作信息
@verbatim
<root>
	<user userid="1" />
	<user userid="2" />
	<user userid="3" />
	<user userid="7" />
</root>
@endverbatim
@param [out] outxml		查询信息
@verbatim
<root>
	<user userid="1" username="admin" loginname="admin" status="1" domid="65008">
		<device domid="65008" devcode="MCU_936805" devtype="20001" streamtype="0" sessionid="111" loginfrom="1" virtualnumber="ppppp" extension='&lt;extension deviceType="20001" extensionName="ext_936805" extensionNumber="936805" extensionPassword="dahua1187!" alternateNumber="" extensionLevel="2" interposeLevel="0" transferNumber="" callTransfer="0" dialPlan="255" DTMFMode="1" recordMode="0" chargeMode="1" advancePayment="1" callHold="1" dnd="0" limitOutIn="0" extensionType="1" /&gt;'/>
	</user>
	<user userid="2" username="rpu" loginname="rpu" status="1" domid="65008"/>
	<user userid="3" username="invisibleadmin" loginname="2de25ec97b45ea2f74bf91799bcadc80" status="1" domid="65008"/>
	<user userid="7" username="niu102" loginname="niu104" status="1" domid="65008"/>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks CMU_SC_QueryOnlineUser是查询所有的在线用户，
	CMU_SC_QueryOnlineUser_Ex是扩展接口，这个接口按照用户需求，查询指定的用户，相当于填空题，inxml为""表示查询所有。
*/
DLIB_API t_int32 CMU_SC_QueryOnlineUser_Ex(t_uint32 handle, t_int32 timeout, char* inxml, char* outxml, t_uint32 maxlen);



/**
@brief 查询当前在线用户的Id
@param [in]  handle	登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 imxml		操作信息
@verbatim
	预留字段，以后可能有需求，比如说查询某个组织下的在线用户。目前inxml为""
@endverbatim
@param [out] outxml		查询信息
@verbatim
<root>
	<user userid="1" />
	<user userid="2" />
	<user userid="3" />
	<user userid="7" />
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks CMU_SC_QueryOnlineUser返回在线用户以及绑定的信息，CMU_SC_QueryOnlineUser_Id仅仅返回在线用户的ID
*/
DLIB_API t_int32 CMU_SC_QueryOnlineUser_Id(t_uint32 handle, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/**
@brief 踢出在线用户
@param [in]  handle	登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<user domid="用户域编码" 
		userid="用户Id" 
		loginfrom="从哪个终端登录"
	/>
	<user domid="" userid="" session=""/>
</root>
@endverbatim
@param [out] outxml		查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root/>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
*/
DLIB_API t_int32 CMU_SC_KickOutUser(t_uint32 handle, t_int32 timeout, char* info, char*outxml, t_uint32 maxlen);

/**
@brief 将设备信息通知给多个用户
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<device domid="" devcode=""/>
	<device domid="" devcode=""/>
	<user userid=""/>
	<user userid=""/>
</root>
@endverbatim
@return 
@remarks
*/
DLIB_API t_int32 CMU_SC_NotifyDevice(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief 配置调度台绑定的用户
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<dispatcher seq="" opt="">
		<user userid="" />
		<user userid="" />
	</dispatcher>
	<dispatcher seq="" opt="">
		<user userid="" />
		<user userid="" />
	</dispatcher>
</root>
@endverbatim
@param [out] outxml		查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root/>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
*/
DLIB_API t_int32 CMU_SC_OptDispatcherUser(t_uint32 handle, t_int32 timeout, char* info, char*outxml, t_uint32 maxlen);

/**
@brief 查询调度台绑定的用户
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<dispatcher seq=""/>
	<dispatcher seq=""/>
</root>
@endverbatim
@param [out] outxml		查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<dispatcher seq="">
		<user userid="" />
		<user userid="" />
	</dispatcher>
	<dispatcher seq="">
		<user userid="" />
		<user userid="" />
	</dispatcher>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
*/
DLIB_API t_int32 CMU_SC_QueryDispatcherUser(t_uint32 handle, t_int32 timeout, char* info, char*outxml, t_uint32 maxlen);

/**
@brief 配置用户绑定的IMEI
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<userdomid></userdomid>
	<userid></userid>
	<imei>为空解绑</imei>
</root>
@endverbatim
@param [out] outxml		返回信息
@param [in]	 maxlen		信息最大长度
@return 
@remarks
*/
DLIB_API t_int32 CMU_SC_OptUserBindIMEI(t_uint32 handle, t_int32 timeout, char* info, char*outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK权限管理
* @{
*/

/**
@brief 操作角色
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			操作类型 0 增加 1 修改 2 删除
	<role 
		roleid=""		角色ID
		orgdomid=""		组织域ID
		orgcode=""		组织代码
		title=""		标签
		level=""		级别
		desc=""			描述
		endtime=""		结束时间
		updatetime=""		更新时间
	/>
</root>
@endverbatim
@param [out] outxml			登陆句柄
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<roleid></roleid>
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return 
@remarks
@see CMU_SC_QueryRole
*/
DLIB_API t_int32 CMU_SC_OptRole(t_uint32 handle, t_int32 timeout, char* info, char* outxml, t_uint32 maxlen);

/**
@brief 查询组织下角色
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 domid		组织域ID
@param [in]	 orgcode	组织代码
@param [out] outxml		查询信息(详见CMU_SC_OptRole注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<role roleid="" orgdomid="" orgcode="" title="" desc="" endtime="" updatetime="" />
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptRole
*/
DLIB_API t_int32 CMU_SC_QueryRoleByOrg(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode, char*outxml, t_uint32 maxlen);

/**
@brief 查询所有角色
@param [in]  handle		登陆句柄
@param [in]	 timeout		超时时间
@param [out] outxml			查询信息(详见CMU_SC_OptRole注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<role roleid="" orgdomid="" orgcode="" title="" desc="" endtime="" updatetime="" />
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 
@remarks
@see CMU_SC_OptRole
*/
DLIB_API t_int32 CMU_SC_QueryAllRole(t_uint32 handle, t_int32 timeout, char*outxml, t_uint32 maxlen);

/**
@brief 操作权限
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>				操作类型 0 增加(组织或设备为空即为删除)
	<roleid></roleid>			角色ID
	<right>
		<funcid></funcid>		功能权限ID
		<org 
			domid=""		域ID
			orgcode=""		组织代码
			flag=""			标识 1 全选 2 半选 3不选
		/>
		<device 
			domid=""		域ID
			devcode=""		设备代码
			flag=""			标识 1 全选 2 半选 3不选
		/>
		<subsys 
			id=""		子系统ID
		/>
	</right>
	<right>
		<funcid></funcid>		功能权限ID
		<org 
			domid=""		域ID
			orgcode=""		组织代码
			flag=""			标识 1 全选 2 半选 3不选
		/>
		<device 
			domid=""		域ID
			devcode=""		设备代码
			flag=""			标识 1 全选 2 半选 3不选
		/>
		<subsys 
			id=""		子系统ID
		/>
	</right>
</root>
@endverbatim
@return 
@remarks
@see CMU_SC_QueryRight
*/
DLIB_API t_int32 CMU_SC_OptRight(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief 查询权限
@param [in]  handle			登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 roleid			角色ID
@param [in]	 domid			域ID
@param [in]	 code			组织或设备代码
@param [in]	 srctype		查询条件标识 1 是组织 2 是设备 3是子系统
@param [in]	 dsttype		查询信息标识 1 组织下组织 2 组织下设备
@param [out] outxml			查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<roleid></roleid>				角色ID
	<org 
		funcid=""				功能权限ID
		halfsel=""				半选
		checkall=""				全选
		domid=""				域ID
		orgcode=""				组织代码
	/>
	<org 
		funcid=""				功能权限ID
		halfsel=""				半选
		checkall=""				全选
		domid=""				域ID
		orgcode=""				组织代码
	/>
	<device
		funcid=""				功能权限ID
		halfsel=""				半选
		checkall=""				全选
		domid=""				域ID
		devcode=""				设备代码	
	/>
	<device
		funcid=""				功能权限ID
		halfsel=""				半选
		checkall=""				全选
		domid=""				域ID
		devcode=""				设备代码	
	/>
	<subsys
		id="" 
		code="" 
		title="" 
		type="" 
		subtype="" 
		desc="" 
	/>
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 
@remarks
@see CMU_SC_OptRight
*/
DLIB_API t_int32 CMU_SC_QueryRight(t_uint32 handle, t_int32 timeout, t_int32 roleid, char* domid, char* code, t_int32 srctype, t_int32 dsttype, char*outxml, t_uint32 maxlen);

/**
@brief 操作角色功能权限关系
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			操作类型 0 增加 2 删除
	<roleid></roleid>		角色ID
	<func 
		funcid=""		功能权限ID
		functype=""		功能权限类型
	/>
</root>
@endverbatim
@return 
@remarks
@see CMU_SC_QueryRoleWithFunc
*/
DLIB_API t_int32 CMU_SC_OptRoleWithFunc(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief 查询角色功能权限关系
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 roleid		角色ID
@param [out] outxml		查询信息(详见CMU_SC_OptRoleWithFunc注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<func funcid="" functype="" />
	<func funcid="" functype="" />
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptRoleWithFunc
*/
DLIB_API t_int32 CMU_SC_QueryRoleWithFunc(t_uint32 handle, t_int32 timeout, t_int32 roleid, char*outxml, t_uint32 maxlen);

/**
@brief 角色下的权限复制
@param [in]  handle		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 info			操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<roleid></roleid>		角色ID
	<srcfuncid></srcfuncid>	源功能权限ID
	<dstfuncid></dstfuncid>	目的功能权限ID
	<dstfuncid></dstfuncid>	目的功能权限ID
</root>
@endverbatim
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_FuncCopyWithRole(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief 根据用户和数据权限查询功能权限
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 userid		用户ID
@param [in]	 dataright	权限类型（为0 表示查询用户下的全部）
@param [out] outxml		查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		funcid=""		功能权限ID
		title=""		标签
		type=""			功能权限类型
		parentid=""		父ID
		version=""		版本
		clienttype=""		客户端类型
		path=""			路径
		status=""		状态
		smallicon=""		小图标
		bigicon=""		大图标
		index= ""		索引
		right=""		权限类型
		level=""		模块等级
		visible=""		是否可见
		desc=""			描述
		updatetime=""		更新时间
	/>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryFuncByUser(t_uint32 handle, t_int32 timeout, t_int32 userid, t_int32 dataright, char* outxml, t_uint32 maxlen);

/**
@brief 查询全部功能权限或根据数据权限查询功能权限
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 dataright	权限类型（为0 表示查询全部）
@param [out] outxml		查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		funcid=""		功能权限ID
		title=""		标签
		type=""			功能权限类型
		parentid=""		父ID
		version=""		版本
		clienttype=""		客户端类型
		path=""			路径
		status=""		状态
		smallicon=""		小图标
		bigicon=""		大图标
		index= ""		索引
		right=""		权限类型
		level=""		模块等级
		visible=""		是否可见
		desc=""			描述
		updatetime=""		更新时间
	/>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryFunc(t_uint32 handle, t_int32 timeout, t_int32 dataright, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK服务配置管理
* @{
*/

/**
@brief 操作服务配置
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<root>
	<opt 
		operate=""			操作类型 0 增加 1 修改 2 删除
	>
		<item 
			svrid=""		服务ID
			title=""		标签
			ipinfo=""		IP和端口信息 如10.36.65.91|9800;
			flag=""			标识 0 表示不能作为master
			desc=""			描述
			fast=""			是否可用
			updatetime=""	更新时间
			status=""		状态
		/>
	</opt>
</root>
flag字段的意思：
0：只能作slave，不能作master，
1：既能作master，又能作slave，
2：只能作master，不能作slave，
3：既不能作master，又不能作slave, 
4：表示Java服务器，cmu不去连接，但是要reportMaster给所有的客户端（不包括服务），
因为客户端（比如手机）要调用Java服务器的http接口
@endverbatim
@return 
@remarks
@see CMU_SC_QueryServerCfg
*/
DLIB_API t_int32 CMU_SC_OptServerCfg(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief 查询服务配置
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [out] outxml		查询信息(详见CMU_SC_OptServerCfg注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item svrid="" title="" ipinfo="" flag="" desc="" fast="" updatetime="" status="" />
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptServerCfg
*/
DLIB_API t_int32 CMU_SC_QueryServerCfg(t_uint32 handle, t_int32 timeout, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK本地配置管理
* @{
*/

/**
@brief 操作本地配置
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			操作类型 0 增加 2 删除
	<userid></userid>		用户ID
	<item 
		title=""		配置名称
		charvalue=""		字符串类型值
		numvalue=""		数字类型值
	/>	
</root>
@endverbatim
@return 
@remarks
@see CMU_SC_QueryLocalCfg
*/
DLIB_API t_int32 CMU_SC_OptLocalCfg(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief 查询本地配置
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 userid		用户ID
@param [out] outxml		查询信息(详见CMU_SC_OptLocalCfg注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item title="" charvalue="" numvalue="" />
	<item title="" charvalue="" numvalue="" />
	<errmsg />
	<errcode />
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptLocalCfg
*/
DLIB_API t_int32 CMU_SC_QueryLocalCfg(t_uint32 handle, t_int32 timeout, t_int32 userid, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK域级联信息管理
* @{
*/

/**
@brief 操作域级联信息
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			操作类型 0 增加 2 删除
	<item 
		otherdomid=""		下级域ID
		title=""		下级域名称
		sendall=""		本级域推送是否携带下级域
		parentdomid=""		下级域挂载组织域ID
		parentorgcode=""	下级域挂载组织代码
		ip=""			下级域CMU IP
		port=""			下级域CMU 端口
		updatetime=""		更新时间
		status=""		状态
		flag=""			B接口标识
	/>	
</root>
@endverbatim
@return 
@remarks
@see CMU_SC_QueryDomInfo
*/
DLIB_API t_int32 CMU_SC_OptDomInfo(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief 查询域级联信息
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [out] outxml		查询信息(详见CMU_SC_OptDomInfo注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item otherdomid="" title="" sendall=""	parentdomid="" parentorgcode="" ip="" port="" updatetime="" status="" flag="" />
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CMU_SC_OptDomInfo
*/
DLIB_API t_int32 CMU_SC_QueryDomInfo(t_uint32 handle, t_int32 timeout, char* outxml, t_uint32 maxlen);

/**
@brief 查询域信息
@param [in]	handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<parentdomid></parentdomid>
</root>
@endverbatim
@param [out] outxml
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domain id="111" parentid="" name=""	cmuip="" cmuport="" status="" lastupdatetime="">
		<domain id="222" parentid="111" name=""	cmuip="" cmuport="" status="" lastupdatetime="">
			<domain id="333" parentid="222" name=""	cmuip="" cmuport="" status="" lastupdatetime=""/>
			<domain id="444" parentid="222" name=""	cmuip="" cmuport="" status="" lastupdatetime=""/>
		</domain>
	</domain>
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
*/
DLIB_API t_int32 CMU_SC_QueryDomain(t_uint32 handle, t_int32 timeout,  char* info, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK订阅
* @{
*/

/**
@brief 操作订阅信息
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<srcdomid><srcdomid>		源域ID
	<modulename></modulename>	订阅者模块名称 如CMU等
	<domid></domid>			域ID
	<userid></userid>		用户ID
	<enable></enable>		订阅能力 1表示订阅，2表示取消订阅
	<item 
		cmd=""			业务命令
		type=""			操作类型
	/>
</root>
@endverbatim
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptSubscribe(t_uint32 handle, t_int32 timeout, char* info);

/** @} */

/**
* @defgroup CMU_SDK日志管理
* @{
*/

/**
@brief 操作用户日志
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>		操作类型 0 增加 2 删除
	<item 
		id=""		日志ID
		userid=""	用户ID
		type=""		日志类型
		username=""	用户名
		eventtime=""	事件时间
		location=""	事件地点
		title=""	事件名称
		msgtxt=""	消息
	/>	
</root>
@endverbatim
@return 
@remarks
@see CM_QueryUserLog
*/
DLIB_API t_int32 CMU_SC_OptUserLog(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief 查询用户日志
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<title></title>				事件名称
	<userid></userid>			用户ID
	<type></type>				日志类型
	<starttime></starttime>			开始时间
	<endtime></endtime>			结束时间
	<size></size>				页大小
	<curpage></curpage>			当前页
</root>
@endverbatim
@param [out] outxml		查询信息(详见CMU_SC_OptLocalCfg注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>		总页数
	<item id="" userid="" type="" username="" eventtime="" location="" title="" msgtxt="" />
	<errmsg />
	<errcode />
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CM_OptUserLog
*/
DLIB_API t_int32 CMU_SC_QueryUserLog(t_uint32 handle, t_int32 timeout, char* info, char* outxml, t_uint32 maxlen);

/**
@brief 操作系统日志
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>				操作类型 0 增加 2 删除
	<item 
		id=""				日志ID
		modulename=""			模块名
		type=""				日志类型
		eventtime=""			事件时间
		title=""			事件名称
		msgtxt=""			消息
	/>	
</root>
@endverbatim
@return 
@remarks
@see CM_QuerySysLog
*/
DLIB_API t_int32 CMU_SC_OptSysLog(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief 查询系统日志
@param [in]  handle		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<title></title>					事件名称
	<modulename></modelname>				模块名
	<type></type>					日志类型
	<starttime></starttime>				开始时间
	<endtime></endtime>				结束时间
	<size></size>					页大小
	<curpage></curpage>				当前页
</root>
@endverbatim
@param [out] outxml		查询信息(详见CM_OptSysLog注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<item id="" modulename="" type=""  eventtime="" title="" msgtxt="" />
	<errmsg />
	<errcode />
</root>
@endverbatim
@param [in]	 maxlen		信息最大长度
@return 
@remarks
@see CM_OptSysLog
*/
DLIB_API t_int32 CMU_SC_QuerySysLog(t_uint32 handle, t_int32 timeout, char* info, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK报表统计
* @{
*/

/**
@brief 统计设备信息
@param [in]  handle			登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 domid			域ID
@param [in]	 orgcode		组织代码
@param [in]	 level			变压等级（保留，填0）			
@param [in]	 size			页大小
@param [in]	 curpage		当前页(从0开始)
@param [out] outxml			查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>			总条数
	<item 
		orgpath=""          	组织设备路径
        level=""            		变压等级
        devname=""          		设备名称
        status=""           		状态
        num=""				摄像头个数
        chnnum=""           		环境通道数
		contrator="" 承包商
		installtime="" 安装时间
		offlinetime=""     掉线时间，如果status!=1，这个字段有效
	/>
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 
@remarks
@see CM_OptSysLog
*/
DLIB_API t_int32 CMU_SC_QueryDevInfo(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode,\
									t_int32 level, t_int32 size, t_int32 curpage, char* outxml, t_uint32 maxlen);

/**
@brief 统计IPC状态信息
@param [in]  handle			登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 domid			设备域ID
@param [in]	 orgcode		组织代码
@param [in]	 level			变压等级（保留，填0）
@param [in]	 size			页大小
@param [in]	 curpage		当前页(从0开始)
@param [out] outxml			查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>			总条数
	<item 
		orgpath=""		组织设备路径
		level=""		变压等级
		devname=""		设备名称
		chnname=""		通道名称
		status=""		状态
		contrator="" 承包商
		installtime="" 安装时间
		offlinetime=""     掉线时间，如果status!=1，这个字段有效
	/>
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 
@remarks
@see CM_OptSysLog
*/
DLIB_API t_int32 CMU_SC_QueryIpcStatus(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode,\
									t_int32 level, t_int32 size, t_int32 curpage, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK监控计划
* @{
*/

/**
@brief 操作监控计划配置信息
@param [in]  handle			登陆句柄
@param [in]	 timeout			超时时间
@param [in]	 info				条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>				操作类型 0 增加 1 修改 2 删除
    <task						一次操作一个计划多个通道
		taskid=""				计划ID
		userid =""				用户ID
		taskname =""			计划名称
		wndnum =""				计划窗口数
		tasktype =""			计划类型
		time=""					计划执行时间
		parentdomid=""			父域ID
		parentcode=""			父代码
	>
        <channel				
			domid =""			域ID
			devcode =""			设备代码
			devtype=""			设备类型
			devname=""			名称
			substream=""		子码流
			timespan=""			轮询时间
			prepoint=""			预置点
			index=""			视频窗口号
		/>
		<channel domid ="" devcode ="" devtype="" devname="" substream="" timespan="" prepoint="" index="" />
 	</task>
</root>
@endverbatim
@return 
@remarks 对于默认视频，当前计划配置协议只有增加、删除两项操作，监控计划包含以上三种操作
@see 
*/
DLIB_API t_int32 CMU_SC_OptMonitorTask(t_uint32 handle, t_int32 timeout, char *info);

/**
@brief 查询监控计划信息
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	info			条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<userid/>				用户ID
	<flag/>					查询类型 0 全查 1 按条件查
	<tasktype/>				监控类型  0:默认视频 1：监控计划 
	<domid/>				父域id
	<code/>					父代码
</root>
@endverbatim
@param [out] outxml			查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<task taskid="" userid ="" taskname ="" wndnum ="" tasktype ="" time="" parentdomid="" parentcode="" >
        <channel id="0" taskid="0" domid ="" devcode ="" devtype="" devname="" substream="" 
			timespan="" prepoint="" index="" manufid="" streamtype="" parentdevtype="" lighttype="" guardtype=""/>
 		<channel/>
	</task>
	<task taskid="" userid ="" taskname ="" wndnum ="" tasktype ="" time="" parentdomid="" parentcode="" >
        <channel/>
 		<channel/>
	</task>
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryMonitorTask(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK数据库管理
* @{
*/

/**
@brief 操作数据库备份计划
@param [in]  handle			登陆句柄
@param [in]	 timeout			超时时间
@param [in]	 opttype			操作类型 0 增加 2 删除
@param [in]	 backtype			备份类型 0 基本表 1 告警表 2 日志表 3 环境量数据表
@param [in]	 backcycle			备份周期 如："1,2,3"
@param [in]	 backtime			备份时间点 如："07:59:00"
@param [in]	 backnum			备份文件个数
@return 
@remarks 
@see 
*/
DLIB_API t_int32 CMU_SC_OptDbBackUp(t_uint32 handle, t_int32 timeout, t_int32 opttype , t_int32 backtype, char* backcycle, char* backtime, t_int32 backnum);

/**
@brief 查询数据库备份计划
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	backtype		备份类型 0 基本表 1 告警表 2 日志表 3 环境量数据表
@param [out] outxml			查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<type/>					备份类型
	<cycle/>				备份周期
	<time/>					备份时间
	<num/>					备份文件个数
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryDbBackUp(t_uint32 handle, t_int32 timeout, t_int32 backtype, char *outxml, t_uint32 maxlen);

/**
@brief 操作数据库清理计划
@param [in]  handle			登陆句柄
@param [in]	 timeout			超时时间
@param [in]	 logtime			日志时间
@param [in]	 alarmtime			告警时间
@return 
@remarks 
@see 
*/
DLIB_API t_int32 CMU_SC_OptDbCleanUp(t_uint32 handle, t_int32 timeout, t_int32 logtime, t_int32 alarmtime);

/**
@brief 查询数据库清理计划
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [out] outxml			查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<logtime/>				日志时间
	<alarmtime/>			告警时间
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryDbCleanUp(t_uint32 handle, t_int32 timeout, char *outxml, t_uint32 maxlen);

/**
@brief 查询数据库可更新版本
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [out] outxml			查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<update version="" date="" desc=""/>
	<update version="" date="" desc=""/>
	<update version="" date="" desc=""/>
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryDbUpdateVersion(t_uint32 handle, t_int32 timeout, char *outxml, t_uint32 maxlen);

/**
@brief 更新数据库脚本
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	info			条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<update version=""/>
</root>
@endverbatim
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_UpdateDatabase(t_uint32 handle, t_int32 timeout, char *info);


/** @} */

/**
* @defgroup CMU_SDK地图信息
* @{
*/

/**
@brief 操作地图信息
@param [in]  handle			登陆句柄
@param [in]	 timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>				操作类型 0 增加 1 修改 2 删除
	<map 
		id=""					ID
		orgdomid=""				组织域ID
		orgcode=""				组织代码
		title=""				名称
		filename=""				文件名称
		desc=""					描述
		config=""				配置信息
	>
		<device 
			domid=""			域ID
			devcode=""			设备代码
		/>
		<device domid="" devcode=""/>
	</map>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<id></id>					ID
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks 
@see 
*/
DLIB_API t_int32 CMU_SC_OptMap(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 根据组织结构查询地图信息
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	timeout			域ID
@param [in]	timeout			组织代码
@param [out] outxml			查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<map id="" orgdomid="" orgcode="" title="" file="" des="" config="" >
		<device domid="" devcode="" devtype="" manufid="" title="" status="" streamtype="" />
		<device domid="" devcode="" devtype="" manufid="" title="" status="" streamtype="" />
	</map>
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryMapByOrg(t_uint32 handle, t_int32 timeout, char *domid, char *orgcode, char *outxml, t_uint32 maxlen);

/**
@brief 根据mapid查询地图信息
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<map id=""/>
	<map id=""/>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<map id="" orgdomid="" orgcode="" title="" filename="" des="" config="" >
        <device domid="" devcode="" devtype="" manufid="" title="" status="" streamtype="" />
        <device domid="" devcode="" devtype="" manufid="" title="" status="" streamtype="" />
    </map>
	<map id="" orgdomid="" orgcode="" title="" filename="" des="" config="" >
        <device domid="" devcode="" devtype="" manufid="" title="" status="" streamtype="" />
        <device domid="" devcode="" devtype="" manufid="" title="" status="" streamtype="" />
    </map>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryMap(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 配置GIS联系人
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<giscontact id="" contactid=" type=0:系统用户id,type=1:联系人id" longitude="" latitude=""/>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<giscontact id=""/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptGisContact(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 查询GIS联系人
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<type>查询类型,0:查询全部,1:查询指定id</type>
	<giscontact id=""/>
	<giscontact id=""/>
	<curpage></curgpage>
	<size></size>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<giscontact id="" contactid=" type="0:系统用户,1:联系人" longitude="" latitude=""/>
	<giscontact id=""/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryGisContact(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 配置GIS建筑
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<gisbuilding id="" name=""/>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<gisbuilding id=""/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptGisBuilding(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 配置GIS建筑坐标
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<gisbuilding id="" longitude="" latitude=""/>
	<gisbuilding id="" longitude="" latitude=""/>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<gisbuilding id=""/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptGisBuildingPos(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 查询GIS建筑
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<type>查询类型,0:查询全部,1:查询指定id</type>
	<gisbuilding id=""/>
	<gisbuilding id=""/>
	<curpage></curgpage>
	<size></size>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<gisbuilding id="" name="" longitude="" latitude=""/>
	<gisbuilding id=""/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryGisBuilding(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 配置GIS设备
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<gisdevice id="" domid=" devcode="" longitude="" latitude=""/>
	<gisdevice id="" domid=" devcode="" longitude="" latitude=""/>
	<gisdevice id="" domid=" devcode="" longitude="" latitude=""/>
	<gisdevice id="" domid=" devcode="" longitude="" latitude=""/>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<gisdevice id=""/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptGisDevice(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 查询GIS设备
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<type>查询类型,0:查询全部,1:查询指定id</type>
	<gisdevice id=""/>
	<gisdevice id=""/>
	<curpage></curgpage>
	<size></size>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<gisdevice id="" domid=" devcode="" name="" longitude="" latitude=""/>
	<gisdevice id=""/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryGisDevice(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 通过组织查询GIS设备
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>
    <orgcode></orgcode>
	<devtype></devtype> 为空查全部类型,多个条件用逗号分隔，如"1,2,3"
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode=""  orgpath="" title="" updatetime="" desc="" >
		<device domid="" devcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" devlinktype="" display="" updatetime="" />
	</org>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryGisDeviceByOrg(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 通过设备查询GIS通道
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>
    <devcode></devcode>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<device domid="" devcode="">
        <channel domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" chnidx="" accesory=""/>
    </device>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryGisDeviceDetail(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 配置GIS楼层
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<gisbuildingfloor id="" buildingid="" mapid="" name="" num=""/>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<gisbuildingfloor id=""/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptGisBuildingFloor(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 查询GIS楼层
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<gisbuildingfloor buildingid=""/>
	<curpage></curgpage>
	<size></size>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<gisbuildingfloor id="" buildingid="" mapid="" name="" num=""/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryGisBuildingFloor(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK在线率统计
* @{
*/
/**
@brief 获取地区级各个站的在线信息
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<region domid=""/>
	<region domid=""/>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<region domid="" orgcode="" parenttitle="" title="" status="" time="">本来应该是station节点，但是最初写错成region节点，所以就延续下来了
		<device domid="" devcode="" parenttitle="" title="" status="" ipaddr="" manufid="" model="" installtime="" contrator="">
			<channel domid="" devcode="" parenttitle="" title="" status="" />
		</device>
	</region>
	<region>
	</region>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryStationStatus(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 获取地区级在线率
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<region domid=""/>
	<region domid=""/>
	<starttime></starttime>
	<endtime></endtime>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<region domid="" title="" ip="" port="" onlinenum="" totalnum="" onlinerate="" time=""/>
	<region domid="" title="" ip="" port="" onlinenum="" totalnum="" onlinerate="" time=""/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryRegionOnlineRate(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);
/** @} */

/**
* @defgroup CMU_SDK用户通讯录管理
* @{
*/
/**
@brief 配置联系人
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt><opt> 操作类型 0 增加 1 修改 2 删除
	<contact 
		id="" 
		userid="" 
		name="" 
		sex="" 性别,0:男 1:女 2:人妖
		age=""
		desc=""
	>
		<telephone number="" desc=""/>
		<telephone number="" desc=""/>
	</contact>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<contactid></contactid>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptUserContact(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 查询用户通讯录
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<userid></userid>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<contact 
		id="" 
		userid="" 
		name="" 
		sex="" 性别,0:男 1:女 2:人妖
		age=""
		desc=""
	>
		<telephone number="" desc=""/>
		<telephone number="" desc=""/>
	</contact>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryUserContact(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 查询联系人
@param [in]	session			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<keywords> 可输入：-1（查全部），电话号码，联系人姓名拼音，联系人姓名首字母，联系人姓名</keywords>
	<curpage></curpage>
	<size></size>
</root>
@endverbatim
@param [out] outxml				返回信息（默认安装联系人姓氏首字母排序）
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<contact domid="" id="" userid="" devcode="" contactid="" name="" type="">
		<telephone number=""/>
		<telephone number=""/>
	</contact>
	<contact/>
		...
	</contact>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryAllContact(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);


/**
@brief 配置联系人分组
@param [in]	session			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0添加 1修改 2删除</opt>
	<contactgroup id="分组id，修改、删除有效"
		name="分组名称，64字节，添加、修改有效"
		userid="分组所属用户id，添加、修改有效"
	>
		<contact domid="" id="" userid="" devcode="" contactid="" type=""/>
		<contact domid="" id="" userid="" devcode="" contactid="" type=""/>
	</contactgroup>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<contactgroup id=""
		name=""
		userid=""
	>
		<contact domid="" id="" userid="" devcode="" contactid="" type=""/>
		<contact domid="" id="" userid="" devcode="" contactid="" type=""/>
	</contactgroup>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks 修改分组时，新的contact节点列表会覆盖原有记录
@see 
*/
DLIB_API t_int32 CMU_SC_OptContactGroup(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 查询联系人分组
@param [in]	session			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<userid>分组所属用户id </userid>
	<size>每页返回记录的数量</size>
	<curpage>第几页，从0开始</curpage>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<contactgroup id="分组id"
		name="分组名称"
		userid="分组所属用户id"
	>
		<contact domid="" id="" userid="" devcode="" contactid="" type=""/>
		<contact domid="" id="" userid="" devcode="" contactid="" type=""/>
	</contactgroup>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks 未分组的联系人查不到
@see 
*/
DLIB_API t_int32 CMU_SC_QueryContactGroup(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 查询联系人
@param [in]	session			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<keywords> 可输入：-1（查全部），电话号码，联系人姓名拼音，联系人姓名首字母，联系人姓名</keywords>
	<size>每页返回记录的数量</size>
	<curpage>第几页，从0开始</curpage>
</root>
@endverbatim
@param [out] outxml				返回信息（默认安装联系人姓氏首字母排序）
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<!--已分组记录-->
	<contactgroup id="分组id"
		name="分组名称"
		userid="分组所属用户id"
	>
		<contact domid="" id="" userid="" devcode="" contactid="" name="" type="">
			<telephone number=""/>
			<telephone number=""/>
		</contact>
		<contact id=""/>
	</contactgroup>
	<contactgroup id=""/>
	<ungrouped>
		<!--未分组记录-->
		<contact id=""/>
		<contact id=""/>
	</ungrouped>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryAllContactWithGroup(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK用户设备管理
* @{
*/

/**
@brief 查询用户设备
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<user id="" session="">
	<user id="" session="">
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<user id="" session="">
		<device devid="" domid="" devcode="" devtype=""/>
		<device devid="" domid="" devcode="" devtype=""/>
		...
	</user>
	...
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryUserBindDevice(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 新增/修改用户设备（覆盖语义）
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<user id="" session="">
		<device  domid="" devcode=""/>
		<device  domid="" devcode=""/>
		...
	</user>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root/>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
会用新的绑定设备列表替换老的绑定设备列表
@see 
*/
DLIB_API t_int32 CMU_SC_OptUserBindDevice(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 查询用户绑定的号码查询用户绑定的设备
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<number></number>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<user id="" handle="" name="">
		<device devid="" domid="" devcode="" devtype=""/>
		<device devid="" domid="" devcode="" devtype=""/>
		...
	</user>
	...
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryUserBindDeviceByNumber(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);


/**
@brief 操作号码绑定的摄像头和预置位
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<root>
	<number opt="" id="">
		<device domid="" chncode="" presetid="">
		<device domid="" chncode="" presetid="">
	</number>
	...
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<root>
	<number opt="" id="" name="">
		<device domid="" chncode="" chnname="" presetid="" presetname="">
		<device domid="" chncode="" chnname="" presetid="" presetname="">
	</number>
	...
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptNumBindDevicePreset(t_uint32 handle, t_int32 timeout, char *inxml, char *outxml, t_uint32 maxlen);

/**
@brief 操作号码绑定的摄像头和预置位
@param [in]	handle			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info			输入信息
@verbatim
<root>
	<number id="">
	</number>
	...
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<root>
	<number opt="" id="" name="">
		<device domid="" chncode="" chnname="" presetid="" presetname="">
		<device domid="" chncode="" chnname="" presetid="" presetname="">
	</number>
	...
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QryNumBindDevicePreset(t_uint32 handle, t_int32 timeout, char *inxml, char *outxml, t_uint32 maxlen);


/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif


