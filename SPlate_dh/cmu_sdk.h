/**
 * Copyright (c) 2014~2015, �㽭��ϵͳ�������޹�˾ All rights reserved.
 * \file		cmu_sdk.h
 * \brief		cmu_sdk
 * \author		24997
 * \date		2014��12��19��
 * \note		CMU SDK �ӿ�
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
* @defgroup CMU_SDK����
* @{
*/

/**
* @defgroup CMU_SDKϵͳ
* @{
*/

/**
@brief CMU_SDK��ʼ��
@return 
@remarks ���������SDKһ��ʹ�ã���Ҫ���ȵ��ô˽ӿ�
@see CMU_SC_Cleanup
*/
DLIB_API t_int32 CMU_SC_Init();

/**
@brief CMU_SDK��ʼ��
@return 
@remarks ���������SDKһ��ʹ�ã���Ҫ���ȵ��ô˽ӿ�
@see CMU_SC_Cleanup
*/
DLIB_API t_int32 CMU_SC_InitNoApp();

/**
@brief CMU_SDK����ʼ��
@return 
@remarks ���������SDKһ��ʹ�ã���Ҫ�����ô˽ӿ�
@see CMU_SC_Init
*/
DLIB_API t_int32 CMU_SC_Cleanup();

/**
@brief ������־�����ļ�·��
@param [in] path		�����ļ�·��
@return 
@remarks
@see
*/
DLIB_API t_int32 CMU_SC_SetLogCfgPath(char* path);

/**
@brief �ͻ��˼�¼��־
@param [in] level		��־�ȼ�
@verbatim
	0	������־
	1	��Ϣ��־
	2	�ӿ���־
	3	������־
	4	������־
	5	������־
@endverbatim
@param [in] info		��־��Ϣ
@return 
@remarks
@see
*/
DLIB_API t_int32 CMU_SC_Log(t_uint32 level, char* info);

/**
@brief �ͻ��˼�¼trace
@param [in] info		trace��Ϣ
@return 
@remarks
@see
*/
DLIB_API t_int32 CMU_SC_Trace(char* info);

/**
@brief ��־���𿪹�
@param [in] level		��־�ȼ�
@verbatim
	0	������־
	1	��Ϣ��־
	2	�ӿ���־
	3	������־
	4	������־
	5	������־
@endverbatim
@param [in] flag		����
@verbatim
0	�ر�
1	����
@endverbatim
@return 
@remarks
@see
*/
DLIB_API t_int32 CMU_SC_LogEnabled(t_uint32 level, t_int32 flag);

/**
@brief ��ѯ�ֵ��
@param [in]	 timeout		��ʱʱ��
@param [in]  ip				����IP
@param [in]  port			����˿�
@param [in]	 tabletype		�ֵ������
@verbatim
	0	������
	1	�豸����
	2	λ������
	3	�澯����
	4	��������
@endverbatim
@param [out] outxml			��ѯ��Ϣ
@verbatim
������
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		id=""			ID
		domid=""		��ID
		title=""		����
		dllname=""		DLL����
		fast=""			�Ƿ���Ч
		updatetime=""		����ʱ��
	/>
</root>
@endverbatim
@verbatim
�豸����
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		typeid=""		����ID
		typename=""		��������
		fast=""			�Ƿ���Ч
		updatetime=""		����ʱ��
	/>
</root>
@endverbatim
@verbatim
λ������
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		typeid=""		��������
		domid=""		��ID
		title=""		����
		fast=""			�Ƿ���Ч
		updatetime=""		����ʱ��
	/>
</root>
@endverbatim
@verbatim
�澯����
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		categoryid=""		Ŀ¼ID
		typeid=""		����ID
		title=""		����
		fast=""			�Ƿ���Ч
		updatetime=""		����ʱ��
	/>
</root>
@endverbatim
@verbatim
��������
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		id=""			ID
		typeid=""		����ID
		desc=""			����
		fast=""			�Ƿ���Ч
		updatetime=""		����ʱ��
	/>
</root>
@endverbatim
@param [in]	 maxlen			��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryDictTable(t_int32 timeout, char* ip, t_uint32 port, t_int32 tabletype, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK�ص�����
* @{
*/

/**
@brief CMU SDK ��Ϣ�ص���������
@param [in] handle		�û���¼���
@param [in] data		��Ϣ����
@param [in] dwBufSize		���ݳ���
@param [in] pUser		�û�����
@return 
@remarks
@see CMU_SC_SetMsg
*/
typedef t_int32 (*fIbpCmuMsgCallBack)(t_uint32 handle, char *data, t_uint32 bufSize, void* pUser);

/**
@brief ����CMU SDK �ص�����
@param [in] cb		���õĻص�����
@param [in] pUser	�û�����
@return 
@remarks �ص���Ϣʾ��
@verbatim
����master��Ϣ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="CMU" type="Request" cmd="reportMasterInfo" sequence="" session="0">
	<modulename></modulename>		ģ���� ���� DMU, VTDU
	<domid></domid>				��ID
	<ipinfo></ipinfo>			IP��Ϣ10.36.65.89|9858;
	<svrid></svrid>				����ID
	<accnum></accnum>			��������
	<adapnum></adapnum>			ת������
</root>
@endverbatim
@verbatim
�û����ߵ�
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="CMU" type="Request" cmd="logout" sequence="" session="0">
	<domid></domid>				��ID
	<userid></userid>			�û�ID
	<username></username>			�û�����
	<strdata></strdata>			�ַ�������
	<intdata></intdata>			��������
</root>
@endverbatim
@verbatim
����online��Ϣ֪ͨ
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="CMU" type="onlineNotify" cmd="onlineNotify" sequence="0" length="0">
	<server 
		servername="" 			��������
		session="" 			������
		status="" 			������״̬
	/>
</root>
@endverbatim
@verbatim
�豸��Ϣ֪ͨ��Ϣ
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
* @defgroup CMU_SDK��½�ǳ�
* @{
*/

/**
@brief �û���¼
@param [in]  timeout		��ʱʱ��
@param [in]  domainId		��ID
@param [in]  ip			����IP
@param [in]  port		����˿�
@param [in]  username		�û���
@param [in]  userpass		�û�����
@param [out] outxml		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<handle></handle>		��½�ɹ����صľ��
	<userid></userid>		���ص��û�ID
	<domid></domid>			���ص��û���ID
	<handle></handle>		���ص��û�handle
</root>
@endverbatim
@param [in]  maxlen		��Ϣ��󳤶�
@return 200 �ɹ� ���� ʧ��
@remarks
@see CMU_SC_Logout
*/
DLIB_API t_int32 CMU_SC_Login(t_int32 timeout, char* domainId, char* ip, t_uint32 port, char *username, char *userpass, char* outxml, t_uint32 maxlen);

/**
@brief �û���¼�ӿڣ������˵�¼�û����ͣ�
@param [in]  timeout		��ʱʱ��
@param [in]  info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<ip>CMU��IP��ַ</ip>
	<port>CMU�Ķ˿ڣ�һ����9800</port>
	<username>��¼�û���</username>
	<userpass>��¼�û���</userpass>
	<type>��¼���ͣ�0:����̨ 1:Web�ͻ��˵�¼ 2:�ֻ��ͻ��˵�¼ 3:PC�ͻ��˵�¼</type>
	<imei>�ֻ��ͻ��˵�¼����дimei�������ֻ��󶨹��ܣ�����д�����øù���</imei>
</root>
@endverbatim
@param [out] outxml		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<handle></handle>		��½�ɹ����صľ��
	<userid></userid>		���ص��û�ID
	<domid></domid>			���ص��û���ID
	<session></session>		���ص��û�handle
</root>
@endverbatim
@param [in]  maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_Logout
*/
DLIB_API t_int32 CMU_SC_LoginEx(t_int32 timeout, char* info, char* outxml, t_uint32 maxlen);

/**
@brief �û��Ƿ��Ѿ���¼
@param [in] handle		��½���
@return 0 δ��¼ 1 �ѵ�¼
@remarks
@see CMU_SC_Login
*/
DLIB_API t_int32 CMU_SC_IsLogin(t_uint32 handle);

/**
@brief �û��ǳ�
@param [in] handle		��½���
@return 
@remarks
@see CMU_SC_Login
*/
DLIB_API t_int32 CMU_SC_Logout(t_uint32 handle);

/**
@brief У���û�������
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [in]  username		�û���
@param [in]  userpass		�û�����
@param [out] outxml		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<val>1</val>			У���� 0 ����ͬһ�û� 1 ͬһ�û� 
</root>
@endverbatim
@param [in]  maxlen		��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_CheckUserPwd(t_uint32 handle, t_int32 timeout, char *username, char *userpass, char *outxml, t_uint32 maxlen );

/**
@brief �ӽ����û�
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [in]  domid		��ID
@param [in]  userid		�û�ID
@param [in]  flag		��ʶ 0 ���� 1 ����
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_LockUser(t_uint32 handle, t_int32 timeout, char* domid, t_int32 userid, t_int32 flag);

/**
@brief �޸�����
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [in]  domid		��id
@param [in]  userid		�û�id
@param [in]  oldpwd		������
@param [in]  newpwd		������
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_ModifyUserPwd(t_uint32 handle, t_int32 timeout, char* domid, t_int32 userid, char* oldpwd, char* newpwd);

/**
@brief �����û���½����
@param [in]  handle		��½���
@param [in]	 timeout		��ʱʱ��
@param [in]	 userid			�û�ID
@param [in]	 num			��½�ǳ�������������������ʾ��
@return 
@remarks
@see CMU_SC_QueryUserWithVideoDev
*/
DLIB_API t_int32 CMU_SC_OptUserLoad(t_uint32 handle, t_int32 timeout, t_int32 userid, t_int32 num);

/** @} */

/**
* @defgroup CMU_SDK��֯����
* @{
*/

/**
@brief ������֯
@param [in] handle		��½���
@param [in] timeout		��ʱʱ��
@param [in] info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			//�������� 0 ���� 1 �޸� 2 ɾ��
	<org 
		domid=""		��ID
		orgcode=""		��֯����
		olddomid=""		����ID(�����ֶ��޸�ʱ��Ч)
		oldorgcode=""		����֯����
		parentdomid=""		����ID
		parentorgcode=""	����֯����
		orgpath=""		��֯·��
		orgposidx=""		��֯λ������
		title=""		��ǩ
		updatetime=""		����ʱ��
		desc=""			����
		orgtype=""			��֯���ͣ������ֶΣ�1:��֯ 2:���� 3:����
	/>
</root>
@endverbatim
@return 
@remarks һ�ο��Բ��������֯�ڵ㣨���ŷ�ʽ��
@see CMU_SC_QueryOrg
*/
DLIB_API t_int32 CMU_SC_OptOrg(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief ��ѯָ����֯��ϸ��Ϣ
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [in]  domid		��֯��ID
@param [in]  orgcode		��֯����
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptOrgע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" />
</root>
@endverbatim
@param [in]  maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptOrg
*/
DLIB_API t_int32 CMU_SC_QueryOrg(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode, char*outxml, t_uint32 maxlen);

/**
@brief ��ѯ������֯
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptOrgע��)
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
@param [in]  maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptOrg
*/
DLIB_API t_int32 CMU_SC_QueryAllOrg(t_uint32 handle, t_int32 timeout, char*outxml, t_uint32 maxlen);

/**
@brief ��ѯ������֯(����Ȩ�޹���)
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<funid></funid>
</root>
@endverbatim
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptOrgע��)
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
@param [in]  maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptOrg
*/
DLIB_API t_int32 CMU_SC_QueryAllOrgEx(t_uint32 handle, t_int32 timeout, char *info, char*outxml, t_uint32 maxlen);

/**
@brief ����������ѯ������֯
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [in] info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<orgdomid></orgdomid>��:ȫ��
	<orgcode></orgcode>��:ȫ��
	<orgtype></orgtype>-1:ȫ�� 1:��֯ 2:���� 3:���ţ����������ö���(",")�ָ�
</root>
@endverbatim
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptOrgע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" orgtype=""/>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" orgtype=""/>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" orgtype=""/>
</root>
@endverbatim
@param [in]  maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptOrg
*/
DLIB_API t_int32 CMU_SC_QueryOrgEx(t_uint32 handle, t_int32 timeout, char *info, char*outxml, t_uint32 maxlen);

/**
@brief ��ѯ����֯
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [in]  domid		��ID
@param [in]  parentorgcode	����֯����(Ϊ���ַ������ظ���֯��Ϣ)
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptOrgע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" />
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" />
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" />
</root>
@endverbatim
@param [in]  maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptOrg
*/
DLIB_API t_int32 CMU_SC_QuerySubOrg(t_uint32 handle, t_int32 timeout, char* domid, char* parentorgcode, char*outxml, t_uint32 maxlen);

/**
@brief ��ѯ����֯����Ҫ�ͷŷ��ض����ڴ棩
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [in]  domid		��ID
@param [in]  parentorgcode	����֯����(Ϊ���ַ������ظ���֯��Ϣ)
@param [out] errorcode		������
@param [out]  reallen		��Ϣʵ�ʳ���
@return 
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" />
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" />
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" />
</root>
@endverbatim
@remarks ���ͷŷ��ض����ڴ棡���ͷŷ��ض����ڴ棡���ͷŷ��ض����ڴ棡
@see CMU_SC_OptOrg
*/
DLIB_API char* CMU_SC_QuerySubOrgXXXX(t_uint32 handle, t_int32 timeout, char* domid, char* parentorgcode, t_int32 *errorcode, t_uint32 *reallen);

/**
@brief �����Զ������
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0��� 1�޸� 2ɾ��</opt>
	<group id="����id���޸ġ�ɾ����Ч"
		parentid="���鸸�ڵ�ID, 0Ϊ���ڵ�"
		name="�������ƣ�64�ֽڣ���ӡ��޸���Ч"
		type="�������ͣ�ͨѶ¼����:1,����̨����:2"
		userid="���������û�ID"
	>
		<device domid="" devcode=""/>
		<user domid="" userid=""/>
		<contact domid="" contactid=""/>
	</group>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<group id=""/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptGroup(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯ�Զ������
@param [in]	session			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<!--userid��parentid��id�����ֶ�ͬʱֻ����һ�������������ֶ���-1-->
	<userid>���������û�id</userid>
	<parentid>���鸸�ڵ�id</parentid>
	<id>����id</id>
	<size>ÿҳ���ؼ�¼������</size>
	<curpage>�ڼ�ҳ����0��ʼ</curpage>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<group id="����id"
		parentid="���鸸�ڵ�ID"
		name="�������ƣ�64�ֽڣ���ӡ��޸���Ч"
		type="�������ͣ�ͨѶ¼����:1"
	>
		<group id="" parentid="" name="" type="">
			<group id="" parentid="" name="" type=""/>
		</group>
	</group>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks δ����Ĳ鲻��
@see 
*/
DLIB_API t_int32 CMU_SC_QueryGroup(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯ�Զ����������Ķ���
@param [in]	session			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<groupid></groupid>
	<size>ÿҳ���ؼ�¼������</size>
	<curpage>�ڼ�ҳ����0��ʼ</curpage>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<group id="����id"
		parentid="���鸸�ڵ�ID"
		name="�������ƣ�64�ֽڣ���ӡ��޸���Ч"
		type="�������ͣ�ͨѶ¼����:1"
	>
		<device devid="3844" domid="73807" devcode="88888channel1" devtype="31" manufid="1" title="通道1" status="2" orgdomid="73807" orgcode="1" devpath="0-3772-" orgpath="0-1-522" devlinktype="0" updatetime="2016-09-01 20:16:56"/>
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
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks δ����Ĳ鲻��
@see 
*/
DLIB_API t_int32 CMU_SC_QueryGroupObject(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯ����֯
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [in] info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<funid></funid>
	<domid></domid>
	<parentorgdomid></parentorgdomid>
	<parentorgcode></parentorgcode>
	<orgtype></orgtype>-1:ȫ�� 1:��֯ 2:���� 3:���ţ����������ö���(",")�ָ�
</root>
@endverbatim
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptOrgע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" orgtype=""/>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" orgtype=""/>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" orgpath="" orgposidx="" title="" updatetime="" desc="" orgtype=""/>
</root>
@endverbatim
@param [in]  maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptOrg
*/
DLIB_API t_int32 CMU_SC_QuerySubOrgEx(t_uint32 handle, t_int32 timeout, char *info, char*outxml, t_uint32 maxlen);

/**
@brief ���֧�ӣ�ɽ���侯��Ŀר�ã�
@param [in]	session			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0:���� 1:�޸� 2:ɾ��</opt>
	<detachment 
		id="֧�ӱ�ţ��޸�ɾ����Ч����������Ҫ��д"
		name="֧������" 
		dbip="֧�����ݿ�IP" 
		dbport="֧�����ݿ�port"
		dbuser="֧�����ݿ��û���" 
		dbpass="֧�����ݿ�����" 
		dbname="֧�����ݿ�����" 
		desc="֧��������Ϣ"
	/>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<detachment id="/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks 
@see 
*/
DLIB_API t_int32 CMU_SC_OptDetachment(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯ֧�ӣ�ɽ���侯��Ŀר�ã�
@param [in]	session			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<detachmentid>֧�ӱ�ţ�-1��ѯȫ��</detachmentid>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<detachment id="" name="" dbip="" dbuser="" dbpass="" dbname="" desc="">
		<sentinel id="���ڱ��" name="��������" number="���ں���"/>
		<sentinel id="" name="" number=""/>
	</detachment>
	<detachment id="" name="" dbip="" dbuser="" dbpass="" dbname="" desc="">
		<sentinel id="" name="" number=""/>
		<sentinel id="" name="" number=""/>
	</detachment>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks 
@see 
*/
DLIB_API t_int32 CMU_SC_QueryDetachment(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ���ø��ڶ�����Ϣ��ɽ���侯��Ŀר�ã�
@param [in]	session			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<detachmentid>֧�ӱ�ţ����ñ���</detachmentid>
	<sentinelid>���ڱ�ţ����ñ���</sentinelid>
	<number>���ں��룬û��Ϊ��</number>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root/>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks 
@see 
*/
DLIB_API t_int32 CMU_SC_OptSentinelExInfo(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯ���ڲ����Ϣ��ɽ���侯��Ŀר�ã�
@param [in]	session			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<number>���ں���</number>
	<checktime>���ʱ�䣬����Ϊ��С��λ����ʽ��yyyy-mm-dd</checktime>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<sentinel id="" name="��������" number="���ں���" dutycheck="���������"/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks 
@see 
*/
DLIB_API t_int32 CMU_SC_QuerySentinelDutyCheck(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);


/** @} */

/**
* @defgroup CMU_SDK�豸����
* @{
*/


/**
@brief �����豸
@param [in] handle		��½���
@param [in] timeout		��ʱʱ��
@param [in] info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			//�������� 0 ���� 1 �޸� 2 ɾ��
	<device 
		domid=""		��ID
		devcode=""		�豸����
		olddomid=""		����ID�������ֶ��޸�ʱ��Ч��
		olddevcode=""		���豸����
		parentdomid=""		����ID
		parentdevcode=""	���豸����
		orgdomid=""		��֯��ID
		orgcode=""		��֯����
		devpath=""		�豸·��
		orgpath=""		��֯·��
		devtype=""		�豸����
		manufid=""		����ID
		title=""		��ǩ
		status=""		״̬
		devposidx=""		�豸λ������
		devlinktype=""
		display=""			�Ƿ���ʾ
		updatetime=""		����ʱ��
		extend=""			��չ��Ϣ�������豸�ã�
		loginname=""		��½�û���
		loginpwd=""		��½����
		ipaddr=""		�豸IP
		portdev=""		�豸�˿�
		streamtype=""		��������
		contrator=""		�а���/������
		locationid=""		����
		installspot=""		��װ�ص�
		installtime=""		��װʱ��
		maintainer=""		������
		phone=""		�绰
		model=""		ģ��
		visible=""		�Ƿ�ɼ�
		longitude=""		����
		latitude=""		γ��
		desc=""			����
	>
		<channel 
			domid=""		��ID
			devcode=""		�豸����
			olddomid=""		����ID�������ֶ��޸�ʱ��Ч��
			olddevcode=""		���豸����
			parentdomid=""		����ID
			parentdevcode=""	���豸����
			orgdomid=""		��֯��ID
			orgcode=""		��֯����
			devpath=""		�豸·��
			orgpath=""		��֯·��
			devtype=""		�豸����
			manufid=""		����ID
			title=""		��ǩ
			status=""		״̬
			devposidx=""		�豸λ������
			updatetime=""		����ʱ��
			chnidx=""		ͨ������
			accesory=""		������Ϣ
		>
			<item domid="" devcode="" slavedomid="" slavedevcode="" />
			<item domid="" devcode="" slavedomid="" slavedevcode="" />
		</channel>
		//��ѡ����Ϣ
		<item domid="" devcode="" slavedomid="" slavedevcode="" />
		<item domid="" devcode="" slavedomid="" slavedevcode="" />
	</device>
	<device ...></device>	//֧�ֶ��豸���
</root>
@endverbatim
@verbatim
//����һ���豸XML��Ϣ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			//�������� 0 ���� 1 �޸� 2 ɾ��
	<device 
		domid=""			��ID
		devcode=""			�豸����
		olddomid=""			����ID�������ֶ��޸�ʱ��Ч��
		olddevcode=""		���豸����
		parentdomid=""		����ID
		parentdevcode=""	���豸����
		orgdomid=""			��֯��ID
		orgcode=""			��֯����
		devpath=""			�豸·��
		orgpath=""			��֯·��
		devtype=""			�豸����
		manufid=""			����ID
		title=""			��ǩ
		status=""			״̬
		devposidx=""		�豸λ������
		updatetime=""		����ʱ��
		devlinktype=""
		
		detecttype=""		��������
		detectpart=""		��ⲿλ
		targettype=""		һ���豸���
		typedesc=""			��������
		ratedcurrent=""		�����
		heatfeature=""		��������
		faultdesc=""		ȱ������
		sequence=""			���к�
		time=""				��������

		installspot=""		��װ�ص�
		installtime=""		��װʱ��
		maintainer=""		������
		model=""			�豸�ͺ�
		visible=""			�Ƿ�ɼ�
		desc=""				����
	>
	</device>
	<device ...></device>	//֧�ֶ��豸���
</root>
@endverbatim
@verbatim
//���ӽ������豸XML��Ϣ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			//�������� 0 ���� 1 �޸� 2 ɾ��
	<device 
		domid=""		��ID
		devcode=""		�豸����
		olddomid=""		����ID�������ֶ��޸�ʱ��Ч��
		olddevcode=""		���豸����
		parentdomid=""		����ID
		parentdevcode=""	���豸����
		orgdomid=""		��֯��ID
		orgcode=""		��֯����
		devpath=""		�豸·��
		orgpath=""		��֯·��
		devtype=""		�豸����
		manufid=""		����ID
		title=""		��ǩ
		status=""		״̬
		devposidx=""		�豸λ������
		devlinktype=""
		display=""			�Ƿ���ʾ
		updatetime=""		����ʱ��
		extend=""			��չ��Ϣ�������豸�ã�
		loginname=""		��½�û���
		loginpwd=""		��½����
		ipaddr=""		�豸IP
		portdev=""		�豸�˿�
		streamtype=""		��������
		contrator=""		�а���
		locationid=""		����
		installspot=""		��װ�ص�
		installtime=""		��װʱ��
		maintainer=""		������
		phone=""		�绰
		model=""		ģ��
		visible=""		�Ƿ�ɼ�
		longitude=""		����
		latitude=""		γ��
		desc=""			����
		
		uintseq=""				���뵥Ԫ���
		decodemode=""		����ģʽ
		streammode=""		������ģʽ
		sort=""						������
		combinestatus=""	����ǽ�ں�״̬��1��ʾ֧���ںϣ�0��ʾ��֧���ں�
	>
		<channel 
				domid=""		��ID
				devcode=""		�豸����
				olddomid=""		����ID�������ֶ��޸�ʱ��Ч��
				olddevcode=""		���豸����
				parentdomid=""		����ID
				parentdevcode=""	���豸����
				orgdomid=""		��֯��ID
				orgcode=""		��֯����
				devpath=""		�豸·��
				orgpath=""		��֯·��
				devtype=""		�豸����
				manufid=""		����ID
				title=""		��ǩ
				status=""		״̬
				devposidx=""		�豸λ������
				updatetime=""		����ʱ��
				chnidx=""		ͨ������
				accesory=""		������Ϣ
				lighttype=""		�ƹ����� 0:�޵ƹ� 1:ipc�Դ��ƹ� 2:�ƹ�������ƹ�
				guardtype=""  �Ž����� 0:���Ž� 1:��ͨ�Ž�
				uintseq=""				���뵥Ԫ���
				splitscreenmax=""	��������
			>
			</channel>
	</device>
	<device ...></device>	//֧�ֶ��豸���
</root>
@endverbatim
@verbatim
//�����Ž����������豸XML��Ϣ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			//�������� 0 ���� 1 �޸� 2 ɾ��
	<device 
		domid=""		��ID
		devcode=""		�豸����
		olddomid=""		����ID�������ֶ��޸�ʱ��Ч��
		olddevcode=""		���豸����
		parentdomid=""		����ID
		parentdevcode=""	���豸����
		orgdomid=""		��֯��ID
		orgcode=""		��֯����
		devpath=""		�豸·��
		orgpath=""		��֯·��
		devtype=""		�豸����
		manufid=""		����ID
		title=""		��ǩ
		status=""		״̬
		devposidx=""		�豸λ������
		devlinktype=""
		display=""			�Ƿ���ʾ
		updatetime=""		����ʱ��
		extend=""			��չ��Ϣ�������豸�ã�
		loginname=""		��½�û���
		loginpwd=""		��½����
		ipaddr=""		�豸IP
		portdev=""		�豸�˿�
		streamtype=""		��������
		contrator=""		�а���
		locationid=""		����
		installspot=""		��װ�ص�
		installtime=""		��װʱ��
		maintainer=""		������
		phone=""		�绰
		model=""		ģ��
		visible=""		�Ƿ�ɼ�
		longitude=""		����
		latitude=""		γ��
		desc=""			����
	>
		<channel 
				domid=""		��ID
				devcode=""		�豸����
				olddomid=""		����ID�������ֶ��޸�ʱ��Ч��
				olddevcode=""		���豸����
				parentdomid=""		����ID
				parentdevcode=""	���豸����
				orgdomid=""		��֯��ID
				orgcode=""		��֯����
				devpath=""		�豸·��
				orgpath=""		��֯·��
				devtype=""		�豸����
				manufid=""		����ID
				title=""		��ǩ
				status=""		״̬
				devposidx=""		�豸λ������
				updatetime=""		����ʱ��
				chnidx=""		ͨ������
				accesory=""		������Ϣ

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
	<device ...></device>	//֧�ֶ��豸���
</root>
@endverbatim
@return 
@remarks
@see CMU_SC_QueryDevice CMU_SC_QueryDevDetail CMU_SC_QueryDevByChn
*/
DLIB_API t_int32 CMU_SC_OptDevice(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief ͨ����֯��ѯ�豸��Ҫ��Ϣ
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [in]  domid		��֯��ID
@param [in]  orgcode		��֯����
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptDeviceע��)
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
			//��ѡ����Ϣ
			<item domid="" devcode="" slavedomid="" slavedevcode="" />
			<item domid="" devcode="" slavedomid="" slavedevcode="" />
		</device>
	</org>
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDevice(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode, char*outxml, t_uint32 maxlen);

/**
@brief ͨ����֯��ѯ�豸��Ϣ(�����豸����)
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [in]  domid			��֯��ID
@param [in]  orgcode		��֯����
@param [in]  devtype		�豸����(""ȫ��, ��������ö��ŷָ�����"1,2,3")
@param [out] outxml			��ѯ��Ϣ(���CMU_SC_OptDeviceע��)
@verbatim
//��������豸���;���������Ϣ����Ҫ��Ϣ���£�
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode=""  orgpath="" title="" updatetime="" desc="" >
		<device domid="" devcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" devlinktype="" display="" updatetime="" />
	</org>
</root>
//һ���豸
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode=""  orgpath="" title="" updatetime="" desc="" >
		<device domid="" devcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" devlinktype="" detecttype="" detectpart="" targettype="" typedesc="" ratedcurrent="" heatfeature="" faultdesc="" sequence="" time="" installspot="" installtime="" maintainer="" model="" visible="" desc="" />
		<device domid="" devcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" devlinktype="" detecttype="" detectpart="" targettype="" typedesc="" ratedcurrent="" heatfeature="" faultdesc="" sequence="" time="" installspot="" installtime="" maintainer="" model="" visible="" desc="" />
	</org>
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDeviceEx(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode, char *devtype, char*outxml, t_uint32 maxlen);

/**
@brief ͨ����֯�͹���Ȩ�޲�ѯ�豸��Ҫ��Ϣ
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [in]  domid		��֯��ID
@param [in]  orgcode		��֯����
@param [in]  funcid			����Ȩ��ID
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptDeviceע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode=""  orgpath="" title="" updatetime="" desc="" >
		<device domid="" devcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" />
	</org>
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDeviceByFuncId(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode, t_int32 funcid, char*outxml, t_uint32 maxlen);

/**
@brief ͨ����֯�͹���Ȩ�޲�ѯ�豸��Ҫ��Ϣ(�����豸����)
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [in]  domid		��֯��ID
@param [in]  orgcode		��֯����
@param [in]  devtype		�豸����(""ȫ��, ��������ö��ŷָ�����"1,2,3")
@param [in]  funcid			����Ȩ��ID
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptDeviceע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode=""  orgpath="" title="" updatetime="" desc="" >
		<device domid="" devcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" />
	</org>
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDeviceByFuncIdEx(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode, char* devtype, t_int32 funcid, char*outxml, t_uint32 maxlen);

/**
@brief �����豸��ѯ�豸��ϸ��Ϣ
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 domid		�豸��ID
@param [in]	 devcode	�豸����
@param [in]	 devtype	�豸����(δ֪������0)
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptDeviceע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<device domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" display="" devlinktype="" updatetime="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" >
		<channel domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" chnidx="" accesory="" lighttype="" guardtype="">
			//��ѡ����Ϣ
			<item domid="" devcode="" slavedomid="" slavedevcode="" />
			<item domid="" devcode="" slavedomid="" slavedevcode="" />
		</channel>
		//��ѡ����Ϣ
		<item domid="" devcode="" slavedomid="" slavedevcode="" />
		<item domid="" devcode="" slavedomid="" slavedevcode="" />
	</device>
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDevDetail(t_uint32 handle, t_int32 timeout, char* domid, char* devcode, t_int32 devtype, char*outxml, t_uint32 maxlen);

/**
@brief �����豸�͹���Ȩ�޲�ѯ�豸��ϸ��Ϣ
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 domid		�豸��ID
@param [in]	 devcode	�豸����
@param [in]	 devtype	�豸����(δ֪������0)
@param [in]  funcid			����Ȩ��ID
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptDeviceע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<device domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" >
		<channel domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" chnidx="" accesory="" />
	</device>
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDevDetailByFuncId(t_uint32 handle, t_int32 timeout, char* domid, char* devcode, t_int32 devtype, t_int32 funcid, char* outxml, t_uint32 maxlen);

/**
@brief ����ͨ����ѯ�豸��ϸ��Ϣ
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 domid		ͨ����ID
@param [in]	 chncode	ͨ������
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptDeviceע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<device domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" >
		<channel domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" chnidx="" accesory="" />
	</device>
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDevByChn(t_uint32 handle, t_int32 timeout, char* domid, char* chncode, char* outxml, t_uint32 maxlen);

/**
@brief ͨ����֯��ѯ�豸�б���ϸ��Ϣ(��ҳ)
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [in]  domid			��֯��ID
@param [in]  code			��֯����
@param [in]	 size			ҳ��С
@param [in]	 curpage		��ǰҳ(��0��ʼ)
@param [out] outxml			��ѯ��Ϣ(���CMU_SC_OptDeviceע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>			������
	<item domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" extend="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" orgname="" />
	<item domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" extend="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" orgname="" />
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDevDetailByCode(t_uint32 handle, t_int32 timeout, char* domid, char* code, t_int32 size, t_int32 curpage, char* outxml, t_uint32 maxlen);

/**
@brief ͨ����֯���豸���Ͳ�ѯ�豸�б���ϸ��Ϣ(��ҳ)
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [in]  domid			��֯��ID
@param [in]  code			��֯����
@param [in]  devtype		�豸����(""ȫ��, ��������ö��ŷָ�����"1,2,3")
@param [in]	 size			ҳ��С
@param [in]	 curpage		��ǰҳ(��0��ʼ)
@param [out] outxml			��ѯ��Ϣ(���CMU_SC_OptDeviceע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>			������
	<item domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" extend="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" orgname="" />
	<item domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" extend="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" orgname="" />
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDevDetailByCodeEx(t_uint32 handle, t_int32 timeout, char* domid, char* code, char *devtype, t_int32 size, t_int32 curpage, char* outxml, t_uint32 maxlen);

/**
@brief ����������ѯ�豸��Ҫ����ϸ����Ϣ
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [in]  domid			��֯��ID��""ȫ����
@param [in]  code			��֯���루""ȫ����
@param [in]	 devname		�豸���ƣ�""ȫ����
@param [in]	 devtype		�豸����(0ȫ��)
@param [in]	 manuftype		��������(-1ȫ��)
@param [in]	 status			����״̬(0ȫ�� 1 ���� 2 ������)
@param [in]	 size			ҳ��С
@param [in]	 curpage		��ǰҳ(��0��ʼ)
@param [out] outxml			��ѯ��Ϣ(���CMU_SC_OptDeviceע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>			������
	<item domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" extend="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" orgname="" />
	<item domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" extend="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" orgname="" />
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDevBrief(t_uint32 handle, t_int32 timeout, char* domid, char* code, char *devname, t_int32 devtype, t_int32 manuftype, t_int32 status, t_int32 size, t_int32 curpage, char* outxml, t_uint32 maxlen);

/**
@brief ����������ѯ�豸��Ҫ����ϸ����Ϣ
@param [in]  handle		��½���
@param [in]  timeout		��ʱʱ��
@param [in]  info			������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid />				��֯��ID��""ȫ����
	<code />				��֯���루""ȫ����
	<devname />				�豸���ƣ�""ȫ����
	<devtype />				�豸����(""ȫ��, ��������ö��ŷָ�����"1,2,3")
	<manuftype />			��������(-1ȫ��)
	<status />				����״̬(0ȫ�� 1 ���� 2 ������)
	<size />				ҳ��С
	<curpage />				��ǰҳ(��0��ʼ)
</root>
@endverbatim		
@param [out] outxml			��ѯ��Ϣ(���CMU_SC_OptDeviceע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>			������
	<item domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" extend="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" orgname="" />
	<item domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" extend="" loginname="" loginpwd="" ipaddr="" portdev="" streamtype="" contrator="" locationid="" installspot="" installtime="" maintainer="" phone="" model="" visible="" longitude="" latitude="" desc="" orgname="" />
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptDevice
*/
DLIB_API t_int32 CMU_SC_QueryDevBriefEx(t_uint32 handle, t_int32 timeout, char *info, char* outxml, t_uint32 maxlen);

/**
@brief �����豸�󶨹�ϵ
@param [in]  handle			��½���
@param [in]	 timeout		��ʱʱ��
@param [in]  info			������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<relation 
		devcode="" �����豸code
		domid="" �����豸��id
		bind="" 0:��� 1:�� (����ʱ�����relation����û��device�ڵ㣬�ͽ��ȫ��)
	>
		<device 
			devcode="" 
			domid="" 
			preposindex="Ԥ��λ���preset postion index"/>�󶨵��豸
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
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptDevRelation(t_uint32 handle, t_int32 timeout, char *info, char* outxml, t_uint32 maxlen);

/**
@brief ��ѯ�豸�󶨹�ϵ
@param [in]  handle			��½���
@param [in]	 timeout		��ʱʱ��
@param [in]  info			������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<relation 
		devcode="" ����ѯ�豸code
		domid="" ����ѯ�豸��id
	/>
</root>
@endverbatim		
@param [out] outxml	
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<relation 
		devcode="" ����ѯ�豸code
		domid="" ����ѯ����id
	>
		<device 
			devcode="" 
			domid=""
			preposindex="Ԥ��λ���preset postion index"
		/> �󶨵��豸
		<device devcode="" domid=""/>
	</relation>
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryDevRelation(t_uint32 handle, t_int32 timeout, char *info, char* outxml, t_uint32 maxlen);

/**
@brief �����¼����豸��֯�ṹ
@param [in]  handle			��½���
@param [in]	 timeout		��ʱʱ��
@param [in]  info			������Ϣ
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
@brief ��ѯ��֯���豸���������ǵ���֯�ṹ
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<title></title>
	<curpage></curpage>
	<size></size>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<org domid="" orgcode="" title=""> ���ڵ�
		<org domid="" orgcode="" title="">
			<org domid="" orgcode="" title=""/>Ҫ���ҵĽڵ�
		</org>
	</org>
	<org domid="" orgcode="" title="">���ڵ�
		<org domid="" orgcode="" title="">
			<device domid="" devcode="" title=""/>Ҫ���ҵĽڵ�
		</org>
	</org>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryOrgDevByTitle(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯ�豸������Ϣ
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ����ʱΪ�գ�
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<upper title="" ʡ������
			devtotalnum="" �豸����
			devfaultnum="" �豸������
			devfaultrate="" �豸������
			chntotalnum=""  ͨ������
			chnfaultnum="" ͨ��������
			chnfaultrate="" ͨ��������
	>
		<level title="" ���ƣ�500kV��220kV��110kV��������ʡ��ͳ������
			devtotalnum="" �豸����
			devfaultnum="" �豸������
			devfaultrate="" �豸������
			chntotalnum=""  ͨ������
			chnfaultnum="" ͨ��������
			chnfaultrate="" ͨ��������
		/>
		<region title="" ����������
				devtotalnum="" �豸����
				devfaultnum="" �豸������
				devfaultrate="" �豸������
				chntotalnum="" ͨ������
				chnfaultnum=""  ͨ��������
				chnfaultrate=""ͨ��������
		>
			<center title="" Ѳά��������
					devtotalnum="" �豸����
					devfaultnum="" �豸������
					devfaultrate="" �豸������
					chntotalnum="" ͨ������
					chnfaultnum=""  ͨ��������
					chnfaultrate=""ͨ��������
			/>
		</region>
	</upper>
	<level title="" ���ƣ�500kV��220kV��110kV��������ȫ��ͳ������
		devtotalnum="" �豸����
		devfaultnum="" �豸������
		devfaultrate="" �豸������
		chntotalnum=""  ͨ������
		chnfaultnum="" ͨ��������
		chnfaultrate="" ͨ��������
	/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryDevFaultInfo(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK�������
* @{
*/

/**
@brief ������������ϵ��Ϣ
@param [in]  handle		��½���
@param [in]	 timeout		��ʱʱ��
@param [in]  info			������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			�������� 0 ���� 1 �޸� 2 ɾ��
	<item 
		id="",				����ID
		srcdomid="",		������ID
		areacode=""			�������
		title=""			��������
		rpudomid=""			RPU��ID
		rpucode=""			RPU����
		domid=""			�����¶�����ID
		code=""				�����¶������
		type=""				�����¶�������
		index=""			�����¶�������
		name=""				��������
		fast=""				�Ƿ�����
		updatetime=""		����ʱ��
		<!--����һ���豸ͨ��ר���ֶ�-->
		analysetype="" ͨ���������� 
									0:������, 
									1:������·���, 
									2:����Աȷ���, 
									3:�Ǳ����, 
									4:��բ����
	/>
</root>
@endverbatim
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptAreaWithObj(t_uint32 handle, t_int32 timeout, char *info);

/**
@brief ����վ��RPU ID��ѯ��������ϵ��Ϣ��ֻ֧�ֹ㶫���ʣ�
@param [in]  handle		��½���
@param [in]	 timeout		��ʱʱ��
@param [in]	 rpudomid		RPU��ID
@param [in]	 rpucode		RPU����
@param [out] outxml			��ѯ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		id="",				����ID
		srcdomid="",		������ID
		areacode=""			�������
		rpudomid=""			RPU��ID
		rpucode=""			RPU����
		domid=""			�����¶�����ID
		code=""				�����¶������
		type=""				�����¶�������
		index=""			�����¶�������
		fast=""				�Ƿ�����
		updatetime=""		����ʱ��
	/>
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryAreaWithObjByRpu(t_uint32 handle, t_int32 timeout, char *rpudomid, char *rpucode, char *outxml, t_uint32 maxlen);

/**
@brief ����������ѯ��������ϵ��Ϣ
@param [in]  handle		��½���
@param [in]	 timeout		��ʱʱ��
@param [in]	 domid			��ID
@param [in]	 code			����
@param [in]	 flag			��ѯ��ʶ 0 ����վ��RPU��ѯ��ֻ֧�ֹ㶫���ʣ� 1 ����ԭ�豸��ѯ
@param [out] outxml			��ѯ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		id="",				����ID
		srcdomid="",		������ID
		areacode=""			�������
		title=""			��������
		rpudomid=""			RPU��ID
		rpucode=""			RPU����
		domid=""			�����¶�����ID
		code=""				�����¶������
		type=""				�����¶�������
		index=""			�����¶�������
		name=""				��������
		fast=""				�Ƿ�����
		updatetime=""		����ʱ��
	/>
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryAreaWithObj(t_uint32 handle, t_int32 timeout, char *domid, char *code, t_int32 flag, char *outxml, t_uint32 maxlen);

 /**
 @brief ���ݻ��������ѯ�󶨵���Ƶ�豸
 @param [in]  handle		��½���
 @param [in]	 timeout		��ʱʱ��
 @param [in]  info			������Ϣ
 @verbatim
 <?xml version='1.0' encoding='utf-8' standalone='no' ?>
 <root>
 	<item number="123"/>
	<item number="456"/>
 </root>
 @endverbatim
 @param [out] outxml			��ѯ��Ϣ
 @verbatim
 <?xml version='1.0' encoding='utf-8' standalone='no' ?>
 <root>
 	<item number="123" domid="" devcode="" devtype="" name="" binddomid="�󶨵���Ƶͨ����ID" binddevcode="�󶨵���Ƶͨ������"/>
	<item number="456" domid="" devcode="" devtype="" name="" binddomid="" binddevcode=""/>
 </root>
 @endverbatim
 @param [in]	 maxlen		��Ϣ��󳤶�
 @return 
 @remarks ����ǿ��ӻ������󶨵���Ƶͨ�����ؿ��ӻ����Լ���ͨ���������IPC�������󶨵���Ƶͨ������IPC��ͨ����
 @see 
 */
 DLIB_API t_int32 CMU_SC_QueryPhonInfo(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ���ݻ��������ѯ�󶨵��豸
@param [in]  handle		��½���
@param [in]	 timeout		��ʱʱ��
@param [in]  info			������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<telephone number=""/>
	<telephone number=""/>
	......
</root>
@endverbatim
@param [out] outxml			��ѯ��Ϣ
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
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryBindDeviceByNumber(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK�û���ɫ����
* @{
*/

/**
@brief �����û�
@param [in]  handle			��½���
@param [in]	 timeout		��ʱʱ��
@param [in]	 info			������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>		�������� 0 ���� 1 �޸� 2 ɾ��
	<user 
		userid=""		�û�ID
		usertype=""		�û�����
		treeid=""		��ID
		username=""		�û�����
		creatorid=""	������ID
		loginname=""	��½�û���
		loginpwd=""		��½����
		telephone=""	�绰����
		status=""		״̬
		ip=""			IP
		updatetime=""	����ʱ��
		begindate=""	��ʼ����
		enddate=""		������־
		lockstatus=""	����״̬
		orgdomid=""		��֯��ID(�û�����ҵ���֯��)
		orgcode=""		��֯����
		medianum=""		ý����
		email=""		�����ʼ�
		multi=""		��֧�ֵ�����ظ���½��
		flag=""			��չ��ʶ 0 Ĭ�ϲ�ʹ�� 1 ����VOIP��Ƶ����ϵͳ
		groupid=""		���
		grouptype=""	������ 0���������1�����в���2�����в���,һ�����������Ҷ�
		groupmember=""  �ն˶�Ӧ�ĺ��룬�ֱ�ΪLoginFrom:MultiLoginNum:PhoneNum����ʽ���£�1:1:65001;2:1:65002;3:1:65003;-1:1:18957130405
		imgguid=""		ͷ���guid, ���guid���ϴ���fs���ص�guid
		extradata=""	��չ��Ϣ��XML��ʾ��<extend><pname1></pname1><pname2></pname2></extend>��
	/>
</root>
@endverbatim
@param [out] outxml			��½���
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<userid></userid>		�û�ID
	<treeid></treeid>		��ID
</root>
@endverbatim
@param [in]  maxlen			��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_QueryUser
*/
DLIB_API t_int32 CMU_SC_OptUser(t_uint32 handle, t_int32 timeout, char* info, char* outxml, t_uint32 maxlen);

/**
@brief ��ѯ�������û���Ϣ
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 userid		�û�ID
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptUserע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<user userid="" usertype="" treeid="" username="" creatorid="" loginname="" loginpwd="" telephone="" status="" ip="" updatetime="" begindate="" enddate="" lockstatus="" orgdomid="" orgcode=""  medianum="" email="" multi="" flag="" extradata="" imei=""/>
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptUser
*/
DLIB_API t_int32 CMU_SC_QueryUser(t_uint32 handle, t_int32 timeout, t_int32 userid, char*outxml, t_uint32 maxlen);

/**
@brief �����ѯ�û���Ϣ
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 domid		�����
@param [in]	 userid		�û�ID
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptUserע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<user userid="" usertype="" treeid="" username="" creatorid="" loginname="" loginpwd="" telephone="" status="" ip="" updatetime="" begindate="" enddate="" lockstatus="" orgdomid="" orgcode=""  medianum="" email="" multi="" flag="" extradata=""	/>
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptUser
*/
DLIB_API t_int32 CMU_SC_QueryDomUser(t_uint32 handle, t_int32 timeout, char *domid, t_int32 userid, char*outxml, t_uint32 maxlen);

/**
@brief ��ѯ��֯���û�
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 domid		��֯��ID
@param [in]	 orgcode	��֯����
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptUserע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<user userid="" usertype="" treeid="" username="" creatorid="" loginname="" loginpwd="" telephone="" status="" ip="" updatetime="" begindate="" enddate="" lockstatus="" orgdomid="" orgcode=""  medianum="" email="" multi="" flag="" extradata="" imei=""/>
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptUser
*/
DLIB_API t_int32 CMU_SC_QueryUserByOrg(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode, char*outxml, t_uint32 maxlen);

/**
@brief ��ѯ�����û�
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptUserע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<user domid="" userid="" usertype="" treeid="" username="" creatorid="" loginname="" loginpwd="" telephone="" status="" ip="" updatetime="" begindate="" enddate="" lockstatus="" orgdomid="" orgcode=""  medianum="" email="" multi="" flag="" extradata="" />
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptUser
*/
DLIB_API t_int32 CMU_SC_QueryAllUser(t_uint32 handle, t_int32 timeout, char*outxml, t_uint32 maxlen);

/**
@brief �����û���Ƶ�豸��ϵ������VOIP��Ƶ����ϵͳ��
@param [in]  handle		��½���
@param [in]	 timeout		��ʱʱ��
@param [in]	 info			������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			��������(�����Ϣֱ���滻)
	<userid></userid>		�û�ID
	<item 
		domid=""			�豸��ID
		chncode=""			�豸ͨ������
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
@brief ��ѯ�û���Ƶ�豸��ϵ������VOIP��Ƶ����ϵͳ��
@param [in]  handle	��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 userid		�û�ID
@param [out] outxml		��ѯ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item domid="" chncode="" chnname="" />
	<item domid="" chncode="" chnname="" />
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptUserWithVideoDev
*/
DLIB_API t_int32 CMU_SC_QueryUserWithVideoDev(t_uint32 handle, t_int32 timeout, t_int32 userid, char*outxml, t_uint32 maxlen);

/**
@brief ��ѯ�û�����
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
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
@param [in]  maxlen			��Ϣ��󳤶�
@return 
@remarks
*/
DLIB_API t_int32 CMU_SC_QueryUserPassword(t_int32 timeout, char* info, char* outxml, t_uint32 maxlen);

/**
@brief �����û���ɫ��ϵ
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>		�������� 0 ���� 2 ɾ��
	<userid></userid>	�û�ID
	<roleid></roleid>	��ɫID
	<roleid></roleid>	��ɫID
</root>
@endverbatim
@return 
@remarks
@see CMU_SC_QueryUserWithRole
*/
DLIB_API t_int32 CMU_SC_OptUserWithRole(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief ��ѯ�û���ɫ��ϵ
@param [in]  handle	��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 userid		�û�ID
@param [out] outxml		��ѯ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<roleid></roleid>	��ɫID
	<roleid></roleid>	��ɫID
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptUserWithRole
*/
DLIB_API t_int32 CMU_SC_QueryUserWithRole(t_uint32 handle, t_int32 timeout, t_int32 userid, char*outxml, t_uint32 maxlen);

/**
@brief ��ѯ��ǰ�����û�
@param [in]  handle	��½���
@param [in]	 timeout	��ʱʱ��
@param [out] outxml		��ѯ��Ϣ
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
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
*/
DLIB_API t_int32 CMU_SC_QueryOnlineUser(t_uint32 handle, t_int32 timeout, char*outxml, t_uint32 maxlen);


/**
@brief �鵱ǰ�����û�����չ�ӿ�
@param [in]  handle	��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 imxml		������Ϣ
@verbatim
<root>
	<user userid="1" />
	<user userid="2" />
	<user userid="3" />
	<user userid="7" />
</root>
@endverbatim
@param [out] outxml		��ѯ��Ϣ
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
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks CMU_SC_QueryOnlineUser�ǲ�ѯ���е������û���
	CMU_SC_QueryOnlineUser_Ex����չ�ӿڣ�����ӿڰ����û����󣬲�ѯָ�����û����൱������⣬inxmlΪ""��ʾ��ѯ���С�
*/
DLIB_API t_int32 CMU_SC_QueryOnlineUser_Ex(t_uint32 handle, t_int32 timeout, char* inxml, char* outxml, t_uint32 maxlen);



/**
@brief ��ѯ��ǰ�����û���Id
@param [in]  handle	��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 imxml		������Ϣ
@verbatim
	Ԥ���ֶΣ��Ժ���������󣬱���˵��ѯĳ����֯�µ������û���ĿǰinxmlΪ""
@endverbatim
@param [out] outxml		��ѯ��Ϣ
@verbatim
<root>
	<user userid="1" />
	<user userid="2" />
	<user userid="3" />
	<user userid="7" />
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks CMU_SC_QueryOnlineUser���������û��Լ��󶨵���Ϣ��CMU_SC_QueryOnlineUser_Id�������������û���ID
*/
DLIB_API t_int32 CMU_SC_QueryOnlineUser_Id(t_uint32 handle, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/**
@brief �߳������û�
@param [in]  handle	��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<user domid="�û������" 
		userid="�û�Id" 
		loginfrom="���ĸ��ն˵�¼"
	/>
	<user domid="" userid="" session=""/>
</root>
@endverbatim
@param [out] outxml		��ѯ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root/>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
*/
DLIB_API t_int32 CMU_SC_KickOutUser(t_uint32 handle, t_int32 timeout, char* info, char*outxml, t_uint32 maxlen);

/**
@brief ���豸��Ϣ֪ͨ������û�
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
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
@brief ���õ���̨�󶨵��û�
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
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
@param [out] outxml		��ѯ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root/>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
*/
DLIB_API t_int32 CMU_SC_OptDispatcherUser(t_uint32 handle, t_int32 timeout, char* info, char*outxml, t_uint32 maxlen);

/**
@brief ��ѯ����̨�󶨵��û�
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<dispatcher seq=""/>
	<dispatcher seq=""/>
</root>
@endverbatim
@param [out] outxml		��ѯ��Ϣ
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
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
*/
DLIB_API t_int32 CMU_SC_QueryDispatcherUser(t_uint32 handle, t_int32 timeout, char* info, char*outxml, t_uint32 maxlen);

/**
@brief �����û��󶨵�IMEI
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<userdomid></userdomid>
	<userid></userid>
	<imei>Ϊ�ս��</imei>
</root>
@endverbatim
@param [out] outxml		������Ϣ
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
*/
DLIB_API t_int32 CMU_SC_OptUserBindIMEI(t_uint32 handle, t_int32 timeout, char* info, char*outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDKȨ�޹���
* @{
*/

/**
@brief ������ɫ
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			�������� 0 ���� 1 �޸� 2 ɾ��
	<role 
		roleid=""		��ɫID
		orgdomid=""		��֯��ID
		orgcode=""		��֯����
		title=""		��ǩ
		level=""		����
		desc=""			����
		endtime=""		����ʱ��
		updatetime=""		����ʱ��
	/>
</root>
@endverbatim
@param [out] outxml			��½���
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<roleid></roleid>
</root>
@endverbatim
@param [in]  maxlen			��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_QueryRole
*/
DLIB_API t_int32 CMU_SC_OptRole(t_uint32 handle, t_int32 timeout, char* info, char* outxml, t_uint32 maxlen);

/**
@brief ��ѯ��֯�½�ɫ
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 domid		��֯��ID
@param [in]	 orgcode	��֯����
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptRoleע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<role roleid="" orgdomid="" orgcode="" title="" desc="" endtime="" updatetime="" />
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptRole
*/
DLIB_API t_int32 CMU_SC_QueryRoleByOrg(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode, char*outxml, t_uint32 maxlen);

/**
@brief ��ѯ���н�ɫ
@param [in]  handle		��½���
@param [in]	 timeout		��ʱʱ��
@param [out] outxml			��ѯ��Ϣ(���CMU_SC_OptRoleע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<role roleid="" orgdomid="" orgcode="" title="" desc="" endtime="" updatetime="" />
</root>
@endverbatim
@param [in]	 maxlen			��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptRole
*/
DLIB_API t_int32 CMU_SC_QueryAllRole(t_uint32 handle, t_int32 timeout, char*outxml, t_uint32 maxlen);

/**
@brief ����Ȩ��
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>				�������� 0 ����(��֯���豸Ϊ�ռ�Ϊɾ��)
	<roleid></roleid>			��ɫID
	<right>
		<funcid></funcid>		����Ȩ��ID
		<org 
			domid=""		��ID
			orgcode=""		��֯����
			flag=""			��ʶ 1 ȫѡ 2 ��ѡ 3��ѡ
		/>
		<device 
			domid=""		��ID
			devcode=""		�豸����
			flag=""			��ʶ 1 ȫѡ 2 ��ѡ 3��ѡ
		/>
		<subsys 
			id=""		��ϵͳID
		/>
	</right>
	<right>
		<funcid></funcid>		����Ȩ��ID
		<org 
			domid=""		��ID
			orgcode=""		��֯����
			flag=""			��ʶ 1 ȫѡ 2 ��ѡ 3��ѡ
		/>
		<device 
			domid=""		��ID
			devcode=""		�豸����
			flag=""			��ʶ 1 ȫѡ 2 ��ѡ 3��ѡ
		/>
		<subsys 
			id=""		��ϵͳID
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
@brief ��ѯȨ��
@param [in]  handle			��½���
@param [in]	 timeout		��ʱʱ��
@param [in]	 roleid			��ɫID
@param [in]	 domid			��ID
@param [in]	 code			��֯���豸����
@param [in]	 srctype		��ѯ������ʶ 1 ����֯ 2 ���豸 3����ϵͳ
@param [in]	 dsttype		��ѯ��Ϣ��ʶ 1 ��֯����֯ 2 ��֯���豸
@param [out] outxml			��ѯ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<roleid></roleid>				��ɫID
	<org 
		funcid=""				����Ȩ��ID
		halfsel=""				��ѡ
		checkall=""				ȫѡ
		domid=""				��ID
		orgcode=""				��֯����
	/>
	<org 
		funcid=""				����Ȩ��ID
		halfsel=""				��ѡ
		checkall=""				ȫѡ
		domid=""				��ID
		orgcode=""				��֯����
	/>
	<device
		funcid=""				����Ȩ��ID
		halfsel=""				��ѡ
		checkall=""				ȫѡ
		domid=""				��ID
		devcode=""				�豸����	
	/>
	<device
		funcid=""				����Ȩ��ID
		halfsel=""				��ѡ
		checkall=""				ȫѡ
		domid=""				��ID
		devcode=""				�豸����	
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
@param [in]	 maxlen			��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptRight
*/
DLIB_API t_int32 CMU_SC_QueryRight(t_uint32 handle, t_int32 timeout, t_int32 roleid, char* domid, char* code, t_int32 srctype, t_int32 dsttype, char*outxml, t_uint32 maxlen);

/**
@brief ������ɫ����Ȩ�޹�ϵ
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			�������� 0 ���� 2 ɾ��
	<roleid></roleid>		��ɫID
	<func 
		funcid=""		����Ȩ��ID
		functype=""		����Ȩ������
	/>
</root>
@endverbatim
@return 
@remarks
@see CMU_SC_QueryRoleWithFunc
*/
DLIB_API t_int32 CMU_SC_OptRoleWithFunc(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief ��ѯ��ɫ����Ȩ�޹�ϵ
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 roleid		��ɫID
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptRoleWithFuncע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<func funcid="" functype="" />
	<func funcid="" functype="" />
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptRoleWithFunc
*/
DLIB_API t_int32 CMU_SC_QueryRoleWithFunc(t_uint32 handle, t_int32 timeout, t_int32 roleid, char*outxml, t_uint32 maxlen);

/**
@brief ��ɫ�µ�Ȩ�޸���
@param [in]  handle		��½���
@param [in]	 timeout		��ʱʱ��
@param [in]	 info			������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<roleid></roleid>		��ɫID
	<srcfuncid></srcfuncid>	Դ����Ȩ��ID
	<dstfuncid></dstfuncid>	Ŀ�Ĺ���Ȩ��ID
	<dstfuncid></dstfuncid>	Ŀ�Ĺ���Ȩ��ID
</root>
@endverbatim
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_FuncCopyWithRole(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief �����û�������Ȩ�޲�ѯ����Ȩ��
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 userid		�û�ID
@param [in]	 dataright	Ȩ�����ͣ�Ϊ0 ��ʾ��ѯ�û��µ�ȫ����
@param [out] outxml		��ѯ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		funcid=""		����Ȩ��ID
		title=""		��ǩ
		type=""			����Ȩ������
		parentid=""		��ID
		version=""		�汾
		clienttype=""		�ͻ�������
		path=""			·��
		status=""		״̬
		smallicon=""		Сͼ��
		bigicon=""		��ͼ��
		index= ""		����
		right=""		Ȩ������
		level=""		ģ��ȼ�
		visible=""		�Ƿ�ɼ�
		desc=""			����
		updatetime=""		����ʱ��
	/>
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryFuncByUser(t_uint32 handle, t_int32 timeout, t_int32 userid, t_int32 dataright, char* outxml, t_uint32 maxlen);

/**
@brief ��ѯȫ������Ȩ�޻��������Ȩ�޲�ѯ����Ȩ��
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 dataright	Ȩ�����ͣ�Ϊ0 ��ʾ��ѯȫ����
@param [out] outxml		��ѯ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		funcid=""		����Ȩ��ID
		title=""		��ǩ
		type=""			����Ȩ������
		parentid=""		��ID
		version=""		�汾
		clienttype=""		�ͻ�������
		path=""			·��
		status=""		״̬
		smallicon=""		Сͼ��
		bigicon=""		��ͼ��
		index= ""		����
		right=""		Ȩ������
		level=""		ģ��ȼ�
		visible=""		�Ƿ�ɼ�
		desc=""			����
		updatetime=""		����ʱ��
	/>
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryFunc(t_uint32 handle, t_int32 timeout, t_int32 dataright, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK�������ù���
* @{
*/

/**
@brief ������������
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
@verbatim
<root>
	<opt 
		operate=""			�������� 0 ���� 1 �޸� 2 ɾ��
	>
		<item 
			svrid=""		����ID
			title=""		��ǩ
			ipinfo=""		IP�Ͷ˿���Ϣ ��10.36.65.91|9800;
			flag=""			��ʶ 0 ��ʾ������Ϊmaster
			desc=""			����
			fast=""			�Ƿ����
			updatetime=""	����ʱ��
			status=""		״̬
		/>
	</opt>
</root>
flag�ֶε���˼��
0��ֻ����slave��������master��
1��������master��������slave��
2��ֻ����master��������slave��
3���Ȳ�����master���ֲ�����slave, 
4����ʾJava��������cmu��ȥ���ӣ�����ҪreportMaster�����еĿͻ��ˣ����������񣩣�
��Ϊ�ͻ��ˣ������ֻ���Ҫ����Java��������http�ӿ�
@endverbatim
@return 
@remarks
@see CMU_SC_QueryServerCfg
*/
DLIB_API t_int32 CMU_SC_OptServerCfg(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief ��ѯ��������
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptServerCfgע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item svrid="" title="" ipinfo="" flag="" desc="" fast="" updatetime="" status="" />
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptServerCfg
*/
DLIB_API t_int32 CMU_SC_QueryServerCfg(t_uint32 handle, t_int32 timeout, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK�������ù���
* @{
*/

/**
@brief ������������
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			�������� 0 ���� 2 ɾ��
	<userid></userid>		�û�ID
	<item 
		title=""		��������
		charvalue=""		�ַ�������ֵ
		numvalue=""		��������ֵ
	/>	
</root>
@endverbatim
@return 
@remarks
@see CMU_SC_QueryLocalCfg
*/
DLIB_API t_int32 CMU_SC_OptLocalCfg(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief ��ѯ��������
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 userid		�û�ID
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptLocalCfgע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item title="" charvalue="" numvalue="" />
	<item title="" charvalue="" numvalue="" />
	<errmsg />
	<errcode />
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptLocalCfg
*/
DLIB_API t_int32 CMU_SC_QueryLocalCfg(t_uint32 handle, t_int32 timeout, t_int32 userid, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK������Ϣ����
* @{
*/

/**
@brief ����������Ϣ
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>			�������� 0 ���� 2 ɾ��
	<item 
		otherdomid=""		�¼���ID
		title=""		�¼�������
		sendall=""		�����������Ƿ�Я���¼���
		parentdomid=""		�¼��������֯��ID
		parentorgcode=""	�¼��������֯����
		ip=""			�¼���CMU IP
		port=""			�¼���CMU �˿�
		updatetime=""		����ʱ��
		status=""		״̬
		flag=""			B�ӿڱ�ʶ
	/>	
</root>
@endverbatim
@return 
@remarks
@see CMU_SC_QueryDomInfo
*/
DLIB_API t_int32 CMU_SC_OptDomInfo(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief ��ѯ������Ϣ
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptDomInfoע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item otherdomid="" title="" sendall=""	parentdomid="" parentorgcode="" ip="" port="" updatetime="" status="" flag="" />
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CMU_SC_OptDomInfo
*/
DLIB_API t_int32 CMU_SC_QueryDomInfo(t_uint32 handle, t_int32 timeout, char* outxml, t_uint32 maxlen);

/**
@brief ��ѯ����Ϣ
@param [in]	handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
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
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
*/
DLIB_API t_int32 CMU_SC_QueryDomain(t_uint32 handle, t_int32 timeout,  char* info, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK����
* @{
*/

/**
@brief ����������Ϣ
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<srcdomid><srcdomid>		Դ��ID
	<modulename></modulename>	������ģ������ ��CMU��
	<domid></domid>			��ID
	<userid></userid>		�û�ID
	<enable></enable>		�������� 1��ʾ���ģ�2��ʾȡ������
	<item 
		cmd=""			ҵ������
		type=""			��������
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
* @defgroup CMU_SDK��־����
* @{
*/

/**
@brief �����û���־
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>		�������� 0 ���� 2 ɾ��
	<item 
		id=""		��־ID
		userid=""	�û�ID
		type=""		��־����
		username=""	�û���
		eventtime=""	�¼�ʱ��
		location=""	�¼��ص�
		title=""	�¼�����
		msgtxt=""	��Ϣ
	/>	
</root>
@endverbatim
@return 
@remarks
@see CM_QueryUserLog
*/
DLIB_API t_int32 CMU_SC_OptUserLog(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief ��ѯ�û���־
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<title></title>				�¼�����
	<userid></userid>			�û�ID
	<type></type>				��־����
	<starttime></starttime>			��ʼʱ��
	<endtime></endtime>			����ʱ��
	<size></size>				ҳ��С
	<curpage></curpage>			��ǰҳ
</root>
@endverbatim
@param [out] outxml		��ѯ��Ϣ(���CMU_SC_OptLocalCfgע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>		��ҳ��
	<item id="" userid="" type="" username="" eventtime="" location="" title="" msgtxt="" />
	<errmsg />
	<errcode />
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CM_OptUserLog
*/
DLIB_API t_int32 CMU_SC_QueryUserLog(t_uint32 handle, t_int32 timeout, char* info, char* outxml, t_uint32 maxlen);

/**
@brief ����ϵͳ��־
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>				�������� 0 ���� 2 ɾ��
	<item 
		id=""				��־ID
		modulename=""			ģ����
		type=""				��־����
		eventtime=""			�¼�ʱ��
		title=""			�¼�����
		msgtxt=""			��Ϣ
	/>	
</root>
@endverbatim
@return 
@remarks
@see CM_QuerySysLog
*/
DLIB_API t_int32 CMU_SC_OptSysLog(t_uint32 handle, t_int32 timeout, char* info);

/**
@brief ��ѯϵͳ��־
@param [in]  handle		��½���
@param [in]	 timeout	��ʱʱ��
@param [in]	 info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<title></title>					�¼�����
	<modulename></modelname>				ģ����
	<type></type>					��־����
	<starttime></starttime>				��ʼʱ��
	<endtime></endtime>				����ʱ��
	<size></size>					ҳ��С
	<curpage></curpage>				��ǰҳ
</root>
@endverbatim
@param [out] outxml		��ѯ��Ϣ(���CM_OptSysLogע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<item id="" modulename="" type=""  eventtime="" title="" msgtxt="" />
	<errmsg />
	<errcode />
</root>
@endverbatim
@param [in]	 maxlen		��Ϣ��󳤶�
@return 
@remarks
@see CM_OptSysLog
*/
DLIB_API t_int32 CMU_SC_QuerySysLog(t_uint32 handle, t_int32 timeout, char* info, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK����ͳ��
* @{
*/

/**
@brief ͳ���豸��Ϣ
@param [in]  handle			��½���
@param [in]	 timeout		��ʱʱ��
@param [in]	 domid			��ID
@param [in]	 orgcode		��֯����
@param [in]	 level			��ѹ�ȼ�����������0��			
@param [in]	 size			ҳ��С
@param [in]	 curpage		��ǰҳ(��0��ʼ)
@param [out] outxml			��ѯ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>			������
	<item 
		orgpath=""          	��֯�豸·��
        level=""            		��ѹ�ȼ�
        devname=""          		�豸����
        status=""           		״̬
        num=""				����ͷ����
        chnnum=""           		����ͨ����
		contrator="" �а���
		installtime="" ��װʱ��
		offlinetime=""     ����ʱ�䣬���status!=1������ֶ���Ч
	/>
</root>
@endverbatim
@param [in]	 maxlen			��Ϣ��󳤶�
@return 
@remarks
@see CM_OptSysLog
*/
DLIB_API t_int32 CMU_SC_QueryDevInfo(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode,\
									t_int32 level, t_int32 size, t_int32 curpage, char* outxml, t_uint32 maxlen);

/**
@brief ͳ��IPC״̬��Ϣ
@param [in]  handle			��½���
@param [in]	 timeout		��ʱʱ��
@param [in]	 domid			�豸��ID
@param [in]	 orgcode		��֯����
@param [in]	 level			��ѹ�ȼ�����������0��
@param [in]	 size			ҳ��С
@param [in]	 curpage		��ǰҳ(��0��ʼ)
@param [out] outxml			��ѯ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>			������
	<item 
		orgpath=""		��֯�豸·��
		level=""		��ѹ�ȼ�
		devname=""		�豸����
		chnname=""		ͨ������
		status=""		״̬
		contrator="" �а���
		installtime="" ��װʱ��
		offlinetime=""     ����ʱ�䣬���status!=1������ֶ���Ч
	/>
</root>
@endverbatim
@param [in]	 maxlen			��Ϣ��󳤶�
@return 
@remarks
@see CM_OptSysLog
*/
DLIB_API t_int32 CMU_SC_QueryIpcStatus(t_uint32 handle, t_int32 timeout, char* domid, char* orgcode,\
									t_int32 level, t_int32 size, t_int32 curpage, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK��ؼƻ�
* @{
*/

/**
@brief ������ؼƻ�������Ϣ
@param [in]  handle			��½���
@param [in]	 timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>				�������� 0 ���� 1 �޸� 2 ɾ��
    <task						һ�β���һ���ƻ����ͨ��
		taskid=""				�ƻ�ID
		userid =""				�û�ID
		taskname =""			�ƻ�����
		wndnum =""				�ƻ�������
		tasktype =""			�ƻ�����
		time=""					�ƻ�ִ��ʱ��
		parentdomid=""			����ID
		parentcode=""			������
	>
        <channel				
			domid =""			��ID
			devcode =""			�豸����
			devtype=""			�豸����
			devname=""			����
			substream=""		������
			timespan=""			��ѯʱ��
			prepoint=""			Ԥ�õ�
			index=""			��Ƶ���ں�
		/>
		<channel domid ="" devcode ="" devtype="" devname="" substream="" timespan="" prepoint="" index="" />
 	</task>
</root>
@endverbatim
@return 
@remarks ����Ĭ����Ƶ����ǰ�ƻ�����Э��ֻ�����ӡ�ɾ�������������ؼƻ������������ֲ���
@see 
*/
DLIB_API t_int32 CMU_SC_OptMonitorTask(t_uint32 handle, t_int32 timeout, char *info);

/**
@brief ��ѯ��ؼƻ���Ϣ
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	info			������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<userid/>				�û�ID
	<flag/>					��ѯ���� 0 ȫ�� 1 ��������
	<tasktype/>				�������  0:Ĭ����Ƶ 1����ؼƻ� 
	<domid/>				����id
	<code/>					������
</root>
@endverbatim
@param [out] outxml			��ѯ��Ϣ
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
@param [in]	 maxlen			��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryMonitorTask(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK���ݿ����
* @{
*/

/**
@brief �������ݿⱸ�ݼƻ�
@param [in]  handle			��½���
@param [in]	 timeout			��ʱʱ��
@param [in]	 opttype			�������� 0 ���� 2 ɾ��
@param [in]	 backtype			�������� 0 ������ 1 �澯�� 2 ��־�� 3 ���������ݱ�
@param [in]	 backcycle			�������� �磺"1,2,3"
@param [in]	 backtime			����ʱ��� �磺"07:59:00"
@param [in]	 backnum			�����ļ�����
@return 
@remarks 
@see 
*/
DLIB_API t_int32 CMU_SC_OptDbBackUp(t_uint32 handle, t_int32 timeout, t_int32 opttype , t_int32 backtype, char* backcycle, char* backtime, t_int32 backnum);

/**
@brief ��ѯ���ݿⱸ�ݼƻ�
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	backtype		�������� 0 ������ 1 �澯�� 2 ��־�� 3 ���������ݱ�
@param [out] outxml			��ѯ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<type/>					��������
	<cycle/>				��������
	<time/>					����ʱ��
	<num/>					�����ļ�����
</root>
@endverbatim
@param [in]	 maxlen			��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryDbBackUp(t_uint32 handle, t_int32 timeout, t_int32 backtype, char *outxml, t_uint32 maxlen);

/**
@brief �������ݿ�����ƻ�
@param [in]  handle			��½���
@param [in]	 timeout			��ʱʱ��
@param [in]	 logtime			��־ʱ��
@param [in]	 alarmtime			�澯ʱ��
@return 
@remarks 
@see 
*/
DLIB_API t_int32 CMU_SC_OptDbCleanUp(t_uint32 handle, t_int32 timeout, t_int32 logtime, t_int32 alarmtime);

/**
@brief ��ѯ���ݿ�����ƻ�
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [out] outxml			��ѯ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<logtime/>				��־ʱ��
	<alarmtime/>			�澯ʱ��
</root>
@endverbatim
@param [in]	 maxlen			��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryDbCleanUp(t_uint32 handle, t_int32 timeout, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯ���ݿ�ɸ��°汾
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [out] outxml			��ѯ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<update version="" date="" desc=""/>
	<update version="" date="" desc=""/>
	<update version="" date="" desc=""/>
</root>
@endverbatim
@param [in]	 maxlen			��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryDbUpdateVersion(t_uint32 handle, t_int32 timeout, char *outxml, t_uint32 maxlen);

/**
@brief �������ݿ�ű�
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	info			������Ϣ
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
* @defgroup CMU_SDK��ͼ��Ϣ
* @{
*/

/**
@brief ������ͼ��Ϣ
@param [in]  handle			��½���
@param [in]	 timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>				�������� 0 ���� 1 �޸� 2 ɾ��
	<map 
		id=""					ID
		orgdomid=""				��֯��ID
		orgcode=""				��֯����
		title=""				����
		filename=""				�ļ�����
		desc=""					����
		config=""				������Ϣ
	>
		<device 
			domid=""			��ID
			devcode=""			�豸����
		/>
		<device domid="" devcode=""/>
	</map>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<id></id>					ID
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks 
@see 
*/
DLIB_API t_int32 CMU_SC_OptMap(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ������֯�ṹ��ѯ��ͼ��Ϣ
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	timeout			��ID
@param [in]	timeout			��֯����
@param [out] outxml			��ѯ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<map id="" orgdomid="" orgcode="" title="" file="" des="" config="" >
		<device domid="" devcode="" devtype="" manufid="" title="" status="" streamtype="" />
		<device domid="" devcode="" devtype="" manufid="" title="" status="" streamtype="" />
	</map>
</root>
@endverbatim
@param [in]	 maxlen			��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryMapByOrg(t_uint32 handle, t_int32 timeout, char *domid, char *orgcode, char *outxml, t_uint32 maxlen);

/**
@brief ����mapid��ѯ��ͼ��Ϣ
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<map id=""/>
	<map id=""/>
</root>
@endverbatim
@param [out] outxml				������Ϣ
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
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryMap(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ����GIS��ϵ��
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<giscontact id="" contactid=" type=0:ϵͳ�û�id,type=1:��ϵ��id" longitude="" latitude=""/>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<giscontact id=""/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptGisContact(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯGIS��ϵ��
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<type>��ѯ����,0:��ѯȫ��,1:��ѯָ��id</type>
	<giscontact id=""/>
	<giscontact id=""/>
	<curpage></curgpage>
	<size></size>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<giscontact id="" contactid=" type="0:ϵͳ�û�,1:��ϵ��" longitude="" latitude=""/>
	<giscontact id=""/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryGisContact(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ����GIS����
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<gisbuilding id="" name=""/>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<gisbuilding id=""/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptGisBuilding(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ����GIS��������
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<gisbuilding id="" longitude="" latitude=""/>
	<gisbuilding id="" longitude="" latitude=""/>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<gisbuilding id=""/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptGisBuildingPos(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯGIS����
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<type>��ѯ����,0:��ѯȫ��,1:��ѯָ��id</type>
	<gisbuilding id=""/>
	<gisbuilding id=""/>
	<curpage></curgpage>
	<size></size>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<gisbuilding id="" name="" longitude="" latitude=""/>
	<gisbuilding id=""/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryGisBuilding(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ����GIS�豸
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<gisdevice id="" domid=" devcode="" longitude="" latitude=""/>
	<gisdevice id="" domid=" devcode="" longitude="" latitude=""/>
	<gisdevice id="" domid=" devcode="" longitude="" latitude=""/>
	<gisdevice id="" domid=" devcode="" longitude="" latitude=""/>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<gisdevice id=""/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptGisDevice(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯGIS�豸
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<type>��ѯ����,0:��ѯȫ��,1:��ѯָ��id</type>
	<gisdevice id=""/>
	<gisdevice id=""/>
	<curpage></curgpage>
	<size></size>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<gisdevice id="" domid=" devcode="" name="" longitude="" latitude=""/>
	<gisdevice id=""/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryGisDevice(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ͨ����֯��ѯGIS�豸
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>
    <orgcode></orgcode>
	<devtype></devtype> Ϊ�ղ�ȫ������,��������ö��ŷָ�����"1,2,3"
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode=""  orgpath="" title="" updatetime="" desc="" >
		<device domid="" devcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" devlinktype="" display="" updatetime="" />
	</org>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryGisDeviceByOrg(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ͨ���豸��ѯGISͨ��
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>
    <devcode></devcode>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<device domid="" devcode="">
        <channel domid="" devcode="" parentdomid="" parentdevcode="" orgdomid="" orgcode="" devpath="" orgpath="" devtype="" manufid="" title="" status="" devposidx="" updatetime="" chnidx="" accesory=""/>
    </device>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryGisDeviceDetail(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ����GIS¥��
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<gisbuildingfloor id="" buildingid="" mapid="" name="" num=""/>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<gisbuildingfloor id=""/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptGisBuildingFloor(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯGIS¥��
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<gisbuildingfloor buildingid=""/>
	<curpage></curgpage>
	<size></size>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<gisbuildingfloor id="" buildingid="" mapid="" name="" num=""/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryGisBuildingFloor(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK������ͳ��
* @{
*/
/**
@brief ��ȡ����������վ��������Ϣ
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<region domid=""/>
	<region domid=""/>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<region domid="" orgcode="" parenttitle="" title="" status="" time="">����Ӧ����station�ڵ㣬�������д���region�ڵ㣬���Ծ�����������
		<device domid="" devcode="" parenttitle="" title="" status="" ipaddr="" manufid="" model="" installtime="" contrator="">
			<channel domid="" devcode="" parenttitle="" title="" status="" />
		</device>
	</region>
	<region>
	</region>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryStationStatus(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ��ȡ������������
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<region domid=""/>
	<region domid=""/>
	<starttime></starttime>
	<endtime></endtime>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<region domid="" title="" ip="" port="" onlinenum="" totalnum="" onlinerate="" time=""/>
	<region domid="" title="" ip="" port="" onlinenum="" totalnum="" onlinerate="" time=""/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryRegionOnlineRate(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);
/** @} */

/**
* @defgroup CMU_SDK�û�ͨѶ¼����
* @{
*/
/**
@brief ������ϵ��
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt><opt> �������� 0 ���� 1 �޸� 2 ɾ��
	<contact 
		id="" 
		userid="" 
		name="" 
		sex="" �Ա�,0:�� 1:Ů 2:����
		age=""
		desc=""
	>
		<telephone number="" desc=""/>
		<telephone number="" desc=""/>
	</contact>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<contactid></contactid>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptUserContact(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯ�û�ͨѶ¼
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<userid></userid>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<contact 
		id="" 
		userid="" 
		name="" 
		sex="" �Ա�,0:�� 1:Ů 2:����
		age=""
		desc=""
	>
		<telephone number="" desc=""/>
		<telephone number="" desc=""/>
	</contact>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryUserContact(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯ��ϵ��
@param [in]	session			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<keywords> �����룺-1����ȫ�������绰���룬��ϵ������ƴ������ϵ����������ĸ����ϵ������</keywords>
	<curpage></curpage>
	<size></size>
</root>
@endverbatim
@param [out] outxml				������Ϣ��Ĭ�ϰ�װ��ϵ����������ĸ����
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
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryAllContact(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);


/**
@brief ������ϵ�˷���
@param [in]	session			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0��� 1�޸� 2ɾ��</opt>
	<contactgroup id="����id���޸ġ�ɾ����Ч"
		name="�������ƣ�64�ֽڣ���ӡ��޸���Ч"
		userid="���������û�id����ӡ��޸���Ч"
	>
		<contact domid="" id="" userid="" devcode="" contactid="" type=""/>
		<contact domid="" id="" userid="" devcode="" contactid="" type=""/>
	</contactgroup>
</root>
@endverbatim
@param [out] outxml				������Ϣ
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
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks �޸ķ���ʱ���µ�contact�ڵ��б�Ḳ��ԭ�м�¼
@see 
*/
DLIB_API t_int32 CMU_SC_OptContactGroup(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯ��ϵ�˷���
@param [in]	session			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<userid>���������û�id </userid>
	<size>ÿҳ���ؼ�¼������</size>
	<curpage>�ڼ�ҳ����0��ʼ</curpage>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<contactgroup id="����id"
		name="��������"
		userid="���������û�id"
	>
		<contact domid="" id="" userid="" devcode="" contactid="" type=""/>
		<contact domid="" id="" userid="" devcode="" contactid="" type=""/>
	</contactgroup>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks δ�������ϵ�˲鲻��
@see 
*/
DLIB_API t_int32 CMU_SC_QueryContactGroup(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯ��ϵ��
@param [in]	session			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<keywords> �����룺-1����ȫ�������绰���룬��ϵ������ƴ������ϵ����������ĸ����ϵ������</keywords>
	<size>ÿҳ���ؼ�¼������</size>
	<curpage>�ڼ�ҳ����0��ʼ</curpage>
</root>
@endverbatim
@param [out] outxml				������Ϣ��Ĭ�ϰ�װ��ϵ����������ĸ����
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<!--�ѷ����¼-->
	<contactgroup id="����id"
		name="��������"
		userid="���������û�id"
	>
		<contact domid="" id="" userid="" devcode="" contactid="" name="" type="">
			<telephone number=""/>
			<telephone number=""/>
		</contact>
		<contact id=""/>
	</contactgroup>
	<contactgroup id=""/>
	<ungrouped>
		<!--δ�����¼-->
		<contact id=""/>
		<contact id=""/>
	</ungrouped>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryAllContactWithGroup(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup CMU_SDK�û��豸����
* @{
*/

/**
@brief ��ѯ�û��豸
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<user id="" session="">
	<user id="" session="">
</root>
@endverbatim
@param [out] outxml				������Ϣ
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
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryUserBindDevice(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ����/�޸��û��豸���������壩
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
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
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root/>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
�����µİ��豸�б��滻�ϵİ��豸�б�
@see 
*/
DLIB_API t_int32 CMU_SC_OptUserBindDevice(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯ�û��󶨵ĺ����ѯ�û��󶨵��豸
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<number></number>
</root>
@endverbatim
@param [out] outxml				������Ϣ
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
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_QueryUserBindDeviceByNumber(t_uint32 handle, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);


/**
@brief ��������󶨵�����ͷ��Ԥ��λ
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<root>
	<number opt="" id="">
		<device domid="" chncode="" presetid="">
		<device domid="" chncode="" presetid="">
	</number>
	...
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<root>
	<number opt="" id="" name="">
		<device domid="" chncode="" chnname="" presetid="" presetname="">
		<device domid="" chncode="" chnname="" presetid="" presetname="">
	</number>
	...
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 CMU_SC_OptNumBindDevicePreset(t_uint32 handle, t_int32 timeout, char *inxml, char *outxml, t_uint32 maxlen);

/**
@brief ��������󶨵�����ͷ��Ԥ��λ
@param [in]	handle			��½���
@param [in]	timeout			��ʱʱ��
@param [in]	 info			������Ϣ
@verbatim
<root>
	<number id="">
	</number>
	...
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<root>
	<number opt="" id="" name="">
		<device domid="" chncode="" chnname="" presetid="" presetname="">
		<device domid="" chncode="" chnname="" presetid="" presetname="">
	</number>
	...
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
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


