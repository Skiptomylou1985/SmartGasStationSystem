/**
 * Copyright (c) 2014, �㽭��ϵͳ�������޹�˾ All rights reserved.
 * \file		vtdu_sdk.h
 * \brief		vtdu_sdk
 * \author		17400
 * \date		2014��12��19��
 * \note		VTDU SDK �ӿ�
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
* @defgroup VTDU_SDK����
* @{
*/

/**
* @defgroup VTDU_SDKϵͳ
* @{
*/

/**
@brief VTDU_SDK��ʼ��
@return 
@remarks
@see VTDU_C_Init
*/
DLIB_API t_int32 VTDU_SC_Init();
/**
@brief VTDU_SDK��ʼ��,��������Ѿ�����applicationBase�ĳ������
@return 
@remarks
@see VTDU_SC_InitNoApp
*/
DLIB_API t_int32 VTDU_SC_InitNoApp();

/**
@brief VTDU_SDK����ʼ��
@return 
@remarks
@see VTDU_C_Cleanup
*/
DLIB_API t_int32 VTDU_SC_Cleanup();

/** @} */

/**
* @defgroup VTDU_SDK�����ص�����
* @{
*/

/**
@brief �����ص��ӿ�
@param [out] realHandle ���
@param [out] buffer	����
@param [out] dwBufSize ����
@param [out] pUser �û���Ϣ
@return 
@see 
*/
typedef t_int32 (*fVtdu_C_RealDataCallBack)(t_uint32 realHandle, char *buffer, t_uint32 dwBufSize, void *pUser);


/**
@brief ���������ص�����
@param [in] realHandle ��Ƶ�����
@param [in] cb �ص�����
@param [in] pUser �û�����
@return 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_SetRealDataCallBack(t_uint32 realHandle, fVtdu_C_RealDataCallBack cb, void *pUser);

/**
@brief ��������ص�����
@param [out] realHandle	���
@param [out] buffer	����
@param [out] dwBufSize ����
@param [out] cacheLen �ڲ����泤��
@param [out] pUser �û���Ϣ
@see 
*/
typedef t_int32 (*fVtdu_C_RealDataCallBackByCache)(t_uint32 realHandle, char *buffer, t_uint32 dwBufSize, t_uint32 cacheLen, void *pUser);

/**
@brief ������������ص�����,�����ڲ�����
@param [in] realHandle ��Ƶ�����
@param [in] cb �ص�����
@param [in] pUser �û�����
@return  
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_SetRealDataCallBackByCache(t_uint32 realHandle, fVtdu_C_RealDataCallBackByCache cb, void *pUser);

/** @} */

/**
* @defgroup VTDU_SDK�ص�����
* @{
*/

/**
@brief �첽��Ϣ�ص�����
@param [out] vtduSession ��Ϣ���
@param [out] buffer		�ص�����
@param [out] buffLen	���ݳ���
@param [out] pUser		�û�����
@return  
@remarks
@see 
*/
typedef t_int32 (*fVtdu_C_CallBack)(t_uint32 vtduSession, char *buffer, t_uint32 buffLen, void *pUser);

/**
@brief �����첽��Ϣ�ص�����
@param [out] vtduSession ��Ϣ���
@param [in] cb �ص�����
@param [in] pUser �û�����
@return  
@remarks
@see
@verbatim
����online��Ϣ֪ͨ
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="SDK" type="onlineNotify" cmd="onlineNotify" sequence="0" length="0">
<server
	servername="VTDU"	��������
	session="1"			������
	status="1"			������״̬
/>
</root>
@endverbatim

rtsp announce��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="SDK" type="request" cmd="announce" sequence="0" length="0"/>

<state>200</state>			״̬��200��ʾ���ߣ��������������
<realhandle>5</realhandle>	��Ƶ���
</root>
@endverbatim
*/
DLIB_API t_int32 VTDU_SC_SetCallBack(t_uint32 vtduSession, fVtdu_C_CallBack cb, void *pUser);

/** @} */

/**
* @defgroup VTDU_SDK�첽����
* @{
*/

/**
@brief �첽����vtdu
@param [in] cmuLoginHandle	cmu�ĵ�¼���
@param [in] ipInfo			����ip��Ϣ����ʽ"ip|port;ip|port;"
@param [in] svrDomId		������id
@param [in] svrId			����id
@param [in] maxLen			xmlOutput����
@param [out] xmlOutput		xml���
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<vtdusession>2</vtdusession>
</root>
@endverbatim
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_Connect(t_uint32 cmuLoginHandle, char *ipInfo, char *svrDomId, t_int32 svrId, char *xmlOutput, t_uint32 maxLen);

/**
@brief �û���֤�첽����vtdu
@param [in] usersession		�û���֤
@param [in] ipInfo			����ip��Ϣ����ʽ"ip|port;ip|port;"
@param [in] svrDomId		������id
@param [in] svrId			����id
@param [in] maxLen			xmlOutput����
@param [out] xmlOutput		xml���
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<vtdusession>2</vtdusession>
</root>
@endverbatim
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_ConnectNoCmu(t_uint32 usersession, char *ipInfo, char *svrDomId, t_int32 svrId, char *xmlOutput, t_uint32 maxLen);

/**
@brief �첽�Ͽ�����
@param [in] vtduSession		������
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_Disconnect(t_uint32 vtduSession);

/** @} */

/**
* @defgroup VTDU_SDK�첽¼��
* @{
*/

/**
@brief �첽¼���ѯ
@param [in] vtduSession		������
@param [in] xmlInput		¼���ѯ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<domid></domid>				�豸��id
<chncode></chncode>			ͨ������
<svrid></svrid>				������ID
<ipinfo></ipinfo>			IP���˿���Ϣ
<sourcetype></sourcetype>	1:����¼��2:ǰ��¼��
<recordtype></recordtype>	¼������ 0:δ֪¼������, 1:�ֶ�¼��, (1<<1):��ʱ¼��, (1<<2):ȫ���¼��, (1<<3):�澯¼��, 1<<4):��Ƶ��ʧ, (1<<5):��Ƶ�ڵ�, (1<<6):�ƶ����, 0xFFFFFFFF:�����ļ�
<vruid></vruid>				¼��洢����ID
<diskid></diskid>			¼��洢����ID
<filehandle></filehandle>	¼��洢�ļ����
<starttime></starttime>		��ʼʱ��
<endtime></endtime>			����ʱ��
<size></size>				ÿҳ��С
<curpage></curpage>			��ǰҳ��1��ʼ
<videofiletype></videofiletype>	¼���ļ����� 0ԭʼ¼�� 1Ũ��¼��
<synopsisstate></synopsisstate>	¼��Ũ��״̬ 0Ũ�������� 1Ũ�����
</root>
@endverbatim
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_QueryRecordFile(t_uint32 vtduSession, char *xmlInput);

/**
@brief �첽¼���ѯ,�����ӿ� (��֤����xml������vrusdk�ӿڹ���)
@param [in] vtduSession		������
@param [in] xmlInput		¼���ѯ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<IBP domid="123" chncode="chad" />
<svrid></svrid>				������ID
<ipinfo></ipinfo>			IP���˿���Ϣ
<sourcetype></sourcetype>	1:����¼��2:ǰ��¼��
<recordtype></recordtype>	¼������ 0:δ֪¼������, 1:�ֶ�¼��, (1<<1):��ʱ¼��, (1<<2):ȫ���¼��, (1<<3):�澯¼��, 1<<4):��Ƶ��ʧ, (1<<5):��Ƶ�ڵ�, (1<<6):�ƶ����, 0xFFFFFFFF:�����ļ�
<vruid></vruid>				¼��洢����ID
<diskid></diskid>			¼��洢����ID
<filehandle></filehandle>	¼��洢�ļ����
<starttime></starttime>		��ʼʱ��
<endtime></endtime>			����ʱ��
</root>
@endverbatim
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_QueryRecordFile_Modify(t_uint32 vtduSession, char *xmlInput);

/** @} */

/**
* @defgroup VTDU_SDK�첽ʵʱ��Ƶ
* @{
*/

/**
@brief �첽��ȡ��Ƶ������ʵʱ,¼��,�����ȣ�������rtsp����
@param [in] vtduSession					������
@param [in] xmlInput							��Ƶ������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<domid></domid>							�豸��id
<chncode></chncode>						ͨ������
<playvideotype></playvideotype>			0:ʵʱ��Ƶ, 1:¼��ط�, 2:�����Խ�
<talktype></talktype>					0:ͨ���Խ���1:�豸�Խ�
<playtype></playtype>					1:���ļ��ط�,  2:��ʱ��ط�
<transproto></transproto>				0:TCP, 1:UDP
<streamtype></streamtype>				0:������, 1:������
<streampacktype></streampacktype>		���������� //-1 ���� 0 �ö��ڵ�������sdk������ 1 rpt h264 ������ 2 rpt h264 nal��� 3 pg  pss�� 
<sourcetype></sourcetype>				1:����¼��2:ǰ��¼��
<filename></filename>					¼���ļ���
<vruid></vruid>							¼��洢����ID
<diskid></diskid>						¼��洢����ID
<filehandle></filehandle>				¼��洢�ļ����
<starttime></starttime>					��ʼʱ��
<endtime></endtime>						����ʱ��
</root>
@endverbatim
@param [in] maxLen						xmlOutput����
@param [out] xmlOutput					xml���
@verbatim
<root version="1.0" unit="Unknown" type="Response" cmd="startRVideo" sequence="16" session="0">
<token>1</token>
<playvideotype>0</playvideotype>
<svrid>4</svrid>
<ipinfo>10.36.65.112|8513;</ipinfo>		�����rtsp ip��port��Ϣ
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
@return									200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_StartVideo_I(t_uint32 vtduSession, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/**
@brief �첽��ȡʵʱ��Ƶ������rtsp����
@param [in] vtduSession		������
@param [in] domainId		�豸��id
@param [in] channelCode		ͨ������
@param [in] streamType		�������� 0������, 1������
@param [in] transType		��������Э��0:TCP 1:UDP
@param [in] streamPackType  ���������� //-1 ���� 0 �ö��ڵ�������sdk������ 1 rpt h264 ������ 2 rpt h264 nal��� 3 pg  pss�� 
@param [in] maxLen			xmlOutput����
@param [out] xmlOutput		xml��� ��ʽͬVTDU_AC_StartVideo_I
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_RealPlay_I(t_uint32 vtduSession, char *domainId, char *channelCode, t_int32 streamType, t_int32 transType, t_int32 streamPackType, char *xmlOutput, t_uint32 maxLen);

/**
@brief �첽��ȡ��Ƶ
@param [in] vtduSession		������
@param [in] xmlInput		��������
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<domid></domid>							�豸��id
<chncode></chncode>						ͨ������
<playvideotype></playvideotype>			0:ʵʱ��Ƶ, 1:¼��ط�, 2:�����Խ�
<talktype></talktype>					0:ͨ���Խ���1:�豸�Խ�
<playtype></playtype>					1:���ļ��ط�,  2:��ʱ��ط�
<transproto></transproto>				0:TCP, 1:UDP
<streamtype></streamtype>				0:������, 1:������
<streampacktype></streampacktype>		0:�ö��ڵ�������sdk������ (�豸����RTP����)	
										1:rpt h264 ������ 	(H264RTP������)
										2:rpt h264 nal��� (H264RTP��׼����)
										3:pg  pss�� 	(�Ϸ�����PG����)	
topacktype>3</topacktype>				�������ת������	 0:Ĭ�� 1:pgתRTMP 2:��2Rtmp 3:��2RTPH264Nal
<blocalrecv>1</blocalrecv>				��0:����ֱ�ӷ��͸�sdk,0:���͸���������
<sourcetype></sourcetype>				1:����¼��2:ǰ��¼��
<filename></filename>					¼���ļ���
<vruid></vruid>							¼��洢����ID
<diskid></diskid>						¼��洢����ID
<filehandle></filehandle>				¼��洢�ļ����
<starttime></starttime>					��ʼʱ��
<endtime></endtime>						����ʱ��
</root>
@endverbatim
@param [in] maxLen						xmlOutput����
@param [out] xmlOutput					xml��� ��ʽͬVTDU_AC_StartVideo_I
@return									200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_StartVideo(t_uint32 vtduSession, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/** @} */

/**
* @defgroup VTDU_SDK�첽RTSP����
* @{
*/

/**
@brief �첽Rtsp����
@param [in] realHandle		������
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_RtspConnect(t_uint32 realHandle);

/**
@brief �첽rtsp Describe
@param [in] realHandle		���ž��
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_VideoDescribe(t_uint32 realHandle);

/**
@brief �첽rtsp Setup
@param [in] realHandle		���ž��
@param [in] clientIpInfo	�����ip��Ϣ����ʽ"ip|port;ip|port;"
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_VideoSetup(t_uint32 realhandle, char *clientIpInfo);

/**
@brief �첽rtsp Play����ؽӿ� VTDU_SC_SeekPlay
@param [in] realHandle		���ž��
@param [in] rang			�����ip��Ϣ����ʽ"ip|port;ip|port;"
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_VideoPlay(t_uint32 realHandle);

/**
@brief �첽¼���϶�,������ŵ�ʱ��Ҳ��Ҫ��range �� scale����ʹ������ӿ�
@param [in] realHandle		���ž��
@param [in] timeout			��ʱʱ��
@param [in] range			��λλ��,��ʱ���϶���ʽ:clock=19000101T000000Z-�����ļ���С�϶���ʽ:byte=12333-
@param [in] scale			�����ٶ� 
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_SeekPlay(t_uint32 realHandle, char *range, t_float32 scale);

/**
@brief �첽¼����ͣ
@param [in] realHandle		���ž��
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_VideoPause(t_uint32 realHandle);

/**
@brief ��Ƶֹͣ
@param [in] realHandle		���ž��
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_AC_Stop(t_uint32 realHandle);

/** @} */

/**
* @defgroup VTDU_SDKͬ������
* @{
*/

/**
@brief ͬ������vtdu
@param [in] cmuLoginHandle	cmu��֤session
@param [in] timeout			��ʱʱ��
@param [in] ipInfo			vtdu����ip��Ϣ
@param [in] svrDomId		������id
@param [in] svrId			����id
@param [in] maxLen			xmlOutput����
@param [out] xmlOutput		xml���
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<vtdusession>2</vtdusession>
</root>
@endverbatim
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_Connect(t_uint32 cmuLoginHandle, t_int32 timeout, char *ipInfo, char *svrDomId, t_int32 svrId, char *xmlOutput, t_uint32 maxLen);

/**
@brief ͬ���Ͽ�����
@param [in] vtduSession		������
@param [in] timeout			��ʱʱ��
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_Disconnect(t_uint32 vtduSession, t_int32 timeout);

/** @} */

/**
* @defgroup VTDU_SDKͬ��¼��
* @{
*/

/**
@brief ͬ��¼���ѯ
@param [in] vtduSession		������
@param [in] timeout			��ʱʱ��
@param [in] xmlInput		¼���ѯ��Ϣ����ʽͬVTDU_AC_QueryRecordFile
@param [in] maxLen			��Ӧ����󳤶�
@param [out] xmlOutput		��ѯ������
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<info>
<count>2</count>
<item sourcetype="2" recordtype="1" starttime="20141229T160000Z" endtime="20141229T170000Z" filename="0|0|77036|682394|0|5|20141229T160000Z|20141229T170000Z" length="682394" title="" planid="0" vruid="0" diskid="0" filehandle="0" devcode="" rtspurl=""/>
<item sourcetype="2" recordtype="1" starttime="20141229T170000Z" endtime="20141229T175534Z" filename="0|0|77631|603136|0|15|20141229T170000Z|20141229T175534Z" length="603136" title="" planid="0" vruid="0" diskid="0" filehandle="0" devcode="" rtspurl=""/>
</info>
@endverbatim
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_QueryRecordFile(t_uint32 vtduSession, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/**
@brief ͬ��¼���ѯ,�����ӿڣ���֤����xml������vrusdk�ӿڹ��ã�
@param [in] vtduSession		������
@param [in] timeout			��ʱʱ��
@param [in] xmlInput		¼���ѯ��Ϣ����ʽͬVTDU_AC_QueryRecordFile_Modify
@param [in] maxLen			��Ӧ����󳤶�
@param [out] xmlOutput		��ѯ������
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<info>
<count>2</count>
<item sourcetype="2" recordtype="1" starttime="20141229T160000Z" endtime="20141229T170000Z" filename="0|0|77036|682394|0|5|20141229T160000Z|20141229T170000Z" length="682394" title="" planid="0" vruid="0" diskid="0" filehandle="0" devcode="" rtspurl=""/>
<item sourcetype="2" recordtype="1" starttime="20141229T170000Z" endtime="20141229T175534Z" filename="0|0|77631|603136|0|15|20141229T170000Z|20141229T175534Z" length="603136" title="" planid="0" vruid="0" diskid="0" filehandle="0" devcode="" rtspurl=""/>
</info>
@endverbatim
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_QueryRecordFile_Modify(t_uint32 vtduSession, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/** @} */

/**
* @defgroup VTDU_SDKͬ����Ƶ����
* @{
*/

/**
@brief ͬ����ȡ��Ƶ������ʵʱ,¼��,�����ȣ�������rtsp����
@param [in] vtduSession		������
@param [in] timeout			��ʱʱ��
@param [in] xmlInput		��Ƶ������Ϣ����ʽͬVTDU_AC_StartVideo_I
@param [in] maxLen			xmlOutput����
@param [out] xmlOutput		xml���
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<realhandle>3</realhandle>
</root>
@endverbatim
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_StartVideo_I(t_uint32 vtduSession, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/**
@brief ͬ����ȡʵʱ��Ƶ������rtsp����
@param [in] vtduSession		������
@param [in] timeout			��ʱʱ��
@param [in] domainId		�豸��id
@param [in] channelCode		ͨ������
@param [in] streamType		�������� 0������, 1������
@param [in] transType		��������Э��0:TCP 1:UDP
@param [in] streamPackType  ���������� //-1 ���� 0 �ö��ڵ�������sdk������ 1 rpt h264 ������ 2 rpt h264 nal��� 3 pg  pss�� 
@param [in] maxLen			xmlOutput����
@param [out] xmlOutput		xml���
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<realhandle>3</realhandle>
</root>
@endverbatim
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_RealPlay_I(t_uint32 vtduSession, t_int32 timeout, char *domainId, char *channelCode, t_int32 streamType, t_int32 transType, t_int32 streamPackType, char *xmlOutput, t_uint32 maxLen);

/**
@brief ͬ�������Խ�������rtsp����
@param [in] vtduSession		������
@param [in] timeout			��ʱʱ��
@param [in] domainId		�������Ƶ������
@param [in] channelCode		ͨ������
@param [in] talkType		�Խ����� 0ͨ���Խ�, 1�豸�Խ�
@param [in] transType		��������Э��0:TCP 1:UDP
@param [in] streamPackType  ���������� //-1 ���� 0 �ö��ڵ�������sdk������ 1 rpt h264 ������ 2 rpt h264 nal��� 3 pg  pss�� 
@param [in] maxLen			xmlOutput����
@param [out] xmlOutput		xml���
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<realhandle>3</realhandle>
</root>
@endverbatim
@return						200 �ɹ�,��������������ĵ�  
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_RealTalking_I(t_uint32 vtduSession, t_int32 timeout, char *domainId, char *channelCode, t_int32 talkType, t_int32 transType, t_int32 streamPackType, char *xmlOutput, t_uint32 maxLen);

/**
@brief ��չͬ�������Խ�������rtsp����
@param [in] vtduSession		������
@param [in] timeout			��ʱʱ��
@param [in] domainId		�������Ƶ������
@param [in] channelCode		ͨ������
@param [in] talkType		�Խ����� 0ͨ���Խ�, 1�豸�Խ�
@param [in] transType		��������Э��0:TCP 1:UDP
@param [in] streamPackType  ���������� //-1 ���� 0 �ö��ڵ�������sdk������ 1 rpt h264 ������ 2 rpt h264 nal��� 3 pg  pss�� 
@param [in] convType        ����ת������ 0��ת�� 3 G711Aת��
@param [in] audioEncodeType ������������
@param [in] audioSamplingRate ��Ƶ������
@param [in] audioChannelNum   ������
@param [in] maxLen			xmlOutput����
@param [out] xmlOutput		xml���
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<realhandle>3</realhandle>
</root>
@endverbatim
@return						200 �ɹ�,��������������ĵ�  
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
@brief ͬ�����ͶԽ�����
@param [in] realHandle		���ž��
@param [in] buffer			����
@param [in] bufferLen		���ݳ���
@return						200 �ɹ�,������������� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_SendTalkData(t_uint32 realHandle, char* buffer, t_uint32 bufferLen);

/**
@brief ͬ����ȡ��Ƶ
@param [in] vtduSession		������
@param [in] timeout			��ʱʱ��
@param [in] xmlInput		�������ݣ���ʽͬVTDU_AC_StartVideo
@param [in] maxLen			xmlOutput����
@param [out] xmlOutput		xml���
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<realhandle>3</realhandle>
</root>
@endverbatim
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_StartVideo(t_uint32 vtduSession, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/** @} */

/**
* @defgroup VTDU_SDKͬ��RTSP����
* @{
*/

/**
@brief ͬ��Rtsp����
@param [in] realHandle		������
@param [in] timeout			��ʱʱ��
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_RtspConnect(t_uint32 realHandle, t_int32 timeout);

/**
@brief ͬ��rtsp Describe
@param [in] realHandle		���ž��
@param [in] timeout			��ʱʱ��
@return						200 �ɹ�,��������������ĵ�  
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_VideoDescribe(t_uint32 realHandle, t_int32 timeout);

/**
@brief ͬ��rtsp Setup
@param [in] realHandle		���ž��
@param [in] timeout			��ʱʱ��
@param [in] clientIpInfo	�����ip��Ϣ����ʽ"ip|port;ip|port;"
@param [in] maxLen			xmlOutput����
@param [out] xmlOutput		xml���
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<serverIp>10.36.65.112</serverIp>
<serverPort>20000</serverPort>
</root>
@endverbatim
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_VideoSetup(t_uint32 realHandle, t_int32 timeout, char *clientIpInfo, char *xmlOutput, t_uint32 maxLen);

/**
@brief ͬ��rtsp Play ��ؽӿ� VTDU_SC_SeekPlay
@param [in] realHandle		���ž��
@param [in] timeout			��ʱʱ��
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_VideoPlay(t_uint32 realHandle, t_int32 timeout);

/**
@brief ͬ��rtsp Play ��ؽӿ� VTDU_SC_SeekPlay
@param [in] realHandle		���ž��
@param [in] timeout			��ʱʱ��
@return						200 �ɹ�,��������������ĵ� 
@remarks					���Ų�������ͣ
@see 
*/
DLIB_API t_int32 VTDU_SC_VideoPlayAndPause(t_uint32 realHandle, t_int32 timeout);

/**
@brief ͬ��¼���϶�,������ŵ�ʱ��Ҳ��Ҫ��range �� scale����ʹ������ӿ�
@param [in] realHandle		���ž��
@param [in] timeout			��ʱʱ��
@param [in] range			��λλ��,��ʱ���϶���ʽ:clock=19000101T000000Z-�����ļ���С�϶���ʽ:byte=12333-
@param [in] scale			�����ٶ� 
@return						200 �ɹ�,��������������ĵ�   
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_SeekPlay(t_uint32 realHandle, t_int32 timeout, char *range, t_float32 scale);

/**
@brief ͬ��¼����ͣ
@param [in] realHandle		���ž��
@param [in] timeout			��ʱʱ��
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_VideoPause(t_uint32 realHandle, t_int32 timeout);

/**
@brief ͬ����Ƶ�ر�
@param [in] realHandle		���ž��
@param [in] timeout			��ʱʱ��
@return						200 �ɹ�,��������������ĵ�  
@remarks
@see 
*/
DLIB_API t_int32 VTDU_SC_Stop(t_uint32 realhandle, t_int32 timeout);

/**
@brief ͬ�������л�        
@param [in] timeout			��ʱʱ��
@param [in] chnCode			ͨ��code
@param [in] domainId		�豸��id
@param [in] streamType		�������ͣ�0�������� 1������
@return						200 �ɹ�,��������������ĵ�  
@remarks					�����㶫����ʹ��
@see 
*/
DLIB_API t_int32 VTDU_SC_StreamChange(t_uint32 vtduSession, t_int32 timeout, char *chnCode, char *domainId, t_int32 streamType);


/** @} */

/** @} */

#ifdef __cplusplus
}
#endif


#endif
