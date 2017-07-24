/**
* \file		player.h
* \brief	���ſ�ӿڶ���
* \author  	dahuasys
* \date		2016-09-07
* \note		���󻪡��������������ҳ������ṩ�Ĳ��ſ⣬�������ϣ������ṩͳһ�Ľӿ�
* \defgroup	ͨ�ý����
* \{
*/

#ifndef _PLAYER_H_
#define _PLAYER_H_


#ifndef API_PLAYER
	#ifdef WIN32
//#include <windows.h>

#ifdef PLAYER_EXPORTS	
#define API_PLAYER  __declspec(dllexport)
#else
#define API_PLAYER  __declspec(dllimport)
#endif

#else // WIN32
#define API_PLAYER 
#endif
#endif


#ifdef WIN32
	#ifdef _DEBUG
//		#include <vld.h>
	#endif
#endif


#define CHANNEL_NUM_MAX 64	//Ƶ����������������ܴ��ڻ����port�����100��
#define WINDOWS_NUM_MAX 16	//��ʾ���ڵ�����������з�����ȷ�Ϲ���������е�MAX_DISPLAY_WND���Ǵ���ģ�ʵ��֧��16������


// �豸�������Ͷ���
enum manufacturer_t
{
	MANU_DH = 0,  // ��
	MANU_HK,        // ����
	MANU_VN       // ����
};

// �������Ͷ���
enum decode_t
{
	DECODE_SOFT = 0,	// Ӳ����
	DECODE_HARD,		// �����
};

// ͼƬ��ʽ����
enum format_t
{
	FORMAT_BMP = 0, //BMPλͼ
	FORMAT_JPG      //JPGͼƬ
};

// ���ſ�������
enum playControl_t
{
	PLAY_NORMAL = 0, // ��������
	PLAY_FAST,       // ���ٲ���
	PLAY_SLOW,       // ���ٲ���
	PLAY_PAUSE,      // ��ͣ����
	PLAY_PLAY,       // ��ͣ�ָ�
	PLAY_ONE_BY_ONE, // ��֡����
	PLAY_ONE_BY_ONE_BACK, // ��֡����
	PLAY_RESET_BUFFER, //��ջ�����
};

// ��ȡ��ǰʱ�䡢֡�ʡ�ý����Ϣ
enum queryCmd_t
{
	QUERY_TIME = 0,	// ��ѯ������ʱ����Ϣ����λms���󻪡����㣬֧�֣�
	QUERY_RATE,		// ��ѯ֡����Ϣ���󻪡����㣬֧�֣�
	QUERY_MEDIA,	// ��ѯý����Ϣ���󻪣�֧�֣�
};

// ����Ƶ��������
enum channel_t
{
	CHANNEL_REALPLAY = 0,		// ʵʱ��Ƶ
	CHANNEL_PLAYBACK_STREAM,	// ¼��طţ���ģʽ��
	CHANNEL_PLAYBACK_FILE,		// ¼��طţ��ļ�ģʽ��
	//CHANNEL_AUDIORECORD,		// �����ɼ�
	CHANNEL_INVALID,			// ��Ч�����ͣ�������PLAY_GetFreePortʧ��ʱ���Ὣm_type�޸ĳ���Ч������
};

//������
enum
{
	PLAYER_ERR_SUCCESS							= 0,	//�ɹ�
	PLAYER_ERR_LOAD_LIBRARY_FAILED				= -1,	//���ؽ����ʧ��
	PLAYER_ERR_GET_PROC_ADDR_FAILED				= -2,	//���ؽ���⺯����ַʧ��
	PLAYER_ERR_CANNOT_CREATE_INVALID_CHANNEL	= -3,	//�޷�����һ������Ϊ����Ч����Ƶ��
	PLAYER_ERR_CREATE_CHANNEL_FAILED			= -4,	//����Ƶ��ʧ�ܣ������û�п��е�port��
	PLAYER_ERR_NONE_FREE_CHANNEL				= -5,	//���벻������Ƶ��
	PLAYER_ERR_OUT_BOUND_CHANNEL				= -6,	//Ƶ����Խ��
	PLAYER_ERR_RELEASE_FREE_CHANNEL				= -7,	//�޷��ͷſ��е�Ƶ��
	PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL		= -8,	//�޷��������е�Ƶ��
	
	PLAYER_ERR_CANNOT_PLAY_WHEN_NOT_STREAM_TYPE	= -10,	//��ǰ��������ģʽ���޷�����
	PLAYER_ERR_CANNOT_PLAY_WHEN_IS_PLAYING		= -11,	//��ǰ�����ڲ����У��޷�����
	PLAYER_ERR_CANNOT_PLAY_WHEN_NONE_WINDOW		= -12,	//��ǰ��δ��Ӵ��ڣ��޷�����
	PLAYER_ERR_SET_STREAM_OPEN_MODE_FAILED		= -13,	//�������򿪵�ģʽʱʧ��
	PLAYER_ERR_OPEN_STREAM_FAILED				= -14,	//����ʧ��
	PLAYER_ERR_SET_DISPLAY_BUF_FAILED			= -15,	//������ʾ����ʧ��
	PLAYER_ERR_PLAY_STREAM_FAILED				= -16,	//������ʧ��
	PLAYER_ERR_SET_FILE_REF_CALLBACK_FAILED		= -17,	//�����ļ�����ʧ��

	PLAYER_ERR_CANNOT_PLAY_WHEN_NOT_FILE_TYPE	= -20,	//��ǰ�������ļ�ģʽ���޷�����
	PLAYER_ERR_FILENAME_IS_NULL					= -21,	//�ļ�����ΪNULL
	PLAYER_ERR_OPEN_FILE_FAILED					= -22,	//���ļ�ʧ��
	PLAYER_ERR_PLAY_FILE_FAILED					= -23,	//�����ļ�ʧ��

	PLAYER_ERR_CANNOT_STOP_WHEN_IS_NOT_PLAYING	= -25,	//��ǰ���ڲ����У��޷�ֹͣ����

	PLAYER_ERR_CANNOT_SET_BUFF_POOL_SIZE_WHEN_NOT_STREAM_TYPE	= -26,	//��ǰ��������ģʽ���޷����ò��Ż�������С
	PLAYER_ERR_CANNOT_SET_BUFF_POOL_SIZE_WHEN_IS_PLAYING		= -27,	//��ǰ�����ڲ����У��޷����ò��Ż�������С
	PLAYER_ERR_CANNOT_SIZE_IS_TOO_SMALL	= 28,			//�����size̫С����СֵΪ1024*50
	PLAYER_ERR_CANNOT_SIZE_IS_TOO_LARGE	= 29,			//�����size̫�����ֵΪ1024*100000

	PLAYER_ERR_CANNOT_INPUT_WHEN_NOT_STREAM_TYPE= -30,	//��ǰ��������ģʽ���޷���������
	PLAYER_ERR_CANNOT_INPUT_WHEN_IS_NOT_PLAYING	= -31,	//��ǰ���ڲ����У��޷���������
	PLAYER_ERR_INPUT_FAILED						= -32,	//��������ʧ��

	PLAYER_ERR_CANNOT_SET_DECODE_WHEN_IS_PLAYING	= -34,	//��ǰ֣�ڲ����У��޷����ý���ģʽ
	PLAYER_ERR_CANNOT_SET_DECODE_WHEN_AUDIO_RECORDING= -35,	//¼���ɼ�ģʽ�£��޷����ý���ģʽ
	PLAYER_ERR_CANNOT_SET_DECODE_WHEN_NOT_STREAM_TYPE= -36,	//��ǰ��������ģʽ���޷����ý���ģʽ
	PLAYER_ERR_CANNOT_SET_DECODE_WHEN_IS_NOT_PLAYING = -37, //��ǰ���ڲ����У��޷����ý���ģʽ
	PLAYER_ERR_SET_DECODE_FAILED					= -38,	//���ý���ģʽʧ��
	PLAYER_ERR_DONOT_SUPPORT_HARD_DECODE			= -39,	//��ĵ��Բ�֧��Ӳ����
	PLAYER_ERR_CANNOT_GET_DECODE_WHEN_AUDIO_RECORDING= -40,	//¼���ɼ�ģʽ�£��޷���ȡ����ģʽ
	PLAYER_ERR_CANNOT_GET_DECODE_WHEN_NOT_STREAM_TYPE= -41,	//��ǰ��������ģʽ���޷���ȡ����ģʽ

	PLAYER_ERR_HWND_IS_NULL							= -42,	//������ʾ��Χʧ�ܣ�����HWDSΪNULL
	PLAYER_ERR_SET_DISPLAY_REGION_FAILED			= -43,	//������ʾ��Χʧ��

	PLAYER_ERR_CANNOT_ADD_MORE_WINDOW				= -45,	//�޷���Ӹ���Ĵ���
	PLAYER_ERR_CANNOT_ADD_EXISTENCE_WINDOW			= -46,	//�޷�����Ѵ��ڵĴ���
	PLAYER_ERR_CANNOT_REMOVE_FIRST_WINDOW_WHEN_PLAYING= -47,//�޷�ɾ�����ڲ��ŵġ���������
	PLAYER_ERR_CANNOT_REMOVE_INEXISTENCE_WINDOW		= -48,	//�޷�ɾ�������ڵĴ���

	PLAYER_ERR_CANNOT_SNAP_WHEN_NOT_PLAYING			= -50,	//��ǰ���ڲ����У��޷�ץͼ
	PLAYER_ERR_CANNOT_SNAP_WHEN_HARD_DECODE			= -51,	//��ǰ����Ӳ����ģʽ���޷�ץͼ
	PLAYER_ERR_SNAP_FAILED							= -52,	//ץͼʧ��

	PLAYER_ERR_CANNOT_OPEN_SOUND_WHEN_NOT_PLAYING	= -55,	//��ǰ���ڲ����У��޷�������
	PLAYER_ERR_OPEN_SOUND_FAILED					= -56,	//������ʧ��
	PLAYER_ERR_CANNOT_CLOSE_SOUND_WHEN_NOT_PLAYING	= -57,	//��ǰ���ڲ����У��޷��ر�����
	PLAYER_ERR_CLOSE_SOUND_FAILED					= -58,	//�ر�����ʧ��

	PLAYER_ERR_CANNOT_GET_VOLUME_WHEN_NOT_PLAYING	= -60,	//��ǰ���ڲ����У��޷���ȡ����ֵ
	PLAYER_ERR_CANNOT_SET_VOLUME_WHEN_NOT_PLAYING	= -61,	//��ǰ���ڲ����У��޷���������ֵ
	PLAYER_ERR_SET_VOLUME_FAILED					= -62,	//��������ֵʧ��

	PLAYER_ERR_CANNOT_GET_COLOR_WHEN_NOT_PLAYING= -65,	//��ǰ���ڲ����У��޷���ȡɫ��ֵ
	PLAYER_ERR_GET_COLOR_FAILED					= -66,	//��ȡɫ��ֵʧ��
	PLAYER_ERR_CANNOT_SET_COLOR_WHEN_NOT_PLAYING= -67,	//��ǰ���ڲ����У��޷�����ɫ��ֵ
	PLAYER_ERR_SET_COLOR_FAILED					= -68,	//����ɫ��ֵʧ��

	PLAYER_ERR_CANNOT_PLAY_CONTROL_WHEN_NOT_PLAYBACK= -70,	//��ǰ���ڻط�ģʽ�£��޷����в��ſ���
	PLAYER_ERR_CANNOT_PLAY_CONTROL_WHEN_NOT_PLAYING	= -71,	//��ǰ���ڲ����У��޷��в��ſ���
	PLAYER_ERR_PLAY_CONTROL_FAILED					= -72,	//���ſ���ʧ��

	PLAYER_ERR_CANNOT_SET_POSITION_WHEN_NOT_FILE_TYPE= -75,	//��ǰ�����ı��ط�ģʽ�£��޷����ò��Ž���ֵ
	PLAYER_ERR_CANNOT_SET_POSITION_WHEN_NOT_PLAYING	= -76,	//��ǰ���ڲ����У��޷����ò��Ž���ֵ
	PLAYER_ERR_OUT_BOUND_POSITION					= -77,	//positionֵԽ��
	PLAYER_ERR_SET_POSITION_FAILED					= -78,	//���ò��Ž���ʧ��
	PLAYER_ERR_CANNOT_GET_POSITION_WHEN_NOT_FILE_TYPE= -79,	//��ǰ�����ı��ط�ģʽ�£��޷���ȡ���Ž���ֵ
	PLAYER_ERR_CANNOT_GET_POSITION_WHEN_NOT_PLAYING= -80,	//��ǰ���ڲ����У��޷���ȡ���Ž���ֵ

	PLAYER_ERR_CANNOT_GET_TOTAL_FRAME_WHEN_NOT_FILE_TYPE= -85,	//��ǰ�����ļ��ط�ģʽ�£��޷���ȡ�ļ���֡��
	PLAYER_ERR_CANNOT_GET_TOTAL_FRAME_WHEN_NOT_PLAYING	= -86,	//��ǰ���ڲ����У��޷���ȡ�ļ���֡��
	PLAYER_ERR_CANNOT_GET_CURRENT_FRAME_WHEN_NOT_FILE_TYPE= -87,//��ǰ�����ļ��ط�ģʽ�£��޷���ȡ�ļ���ǰ֡��
	PLAYER_ERR_CANNOT_GET_CURRENT_FRAME_WHEN_NOT_PLAYING= -88,	//��ǰ���ڲ����У��޷���ȡ�ļ���ǰ֡��
	PLAYER_ERR_CANNOT_SET_CURRENT_FRAME_WHEN_NOT_FILE_TYPE= -89,//��ǰ�����ļ��ط�ģʽ�£��޷������ļ���ǰ֡��
	PLAYER_ERR_CANNOT_SET_CURRENT_FRAME_WHEN_NOT_PLAYING= -90,	//��ǰ���ڲ����У��޷������ļ���ǰ֡��
	PLAYER_ERR_SET_CURRENT_FRAME_FAILED					= -91,	//�����ļ���ǰ֡��ʧ��
	
	PLAYER_ERR_CANNOT_GET_CURRENT_TIME_WHEN_NOT_PLAYBACK= -95,	//��ǰ���ڻط�ģʽ�£��޷���ȡ��ǰ����ʱ��
	PLAYER_ERR_CANNOT_GET_CURRENT_TIME_WHEN_NOT_PLAYING	= -96,	//��ǰ���ڲ����У��޷���ȡ��ǰ����ʱ��
	PLAYER_ERR_GET_CURRENT_TIME_FAILED					= -97,	//��ȡ��ǰ����ʱ��ʧ��

	PLAYER_ERR_CANNOT_GET_REMAIN_WHEN_NOT_PLAYBACK		= -100,	//��ǰ���ڻط�ģʽ�£��޷���ȡ��ǰʣ��֡��
	PLAYER_ERR_CANNOT_GET_REMAIN_WHEN_NOT_PLAYING		= -101,	//��ǰ���ڲ����У��޷���ȡ��ǰʣ��֡��
	
	PLAYER_ERR_CANNOT_GET_PICTURE_SIZE_WHEN_AUDIO_RECORDING= -105,//��ǰ���������ɼ��У��޷���ȡͼƬ�ߴ�
	PLAYER_ERR_CANNOT_GET_PICTURE_SIZE_WHEN_NOT_PLAYING	= -106,	//��ǰ���ڲ����У��޷���ȡͼƬ�ߴ�
	PLAYER_ERR_GET_PICTURE_SIZE_FAILED			= -107,	//��ȡͼƬ�ߴ�ʧ��

	PLAYER_ERR_CB_IS_NULL						= -110,	//�����cbΪNULL
	PLAYER_ERR_SET_DRAW_CALLBACK_FAILED			= -111,	//������ʾ�����ص�����ʧ��
	PLAYER_ERR_SET_FILE_END_CALLBACK_FAILED		= -112,	//�����ļ������ص�����ʧ��
	PLAYER_ERR_TRY_LOCK_FAILED					= -113,	//���ûص�ʱtrylockʧ�ܣ���ͻ�����ִ��һ�Ρ�

	PLAYER_ERR_BUFF_IS_NULL						= -115,	//�����buffΪNULL
	PLAYER_ERR_OUT_BOUND_CMD					= -116,	//�����������Խ��
	PLAYER_ERR_DO_NOT_SUPPORT_QUERY_MEDIA		= -117,	//��֧�ֲ�ѯý����Ϣ
	PLAYER_ERR_QUERY_INFO_FAILED				= -118,	//��ѯ��Ϣʧ��

	PLAYER_ERR_CANNOT_START_RECORD_WHEN_NOT_AUDIO_RECORD= -120,	//��ǰ�����������ɼ�ģʽ���޷����������ɼ�
	PLAYER_ERR_START_AUDIO_RECORD_FAILED				= -121,	//���������ɼ�ʧ��
	PLAYER_ERR_CANNOT_STOP_RECORD_WHEN_NOT_AUDIO_RECORD	= -122,	//��ǰ�����������ɼ�ģʽ���޷��ر������ɼ�
	PLAYER_ERR_STOP_AUDIO_RECORD_FAILED					= -123,	//�ر������ɼ�ʧ��
};

#define PLAYER_CALLBACK    __stdcall
/**
 * \defgroup	�������ӿ�
 * \{
 */

/**
 * \brief		һ֡����Ļص���������
 * \param		[in] hdc		��ʾ���ڵľ�� 
 * \param		[in] width		�� 	
 * \param		[in] height		��
 * \param		[in] data		�û��Զ������� 
 * \return		void
 * \date		2016-09-07
 * \note		��������ʾOSD��
 * \note		�ڱ������ڣ�Ӧ�����ʱ�Ļ�ͼ����������Ӱ������
 */
typedef void (PLAYER_CALLBACK *drawCallback)(void *hdc, unsigned int width, unsigned int height, void *data);

/**
 * \brief		�ļ��طŽ����Ļص���������
 * \param		[in] fileName	�ļ�����
 * \param		[in] data		�û��Զ������� 
 * \return		void
 * \date		2016-09-07
 */
typedef void (PLAYER_CALLBACK *fileEndCallback)(const char *fileName, void *data);

/**
 * \brief		�����ɼ����ݻص�����
 * \param		[in] data		����	 
 * \param		[in] len		���ݳ���	 
 * \return		void
 * \date		2016-09-07
 * \note		
 */
typedef void (PLAYER_CALLBACK *audioRecordCallback)(unsigned char *data, unsigned int len);



/**
 * \class		player�����ռ�
 * \brief		�������ӿ��ඨ��
 * \date		2016-09-07
 */
namespace player
{	
	//�����ڲ�ʹ��
	API_PLAYER void PLAYER_CALLBACK doDrawCallback(int port, void *hdc, void *data);
	API_PLAYER void PLAYER_CALLBACK doDrawCallback_2(int port, void *hdc, long data);
	API_PLAYER void PLAYER_CALLBACK doFileEndCallback(int port, void *data);
	API_PLAYER void PLAYER_CALLBACK doFileEndCallback_2(unsigned long port, unsigned long data);
	API_PLAYER void PLAYER_CALLBACK doAudioRecordCallback(unsigned char *audio, unsigned int len, void *data);
	API_PLAYER void PLAYER_CALLBACK doFileRefDoneCallback(int port, long data);

/**
 * \brief		��������Ƶ��
 * \param		[in] manufacturer	�豸���̣����manufacturer_t
 * \param		[in] type			�������ͣ����channel_t	
 * \param		[out] id			�������õ�Ƶ����	
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		
 */
	API_PLAYER int createChannel(manufacturer_t manufacturer, channel_t type, int &id);

/**
 * \brief		�ͷŲ���Ƶ��
 * \param		[in] id				���ͷŵ�Ƶ����	 
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		
 */
	API_PLAYER int releaseChannel(int id);

/**
 * \brief		���ò��Ż�������С��ʵʱ��/¼������
 * \param		[in] id				Ƶ����
 * \param		[in] size			���Ż�������С
 * \return		�����룬ͬC�ӿں���
 * \date		2017-06-02
 * \note		����play֮ǰ���ò��Ż�������С���������ã���playʱ��ʹ��Ĭ��ֵ
 */
	API_PLAYER int setBuffPoolSize(int id, unsigned long size);

/**
 * \brief		��ʼ���ţ�ʵʱ��/¼������
 * \param		[in] id				Ƶ����
 * \param		[in] streamHeader	����
 * \param		[in] len			���׳���
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		
 */
	API_PLAYER int play(int id, unsigned char *streamHeader, unsigned int len);

/**
 * \brief		��ʼ���ţ�¼���ļ���
 * \param		[in] id				Ƶ����
 * \param		[in] fileName		�ļ���
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		
 * \note			
 */	
	API_PLAYER int play(int id, const char *fileName);

/**
 * \brief		ֹͣ����
 * \param		[in] id				Ƶ����
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		
 */	
	API_PLAYER int stop(int id);

/**
 * \brief		�����������ʾ����Ƶ����
 * \param		[in] id				Ƶ����
 * \param		[in] data			��������ʾ����Ƶ����
 * \param		[in] len			��Ƶ���ݳ���
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		
 */	
	API_PLAYER int inputData(int id, unsigned char *data, unsigned int len); 

/**
 * \brief		���ý�������
 * \param		[in] id				Ƶ����
 * \param		[in] type			�������ͣ���decode_t	 
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		����Ӳ����ģʽʱ���н϶๦�ܲ����ݣ��ʲ�������á�
 */
	API_PLAYER int setDecodeType(int id, decode_t type); 

/**
 * \brief		��ȡ��������	
 * \param		[in] id				Ƶ����
 * \param		[out] type			�������ͣ���decode_t
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		
 */	
	API_PLAYER int getDecodeType(int id, decode_t &type); 

/**
 * \brief		������ʾ��Χ 
 * \param		[in] id				Ƶ����
 * \param		[in] hWnd			��������ʾ��Χ�Ĵ��ھ��
 * \param		[in] left			��ʾ��Χ��λ��
 * \param		[in] top			��ʾ��Χ��λ��
 * \param		[in] right			��ʾ��Χ��λ��
 * \param		[in] bottom			��ʾ��Χ��λ��
 * \return		�����룬ͬC�ӿں���
 * \date		2016-12-07
 * \note		
 */	
	API_PLAYER int setDisplayRegion(int id, void *hWnd, long left, long top, long right, long bottom);

/**
 * \brief		��Ӳ��Ŵ��� 
 * \param		[in] id				Ƶ����
 * \param		[in] hWnd			����ӵ���ʾ���ھ��
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		��ӵĵ�һ������Ϊ�����ڣ�������ӵĴ���Ϊ�Ӵ��ڡ�
 */	
	API_PLAYER int addWindow(int id, void *hWnd);

/**
 * \brief		ɾ�����Ŵ���
 * \param		[in] id				Ƶ����
 * \param		[in] hWnd			��ɾ������ʾ���ھ��	
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		
 */	
	API_PLAYER int removeWindow(int id, void *hWnd);
	
/**
 * \brief		ץͼ�ӿ�
 * \param		[in] id				Ƶ����
 * \param		[in] fileName		�ļ���
 * \param		[in] format			��ʽ�����format_t
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		
 */	
	API_PLAYER int snapPicture(int id, const char *fileName, format_t format = FORMAT_JPG);

/**
 * \brief		������
 * \param		[in] id				Ƶ����
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		�������ƽӿ�
 * \note		
 */	
	API_PLAYER int openSound(int id);

/**
 * \brief		�ر�����
 * \param		[in] id				Ƶ����
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		�������ƽӿ�
 * \note		
 */	
	API_PLAYER int closeSound(int id);

/**
 * \brief		��ȡ����ֵ
 * \param		[in] id				Ƶ����
 * \param		[out] volume		����ֵ  
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		�������ƽӿ�
 * \note		
 */	
	API_PLAYER int getVolume(int id, unsigned short &volume);

/**
 * \brief		��������ֵ
 * \param		[in] id				Ƶ����
 * \param		[in] volume			����ֵ  
 * \return		�����룬ͬC�ӿں��� 
 * \date		2016-09-07
 * \note		�������ƽӿ�
 * \note		
 */		
	API_PLAYER int setVolume(int id, unsigned short volume);

/**
 * \brief		��ȡɫ��ֵ
 * \param		[in] id				Ƶ����
 * \param		[out] brightness	����ֵ 
 * \param		[out] contrast		ɫ��ֵ  
 * \param		[out] saturation   	�Աȶ� 
 * \param		[out] hue  			���Ͷ�  
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		���������ȣ�ɫ�ȣ��Աȶȣ����Ͷ�
 */
	API_PLAYER int getColor(int id, int &brightness, int &contrast, int &saturation, int &hue);
	
/**
 * \brief		����ɫ��ֵ
 * \param		[in] id				Ƶ����
 * \param		[in] brightness		����ֵ 
 * \param		[in] contrast		ɫ��ֵ  
 * \param		[in] saturation   	�Աȶ� 
 * \param		[in] hue  			���Ͷ�  
 * \return		�����룬ͬC�ӿں���	 
 * \date		2016-09-07
 * \note		���������ȣ�ɫ�ȣ��Աȶȣ����Ͷ�
 */	
	API_PLAYER int setColor(int id, int brightness, int contrast, int saturation, int hue);

/**
 * \brief		���ſ���
 * \param		[in] id				Ƶ����
 * \param		[in] option			����������playControl_t
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note			
 */	
	API_PLAYER int playControl(int id, playControl_t option);

/**
 * \brief		���ò��Ž���
 * \param		[in] id				Ƶ����
 * \param		[in] position		���Ž��ȣ���Χ��0>position>100��
 * \return		�����룬ͬC�ӿں���		
 * \date		2016-09-07
 * \note		�ļ�ģʽר��
 */	
	API_PLAYER int setPlayPosition(int id, int position);
	
/**
 * \brief		��ȡ���Ž���
 * \param		[in] id				Ƶ����
 * \param		[out] position		���Ž���
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		�ļ�ģʽר��
 * \note		
 */	
	API_PLAYER int getPlayPosition(int id, int &position);

/**
 * \brief		����ļ���֡��
 * \param		[in] id				Ƶ����
 * \param		[out] number		�ļ���֡��
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		
 */	
	API_PLAYER int getFileTotalFrame(int id, unsigned long &number);

/**
 * \brief		����ļ���ǰ����֡��
 * \param		[in] id				Ƶ����
 * \param		[out] number		�ļ���ǰ����֡��
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		
 */		
	API_PLAYER int getFileCurrentFrame(int id, unsigned long &number);
	
/**
 * \brief		�����ļ���ǰ����֡��
 * \param		[in] id			Ƶ����
 * \param		[in] number			�ļ���ǰ����֡��
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		
 */		
	API_PLAYER int setFileCurrentFrame(int id, unsigned long number);

/**
 * \brief		��õ�ǰ����ʱ��
 * \param		[in] id				Ƶ����
 * \param		[out] dwYear		��
 * \param		[out] dwMonth		��
 * \param		[out] dwDay			��
 * \param		[out] dwHour		ʱ
 * \param		[out] dwMinute		��
 * \param		[out] dwSecond		��
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		
 */	
	API_PLAYER int getCurrentPlayTime(int id, unsigned long &year, unsigned long &month, unsigned long &day, 
								unsigned long &hour, unsigned long &minute, unsigned long &second); 

/**
 * \brief		��ȡԴ������֡����
 * \param		[in] id				Ƶ����
 * \param		[out] number		Դ������֡����
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		
 */		
	API_PLAYER int getSourceBufferRemain(int id, unsigned long &number);
		
/**
 * \brief		��ȡԭʼͼ���С
 * \param		[in] id				Ƶ����
 * \param		[out] width			��
 * \param		[out] height		��
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		
 */	
	API_PLAYER int getPictureSize(int id, int &width, int &height);

/**
 * \brief		����drawCallback�ص�����
 * \param		[in] id				Ƶ����
 * \param		[in] cb				�ص�����ָ��
 * \param		[in] data	  		�û����� 
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note	    
 */
	API_PLAYER int setDrawCallback(int id, drawCallback cb, void *data);

/**
 * \brief		�����ļ�������Ļص�����
 * \param		[in] id				Ƶ����
 * \param		[in] cb				�ص�����ָ�� 
 * \param		[in] data	  		�û����� 
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		
 */		
	API_PLAYER int setFileEndCallback(int id, fileEndCallback cb, void *data);

/**
 * \brief		��ѯ��Ϣ
 * \param		[in] id				Ƶ����
 * \param		[in] cmd			����
 * \param		[out] buff  		��ѯ���õ���Ϣ
 * \param		[in] len  			buff�ĳ���
 * \param		[out] returnLen  	��ѯ���õ���Ϣ����Ч����
 * \return		�����룬ͬC�ӿں���
 * \date		2016-08-31
 * \note		��������ǰʱ�䡢֡����Ϣ��ý����Ϣ
 */
	API_PLAYER int queryInfo(int id, queryCmd_t cmd, char *buff, int len, int &returnLen);

	/**
 * \brief		�������������ɼ�
 * \param		[in] id				Ƶ����
 * \param		[in] cb				�ص�����	 
 * \param		[in] sampleBit		����λ����8λ 	
 * \param		[in] sampleRate		ÿ������� 
 * \param		[in] len			����
 * \return		�����룬ͬC�ӿں���	 
 * \date		2016-09-07
 * \note		
 */
	API_PLAYER int startAudioRecord(int id, audioRecordCallback cb, unsigned int sampleBit, unsigned int sampleRate, unsigned int len);

/**
 * \brief		�رձ��������ɼ�
 * \param		[in] id				Ƶ����
 * \return		�����룬ͬC�ӿں���
 * \date		2016-09-07
 * \note		
 */
	API_PLAYER int stopAudioRecord(int id);
};



#if defined(__cplusplus)
extern "C" 
{
#endif

/**
 * \brief		��������Ƶ��
 * \param		[in] manufacturer	�豸���̣����manufacturer_t
 * \param		[in] type			�������ͣ����channel_t	
 * \param		[out] id			�������õ�Ƶ����	
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_LOAD_LIBRARY_FAILED
 * \return		������ PLAYER_ERR_GET_PROC_ADDR_FAILED
 * \return		������ PLAYER_ERR_CANNOT_CREATE_INVALID_CHANNEL
 * \return		������ PLAYER_ERR_CREATE_CHANNEL_FAILED
 * \return		������ PLAYER_ERR_NONE_FREE_CHANNEL
 * \date		2016-09-07
 * \note		
 */
API_PLAYER int Player_createChannel(manufacturer_t manufacturer, channel_t type, int *id);

/**
 * \brief		�ͷŲ���Ƶ��
 * \param		[in] id				���ͷŵ�Ƶ����	 
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_RELEASE_FREE_CHANNEL
 * \date		2016-09-07
 * \note		
 */
API_PLAYER int Player_releaseChannel(int id);


/**
 * \brief		���ò��Ż�������С��ʵʱ��/¼������
 * \param		[in] id				Ƶ����
 * \param		[in] size			���Ż�������С
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_SET_BUFF_POOL_SIZE_WHEN_NOT_STREAM_TYPE
 * \return		������ PLAYER_ERR_CANNOT_SET_BUFF_POOL_SIZE_WHEN_IS_PLAYING
 * \return		������ PLAYER_ERR_CANNOT_SIZE_IS_TOO_SMALL
 * \return		������ PLAYER_ERR_CANNOT_SIZE_IS_TOO_LARGE
 * \date		2017-06-02
 * \note		����play֮ǰ���ò��Ż�������С���������ã���playʱ��ʹ��Ĭ��ֵ
 */
API_PLAYER int Player_setBuffPoolSize(int id, unsigned long size);



/**
 * \brief		��ʼ���ţ�ʵʱ��/¼������
 * \param		[in] id				Ƶ����
 * \param		[in] streamHeader	����
 * \param		[in] len			���׳���
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_PLAY_WHEN_NOT_STREAM_TYPE
 * \return		������ PLAYER_ERR_CANNOT_PLAY_WHEN_IS_PLAYING
 * \return		������ PLAYER_ERR_CANNOT_PLAY_WHEN_NONE_WINDOW
 * \return		������ PLAYER_ERR_SET_STREAM_OPEN_MODE_FAILED
 * \return		������ PLAYER_ERR_OPEN_STREAM_FAILED
 * \return		������ PLAYER_ERR_SET_DISPLAY_BUF_FAILED
 * \return		������ PLAYER_ERR_PLAY_STREAM_FAILED
 * \date		2016-09-07
 * \note		
 */
API_PLAYER int Player_play_stream(int id, unsigned char *streamHeader, unsigned int len);

/**
 * \brief		��ʼ���ţ�¼���ļ���
 * \param		[in] id				Ƶ����
 * \param		[in] fileName		�ļ���
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_PLAY_WHEN_NOT_FILE_TYPE
 * \return		������ PLAYER_ERR_CANNOT_PLAY_WHEN_IS_PLAYING
 * \return		������ PLAYER_ERR_FILENAME_IS_NULL
 * \return		������ PLAYER_ERR_CANNOT_PLAY_WHEN_NONE_WINDOW
 * \return		������ PLAYER_ERR_OPEN_FILE_FAILED
 * \return		������ PLAYER_ERR_PLAY_FILE_FAILED
 * \date		2016-09-07
 * \note					
 */	
API_PLAYER int Player_play_file(int id, const char *fileName);

/**
 * \brief		ֹͣ����
 * \param		[in] id				Ƶ����
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_STOP_WHEN_IS_NOT_PLAYING
 * \date		2016-09-07
 * \note		
 */	
API_PLAYER int Player_stop(int id);

/**
 * \brief		�����������ʾ����Ƶ����
 * \param		[in] id				Ƶ����
 * \param		[in] data			��������ʾ����Ƶ����
 * \param		[in] len			��Ƶ���ݳ���
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_INPUT_WHEN_NOT_STREAM_TYPE
 * \return		������ PLAYER_ERR_CANNOT_INPUT_WHEN_IS_NOT_PLAYING
 * \return		������ PLAYER_ERR_INPUT_FAILED
 * \date		2016-09-07
 * \note		
 */	
API_PLAYER int Player_inputData(int id, unsigned char *data, unsigned int len); 

/**
 * \brief		���ý�������
 * \param		[in] id				Ƶ����
 * \param		[in] type			�������ͣ���decode_t	 
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_SET_DECODE_WHEN_AUDIO_RECORDING
 * \return		������ PLAYER_ERR_CANNOT_SET_DECODE_WHEN_NOT_STREAM_TYPE
 * \return		������ PLAYER_ERR_CANNOT_SET_DECODE_WHEN_IS_NOT_PLAYING
 * \return		������ PLAYER_ERR_CANNOT_SET_DECODE_WHEN_IS_PLAYING
 * \return		������ PLAYER_ERR_SET_DECODE_FAILED
 * \return		������ PLAYER_ERR_DONOT_SUPPORT_HARD_DECODE
 * \date		2016-09-07
 * \note		����Ӳ����ģʽʱ���н϶๦�ܲ����ݣ��ʲ�������á�
 */
API_PLAYER int Player_setDecodeType(int id, decode_t type); 

/**
 * \brief		��ȡ��������	
 * \param		[in] id				Ƶ����
 * \param		[out] type			�������ͣ���decode_t
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_GET_DECODE_WHEN_AUDIO_RECORDING
 * \return		������ PLAYER_ERR_CANNOT_GET_DECODE_WHEN_NOT_STREAM_TYPE
 * \date		2016-09-07
 * \note		
 */	
API_PLAYER int Player_getDecodeType(int id, decode_t *type); 

/**
 * \brief		������ʾ��Χ 
 * \param		[in] id				Ƶ����
 * \param		[in] hWnd			��������ʾ��Χ�Ĵ��ھ��
 * \param		[in] left			��ʾ��Χ��λ��
 * \param		[in] top			��ʾ��Χ��λ��
 * \param		[in] right			��ʾ��Χ��λ��
 * \param		[in] bottom			��ʾ��Χ��λ��
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_HWND_IS_NULL
 * \return		������ PLAYER_ERR_RECT_IS_NULL
 * \return		������ PLAYER_ERR_SET_DISPLAY_REGION_FAILED
 * \date		2016-12-07
 * \note		
 */	
API_PLAYER int Player_setDisplayRegion(int id, void *hWnd, long left, long top, long right, long bottom);

/**
 * \brief		��Ӳ��Ŵ��� 
 * \param		[in] id				Ƶ����
 * \param		[in] hWnd			����ӵ���ʾ���ھ��
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_ADD_MORE_WINDOW
 * \return		������ PLAYER_ERR_CANNOT_ADD_EXISTENCE_WINDOW
 * \date		2016-09-07
 * \note		��ӵĵ�һ������Ϊ�����ڣ�������ӵĴ���Ϊ�Ӵ��ڡ�
 */	
API_PLAYER int Player_addWindow(int id, void *hWnd);

/**
 * \brief		ɾ�����Ŵ���
 * \param		[in] id				Ƶ����
 * \param		[in] hWnd			��ɾ������ʾ���ھ��	
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_REMOVE_FIRST_WINDOW_WHEN_PLAYING
 * \return		������ PLAYER_ERR_CANNOT_REMOVE_INEXISTENCE_WINDOW
 * \date		2016-09-07
 * \note		
 */	
API_PLAYER int Player_removeWindow(int id, void *hWnd);
	
/**
 * \brief		ץͼ�ӿ�
 * \param		[in] id				Ƶ����
 * \param		[in] fileName		�ļ���
 * \param		[in] format			��ʽ�����format_t
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_SNAP_WHEN_NOT_PLAYING
 * \return		������ PLAYER_ERR_CANNOT_SNAP_WHEN_HARD_DECODE
 * \return		������ PLAYER_ERR_GET_PICTURE_SIZE_FAILED
 * \return		������ PLAYER_ERR_SNAP_FAILED
 * \date		2016-09-07
 * \note		
 */	
API_PLAYER int Player_snapPicture(int id, const char *fileName, format_t format = FORMAT_JPG);

/**
 * \brief		������
 * \param		[in] id				Ƶ����
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPEN_SOUND_WHEN_NOT_PLAYING
 * \return		������ PLAYER_ERR_OPEN_SOUND_FAILED
 * \date		2016-09-07
 * \note		�������ƽӿ�		
 */	
API_PLAYER int Player_openSound(int id);

/**
 * \brief		�ر�����
 * \param		[in] id				Ƶ����
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_CLOSE_SOUND_WHEN_NOT_PLAYING
 * \return		������ PLAYER_ERR_CLOSE_SOUND_FAILED
 * \date		2016-09-07
 * \note		�������ƽӿ�	
 */	
API_PLAYER int Player_closeSound(int id);

/**
 * \brief		��ȡ����ֵ
 * \param		[in] id				Ƶ����
 * \param		[out] volume		����ֵ  
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_GET_VOLUME_WHEN_NOT_PLAYING
 * \date		2016-09-07
 * \note		�������ƽӿ�		
 */	
API_PLAYER int Player_getVolume(int id, unsigned short *volume);

/**
 * \brief		��������ֵ
 * \param		[in] id				Ƶ����
 * \param		[in] volume			����ֵ  
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_SET_VOLUME_WHEN_NOT_PLAYING
 * \return		������ PLAYER_ERR_SET_VOLUME_FAILED
 * \date		2016-09-07
 * \note		�������ƽӿ�		
 */		
API_PLAYER int Player_setVolume(int id, unsigned short volume);

/**
 * \brief		��ȡɫ��ֵ
 * \param		[in] id				Ƶ����
 * \param		[out] brightness	����ֵ 
 * \param		[out] contrast		ɫ��ֵ  
 * \param		[out] saturation   	�Աȶ� 
 * \param		[out] hue  			���Ͷ�  
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_GET_COLOR_WHEN_NOT_PLAYING
 * \return		������ PLAYER_ERR_GET_COLOR_FAILED
 * \date		2016-09-07
 * \note		���������ȣ�ɫ�ȣ��Աȶȣ����Ͷ�
 */
API_PLAYER int Player_getColor(int id, int *brightness, int *contrast, int *saturation, int *hue);
	
/**
 * \brief		����ɫ��ֵ
 * \param		[in] id				Ƶ����
 * \param		[in] brightness		����ֵ 
 * \param		[in] contrast		ɫ��ֵ  
 * \param		[in] saturation   	�Աȶ� 
 * \param		[in] hue  			���Ͷ�  
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_SET_COLOR_WHEN_NOT_PLAYING
 * \return		������ PLAYER_ERR_SET_COLOR_FAILED	
 * \date		2016-09-07
 * \note		���������ȣ�ɫ�ȣ��Աȶȣ����Ͷ�
 */	
API_PLAYER int Player_setColor(int id, int brightness, int contrast, int saturation, int hue);

/**
 * \brief		���ſ���
 * \param		[in] id				Ƶ����
 * \param		[in] option			����������playControl_t
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_PLAY_CONTROL_WHEN_NOT_PLAYBACK
 * \return		������ PLAYER_ERR_CANNOT_PLAY_CONTROL_WHEN_NOT_PLAYING
 * \return		������ PLAYER_ERR_PLAY_CONTROL_FAILED
 * \date		2016-09-07
 * \note			
 */	
API_PLAYER int Player_playControl(int id, playControl_t option);

/**
 * \brief		���ò��Ž���
 * \param		[in] id				Ƶ����
 * \param		[in] position		���Ž��ȣ���Χ��0>position>100��
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_SET_POSITION_WHEN_NOT_FILE_TYPE
 * \return		������ PLAYER_ERR_CANNOT_SET_POSITION_WHEN_NOT_PLAYING
 * \return		������ PLAYER_ERR_OUT_BOUND_POSITION		
 * \return		������ PLAYER_ERR_SET_POSITION_FAILED
 * \date		2016-09-07
 * \note		�ļ�ģʽר��
 */	
API_PLAYER int Player_setPlayPosition(int id, int position);
	
/**
 * \brief		��ȡ���Ž���
 * \param		[in] id				Ƶ����
 * \param		[out] position		���Ž���
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_GET_POSITION_WHEN_NOT_FILE_TYPE
 * \return		������ PLAYER_ERR_CANNOT_GET_POSITION_WHEN_NOT_PLAYING
 * \return		������ PLAYER_ERR_SET_POSITION_FAILED
 * \date		2016-09-07
 * \note		�ļ�ģʽר��
 * \note		
 */	
API_PLAYER int Player_getPlayPosition(int id, int *position);

/**
 * \brief		����ļ���֡��
 * \param		[in] id				Ƶ����
 * \param		[out] number		�ļ���֡��
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_GET_TOTAL_FRAME_WHEN_NOT_FILE_TYPE
 * \return		������ PLAYER_ERR_CANNOT_GET_TOTAL_FRAME_WHEN_NOT_PLAYING
 * \date		2016-09-07
 * \note		
 */	
API_PLAYER int Player_getFileTotalFrame(int id, unsigned long *number);

/**
 * \brief		����ļ���ǰ����֡��
 * \param		[in] id				Ƶ����
 * \param		[out] number		�ļ���ǰ����֡��
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_GET_CURRENT_FRAME_WHEN_NOT_FILE_TYPE
 * \return		������ PLAYER_ERR_CANNOT_GET_CURRENT_FRAME_WHEN_NOT_PLAYING
 * \date		2016-09-07
 * \note		
 */		
API_PLAYER int Player_getFileCurrentFrame(int id, unsigned long *number);
	
/**
 * \brief		�����ļ���ǰ����֡��
 * \param		[in] id				Ƶ����
 * \param		[in] number			�ļ���ǰ����֡��
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_SET_CURRENT_FRAME_WHEN_NOT_FILE_TYPE
 * \return		������ PLAYER_ERR_CANNOT_SET_CURRENT_FRAME_WHEN_NOT_PLAYING
 * \return		������ PLAYER_ERR_SET_CURRENT_FRAME_FAILED
 * \date		2016-09-07
 * \note		
 */		
API_PLAYER int Player_setFileCurrentFrame(int id, unsigned long number);

/**
 * \brief		��õ�ǰ����ʱ��
 * \param		[in] id				Ƶ����
 * \param		[out] dwYear		��
 * \param		[out] dwMonth		��
 * \param		[out] dwDay			��
 * \param		[out] dwHour		ʱ
 * \param		[out] dwMinute		��
 * \param		[out] dwSecond		��
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_GET_CURRENT_TIME_WHEN_NOT_PLAYBACK
 * \return		������ PLAYER_ERR_CANNOT_GET_CURRENT_TIME_WHEN_NOT_PLAYING
 * \return		������ PLAYER_ERR_GET_CURRENT_TIME_FAILED
 * \date		2016-09-07
 * \note		
 */	
API_PLAYER int Player_getCurrentPlayTime(int id, unsigned long *year, unsigned long *month, unsigned long *day, 
								unsigned long *hour, unsigned long *minute, unsigned long *second); 

/**
 * \brief		��ȡԴ������֡����
 * \param		[in] id				Ƶ����
 * \param		[out] number		Դ������֡����
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_GET_REMAIN_WHEN_NOT_PLAYBACK
 * \return		������ PLAYER_ERR_CANNOT_GET_REMAIN_WHEN_NOT_PLAYING
 * \date		2016-09-07
 * \note		
 */		
API_PLAYER int Player_getSourceBufferRemain(int id, unsigned long *number);
		
/**
 * \brief		��ȡԭʼͼ���С
 * \param		[in] id				Ƶ����
 * \param		[out] width			��
 * \param		[out] height		��
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_GET_PICTURE_SIZE_WHEN_AUDIO_RECORDING
 * \return		������ PLAYER_ERR_CANNOT_GET_PICTURE_SIZE_WHEN_NOT_PLAYING
 * \return		������ PLAYER_ERR_GET_PICTURE_SIZE_FAILED
 * \date		2016-09-07
 * \note		
 */	
API_PLAYER int Player_getPictureSize(int id, int *width, int *height);

/**
 * \brief		����drawCallback�ص�����
 * \param		[in] id				Ƶ����
 * \param		[in] cb				�ص�����ָ��
 * \param		[in] data	  		�û����� 
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CB_IS_NULL
 * \return		������ PLAYER_ERR_SET_DRAW_CALLBACK_FAILED
 * \date		2016-09-07
 * \note	    
 */
API_PLAYER int Player_setDrawCallback(int id, drawCallback cb, void *data);

/**
 * \brief		�����ļ�������Ļص�����
 * \param		[in] id				Ƶ����
 * \param		[in] cb				�ص�����ָ�� 
 * \param		[in] data	  		�û����� 
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CB_IS_NULL
 * \return		������ PLAYER_ERR_SET_FILE_END_CALLBACK_FAILED
 * \date		2016-09-07
 * \note		
 */		
API_PLAYER int Player_setFileEndCallback(int id, fileEndCallback cb, void *data);

/**
 * \brief		��ѯ��Ϣ
 * \param		[in] id				Ƶ����
 * \param		[in] cmd			����
 * \param		[out] buff  		��ѯ���õ���Ϣ
 * \param		[in] len  			buff�ĳ���
 * \param		[out] returnLen  	��ѯ���õ���Ϣ����Ч����
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_BUFF_IS_NULL
 * \return		������ PLAYER_ERR_OUT_BOUND_CMD
 * \return		������ PLAYER_ERR_DO_NOT_SUPPORT_QUERY_MEDIA
 * \return		������ PLAYER_ERR_QUERY_INFO_FAILED
 * \date		2016-09-07
 * \note		��������ǰʱ�䡢֡����Ϣ��ý����Ϣ
 */
API_PLAYER int Player_queryInfo(int id, queryCmd_t cmd, char *buff, int len, int *returnLen);

/**
 * \brief		�������������ɼ�
 * \param		[in] id				Ƶ����
 * \param		[in] cb				�ص�����	 
 * \param		[in] sampleBit		����λ����8λ 	
 * \param		[in] sampleRate		ÿ������� 
 * \param		[in] len			����
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_START_RECORD_WHEN_NOT_AUDIO_RECORD
 * \return		������ PLAYER_ERR_CB_IS_NULL
 * \return		������ PLAYER_ERR_START_AUDIO_RECORD_FAILED
 * \date		2016-09-07
 * \note		
 */
API_PLAYER int Player_startAudioRecord(int id, audioRecordCallback cb, unsigned int sampleBit, unsigned int sampleRate, unsigned int len);

/**
 * \brief		�رձ��������ɼ�
 * \param		[in] id				Ƶ����
 * \return		������ PLAYER_ERR_SUCCESS
 * \return		������ PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		������ PLAYER_ERR_CANNOT_STOP_RECORD_WHEN_NOT_AUDIO_RECORD
 * \return		������ PLAYER_ERR_STOP_AUDIO_RECORD_FAILED 
 * \date		2016-09-07
 * \note		
 */
API_PLAYER int Player_stopAudioRecord(int id);

#if defined(__cplusplus)
}
#endif
/** 
\}
*/
/**
\} 
*/
/**
\} 
*/
#endif
