/**
 * Copyright (c) 2014, �㽭��ϵͳ�������޹�˾ All rights reserved.
 * \file		dmu_sdk.h
 * \brief		dmu_sdk
 * \author		24997
 * \date		2014��12��19��
 * \note		DMU SDK �ӿ�
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
* @defgroup DMU_SDK����
* @{
*/

#pragma region ͨ�ù���



/**
* @defgroup DMU_SDKϵͳ
* @{
*/

/**
@brief DMU_SDK��ʼ��
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_Init();


/**
@brief DMU_SDK��ʼ��,��������Ѿ�����applicationBase�ĳ������
@return 
@remarks
@see DMU_SC_InitNoApp
*/
DLIB_API t_int32 DMU_SC_InitNoApp();

/**
@brief DMU_SDK����ʼ��
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_Cleanup();

/** @} */

/**
* @defgroup DMU_SDK���ӷ���
* @{
*/

/**
@brief ����DMU����
@param [in]  timeout		��ʱʱ��
@param [in]  cmusession		CMU��½���
@param [in]  ipinfo		    DMU�����ip��Ϣ
@param [in]  svrdomid		DMU�������id
@param [in]  serverid		DMU����id
@param [out] outxml			������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<handle></handle>		���ӳɹ����صľ��
</root>
@endverbatim
@param [in]  maxlen			��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_AC_Connect(t_uint32 cmusession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
@brief �û���֤����DMU����
@param [in]  timeout		��ʱʱ��
@param [in]  usersession	�û���֤
@param [in]  ipinfo		    DMU�����ip��Ϣ
@param [in]  svrdomid		DMU�������id
@param [in]  serverid		DMU����id
@param [out] outxml			������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<handle></handle>		���ӳɹ����صľ��
</root>
@endverbatim
@param [in]  maxlen			��Ϣ��󳤶�
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_AC_ConnectNoCmu(t_uint32 usersession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
* @defgroup DMU_SDKͬ������
* @{
*/
/**
@brief ͬ������dmu
@param [in] cmuLoginHandle	cmu��֤session
@param [in] timeout			��ʱʱ��
@param [in] ipInfo			dmu����ip��Ϣ
@param [in] svrDomId		������id
@param [in] svrId			����id
@param [in] maxLen			xmlOutput����
@param [out] xmlOutput		xml���
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<dmusession>2</dmusession>
</root>
@endverbatim
@return						200 �ɹ�,��������������ĵ� 
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_Connect(t_uint32 cmuLoginHandle, t_int32 timeout, char *ipInfo, char *svrDomId, t_int32 svrId, char *outxml, t_uint32 maxlen);


/**
@brief �Ͽ�DMU����
@param [in]  session		���Ӿ��
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_Disconn(t_uint32 session);

/** @} */

/**
* @defgroup DMU_SDK�ص�����
* @{
*/

/**
@brief ��Ϣ�ص�����
@param [in] session		���Ӿ��
@param [in] data		��Ϣ����
@param [in] bufSize	    ���ݳ���
@param [in] pUser		�û��Զ�������
@return 
@remarks
@see 
*/
typedef t_int32 (*fIbpDmuMsgCallBack)(t_uint32 session, char *data, t_uint32 bufSize, void* pUser);

/**
@brief ������Ϣ�ص�����
@param [in] session		���Ӿ��
@param [in] cb			�ص�����
@param [in] pUser		�û�����
@return 
@remarks �ص���Ϣʾ��
@verbatim
����online��Ϣ֪ͨ
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="DMU" type="onlineNotify" cmd="onlineNotify" sequence="0" length="0">
	<server 
		servername="" 			��������
		session="" 				������
		status="" 				������״̬
	/>
</root>
@endverbatim
@verbatim
����master����֪ͨ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="reportMasterUpdate" sequence="" session="0">
	<domid></domid>				��ID
	<modulename></modulename>	ģ������
</root>
@endverbatim
@verbatim
�澯����֪ͨ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="alarmData" sequence="">
	<item
		domid=""				��ID
		devcode=""				�豸����
		devname=""				�豸����
		subdevcode=""			���豸����
		name=""					���豸����
		chncode=""				��Դ��ͨ������
		chnname=""				��Դ��ͨ������
		chnidx=""				��Դ��ͨ������
		type=""					�澯����
		subtype=""				�澯������
		status=""				״̬
		level=""				�澯�ȼ� 0 �� 1 ���� 2 ��Ҫ 3 һ�� 4 ��Ҫ 5��ͨ
		alarmtime=""			�澯�ϱ�ʱ��
		msgtxt=""				��Ϣ����
		val=""					ֵ
		unit=""					��λ
		orgpath=""				��֯�豸·��
		title=""				��֯�豸·����
		longitude=""            ����(��λ�ǰ����֮�ȣ���Χ0-360��)
		latitude=""             γ��(��λ�ǰ����֮�ȣ���Χ0-180��)
		phonedomid=""			������
		phonecode=""			��������
		phonenum=""				��������
		phonepass=""			��������
	/>
</root>
@endverbatim
@verbatim
ʵʱ����֪ͨ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="realData" sequence="">
	<item
		domid=""				��ID
		devcode=""				�豸����
		subdevcode=""			���豸����
		chncode=""				ͨ������
		chnidx=""				ͨ������
		val=""					ֵ
		unit=""					��λ
		desc=""					����
		time=""					ʱ��
		isalarm=""				�Ƿ�澯
		type=""					�澯����
		level=""				�澯�ȼ�
		orgpath=""			
		title=""
		phonedomid=""			������
		phonecode=""			��������
		phonenum=""				��������
		phonepass=""			��������

		intparam1=""			gps��λ����
		intparam2=""			gps����״̬(true �ã�false ��)
		intparam3=""			gps��λ״̬(true ��λ��false ����λ)
		strparam1=""
		strparam2=""
		strparam3=""
	>
		<expand					    pgs��չ��Ϣ
			longitude=""			����(��λ�ǰ����֮�ȣ���Χ0-360��)
			latitude=""				γ��(��λ�ǰ����֮�ȣ���Χ0-180��)
			height=""				�߶�(��)
			angle=""				�����(��������Ϊԭ�㣬˳ʱ��Ϊ��)
			speed=""				�ٶ�(��λ�Ǻ��speed/1000*1.852����/Сʱ)
		/>
	</item>
</root>
@endverbatim
@verbatim
�޸�Ԥ�õ�֪ͨ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="modifyPrepointNotify" sequence="">
	<domid></domid>				��ID
	<devcode></devcode>			�豸����
	<index></index>				Ԥ�õ��
	<name></name>				����
	<operate></operate>			��������
	<userid></userid>			�û�ID
	<username></username>		�û�����
	<level>1</level>			�û�����
	<updatetime></updatetime>	����ʱ��
</root>
@endverbatim
@verbatim
�޸�OSD֪ͨ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="modifyOSDNotify" sequence="">
	<opt 
		domid="" 				��ID
		devcode="" 				�豸����
		userid="" 				�û�ID
		operate="" 				��������
		count=""				��������
	>
		<info 
			type="" 			�޸����� 1 �޸�OSD��ǩ 2 �޸�OSDʱ��
			pointx="" 			ԭ��X����
			pointy="" 			ԭ��Y����
			width="" 			���
			length="" 			�߶�
			rgb="" 				RGBֵ
			alpha="" 			ALPHAֵ
			title=""			��ǩ����
		/>
	</opt>
</root>
@endverbatim
@verbatim
��̨��ռ֪ͨ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="ptzArrange" sequence="">
	<domid></domid>				��ID
	<chncode></chncode>			ͨ������
	<userid></userid>			�û�ID
	<username>0</username>		�û��� 
	<level></level>				�û�����
	<department></department>	����
	<locktime></locktime>		����ʱ��
</root>
@endverbatim
@verbatim
��ѯ�������豸���֪ͨ
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
@brief ���ûص��澯���ݻ�������
@param [in] session		���Ӿ��
@param [in] num			�澯����(Ĭ������100��)
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_SetAlarmDataCfg(t_uint32 session, t_int32 num);

/**
@brief ��ѯ���»ص��澯����
@param [in] session		���Ӿ��
@param [out] outxml		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		domid=""			��ID
		devcode=""			�豸����
		devname=""			�豸����
		subdevcode=""		���豸����
		name=""				���豸����
		chncode=""			��Դ��ͨ������
		chnname=""			��Դ��ͨ������
		chnidx=""			��Դ��ͨ������
		type=""				�澯����
		subtype=""			�澯������
		status=""			״̬
		level=""			�澯�ȼ�
		alarmtime=""		�澯�ϱ�ʱ��
		msgtxt=""			��Ϣ����
		val=""				ֵ
		unit=""				��λ
		orgpath=""			��֯�豸·��
		title=""			��֯�豸·����
	/>
</root>
@endverbatim
@param [in]  maxlen		��Ϣ��󳤶�
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_QueryNewAlarmData(t_uint32 session, char *outxml, t_uint32 maxlen);

/**
@brief ���ûص����豸�����ߵĸ澯��Ϣ
@param [in] session		���Ӿ��
@param [in] flag		�ص���ʶ 0 Ĭ�ϲ��ص� 1 �ص�
@return
@remarks �����ʵʱ�ص��澯��Ϣ������ô˽ӿ�
@see 
*/
DLIB_API t_int32 DMU_SC_OpenCbAlarmData(t_uint32 session, t_int32 flag);

/** @} */

/**
* @defgroup DMU_SDK�澯����
* @{
*/

/**
@brief ���ö���ȫ���澯��ʵʱ���ݱ�ʶ
@param [in] session				���Ӿ��
@param [in] subscribeflag		�澯ȫ�����ı�ʶ 0 Ĭ�Ϸ� 1 ��
@param [in] distributeflag		�ַ��豸��Ȩ��ʶ 0 �� 1 Ĭ����
@return
@remarks 1��Ĭ��ʱ��������ô˽ӿ� 2������Ҫ�����ӳɹ�����������
@see 
*/
DLIB_API t_int32 DMU_SC_SetSubAllAlarm(t_uint32 session, t_int32 subscribeflag = 0, t_int32 distributeflag = 1);

/**
@brief �����澯��ʵʱ���ݶ���
@param [in] session		���Ӿ��
@param [in] timeout		��ʱʱ��
@param [in] info		����xml
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt
		type=""			������ 0 �澯���� 1 ʵʱ���ݶ��� 2pgs��Ϣ 
		level=""		���и澯�ȼ� -1 ��ʾ���ĸ澯 1~5���ĵȼ�ͳһ�޸�λ�õȼ�
	>
		<item 
			operate=""	��������
			flag=""		0�����ľ�����豸��1��������֯��2:����ͨ��
			devcode=""	�豸����(Ϊ��֯ʱ����д·��)
			domid=""	�豸��ID
			type=""		�澯���� -1 ��������
			level=""	�澯�ȼ� 5 ���ڵ��ڸõȼ��ĸ澯�������յ�
		/>
		....

	</opt>
</root>
@endverbatim
@return
@remarks ������֯���Ƕ�����֯�����������豸
@see 
*/
DLIB_API t_int32 DMU_SC_OptSubscribe(t_uint32 session, t_int32 timeout, char *info);


/**
@brief �����澯��ʵʱ���ݶ��ģ������û���
@param [in] session		���Ӿ��
@param [in] timeout		��ʱʱ��
@param [in] info		����xml
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt
		type=""			������ 0 �澯���� 1 ʵʱ���ݶ��� 2pgs��Ϣ 3 �����û��澯
		level=""		���и澯�ȼ� -1 ��ʾ���ĸ澯 1~5���ĵȼ�ͳһ�޸�Ϊ�õȼ�
		userid=""       �����û���useid
	>
		<item 
			operate=""	��������
			flag=""		0�����ľ�����豸��1��������֯; 2 ����ͨ��; 
			flaguser=""	0 �����û� 1 �����û���֯
			devcode=""  �豸���루������֯ʱ����֯·����
			userid=""	�������û�id(Ϊ��֯ʱ�������orgpath��д·��)
			orgpath=""  �������û���֯·��
			domid=""	��ID
			type=""		�澯���� -1 ��������
			level=""	�澯�ȼ� 5 ���ڵ��ڸõȼ��ĸ澯�������յ�
		/>
		......
	</opt>
</root>
@endverbatim
@return
@remarks ������֯���Ƕ�����֯�����������û�
@see 
*/
DLIB_API t_int32 DMU_SC_OptSubscribeUser(t_uint32 session, t_int32 timeout, char *info);

/**
@brief ��ѯ�û��澯��ʵʱ���ݶ���
@param [in] session		���Ӿ��
@param [in] timeout		��ʱʱ��
@param [in] subtype		������ 0 �澯���� 1 ʵʱ���ݶ��� 2 �豸GPS�澯 3 �û��澯
@param [in] userid		�����û�userid��userId=0 �������û���userId!=0��ָ���û���
@param [out] outxml		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		userid=""		�û�ID
		devcode=""		�豸����
		domid=""		�豸��ID
		type=""			�澯����
		level=""		�澯�ȼ�
	/>
</root>
@endverbatim
@param [in]  maxlen		��Ϣ��󳤶�
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_QuerySubscribe(t_uint32 session, t_int32 timeout, t_int32 subtype, t_int32 userid, char *outxml, t_uint32 maxlen);


/**
@brief ��ѯ�û��澯��ʵʱ���ݶ���
@param [in] session		���Ӿ��
@param [in] timeout		��ʱʱ��
@param [in] subtype		������ 0 �澯���� 1 ʵʱ���ݶ���
@param [out] outxml		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		userid=""		�û�ID(���ﶩ�Ĳ�ѯ)��userId=0 �������û���userId!=0��ָ���û���
		devcode=""		�豸����
		domid=""		�豸��ID
		type=""			�澯����
		level=""		�澯�ȼ�
	/>
</root>
@endverbatim
@param [in]  maxlen		��Ϣ��󳤶�
@return
@remarks
@see 
*/
//DLIB_API t_int32 DMU_SC_QueryUserSubscribe(t_uint32 session, t_int32 timeout, t_int32 subtype, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK��ƵOSD��Ϣ
* @{
*/

/**
@brief ����OSD��Ϣ
@param [in] session		���Ӿ��
@param [in] timeout		��ʱʱ��
@param [in] info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt 
		domid=""		��ID
		devcode=""		�豸����
		operate=""		��������
		count=""		OSD����
	>
		<item 
			type=""		OSD�������� 1 ����OSD 2 ʱ��OSD
			pointx=""	ԭ��X����
			pointy=""	ԭ��Y����
			width=""	���
			length=""	����
			rgb=""		RGBֵ
			alapha=""	ALAPHAֵ
			title=""	��ǩ
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
@brief ��ȡOSD��Ϣ
@param [in]  session		���Ӿ��
@param [in]  timeout		��ʱʱ��
@param [in]  domainid		�豸��id
@param [in]  chncode		ͨ������
@param [in]  idx			��Ϣ���� 0 ȫ�� 1 ����OSD 2 ʱ��OSD
@param [out] outxml			������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item type="" pointx="" pointy="" width="" length="" rgb="" alapha="" title="" />
</root>
@endverbatim
@param [in]  maxlen			��Ϣ��󳤶�
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_QueryOsdInfo(t_uint32 session, t_int32 timeout, char* domainid, char* chncode, t_int32 idx, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDKԤ�õ�
* @{
*/

/**
@brief ����Ԥ�õ�
@param [in] session			���Ӿ��
@param [in] timeout			��ʱʱ��
@param [in] info			������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<srcdomid></srcdomid>	Դ������ID
	<domid></domid>			�豸��ID
	<devcode></devcode>		ͨ���豸����
	<chnidx></chnidx>		ͨ�����(����)
	<index></index>			Ԥ�õ�ID
	<name></name>			Ԥ�õ�����
	<flag></flag>			�Ƿ�ΪĬ��Ԥ�õ㣬1 Ĭ��Ԥ�õ㣬0 ��Ĭ��Ԥ�õ�
	<interval></interval>	flagΪ1ʱ���豸�ع�Ĭ��Ԥ�õ�ʱ����
	<operate></operate>		�������� 0 ��ӣ�1�޸ģ�2ɾ��
</root>
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptPrepoint(t_uint32 session, t_int32 timeout, char *info);

/**
@brief ��ȡԤ�õ�
@param [in] session			���Ӿ��
@param [in] timeout			��ʱʱ��
@param [in] domainid		�豸��id
@param [in] chncode			ͨ������
@param [out] outxml			������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<count></count>			����
	<item 
		index=""			Ԥ�õ���
		name=""				Ԥ�õ�����
		flag=""				��־��1 Ĭ��Ԥ�õ㣬0 ��Ĭ��Ԥ�õ�
		revered=""			����
	/>
</root>
@endverbatim
@param [in]  maxlen			��Ϣ��󳤶�
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_QueryPrepoint(t_uint32 session, t_int32 timeout, char* domainid, char* chncode, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK��̨����
* @{
*/

/**
@brief ��̨����
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>				��ID
	<chncode></chncode>			ͨ������
	<stop></stop>				ֹͣλ��1��ʾֹͣ��0��ʾ����
	<cmd></cmd>					��������
	<intparam1></intparam1>		����1
	<intparam2></intparam2>		����2
	<intparam3></intparam3>		����3
	<intparam4></intparam4>		����4
	<intparam5></intparam5>		����5
	<intparam6></intparam6>		����6
	<intparam7></intparam7>		����7
	<intparam8></intparam8>		����8
	<strparam1></strparam1>		�ַ�������1
	<strparam2></strparam2>		�ַ�������2
</root>
@endverbatim
@param [out] outxml				��������Ϣ
@param [in]  maxlen				��Ϣ��󳤶�
@return
@remarks 
@verbatim
���������
	0 ePTZCmd_Unknown,			δ֪
	1 ePTZCmd_Up,               ���� 
	2 ePTZCmd_Down,             ����
	3 ePTZCmd_Left,		        ����
	4 ePTZCmd_Right,		    ����
	5 ePTZCmd_LeftUp,           ���� 
	6 ePTZCmd_RightUp,          ���� 
	7 ePTZCmd_LeftDown,         ���� 
	8 ePTZCmd_RightDown,        ���� 
	9 ePTZCmd_GotoPreset,       ת��Ԥ�õ� 
	10 ePTZCmd_SetPreset,       ����Ԥ�õ�
	11 ePTZCmd_ClearPreset,     ���Ԥ�õ�
	12 ePTZCmd_QuickOrient,     ��ά���ٶ�λ 
	13 ePTZCmd_Zoom_Tele,       �������� 
	14 ePTZCmd_Zoom_Wide,       ������Զ 
	15 ePTZCmd_Focus_Near,      ������� 
	16 ePTZCmd_Focus_Far,       �����Զ 
	17 ePTZCmd_Iris_Auto,       ��Ȧ�Զ����� 
	18 ePTZCmd_Iris_Large,      ��Ȧ���� 
	19 ePTZCmd_Iris_Small,      ��Ȧ��С
	20 ePTZCmd_Aux_On,          ��������
	21 ePTZCmd_Aux_Off,         ����ֹͣ
	22 ePTZCmd_Light_On ,       �ƹ⿪�� 
	23 ePTZCmd_Light_Off,       �ƹ�ر�
	24 ePTZCmd_StartTour,       ��ʼ�Զ�Ѳ��
	25 ePTZCmd_StopTour,        ֹͣ�Զ�Ѳ�� 
	26 ePTZCmd_AutoPan_On,      ˮƽѲ������ 
	27 ePTZCmd_AutoPan_Off      ˮƽѲ��ֹͣ 
	39 ePTZCmd_IOControl		IO״̬����(�����������)
	40 ePTZCmd_LockPtz			��̨�ӽ�������(stop:1 ���� 0 ����)
��Բ�ͬ�������˵����δ˵�������������Ĭ�ϣ�
1��3D��λ����
	intparam1					����X����
	intparam2					�׵�X����
	intparam3					����Y����
	intparam4					�׵�Y����
2��Ԥ�õ�����
	intparam2					Ԥ�õ�����
3����������
	intparam1					��ֱ�ٶ�
	intparam2					ˮƽ�ٶ�
@endverbatim
@see 
*/
DLIB_API t_int32 DMU_SC_PTZControl(t_uint32 session, t_int32 timeout, char *info, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK��ѯ�澯����
* @{
*/

/**
@brief ��ѯ��ʷ�澯��Ϣ
@param [in]  session			���Ӿ��
@param [in]  timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<srcdomid />		������ID
	<starttime />		��ʼʱ��
	<endtime />			����ʱ��
	<type />			�澯���� -1 ��ѯȫ�� ������ѯָ��
	<domid />			�豸��ID
	<devcode />			ͨ���豸���룬����"'chn0','chn1','chn2'"
	<chnidx />			ͨ�����
	<domdevcode />		�豸��ID+�豸���룬����"'chn0','chn1','chn2'@domid1; 'chn0','chn1','chn2'@domid2"
	<size />			ÿҳ��С
	<curpage />			��ѯ�ڼ�ҳ
	<orgcode />		    ��֯����(orgcode��devcodeֻ�ܴ���һ��)
</root>
@endverbatim
@param [out] outxml				������Ϣ

// ע��devcode��������豸�澯��devcode�����豸����
// �����ͨ���澯��devcode����ͨ������

@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>				����
	<item 
		id=""					�澯��¼ID
		domid=""				��ID
		devcode=""				�豸����
		devname=""				�豸����
		chnidx=""				ͨ������
		devtype=""				�豸����
		type=""					�澯����
		status=""				״̬
		level=""				�澯�ȼ�
		alarmtime=""			�澯ʱ��
		length=""				���ݳ���
		msgtxt=""				��Ϣ�ı�
		confirmor=""			ȷ����
		confirmtime=""			ȷ��ʱ��
		confirmmsg=""			ȷ����Ϣ
		confirmstatus=""		ȷ��״̬
	/>
	...
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryHistoryAlarmInfo(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief �����澯ȷ����Ϣ
@param [in]  session			���Ӿ��
@param [in]  timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<confirmtime></confirmtime>	�澯��Ϣ����(����澯ʱ��)
	<item 
		id=""					�澯��¼ID
		confirmmsg=""			ȷ����Ϣ
		confirmstatus=""		ȷ��״̬ 0 δȷ�� 1 ��ȷ��
	/>
</root>
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptAlarmConfirm(t_uint32 session, t_int32 timeout, char *info);


/**
@brief ���������û��澯ȷ����Ϣ
@param [in]  session			���Ӿ��
@param [in]  timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total><total>                 		����
	<confirmmsg><confirmmsg>			ȷ���������
	<item
		revalarmusername=""				�����û�����
		revalarmuserid=""				�����û�id
		username=""						�澯�û����ƣ������DB��
		userid=""						�澯�û�id
		domid=""                        �澯��ID
		devcode=""                      �澯�豸����
		chncode=""						�澯ͨ������
		orgpath=""                      ��֯·���������DB��
		devtype=""                      �豸����
		type=""							�澯����
		guid=""							�澯guid                     
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
@brief ��ѯ�����澯��Ϣ
@param [in]  session                       ���Ӿ��
@param [in]  timeout                      ��ʱʱ��
@param [in]    info                                     ������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
         <srcdomid />             ������ID
         <starttime />            ��ʼʱ�䣺2016-05-10 00:00:00
         <endtime />              ����ʱ��
         <type />                 �澯���� -1 ��ѯȫ�� ������ѯָ��4,201
         <domid />                �豸��ID
         <status />               ״̬����ѯ�澯״̬,0��δ����1�Ǵ���
         <size />                 ÿҳ��С
         <curpage />              ��ѯ�ڼ�ҳ,1��ʾ��һҳ
		 <confirmstatus />        �澯�û�ȷ��״̬
		 <flaguser  />            1:subuserid���Ǹ澯�û���userid,��alarm_log�����Ѿ����͵ĸ澯״̬��0����ѯ�����û�subuserid�ĸ澯
		 <subuserid />            �����û�ID,���ݶ����û���ID���飬subuserid<=0 �Ͱ���ԭ�ȵ���ͨ��ѯ��subuserid>0���ݶ��Ĳ�ѯ
		 <devtype />              �豸���� -1 ��ѯȫ�� ������ѯָ�����֣���ʽ�磺27,111,102,301
		 <flag />                 0:�������ʱ��������ѯ��1��ѯ��������ȥ24Сʱ������
		 <flagtime />             0:���յȼ�ʱ�������ѯ��1�����յȼ������ѯ,2����ʱ�������ѯ��3����ʱ��ȼ�����    ��ע��Ĭ��ʱ�����򣬵ȼ���������
</root>
@endverbatim
@param [out] outxml                                  ������Ϣ

// ע��devcode��������豸�澯��devcode�����豸����
// �����ͨ���澯��devcode����ͨ������

@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
         <total></total>                                    ����
         <item 
                    id=""                                   �澯��¼ID
                   domid=""                                ��ID
                   devcode=""                              �豸����
                   devname=""                              �豸����
                   chnidx=""                               ͨ������
                   devtype=""                              �豸����
                   type=""                                 �澯����
                   status=""                               ״̬
                   level=""                                �澯�ȼ�
                   alarmtime=""                            �澯ʱ��
                   length=""                               ���ݳ���
                   msgtxt=""                               ��Ϣ�ı�
                   confirmor=""                            ȷ����
                   confirmtime=""                          ȷ��ʱ��
                   confirmmsg=""                           ȷ����Ϣ
                   comfirmstatus=""                        ȷ��״̬
				   guid=""                                 �澯guid
				   alarmstatus=""                          �澯״̬ȷ��   
         />
</root>
@endverbatim
@param [in]  maxlen                                 ��Ϣ��󳤶�
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryAlarmCaseInfo(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);


/**
@brief ��ѯ��ʷʵʱ������Ϣ
@param [in]  session			���Ӿ��
@param [in]  timeout			��ʱʱ��
@param [in]  inxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<srcdomid />		������ID
	<starttime />		��ʼʱ��
	<endtime />			����ʱ��
	<domid />			�豸��ID
	<devcode />			ͨ���豸���룬����"'chn0';'chn1';'chn2'"
	<size />			ÿҳ��С
	<curpage />			��ѯ�ڼ�ҳ
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>				����
	<item 
		domid=""				��ID
		devcode=""				�豸����
		devname=""				�豸����
		devtype=""				�豸����
		time=""					�ϱ�ʱ��
		val=""					ʵʱ����ֵ
		unit=""					ʵʱ���ݵ�λ
	/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryHistoryRealData(t_uint32 session, t_int32 timeout, char* inxml, char* outxml, t_uint32 maxlen);


/**
@brief ��ѯ��ʷʵʱ���ݵ�ƽ��ֵ
@param [in]  session			���Ӿ��
@param [in]  timeout			��ʱʱ��
@param [in]  inxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<starttime />		��ʼʱ��
	<endtime />			����ʱ��
	<domid />			�豸��ID
	<devcode />			�豸����
	<interval />		�����ʱ�䣬��λ��
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		domid=""				��ID
		devcode=""				�豸����
		devname=""				�豸����
		devtype=""				�豸����
		starttime=""			ʱ��ο�ʼʱ��
		endtime=""			    ʱ��ν���ʱ��
		val=""					ʱ��ε�ƽ��ֵ
		unit=""					ʵʱ���ݵ�λ
	/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryHistoryRealData_AVG(t_uint32 session, t_int32 timeout, char* inxml, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK�澯�ȼ�
* @{
*/

/**
@brief �����澯���ȼ�
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt 
		operate=""				��������
	>
		<item 
			devcode=""			�豸����
			domid=""			��ID
			type=""				�澯����
			level=""			�澯�ȼ�
			updatetime=""		����ʱ��
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
@brief ��ѯ�澯���ȼ�
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] alarmcategory		�澯������ 0��ʾ�Ǵ�������
@param [in] info				�Ǵ�������
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		devcode=""				�豸����
		domid=""				��ID
		type=""					�澯����
		level=""				�澯�ȼ�(����)
		udatetime=""			����ʱ��(����)
	/>
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		devcode=""				�豸����
		domid=""				��ID
		type=""					�澯����
		level=""				�澯�ȼ�
		udatetime=""			����ʱ��
	/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryAlarmPriority( t_uint32 session, t_int32 timeout, t_int32 alarmcategory, char* info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK�������
* @{
*/

/**
@brief �����澯��ʵʱ���ݱ������
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt 
		operate=""				�������� 0 ���� 1 �޸� 2 ɾ��
	>
		<item 
			domId=""			�豸��
			devcode=""			�豸���루Ϊ�ձ�ʾ�����豸��
			type=""				�澯���� �������� ���� 1 ��һ�ָ澯����һ��item��
			interval=""			���ʱ�䣨������ظ��澯������
			autodisappear=""	�澯�Զ���ʧʱ�䣨-1��ʾ���Զ���ʧ������ģ���Զ���ʧ��
			stop=""				����澯ֹͣ ��ʱ����
			enable==""			�Ƿ�����
			msgtxt=""			�澯����
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
@brief ��ѯ�澯��ʵʱ���ݱ������
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<category></category>		���                          
	<size />					ÿҳ��С
	<curpage />					��ѯ�ڼ�ҳ
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>				����
	<item domId="" devcode="" type="" interval="" autodisappear="" stop="" enable=="" msgtxt="" />
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return
@remarks
@see DMU_SC_OptSaveStrategy
*/
DLIB_API t_int32 DMU_SC_QuerySaveStrategy( t_uint32 session, t_int32 timeout, char* info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK��������
* @{
*/

/**
@brief ��������
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] domid				��ID
@param [in] scsid				����ID
@param [in] scsdevid			�����豸ID
@param [in] scslabel			��� 0 �ʲ� 1 ��Դ
@param [in] scsopt				���� �� 1 ���� 0 �ص�
@param [in] scspram				�����������û��Զ���
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_ScsControl(t_uint32 session, t_int32 timeout, char *domid, char *scsid, char *scsdevid, t_int32 scslabel, t_int32 scsopt, char *scspram);

/**
@brief ��ѯ������Ϣ
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] domid				��ID
@param [in] scsid				����ID
@param [in] scsdevid			�����豸ID
@param [in] scslabel			��� 0 �ʲ� 1 ��Դ
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<id/>						SCS�ʲ�����ԴID
	<res/>0						��ȡ�ɹ� 1 ��ȡʧ��
	<time/>						ʱ��
	<devtype/>					�ʲ���Դ����
	<val/>						ֵ
	<desc/>						����
	<errmsg/>
	<errcode/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return  ������鿴 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryScsInfo(t_uint32 session, t_int32 timeout, char *domid, char *scsid, char *scsdevid, t_int32 scslabel, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯ���������޷�ֵ
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] domainid			��ID
@param [in] resourceid			��ԴID
@param [in] info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<alarmtype />                �澯���ͣ����
</root>
@verbatim
@param [out] outxml				 ������Ϣ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<alarmtype />                �澯����
	<x_top1 />				     ����
	<y_but1 />					 ����
	<width_top2 />				 �������
	<height_but2 />				 �߶�����
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return  ������鿴 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryScsAlarmCfg( t_uint32 session, t_int32 timeout, char* domainid, char* resourceid,char* info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK�豸״̬
* @{
*/

/**
@brief ��ѯ�豸״̬
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��ѯ���豸
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="CLIENT">
<device domid="2000" devcode="123" status="0"/>
...
</root>
@endverbatim
@param [out] outxml				���ص��豸״̬
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="CLIENT">
<device domid="2000" devcode="123" status="1"/> 1:���� 2:����
...
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryDevStatus(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK������ͼ
* @{
*/

/**
@brief ��ȡ�����豸������
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] domid				��ID
@param [in] chnCode				ͨ��ID
@param [in] type				������ʶ����һ��������
0: NET_DEV_CAP_SEQPOWER     // ��Դʱ�������� 
1: NET_ENCODE_CFG_CAPS      // �豸�������ö�Ӧ���� 
2: NET_VIDEOIN_FISHEYE_CAPS // �������� 
3: NET_THERMO_GRAPHY_CAPS	// �ȳ������� 
4: NET_RADIOMETRY_CAPS	    // �ȳ���������� 
@param [out] outxml				������Ϣ
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
@param [in]  maxlen				��Ϣ��󳤶�
@return  ������鿴 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_GetThermoDevCaps(t_uint32 session, t_int32 timeout,char* domId,char* chnCode,int type,char* outxml, t_uint32 maxlen);


/**
@brief ��ȡ�����豸����Ϣ
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] domid				��ID
@param [in] chnCode				ͨ��ID
@param [in] type				��ѯ��һ����Ϣ
9: NET_QUERY_DEV_THERMO_GRAPHY_PRESET		// ��ѯ�ȳ���Ԥ����Ϣ		
10: NET_QUERY_DEV_THERMO_GRAPHY_OPTREGION	// ��ѯ�ȳ����Ż�������Ϣ	
11: NET_QUERY_DEV_THERMO_GRAPHY_EXTSYSINFO	// ��ѯ�ȳ����ⲿϵͳ��Ϣ	
12: NET_QUERY_DEV_RADIOMETRY_POINT_TEMPER	// ��ѯ���µ�Ĳ���ֵ		
13:NET_QUERY_DEV_RADIOMETRY_TEMPER 			// ��ѯ�������¶ȵĲ���ֵ
@param [in] inxml				���ڲ��µ�Ͳ������Ĳ�ѯ������Ҫ�����Ĳ���
���µ�
<root>
<x>200</x>
<y>120</y>
</root>
������
<root>
<presetid>1</presetid>
<ruleid>2</ruleid>
<metertype>3</metertype>
<itemname>4</itemname>
</root>
@param [out] outxml				������Ϣ
���·��ؽ��
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
@param [in]  maxlen				��Ϣ��󳤶�
@return  ������鿴 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryThermoDevInfo(t_uint32 session, t_int32 timeout,char* domId,char* chnCode,int type,char* inxml,char* outxml, t_uint32 maxlen);


/**
@brief ��ȡ�����豸����Ϣ
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] domid				��ID
@param [in] chnCode				ͨ��ID
@param [in] type				��������
0: NET_CTRL_DEV_THERMO_GRAPHY_ENSHUTTER, // �ȳ��񿪹�
1: NET_CTRL_DEV_RADIOMETRY_SETOSDMARK,	 // ���ò������osdΪ����
@param [in] inxml				��Ҫ�����Ĳ���
�ȳ��񿪹�
<root>
<enable>1</enable>
</root>
 ���ò������osdΪ����
<root>
<presetid>1</presetid>
<ruleid>2</ruleid>
<metertype>3</metertype>
<itemname>4</itemname>
</root>
@param [out] outxml				������Ϣ


@param [in]  maxlen				��Ϣ��󳤶�
@return  ������鿴 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_ControlThermoDevEx(t_uint32 session, t_int32 timeout,char* domId,char* chnCode,int type,char* inxml);


/**
@brief ��ȡ�����豸������
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] domid				��ID
@param [in] chnCode				ͨ��ID
@param [in] type				���ñ�ʶ����һ�����ã�
0: CFG_CMD_THERMO_GRAPHY	// �ȳ�������
1: CFG_CMD_THERMOMETRY_RULE	// �ȳ����������
2: CFG_CMD_TEMP_STATISTICS	// �¶�ͳ������
3: CFG_CMD_THERMOMETRY		// �ȳ����������
@param [out] outxml				������Ϣ

@param [in]  maxlen				��Ϣ��󳤶�
@return  ������鿴 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_GetThermoDevConfig(t_uint32 session, t_int32 timeout,char* domId,char* chnCode,int type,char* outxml, t_uint32 maxlen);

/**
@brief ��ȡ�����豸������
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] domid				ͨ������
@param [in] chnCode				ͨ������
@param [in] type				���ñ�ʶ����һ�����ã�
0: CFG_CMD_THERMO_GRAPHY	// �ȳ�������
1: CFG_CMD_THERMOMETRY_RULE	// �ȳ����������
2: CFG_CMD_TEMP_STATISTICS	// �¶�ͳ������
3: CFG_CMD_THERMOMETRY		// �ȳ����������
@param [in] isSaveDB			�Ƿ񱣴浽���ݿ�
@param [in] inxml				������Ϣ

@return  ������鿴 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_SetThermoDevConfig(t_uint32 session, t_int32 timeout,
	char* domId,char* chnCode,int type,int isSaveDB,char* inxml);


/**
@brief ����һ���豸����ͨ����Ԥ��λ����ѯ���¶���
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] qryFlg				��ѯ��ʶ
1: ����eleDom+eleCode,��ѯ
2: ����chnDom+chnCode,��ѯ
3: ����eleDom+eleCode+chnDom+chnCode+prepointId,��ѯ
@param [in] eleDom				һ���豸����
@param [in] eleCode				һ���豸�ı���
@param [in] chnDom				ͨ������
@param [in] chnCode				ͨ���ı���
@param [in] prepointId			ͨ����Ԥ��λ
@param [out] outxml				������Ϣ
@param [in]  maxlen				��Ϣ��󳤶�
@return  ������鿴 IBP_Error.h
@remarks ���eleDom��eleCodeΪ���ַ���������ͨ����Ԥ��λ��ѯ
@see
*/
DLIB_API t_int32 DMU_SC_GetIrArea_ByElecDev_ChnPrepoint(t_uint32 session, t_int32 timeout,int qryFlag,char* eleDom,char* eleCode,
	char* chnDom,char* chnCode,int prepointId,char* outxml, t_uint32 maxlen);


/**
@brief ץȡ������ͼ
@param [in]  session			���Ӿ��
@param [in]  timeout			��ʱʱ��
@param [in]	 chnDom				ͨ������
@param [in]	 chnCode			ͨ���ı���
@param [out] outxml				������Ϣ
@param [in]  maxlen				��Ϣ��󳤶�
@return  ������鿴 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_FetchThermoGraphy(t_uint32 session, t_int32 timeout,char* chnDom,char* chnCode,char* outxml,t_uint32 maxlen);

/** @} */


/**
* @defgroup DMU_SDK������ͨ����Ϣ
* @{
*/

/**
@brief ��ѯ������ͨ����Ϣ
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��ѯ�Ľ�����
@verbatim
<root>
	<ip>1</ip>
	<port>1</port>
	<username>1</username>
	<password>1</password>
</root>
@endverbatim
@param [out] outxml				���صĽ�����ͨ����Ϣ
@verbatim
<root>
	<chn seq=xxx maxsplit=xxx />
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryDecorderChnInfo(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK��ʼ�������豸����
* @{
*/

/**
@brief ��ѯ���������豸
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��ѯ��IP��Χ(һ������)
@verbatim
<root>
	<startip>1</startip>
	<endip>1</endip>
	<searchtime>1</searchtime>
</root>
@endverbatim
@param [in] cb					�ص�����
@param [in] pUser				�û��Զ�������
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_StartSearchLanDev(t_uint32 session, t_int32 timeout,char* inxml);

/** @} */


/**
* @defgroup DMU_SDKֹͣ�������豸����
* @{
*/

/**
@brief ��ѯ���������豸
@param [in] session				���Ӿ��
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_StopSearchLanDev(t_uint32 session);

/** @} */


/**
* @defgroup DMU_SDK��ѯ�豸��Ϣ
* @{
*/

/**
@brief ��ѯ���������豸
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��ѯ�Ľ�����
@verbatim
<root>
	<device devtype="" loginname="" loginpwd="" ipaddr="" portdev="" />
</root>
@endverbatim
@param [out] outxml				���ص��豸��Ϣ
@verbatim
<root>
	<device ipaddr="" portdev="" errcode="" devcode="id" maxchn="16" manufid="1">
		<channel title="ͨ��1" devtype="22" manufid="1"/>	����ͨ����Ϣ
		<channel title="ͨ��2" devtype="22" manufid="1"/>	����ͨ����Ϣ
	</device>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryLanDevInfo(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK�ͻ��˸澯
* @{
*/
/**
@brief �ͻ�����dmu���Ϳͻ��˸澯
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��ѯ�Ľ�����
@verbatim
��DMU_SC_SetDmuMsg�еĸ澯����֪ͨ
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_SendClientAlarm(t_uint32 session, t_int32 timeout,char* inxml);

/**
@brief �ֻ��澯�ϱ���������Ŀ��
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��ѯ�Ľ�����
@param [out] outguid			�澯ID
@param [in]  maxlen				��Ϣ��󳤶�
@verbatim
��DMU_SC_SetDmuMsg�еĸ澯����֪ͨ
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_SendPhoneClientAlarm(t_uint32 session, t_int32 timeout,char* inxml,char* outguid,t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDKʵʱ����
* @{
*/
/**
@brief �ͻ�����dmu���Ϳͻ���ʵʱ����
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				gps��Ϣ
@verbatim
��DMU_SC_SetDmuMsg�е�ʵʱ����֪ͨ
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_SendClientRealData(t_uint32 session, t_int32 timeout,char* inxml);

/**
@brief ��ѯ�Ž���Ƭ��Ϣ
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��ѯ������
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
@param [out] outxml				��ѯ�Ŀ���Ϣ
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
@param [in] maxlen				��Ϣ��󳤶�
*/
DLIB_API t_int32 DMU_SC_QueryAcOwnerInfo(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/**
@brief �Ž�����Ϣ����
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��������
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<acowner userid="" domid="" username="" deptid="" deptname="" cardnum="" cardtype="" password="" startdate="" enddate="" doorpwd="" worktype=""/>
</root>
@endverbatim
@param [in] maxlen				��Ϣ��󳤶�
*/
DLIB_API t_int32 DMU_SC_OptAcOwnerInfo(t_uint32 session, t_int32 timeout,char* inxml,t_uint32 maxlen);

/**
@brief ��ѯ�Ž���־��Ϣ
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��ѯ������
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
	<orgcode></orgcode>		   ����֯�����ʱ�ű���Ϊ��
</root>
@endverbatim
@param [out] outxml				��ѯ����־��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<count></count>
	<item id="" domid="" doorcode=""  doorname="" doorindex="" devcode=""  cardnum=""  
	userid="" username="" time="" opentype="" result=""
	/>
</root>
@endverbatim
@param [in] maxlen				��Ϣ��󳤶�
*/
DLIB_API t_int32 DMU_SC_QueryAcLogInfo(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/**
@brief ��ѯ�Ž�Ȩ����Ϣ
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��ѯ������
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>
	<cardnum></cardnum>
	<startindex></startindex>
	<pagecount></pagecount>
</root>
@param [out] outxml				��ѯ���Ž�Ȩ����Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<count></count>
	<item domid="" cardnum="" devcode="" devname="" doorcode="" doorname="" doorindex="" recnum="" />
</root>
@endverbatim
@param [in] maxlen				��Ϣ��󳤶�
*/
DLIB_API t_int32 DMU_SC_QueryAcRightInfo(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/**
@brief �Ž�Ȩ����Ϣ����
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��������
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
@param [out] outxml				��ѯ���Ž�Ȩ����Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<recnum></recnum>
</root>
@endverbatim
@param [in] maxlen				��Ϣ��󳤶�
*/
DLIB_API t_int32 DMU_SC_OptAcRightInfo(t_uint32 session, t_int32 timeout,char* inxml,char* outxml,t_uint32 maxlen);

/**
@brief �ſ��Ʋ���(���š����š���ѯ��״̬)
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��ѯ������
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<domid></domid>
	<devcode></devcode>
	<doorcode></doorcode>
	<doorindex></doorindex>
</root>
@param [out] outxml				��ѯ���Ž�Ȩ����Ϣ
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
@param [in] maxlen				��Ϣ��󳤶�
*/
DLIB_API t_int32 DMU_SC_OptAcControlInfo(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/**
@brief �������Ų���֪ͨ�ϱ�
@param [in] session				���Ӿ��
@param [in] inxml				��������
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
@brief ���Ž���������ѯ�Ų���
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��ѯ������
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>
	<devcode></devcode>
	<doorcode></doorcode>
	<doorindex></doorindex>
</root>
@param [out] outxml				���Ž���������ѯ���Ų���
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<acparam domid="" devcode="" doorcode="" doorindex="" openmode="" duration="" timeout="" openmethod="" />
</root>
@endverbatim
@param [in] maxlen				��Ϣ��󳤶�
*/
DLIB_API t_int32 DMU_SC_QueryAcParamInfo(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/**
@brief �Ų�������
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��������
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<acparam domid="" devcode="" doorcode="" doorindex="" openmode="" 
	cardtype="" password="" startdate="" enddate="" />
</root>
@endverbatim
@param [in] maxlen				��Ϣ��󳤶�
*/
DLIB_API t_int32 DMU_SC_OptAcParamInfo(t_uint32 session, t_int32 timeout,char* inxml,t_uint32 maxlen);

/**
@brief ���˿��Ų�������
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��������
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
@param [in] maxlen				��Ϣ��󳤶�
*/
DLIB_API t_int32 DMU_SC_SetAcMultiPersonOpen(t_uint32 session, t_int32 timeout,char* inxml,t_uint32 maxlen);


/**
@brief �����豸ʱ��
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��������
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>
	<devcode></devcode>
	<time></time>
</root>
@endverbatim
@param [in] maxlen				��Ϣ��󳤶�
*/
DLIB_API t_int32 DMU_SC_SetDeviceTime(t_uint32 session, t_int32 timeout, char* inxml, t_uint32 maxlen);


/**
@brief �����Ž���������Ϣ
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��������
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<item domid="" devcode="" devname="" doorcode="" doorname="" />
<item domid="" devcode="" devname="" doorcode="" doorname="" />
</root>
@endverbatim
@param [in] maxlen				��Ϣ��󳤶�
*/
DLIB_API t_int32 DMU_SC_UpdateACDevice(t_uint32 session, t_int32 timeout, char* inxml, t_uint32 maxlen);

/**
@brief ɾ���Ž�������(dmu��Ҫ�������ݿ⣬Ȼ��ɾ������Ȩ��)
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��������
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<domid></domid>
<devcode></devcode>
</root>
@endverbatim
@param [in] maxlen				��Ϣ��󳤶�
*/
DLIB_API t_int32 DMU_SC_DeleteACDevice(t_uint32 session, t_int32 timeout, char* inxml, t_uint32 maxlen);


/**
@brief ��ȡ�豸ץͼ��Ϣ
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��ѯ������
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<srcdomid></srcdomid>			Դ�豸��ID
	<srcdevcode></srcdevcode>		Դ�豸����
	<domid></domid>					��Ƶ�豸��ID
	<devcode></devcode>				��Ƶ�豸����
	<alarmtype>0</alarmtype>		�澯����
	<alarmsubtype>0</alarmsubtype>	�澯������
	<flag>0</flag>					ץͼ֪ͨ����Դ��ʶ 0 ��֪ͨ 1 ֪ͨ 
</root>
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<guid></guid>					ͼƬguid
	<filesize>0</filesize>			ͼƬ�ļ���С
	<filename/>						�ļ���
</root>
@endverbatim
@param [in] maxlen				��Ϣ��󳤶�
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_GetSnapshot(t_uint32 session, t_int32 timeout, char* inxml, char* outxml, t_uint32 maxlen);

#pragma endregion


#pragma region �㲥�ӿ�

/**
* @defgroup �㲥�ӿ�
* @{
*/

/**
@brief ��ѯ�����ն���Ϣ
@param [in]  session			���Ӿ��
@param [in]  timeout			��ʱʱ��
@param [in]	 info				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid />			��ID
	<size />			ÿҳ��С Ĭ��100��
	<curpage />			��ѯ�ڼ�ҳ
	<parentorgcode />   ���ڵ����(���ڵ�Ϊ�ղ�ѯȫ������Ϊ�ղ�ѯ�ýڵ��µ������ն�)
	<name />            �ն�����(�����ն�������ƥ��ģ����ѯ��Ϊ�ղ�ѯȫ��)
	<status />          �ն�״̬(0��ʾ��ѯȫ��)
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>				����
	<item 
		domid=""				��ID
		id=""					�ն˱��
		parentorgcode=""        ����֯����
		name=""				    �ն�����
		status=""				״̬ 1:��¼ 2. δ��¼ (�㲥�������ն�֮���״̬)
	/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_NBSQueryTerminalInfo(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);


/**
@brief �޸��ն���Ϣ(�޸��ն˵����ơ����ڵ�)
@param [in] session		   ���Ӿ��
@param [in] timeout	 	   ��ʱʱ��
@param [in] terminalId	   �ն�id
@param [in] opt	           �޸�����(1.�޸����ƣ�2.�޸ĸ��ڵ㣬3.���ƺ͸��ڵ�ͬʱ�޸�)
@param [in] terminalName   �µ��ն�����
@param [in] parentcode     ����֯����
@param [in] groupname      ����֯����
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSModifyTerminalInfo(t_uint32 session, t_int32 timeout, int terminalId, int opt, char *terminalName, char *parentcode, char *groupname);

/**
@brief ��ѯ�����ն���Ϣ
@param [in] session		   ���Ӿ��
@param [in] timeout	 	   ��ʱʱ��
@param [in] Flag	       ��־λ����1
@param [in] domId          ��ID
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSQryAllTerminalInfo(t_uint32 session, t_int32 timeout, int Flag, char *domId);

/**
@brief ��ѯ��Ŀ�б���Ϣ
@param [in]  session			���Ӿ��
@param [in]  timeout			��ʱʱ��
@param [in]  inxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid />		    ��ID
	<size />			ÿҳ��С
	<curpage />			��ѯ�ڼ�ҳ
	<parentcode />      ������Ŀ�������(������벻Ϊ�գ����ѯ�ñ����µ����н�Ŀ)
	<name />            ��Ŀ����(����������ƥ��ģ����ѯ��Ϊ�ղ�ѯȫ��)
</root>
@endverbatim
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>			����
	<item 
		domid=""			��ID
		name=""				�ļ�����(abc.mp3)
		guid=""				�ļ���guid
		parentcode=""       ������Ŀ�����
	/>
</root>
@endverbatim
@param [in]  maxlen				��Ϣ��󳤶�
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_NBSQueryProgramInfo(t_uint32 session, t_int32 timeout, char* inxml, char* outxml, t_uint32 maxlen);


/**
@brief ��Ŀ����
@param [in] session		   ���Ӿ��
@param [in] timeout	 	   ��ʱʱ��
@param [in]  inxml		   ������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item
		opt=""              1:���ӽ�Ŀ, 2:�޸Ľ�Ŀ, 3:ɾ����Ŀ
		domid=""			��ID
		name=""				��Ŀ����(��: abc.mp3)
		guid=""				�ļ���guid(ͨ��FS�����ϴ���Ŀ��ȡ��guid)
		parentcode=""       ������Ŀ�����
	/>
</root>
@endverbatim
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSOptProgramInfo(t_uint32 session, t_int32 timeout, char* inxml);

/**
@brief ������Ŀ������Ϣ
@param [in] session		��¼�ɹ��󷵻ص�ֵ
@param [in] timeout		��ʱʱ��
@param [in] info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org opt=""            �������� 0 ���� 1 �޸� 2 ɾ��
		domid=""		   ��ID
		orgcode=""	 	   �������
		parentdomid=""	   ����ID
		parentorgcode=""   ������(�����ڵ����Ϊ�ձ�ʾ���ڵ�)
		name=""            ��������
	/>
</root>
@endverbatim
@return 
@remarks һ�ο��Բ��������֯�ڵ�
@see
*/
DLIB_API t_int32 DMU_SC_NBSOptProgramOrg(t_uint32 session, t_int32 timeout, char *info);

/**
@brief ��ѯָ����Ŀ������ϸ��Ϣ
@param [in]  session	
@param [in]  timeout	��ʱʱ��
@param [in]  domid		��ID
@param [in]  orgcode	��Ŀ�������
@param [out] outxml		��ѯ��Ϣ(���DMU_SC_NBSOptOrgע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" name="" />
</root>
@endverbatim
@param [in]  maxlen		��Ϣ��󳤶�
@return 
@remarks
@see DMU_SC_NBSOptProgramOrg
*/
DLIB_API t_int32 DMU_SC_NBSQueryProgramOrg(t_uint32 session, t_int32 timeout, char *domid, char *orgcode, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯ���н�Ŀ����
@param [in]  session	
@param [in]  timeout	��ʱʱ��
@param [out] outxml		��ѯ��Ϣ(���DMU_SC_NBSOptOrgע��)
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
@param [in]  maxlen		��Ϣ��󳤶�
@return 
@remarks
@see DMU_SC_NBSOptProgramOrg
*/
DLIB_API t_int32 DMU_SC_NBSQueryAllProgramOrg(t_uint32 session, t_int32 timeout, char *outxml, t_uint32 maxlen);

/*
@brief ����ʱ��ģ��
@param [in] session    ��¼�ɹ��󷵻ص�ֵ
@param [in] timeout	   ��ʱʱ��
@param [in] xmlInput   ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<opt 
	operatetype="0"   //�������� 0 ���� 1 �޸� 2 ɾ��
>
	<timetemplate 
		id=""; //ģ��id
		title="";//ģ����
		type="";//ģ������ 1:����; 2:����; 3:����;4:����ִ�У����������
		config="";//ģ�����ã���xml��ʽ����ʽ����
	/>
</opt>
</root>
@endverbatim

@ģ�����ø�ʽ
@verbatim
//�������
<Config>
<Day>
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
</Config>

//ĳ�쵥�ν���,��Ч����ʼ����ֹһ��
<Config>
<Day>//һ��
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
</Config>


//���ܽ���
<Config>
<Week>
<Day Num="1"> //��һ
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
<Day Num="5">//����
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
</Week>
</Config>

//���½���
<Config>
<Month>
<Day Num="1">//һ��
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
<Day Num="5">//���
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
<Day Num="28">//��ʮ�˺�
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
</Month>
</Config>
@endverbatim

@param [in] maxLen			xmlOutput����
@param [out] xmlOutput��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<templateid></templateid>
</root>
@endverbatim
@return  ������鿴 ibp_error_enum.h
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSOptTimeTemplate(t_uint32 session, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);


/*
@brief ��ѯʱ��ģ��
@param [in] session    ��¼�ɹ��󷵻ص�ֵ
@param [in] timeout	   ��ʱʱ��
@param [in] xmlInput   ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<id />             ʱ��ģ��id(���id��Ϊ0�����ѯ��id��ģ������,id��Ϊ0������Ĳ�����������;Ϊ0���ѯȫ��)
	<size />		   ÿҳ��С Ĭ��100��
	<curpage />		   ��ѯ�ڼ�ҳ
</root>
@endverbatim

@param [in]  maxLen			xmlOutput����
@param [out] xmlOutput��Ϣ  �μ�DMU_SC_NBSOptTimeTemplate�еĸ�ʽ
@return  ������鿴 ibp_error_enum.h
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSQueryTimeTemplate(t_uint32 session, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);


/**
@brief �����㲥��֯�ṹ
@param [in] session		��¼�ɹ��󷵻ص�ֵ
@param [in] timeout		��ʱʱ��
@param [in] info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org
	    opt=""             �������� 0 ���� 1 �޸� 2 ɾ��
		domid=""		   ��ID
		orgcode=""	 	   ��֯����
		olddomid=""		   ����ID(�����ֶ��޸�ʱ��Ч)
		oldorgcode=""	   ����֯����
		parentdomid=""	   ����ID
		parentorgcode=""   ����֯����(�����ڵ����Ϊ�ձ�ʾ���ڵ�)
		name=""            ��֯����
		desc=""			   ����
	/>
</root>
@endverbatim
@return 
@remarks һ�ο��Բ��������֯�ڵ�
@see
*/
DLIB_API t_int32 DMU_SC_NBSOptOrg(t_uint32 session, t_int32 timeout, char *info);

/**
@brief ��ѯָ����֯��ϸ��Ϣ
@param [in]  session	
@param [in]  timeout	��ʱʱ��
@param [in]  domid		��֯��ID
@param [in]  orgcode	��֯����
@param [out] outxml		��ѯ��Ϣ(���DMU_SC_NBSOptOrgע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" name=""  desc="" updatetime=""/>
</root>
@endverbatim
@param [in]  maxlen		��Ϣ��󳤶�
@return 
@remarks
@see DMU_SC_OptOrg
*/
DLIB_API t_int32 DMU_SC_NBSQueryOrg(t_uint32 session, t_int32 timeout, char *domid, char *orgcode, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯ���й㲥��֯
@param [in]  session	
@param [in]  timeout	��ʱʱ��
@param [out] outxml		��ѯ��Ϣ(���DMU_SC_NBSOptOrgע��)
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
@param [in]  maxlen		��Ϣ��󳤶�
@return 
@remarks
@see DMU_SC_NBSOptOrg
*/
DLIB_API t_int32 DMU_SC_NBSQueryAllOrg(t_uint32 session, t_int32 timeout, char *outxml, t_uint32 maxlen);

/**
@brief ��ѯ����֯
@param [in]  session		
@param [in]  timeout	��ʱʱ��
@param [in]  domid		��ID
@param [in]  parentorgcode	����֯����(Ϊ���ַ������ظ���֯��Ϣ)
@param [out] outxml		��ѯ��Ϣ(���DMU_SC_NBSOptOrgע��)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<org domid="" orgcode="" parentdomid="" parentorgcode="" name="" updatetime="" desc="" />
	<org domid="" orgcode="" parentdomid="" parentorgcode="" name="" updatetime="" desc="" />
</root>
@endverbatim
@param [in]  maxlen		��Ϣ��󳤶�
@return 
@remarks
@see DMU_SC_NBSOptOrg
*/
DLIB_API t_int32 DMU_SC_NBSQuerySubOrg(t_uint32 session, t_int32 timeout, char* domid, char* parentorgcode, char*outxml, t_uint32 maxlen);

/**
@brief �����㲥����
@param [in] session		��¼�ɹ��󷵻ص�ֵ
@param [in] timeout		��ʱʱ��
@param [in] info		������Ϣ
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
��������:
opt			//�������� 0 ���� 1 �޸� 2 ɾ��
domid       //��ID
id          //����id(���Ӳ�����ʱ����Ҫ��д���ɷ�������󷵻�; ɾ���������id�����������������Ժ���)
name        //��������
desc        //��������
terminal: id    //�ն�id 
		  name //�ն�����
          parentorgcode ����֯����  
program:   name        //��Ŀ����
           guid        //��Ŀ�ļ���guid
		   parentcode  //������Ŀ�������

@endverbatim
@param [in] maxLen		xmlOutput����
@param [out] xmlOutput��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<id></id>
</root>
@endverbatim
@return  ������鿴 ibp_error_enum.h
@remarks ֻ�����Ӳ�����Ϣ��ʱ��᷵������id
@see 
*/
DLIB_API t_int32 DMU_SC_NBSOptTask(t_uint32 session, t_int32 timeout, char *info, char *xmlOutput, t_uint32 maxLen);


/*
@brief ��ѯ�㲥������Ϣ
@param [in] session    ��¼�ɹ��󷵻ص�ֵ
@param [in] timeout	   ��ʱʱ��
@param [in] xmlInput   ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<id />            ����id(���id��Ϊ0�����ѯ��id������,id��Ϊ0������Ĳ�����������;Ϊ0���ѯȫ��)
	<size />		  ÿҳ��С Ĭ��100��
	<curpage />		  ��ѯ�ڼ�ҳ
	<name />          ��������(����������ƥ��ģ����ѯ��Ϊ�ղ�ѯȫ��)
</root>
@endverbatim

@param [in]  maxLen			xmlOutput����
@param [out] xmlOutput��Ϣ  �μ�DMU_SC_NBSOptTask�еĸ�ʽ
@return  ������鿴 ibp_error_enum.h
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSQueryTask(t_uint32 session, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);


/**
@brief �����㲥�ƻ�
@param [in] session		��¼�ɹ��󷵻ص�ֵ
@param [in] timeout		��ʱʱ��
@param [in] info		������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>����
	<item opt="" domid="" id="" name="" name="" desc="" enable="" startdate="", enddate="", timeid="", config="", taskid="", taskname="", status="" title="" type="" updatetime=""/>
	<item opt="" domid="" id="" name="" name="" desc="" enable="" startdate="", enddate="", timeid="", config="", taskid="", taskname="", status="" title="" type="" updatetime="" />
	����˵��:
	opt		    //�������� 0 ���� 1 �޸� 2 ɾ��
	domid       //��ID
	id          //�ƻ�id(���Ӳ�����ʱ����Ҫ��д���ɷ�������󷵻�; ɾ������ʱ����idɾ�������������������Ժ���)
	name        //�ƻ�����
	desc        //�ƻ�����
	enable      //�ƻ�ʹ�� 1.���� 2. ͣ��
	startdate   //��Ч�ڿ�ʼʱ�� ��ʽ:2015-10-21  
	enddate     //��Ч�ڽ���ʱ�� ��ʽ:2016-10-21
	timeid      //ʱ��ģ��id(���idΪ0��ʾ��Ҫ�����æ����һ��ʱ��ģ�壬��Ҫ��д�µ�timecontent, title type)
	config      //ʱ��ģ������(timeid��Ϊ0��ʱ�����ﲻ��Ҫ��д�����ֶ��ڲ�ѯ�ƻ�ʱ��)
	title       //������ʱ��ģ������
	type        //������ʱ��ģ������
	taskid      //����id
	taskname    //��������
	status      //�ƻ�״̬ 0:δִ�� 1:����ִ��(���ֶ�Ϊ��ѯ�ƻ���ʱ����)
</root>
@endverbatim
@param [in] maxLen		xmlOutput����
@param [out] xmlOutput��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<id></id>
</root>
@endverbatim
@return  ������鿴 ibp_error_enum.h
@remarks ֻ�����Ӳ�����ʱ��᷵�ؼƻ�id
@see 
*/
DLIB_API t_int32 DMU_SC_NBSOptPlan(t_uint32 session, t_int32 timeout, char *info, char *xmlOutput, t_uint32 maxLen);


/*
@brief ��ѯ�㲥�ƻ���Ϣ
@param [in] session    ��¼�ɹ��󷵻ص�ֵ
@param [in] timeout	   ��ʱʱ��
@param [in] xmlInput   ��Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<id />            �ƻ�id(���id��Ϊ0�����ѯ��id������,id��Ϊ0������Ĳ�����������;Ϊ0���ѯȫ��)
	<size />		  ÿҳ��С Ĭ��100��
	<curpage />		  ��ѯ�ڼ�ҳ
	<name />          �ƻ�����(����������ƥ��ģ����ѯ��Ϊ�ղ�ѯȫ��)
	<enable />        ʹ�ܣ�0��ʾ��ѯȫ��
	<startdate />     ��ʼʱ�䣬0��ʾȫ��
	<enddate />       ����ʱ�䣬0��ʾȫ��
</root>
@endverbatim

@param [in]  maxLen			xmlOutput����
@param [out] xmlOutput��Ϣ  �μ�DMU_SC_NBSOptPlan�еĸ�ʽ
@return  ������鿴 ibp_error_enum.h
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSQueryPlan(t_uint32 session, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/*
@brief �ֶ�ִ�й㲥�ƻ�
@param [in] session    ��¼�ɹ��󷵻ص�ֵ
@param [in] timeout	   ��ʱʱ��
@param [in] taskId     ����id
@param [in] opt        �������ͣ�1.����ִ�мƻ�  2.����ֹͣ�ƻ� 3.��ִͨ�У�ʹ�ܣ�
@return  ������鿴 ibp_error_enum.h
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSRunTask(t_uint32 session, t_int32 timeout, t_uint32 taskId, t_uint32 opt);

/*
@brief ��ѯ�ն����ڲ��Ž�Ŀ��Ϣ
@param [in] session    ��¼�ɹ��󷵻ص�ֵ
@param [in] timeout	   ��ʱʱ��
@param [in] Id		   �ն�id
@return  ������鿴 ibp_error_enum.h

@endverbatim
@param [in] maxLen		xmlOutput����
@param [out] xmlOutput��Ϣ
@verbatim

<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>	
	<name></name>    ��Ŀ����
	<time></time>	 ������ʼʱ��
	<totle></totle>	 ��ʱ��
</root>
@endverbatim

@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_NBSQueryTerminalProgram(t_uint32 session, t_int32 timeout, t_uint32 Id, char *xmlOutput, t_uint32 maxLen);


/** @} */

#pragma endregion


#pragma region ����ʶ����

/**
* @defgroup ����ʶ����
* @{
*/

/**
@brief ����ͣ����
@param [in] session			���Ӿ��
@param [in] timeout			��ʱʱ��
@param [in] inxml			������Ϣ
@verbatim
opt: 0 add 1 modify 2 del
<root>
	<carpark opt="0" //������ parentid="0" //������֯��id domid="" //������֯����id name="" //ͣ����������
		totalnum="100" //ͣ�������� />
</root>
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptCarPark(t_uint32 session,t_int32 timeout,char* inxml);

/**
@brief ��ѯͣ����
@param [in] session			���Ӿ��
@param [in] timeout			��ʱʱ��
@param [in] inxml			������Ϣ
@verbatim
opt: 3 ��ѯһ�� 4 ��ѯȫ��
<root> 
	<carpark opt="3" id="0" parentid="0" curpage="0" size="0" />
</root>
@param [out] outxml			�����Ϣ
	<carpark opt="3" id="0" parentid="0"  domid="" parentorgcode="" //������֯�ı���
		name="" totalnum="100" unusednum="50" />
@param [in]  maxlen			��󳤶�
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QryCarPark(t_uint32 session,t_int32 timeout,char* inxml,char* outxml,t_uint32 maxlen);

/**
@brief ��������
@param [in] session			���Ӿ��
@param [in] timeout			��ʱʱ��
@param [in] inxml			������Ϣ
@verbatim
opt: 0 add 1 modify 2 del
<root>
	<cargate opt="0" id="7" name="" carparkid="0">
		<chn flag=0 domainid="" chncode=""> // flag 0 ����ץ������� 1 ��ȥץ�������
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
@brief ��ѯͣ��������
@param [in] session			���Ӿ��
@param [in] timeout			��ʱʱ��
@param [in] inxml			������Ϣ
@verbatim
opt: 3 ��ѯһ�� 4 ��ѯȫ��
<root>
	<cargate opt="3" id="0"//����id  carparkid="0" //ͣ����id curpage="0" size="0" />
</root>
@param [out] outxml			�����Ϣ
<root>
	<cargate opt="3" id="0" carparkid="" //ͣ����id name="" //�������� />
		<chn flag="" domainid="" chncode="">
	</cargate>
</root>
@param [in]  maxlen			��󳤶�
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QryCarGate(t_uint32 session,t_int32 timeout,char* inxml,char* outxml,t_uint32 maxlen);

/**
@brief ����������Ϣ
@param [in] session			���Ӿ��
@param [in] timeout			��ʱʱ��
@param [in] inxml			������Ϣ
@verbatim
opt: 0 add 1 modify 2 del
<root>
	<cargate opt="0" id="7" //���� cartype="" //�������� owner="" //���������� ownerid="" //���֤����
		ownertype="" //����״̬ reason="" //���� remark=""//��ע /> 
</root>
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptCarInfo(t_uint32 session,t_int32 timeout,char* inxml);

/**
@brief ��ѯ������Ϣ
@param [in] session			���Ӿ��
@param [in] timeout			��ʱʱ��
@param [in] inxml			������Ϣ
@verbatim
opt: 3 ��ѯһ�� 4 ��ѯȫ��
<root>
	<cargate opt="3" id="7" curpage="0" size="0" />
</root>
@param [in]  maxlen			��󳤶�
@param [out] outxml			�����Ϣ
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
@brief ��ѯ��ʷ������Ϣ
@param [in]  session			���Ӿ��
@param [in]  timeout			��ʱʱ��
@param [in]  inxml				������Ϣ
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
@param [out] outxml				������Ϣ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<total>2</total>
	<carlog id="1" carid="" carpark="" carcolor="BB22DD" cartype="MPV" owner="" indomid="111" inchncode="chn1" ineventtype="1" intime="2017-03-11 09:28:51" infile="" inplace="" outdomid="" outchncode="" outeventtype="0" outtime="" outfile="" outplace=""/>
	<carlog id="2" carid="" carpark="" carcolor="" cartype="" owner="" indomid="" inchncode="" ineventtype="" intime="" infile="" inplace="" outdomid="" outchncode="" outeventtype="0"	outtime="" outfile="" outplace=""/>
</root>
@param [in]  maxlen				��Ϣ��󳤶�
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QryCarLog(t_uint32 session, t_int32 timeout, char* inxml, char* outxml, t_uint32 maxlen);

/**
@brief �ͻ����У������У���ѯ
@param [in]  session			���Ӿ��
@param [in]  timeout			��ʱʱ��
@param [in]  inxml				������Ϣ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<carparkid></carparkid>		//ͣ����ID
	<starttime></starttime>     //��ʼʱ��,����:2016-3
	<endtime></endtime>			//����ʱ��,����:2016-5
	<carid></carid>      		//���ƺ�,���Ϊ��,��ȫ��
</root>
@param [out] outxml				������Ϣ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<count time="2016-3" num="60"/>		(����time��С��������)
	<count time="2016-4" num="80"/>
   	<count time="2016-5" num="50"/>
</root>
@param [in]  maxlen				��Ϣ��󳤶�
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QryCusMonthRank(t_uint32 session,t_int32 timeout,char* inxml,char* outxml,t_uint32 maxlen);

/**
@brief �ͻ����У������У���ϸ��ѯ
@param [in]  session			���Ӿ��
@param [in]  timeout			��ʱʱ��
@param [in]  inxml				������Ϣ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<carparkid></carparkid>		//ͣ����ID
	<searchtime></searchtime>   //������·�:2016-3
	<carid></carid>      		//���ƺ�,���Ϊ��,��ȫ��
	<curpage></curpage>
	<size></size>
</root>
@param [out] outxml				������Ϣ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total>3</total>
	<count carid="" num="20"/>		(����num�Ӷൽ������)
	<count carid="" num="10"/>
    <count carid="" num="5"/>
</root>
@param [in]  maxlen				��Ϣ��󳤶�
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QryCusMonthDetailRank(t_uint32 session,t_int32 timeout,char* inxml,char* outxml,t_uint32 maxlen);

/**
@brief �ͻ����У��������У���ѯ
@param [in]  session			���Ӿ��
@param [in]  timeout			��ʱʱ��
@param [in]  inxml				������Ϣ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<carparkid></carparkid>		//ͣ����ID
	<searchtime></searchtime>   //������·�:2016-3
</root>
@param [out] outxml				������Ϣ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<count cartype=""   num="60"  ratio="30.51"/>
	<count cartype=""   num="80"  ratio="40.31"/>
    <count cartype=""   num="50"  ratio="29.31"/>
</root>
@param [in]  maxlen			    ��Ϣ��󳤶�
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QryCusCartypeRank(t_uint32 session,t_int32 timeout,char* inxml,char* outxml,t_uint32 maxlen);

/**
@brief �ͻ����У��������У���ϸ��ѯ
@param [in]  session			���Ӿ��
@param [in]  timeout			��ʱʱ��
@param [in]  inxml				������Ϣ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<carparkid></carparkid>		//ͣ����ID
	<searchtime></searchtime>   //������·�:2016-3
	<cartype></cartype>         //���ͣ����Ϊ�գ���ȫ��
	<curpage></curpage>
	<size></size>
</root>
@param [out] outxml				������Ϣ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total>3</total>
	<count cartype="" carid="" num="20"/>	(�ȸ���cartype�����ٸ���num�Ӷൽ������)
	<count cartype="" carid="" num="10"/>
	<count cartype="" carid="" num="5" />
</root>
@param [in]  maxlen				��Ϣ��󳤶�
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QryCusCartypeDetailRank(t_uint32 session,t_int32 timeout,char* inxml,char* outxml,t_uint32 maxlen);

/**
@brief ����������
@param [in]  session			���Ӿ��
@param [in]  timeout			��ʱʱ��
@param [in]  inxml				������Ϣ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>				 //��ѯ��ʽ��0 ��ʱ��1 ���ա�2 ����
	<carparkid></carparkid>  //ͣ����ID
	<starttime></starttime>
	<endtime></endtime>
	<curpage></curpage>
	<size></size>
</root>
@param [out] outxml				������Ϣ
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total>10</total>
	<carflow time="2016-1-1"  incarnum="" >  (����time��С��������)
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
@param [in]  maxlen				��Ϣ��󳤶�
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QryCusCarflowRank(t_uint32 session,t_int32 timeout,char* inxml,char* outxml,t_uint32 maxlen);

/**
@brief ��������ͷʹ���ϱ�
@param [in] session			���Ӿ��
@param [in] timeout			��ʱʱ��
@param [in] opt				�������� 0 ʹ��   1 ȥʹ�� 
@param [in] chnlane			����ͷ�������
@param [in] chncode			����ͷ���
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptChnEnableReport(t_uint32 session, t_int32 timeout, int opt, int chnlane, char *chncode);

/**
@brief ��ȡ�豸ץͼ��Ϣ
@param [in] session				���Ӿ��
@param [in] timeout				��ʱʱ��
@param [in] inxml				��ѯ������
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<channelid></channelid>		 // ͨ����
	<times></time>               // ���Ĵ���, 0��ʾֹͣץ��,������ʾ����ץ�ĵ�����
</root>
@param [out] outxml				������Ϣ
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<alarmtype></alarmtype>			//�¼����ͣ���ͨ�����¼���
	<carcolor></carcolor>			// ������ɫ
	<cargate></cargate>				// ��������
	<carid></carid>					// ��ʾ���ƺ�
	<carplatetype></carplatetype>	//���ͣ���ֵΪ�γ�����SUV��
	<cartype></cartype>				// ��������
	<chnid></chnid>					//����ͷͨ��ID
	<devcode></devcode>				// ��ʾ����ͷͨ�����
	<eventtime></eventtime>			//�¼�����ʱ��
	<filename></filename>			//ץ�ĵ�ͼƬ����
	<lane></lane>					//������ţ���ȡֵΪ0��1��2��
	<cararea></cararea>				//��ͷ���ǳ�β����ֵΪhead����tail
	<carlogo></carlogo>				//Ʒ�ƣ���ȡֵΪ�µϡ��������ص�
	<carseries></carseries>			//��ϵ����ֵΪA4L����X5��
	<carlable></carlable>			//����ȡֵΪA4L-20092012-�и�������X5-20112013-M�˶��͵�
	<piccontent></piccontent>		//ͼƬ����
</root>
@endverbatim
@param [in] maxlen				��Ϣ��󳤶�
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


