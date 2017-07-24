/**
* \file		player.h
* \brief	播放库接口定义
* \author  	dahuasys
* \date		2016-09-07
* \note		将大华、海康、华燕三家厂商所提供的播放库，进行整合，对外提供统一的接口
* \defgroup	通用解码库
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


#define CHANNEL_NUM_MAX 64	//频道的最大数。（不能大于华雁的port最大数100）
#define WINDOWS_NUM_MAX 16	//显示窗口的最大数，跟研发中心确认过，解码库中的MAX_DISPLAY_WND宏是错误的，实际支持16个窗口


// 设备厂商类型定义
enum manufacturer_t
{
	MANU_DH = 0,  // 大华
	MANU_HK,        // 海康
	MANU_VN       // 华雁
};

// 解码类型定义
enum decode_t
{
	DECODE_SOFT = 0,	// 硬解码
	DECODE_HARD,		// 软解码
};

// 图片格式定义
enum format_t
{
	FORMAT_BMP = 0, //BMP位图
	FORMAT_JPG      //JPG图片
};

// 播放控制类型
enum playControl_t
{
	PLAY_NORMAL = 0, // 正常播放
	PLAY_FAST,       // 加速播放
	PLAY_SLOW,       // 减速播放
	PLAY_PAUSE,      // 暂停播放
	PLAY_PLAY,       // 暂停恢复
	PLAY_ONE_BY_ONE, // 单帧播放
	PLAY_ONE_BY_ONE_BACK, // 单帧倒放
	PLAY_RESET_BUFFER, //清空缓冲区
};

// 获取当前时间、帧率、媒体信息
enum queryCmd_t
{
	QUERY_TIME = 0,	// 查询编码中时间信息，单位ms（大华、华雁，支持）
	QUERY_RATE,		// 查询帧率信息（大华、华雁，支持）
	QUERY_MEDIA,	// 查询媒体信息（大华，支持）
};

// 播放频道的类型
enum channel_t
{
	CHANNEL_REALPLAY = 0,		// 实时视频
	CHANNEL_PLAYBACK_STREAM,	// 录像回放（流模式）
	CHANNEL_PLAYBACK_FILE,		// 录像回放（文件模式）
	//CHANNEL_AUDIORECORD,		// 语音采集
	CHANNEL_INVALID,			// 无效的类型，当调用PLAY_GetFreePort失败时，会将m_type修改成无效的类型
};

//错误码
enum
{
	PLAYER_ERR_SUCCESS							= 0,	//成功
	PLAYER_ERR_LOAD_LIBRARY_FAILED				= -1,	//加载解码库失败
	PLAYER_ERR_GET_PROC_ADDR_FAILED				= -2,	//加载解码库函数地址失败
	PLAYER_ERR_CANNOT_CREATE_INVALID_CHANNEL	= -3,	//无法创建一个类型为“无效”的频道
	PLAYER_ERR_CREATE_CHANNEL_FAILED			= -4,	//创建频道失败（解码库没有空闲的port）
	PLAYER_ERR_NONE_FREE_CHANNEL				= -5,	//申请不到空闲频道
	PLAYER_ERR_OUT_BOUND_CHANNEL				= -6,	//频道号越界
	PLAYER_ERR_RELEASE_FREE_CHANNEL				= -7,	//无法释放空闲的频道
	PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL		= -8,	//无法操作空闲的频道
	
	PLAYER_ERR_CANNOT_PLAY_WHEN_NOT_STREAM_TYPE	= -10,	//当前不处于流模式，无法播放
	PLAYER_ERR_CANNOT_PLAY_WHEN_IS_PLAYING		= -11,	//当前已正在播放中，无法播放
	PLAYER_ERR_CANNOT_PLAY_WHEN_NONE_WINDOW		= -12,	//当前还未添加窗口，无法播放
	PLAYER_ERR_SET_STREAM_OPEN_MODE_FAILED		= -13,	//设置流打开的模式时失败
	PLAYER_ERR_OPEN_STREAM_FAILED				= -14,	//打开流失败
	PLAYER_ERR_SET_DISPLAY_BUF_FAILED			= -15,	//设置显示缓冲失败
	PLAYER_ERR_PLAY_STREAM_FAILED				= -16,	//播放流失败
	PLAYER_ERR_SET_FILE_REF_CALLBACK_FAILED		= -17,	//设置文件索引失败

	PLAYER_ERR_CANNOT_PLAY_WHEN_NOT_FILE_TYPE	= -20,	//当前不处于文件模式，无法播放
	PLAYER_ERR_FILENAME_IS_NULL					= -21,	//文件名称为NULL
	PLAYER_ERR_OPEN_FILE_FAILED					= -22,	//打开文件失败
	PLAYER_ERR_PLAY_FILE_FAILED					= -23,	//播放文件失败

	PLAYER_ERR_CANNOT_STOP_WHEN_IS_NOT_PLAYING	= -25,	//当前不在播放中，无法停止播放

	PLAYER_ERR_CANNOT_SET_BUFF_POOL_SIZE_WHEN_NOT_STREAM_TYPE	= -26,	//当前不处于流模式，无法设置播放缓冲区大小
	PLAYER_ERR_CANNOT_SET_BUFF_POOL_SIZE_WHEN_IS_PLAYING		= -27,	//当前已正在播放中，无法设置播放缓冲区大小
	PLAYER_ERR_CANNOT_SIZE_IS_TOO_SMALL	= 28,			//传入的size太小，最小值为1024*50
	PLAYER_ERR_CANNOT_SIZE_IS_TOO_LARGE	= 29,			//传入的size太大，最大值为1024*100000

	PLAYER_ERR_CANNOT_INPUT_WHEN_NOT_STREAM_TYPE= -30,	//当前不处于流模式，无法送入数据
	PLAYER_ERR_CANNOT_INPUT_WHEN_IS_NOT_PLAYING	= -31,	//当前不在播放中，无法送入数据
	PLAYER_ERR_INPUT_FAILED						= -32,	//送入数据失败

	PLAYER_ERR_CANNOT_SET_DECODE_WHEN_IS_PLAYING	= -34,	//当前郑在播放中，无法设置解码模式
	PLAYER_ERR_CANNOT_SET_DECODE_WHEN_AUDIO_RECORDING= -35,	//录音采集模式下，无法设置解码模式
	PLAYER_ERR_CANNOT_SET_DECODE_WHEN_NOT_STREAM_TYPE= -36,	//当前不处于流模式，无法设置解码模式
	PLAYER_ERR_CANNOT_SET_DECODE_WHEN_IS_NOT_PLAYING = -37, //当前不在播放中，无法设置解码模式
	PLAYER_ERR_SET_DECODE_FAILED					= -38,	//设置解码模式失败
	PLAYER_ERR_DONOT_SUPPORT_HARD_DECODE			= -39,	//你的电脑不支持硬解码
	PLAYER_ERR_CANNOT_GET_DECODE_WHEN_AUDIO_RECORDING= -40,	//录音采集模式下，无法获取解码模式
	PLAYER_ERR_CANNOT_GET_DECODE_WHEN_NOT_STREAM_TYPE= -41,	//当前不处于流模式，无法获取解码模式

	PLAYER_ERR_HWND_IS_NULL							= -42,	//设置显示范围失败，传入HWDS为NULL
	PLAYER_ERR_SET_DISPLAY_REGION_FAILED			= -43,	//设置显示范围失败

	PLAYER_ERR_CANNOT_ADD_MORE_WINDOW				= -45,	//无法添加更多的窗口
	PLAYER_ERR_CANNOT_ADD_EXISTENCE_WINDOW			= -46,	//无法添加已存在的窗口
	PLAYER_ERR_CANNOT_REMOVE_FIRST_WINDOW_WHEN_PLAYING= -47,//无法删除正在播放的“主”窗口
	PLAYER_ERR_CANNOT_REMOVE_INEXISTENCE_WINDOW		= -48,	//无法删除不存在的窗口

	PLAYER_ERR_CANNOT_SNAP_WHEN_NOT_PLAYING			= -50,	//当前不在播放中，无法抓图
	PLAYER_ERR_CANNOT_SNAP_WHEN_HARD_DECODE			= -51,	//当前处于硬解码模式，无法抓图
	PLAYER_ERR_SNAP_FAILED							= -52,	//抓图失败

	PLAYER_ERR_CANNOT_OPEN_SOUND_WHEN_NOT_PLAYING	= -55,	//当前不在播放中，无法打开声音
	PLAYER_ERR_OPEN_SOUND_FAILED					= -56,	//打开声音失败
	PLAYER_ERR_CANNOT_CLOSE_SOUND_WHEN_NOT_PLAYING	= -57,	//当前不在播放中，无法关闭声音
	PLAYER_ERR_CLOSE_SOUND_FAILED					= -58,	//关闭声音失败

	PLAYER_ERR_CANNOT_GET_VOLUME_WHEN_NOT_PLAYING	= -60,	//当前不在播放中，无法获取音量值
	PLAYER_ERR_CANNOT_SET_VOLUME_WHEN_NOT_PLAYING	= -61,	//当前不在播放中，无法设置音量值
	PLAYER_ERR_SET_VOLUME_FAILED					= -62,	//设置音量值失败

	PLAYER_ERR_CANNOT_GET_COLOR_WHEN_NOT_PLAYING= -65,	//当前不在播放中，无法获取色彩值
	PLAYER_ERR_GET_COLOR_FAILED					= -66,	//获取色彩值失败
	PLAYER_ERR_CANNOT_SET_COLOR_WHEN_NOT_PLAYING= -67,	//当前不在播放中，无法设置色彩值
	PLAYER_ERR_SET_COLOR_FAILED					= -68,	//设置色彩值失败

	PLAYER_ERR_CANNOT_PLAY_CONTROL_WHEN_NOT_PLAYBACK= -70,	//当前不在回放模式下，无法进行播放控制
	PLAYER_ERR_CANNOT_PLAY_CONTROL_WHEN_NOT_PLAYING	= -71,	//当前不在播放中，无法行播放控制
	PLAYER_ERR_PLAY_CONTROL_FAILED					= -72,	//播放控制失败

	PLAYER_ERR_CANNOT_SET_POSITION_WHEN_NOT_FILE_TYPE= -75,	//当前不在文本回放模式下，无法设置播放进度值
	PLAYER_ERR_CANNOT_SET_POSITION_WHEN_NOT_PLAYING	= -76,	//当前不在播放中，无法设置播放进度值
	PLAYER_ERR_OUT_BOUND_POSITION					= -77,	//position值越界
	PLAYER_ERR_SET_POSITION_FAILED					= -78,	//设置播放进度失败
	PLAYER_ERR_CANNOT_GET_POSITION_WHEN_NOT_FILE_TYPE= -79,	//当前不在文本回放模式下，无法获取播放进度值
	PLAYER_ERR_CANNOT_GET_POSITION_WHEN_NOT_PLAYING= -80,	//当前不在播放中，无法获取播放进度值

	PLAYER_ERR_CANNOT_GET_TOTAL_FRAME_WHEN_NOT_FILE_TYPE= -85,	//当前不在文件回放模式下，无法获取文件总帧数
	PLAYER_ERR_CANNOT_GET_TOTAL_FRAME_WHEN_NOT_PLAYING	= -86,	//当前不在播放中，无法获取文件总帧数
	PLAYER_ERR_CANNOT_GET_CURRENT_FRAME_WHEN_NOT_FILE_TYPE= -87,//当前不在文件回放模式下，无法获取文件当前帧数
	PLAYER_ERR_CANNOT_GET_CURRENT_FRAME_WHEN_NOT_PLAYING= -88,	//当前不在播放中，无法获取文件当前帧数
	PLAYER_ERR_CANNOT_SET_CURRENT_FRAME_WHEN_NOT_FILE_TYPE= -89,//当前不在文件回放模式下，无法设置文件当前帧数
	PLAYER_ERR_CANNOT_SET_CURRENT_FRAME_WHEN_NOT_PLAYING= -90,	//当前不在播放中，无法设置文件当前帧数
	PLAYER_ERR_SET_CURRENT_FRAME_FAILED					= -91,	//设置文件当前帧数失败
	
	PLAYER_ERR_CANNOT_GET_CURRENT_TIME_WHEN_NOT_PLAYBACK= -95,	//当前不在回放模式下，无法获取当前播放时间
	PLAYER_ERR_CANNOT_GET_CURRENT_TIME_WHEN_NOT_PLAYING	= -96,	//当前不在播放中，无法获取当前播放时间
	PLAYER_ERR_GET_CURRENT_TIME_FAILED					= -97,	//获取当前播放时间失败

	PLAYER_ERR_CANNOT_GET_REMAIN_WHEN_NOT_PLAYBACK		= -100,	//当前不在回放模式下，无法获取当前剩余帧数
	PLAYER_ERR_CANNOT_GET_REMAIN_WHEN_NOT_PLAYING		= -101,	//当前不在播放中，无法获取当前剩余帧数
	
	PLAYER_ERR_CANNOT_GET_PICTURE_SIZE_WHEN_AUDIO_RECORDING= -105,//当前处于语音采集中，无法获取图片尺寸
	PLAYER_ERR_CANNOT_GET_PICTURE_SIZE_WHEN_NOT_PLAYING	= -106,	//当前不在播放中，无法获取图片尺寸
	PLAYER_ERR_GET_PICTURE_SIZE_FAILED			= -107,	//获取图片尺寸失败

	PLAYER_ERR_CB_IS_NULL						= -110,	//传入的cb为NULL
	PLAYER_ERR_SET_DRAW_CALLBACK_FAILED			= -111,	//设置显示结束回调函数失败
	PLAYER_ERR_SET_FILE_END_CALLBACK_FAILED		= -112,	//设置文件结束回调函数失败
	PLAYER_ERR_TRY_LOCK_FAILED					= -113,	//设置回调时trylock失败，请客户端再执行一次。

	PLAYER_ERR_BUFF_IS_NULL						= -115,	//传入的buff为NULL
	PLAYER_ERR_OUT_BOUND_CMD					= -116,	//传入的命令字越界
	PLAYER_ERR_DO_NOT_SUPPORT_QUERY_MEDIA		= -117,	//不支持查询媒体信息
	PLAYER_ERR_QUERY_INFO_FAILED				= -118,	//查询信息失败

	PLAYER_ERR_CANNOT_START_RECORD_WHEN_NOT_AUDIO_RECORD= -120,	//当前不处于语音采集模式，无法开启语音采集
	PLAYER_ERR_START_AUDIO_RECORD_FAILED				= -121,	//开启语音采集失败
	PLAYER_ERR_CANNOT_STOP_RECORD_WHEN_NOT_AUDIO_RECORD	= -122,	//当前不处于语音采集模式，无法关闭语音采集
	PLAYER_ERR_STOP_AUDIO_RECORD_FAILED					= -123,	//关闭语音采集失败
};

#define PLAYER_CALLBACK    __stdcall
/**
 * \defgroup	播放器接口
 * \{
 */

/**
 * \brief		一帧画完的回调函数定义
 * \param		[in] hdc		显示窗口的句柄 
 * \param		[in] width		宽 	
 * \param		[in] height		高
 * \param		[in] data		用户自定义数据 
 * \return		void
 * \date		2016-09-07
 * \note		可用于显示OSD。
 * \note		在本函数内，应避免耗时的绘图工作，以免影响性能
 */
typedef void (PLAYER_CALLBACK *drawCallback)(void *hdc, unsigned int width, unsigned int height, void *data);

/**
 * \brief		文件回放结束的回调函数定义
 * \param		[in] fileName	文件名称
 * \param		[in] data		用户自定义数据 
 * \return		void
 * \date		2016-09-07
 */
typedef void (PLAYER_CALLBACK *fileEndCallback)(const char *fileName, void *data);

/**
 * \brief		语音采集数据回调定义
 * \param		[in] data		数据	 
 * \param		[in] len		数据长度	 
 * \return		void
 * \date		2016-09-07
 * \note		
 */
typedef void (PLAYER_CALLBACK *audioRecordCallback)(unsigned char *data, unsigned int len);



/**
 * \class		player命名空间
 * \brief		播放器接口类定义
 * \date		2016-09-07
 */
namespace player
{	
	//仅供内部使用
	API_PLAYER void PLAYER_CALLBACK doDrawCallback(int port, void *hdc, void *data);
	API_PLAYER void PLAYER_CALLBACK doDrawCallback_2(int port, void *hdc, long data);
	API_PLAYER void PLAYER_CALLBACK doFileEndCallback(int port, void *data);
	API_PLAYER void PLAYER_CALLBACK doFileEndCallback_2(unsigned long port, unsigned long data);
	API_PLAYER void PLAYER_CALLBACK doAudioRecordCallback(unsigned char *audio, unsigned int len, void *data);
	API_PLAYER void PLAYER_CALLBACK doFileRefDoneCallback(int port, long data);

/**
 * \brief		创建播放频道
 * \param		[in] manufacturer	设备厂商，详见manufacturer_t
 * \param		[in] type			播放类型，详见channel_t	
 * \param		[out] id			创建所得的频道号	
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		
 */
	API_PLAYER int createChannel(manufacturer_t manufacturer, channel_t type, int &id);

/**
 * \brief		释放播放频道
 * \param		[in] id				待释放的频道号	 
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		
 */
	API_PLAYER int releaseChannel(int id);

/**
 * \brief		设置播放缓冲区大小（实时流/录像流）
 * \param		[in] id				频道号
 * \param		[in] size			播放缓冲区大小
 * \return		错误码，同C接口函数
 * \date		2017-06-02
 * \note		请在play之前设置播放缓冲区大小。若不设置，则play时将使用默认值
 */
	API_PLAYER int setBuffPoolSize(int id, unsigned long size);

/**
 * \brief		开始播放（实时流/录像流）
 * \param		[in] id				频道号
 * \param		[in] streamHeader	流首
 * \param		[in] len			流首长度
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		
 */
	API_PLAYER int play(int id, unsigned char *streamHeader, unsigned int len);

/**
 * \brief		开始播放（录像文件）
 * \param		[in] id				频道号
 * \param		[in] fileName		文件名
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		
 * \note			
 */	
	API_PLAYER int play(int id, const char *fileName);

/**
 * \brief		停止播放
 * \param		[in] id				频道号
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		
 */	
	API_PLAYER int stop(int id);

/**
 * \brief		送入待解码显示的视频数据
 * \param		[in] id				频道号
 * \param		[in] data			待解码显示的视频数据
 * \param		[in] len			视频数据长度
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		
 */	
	API_PLAYER int inputData(int id, unsigned char *data, unsigned int len); 

/**
 * \brief		设置解码类型
 * \param		[in] id				频道号
 * \param		[in] type			解码类型，见decode_t	 
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		采用硬解码模式时，有较多功能不兼容，故不建议采用。
 */
	API_PLAYER int setDecodeType(int id, decode_t type); 

/**
 * \brief		获取解码类型	
 * \param		[in] id				频道号
 * \param		[out] type			解码类型，见decode_t
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		
 */	
	API_PLAYER int getDecodeType(int id, decode_t &type); 

/**
 * \brief		设置显示范围 
 * \param		[in] id				频道号
 * \param		[in] hWnd			需设置显示范围的窗口句柄
 * \param		[in] left			显示范围左位置
 * \param		[in] top			显示范围顶位置
 * \param		[in] right			显示范围右位置
 * \param		[in] bottom			显示范围底位置
 * \return		错误码，同C接口函数
 * \date		2016-12-07
 * \note		
 */	
	API_PLAYER int setDisplayRegion(int id, void *hWnd, long left, long top, long right, long bottom);

/**
 * \brief		添加播放窗口 
 * \param		[in] id				频道号
 * \param		[in] hWnd			需添加的显示窗口句柄
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		添加的第一个窗口为主窗口，后续添加的窗口为从窗口。
 */	
	API_PLAYER int addWindow(int id, void *hWnd);

/**
 * \brief		删除播放窗口
 * \param		[in] id				频道号
 * \param		[in] hWnd			待删除的显示窗口句柄	
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		
 */	
	API_PLAYER int removeWindow(int id, void *hWnd);
	
/**
 * \brief		抓图接口
 * \param		[in] id				频道号
 * \param		[in] fileName		文件名
 * \param		[in] format			格式，详见format_t
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		
 */	
	API_PLAYER int snapPicture(int id, const char *fileName, format_t format = FORMAT_JPG);

/**
 * \brief		打开语音
 * \param		[in] id				频道号
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		语音控制接口
 * \note		
 */	
	API_PLAYER int openSound(int id);

/**
 * \brief		关闭语音
 * \param		[in] id				频道号
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		语音控制接口
 * \note		
 */	
	API_PLAYER int closeSound(int id);

/**
 * \brief		获取音量值
 * \param		[in] id				频道号
 * \param		[out] volume		音量值  
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		语音控制接口
 * \note		
 */	
	API_PLAYER int getVolume(int id, unsigned short &volume);

/**
 * \brief		设置音量值
 * \param		[in] id				频道号
 * \param		[in] volume			音量值  
 * \return		错误码，同C接口函数 
 * \date		2016-09-07
 * \note		语音控制接口
 * \note		
 */		
	API_PLAYER int setVolume(int id, unsigned short volume);

/**
 * \brief		获取色彩值
 * \param		[in] id				频道号
 * \param		[out] brightness	亮度值 
 * \param		[out] contrast		色度值  
 * \param		[out] saturation   	对比度 
 * \param		[out] hue  			饱和度  
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		包含：亮度，色度，对比度，饱和度
 */
	API_PLAYER int getColor(int id, int &brightness, int &contrast, int &saturation, int &hue);
	
/**
 * \brief		设置色彩值
 * \param		[in] id				频道号
 * \param		[in] brightness		亮度值 
 * \param		[in] contrast		色度值  
 * \param		[in] saturation   	对比度 
 * \param		[in] hue  			饱和度  
 * \return		错误码，同C接口函数	 
 * \date		2016-09-07
 * \note		包含：亮度，色度，对比度，饱和度
 */	
	API_PLAYER int setColor(int id, int brightness, int contrast, int saturation, int hue);

/**
 * \brief		播放控制
 * \param		[in] id				频道号
 * \param		[in] option			播放命令，详见playControl_t
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note			
 */	
	API_PLAYER int playControl(int id, playControl_t option);

/**
 * \brief		设置播放进度
 * \param		[in] id				频道号
 * \param		[in] position		播放进度（范围：0>position>100）
 * \return		错误码，同C接口函数		
 * \date		2016-09-07
 * \note		文件模式专用
 */	
	API_PLAYER int setPlayPosition(int id, int position);
	
/**
 * \brief		获取播放进度
 * \param		[in] id				频道号
 * \param		[out] position		播放进度
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		文件模式专用
 * \note		
 */	
	API_PLAYER int getPlayPosition(int id, int &position);

/**
 * \brief		获得文件总帧数
 * \param		[in] id				频道号
 * \param		[out] number		文件总帧数
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		
 */	
	API_PLAYER int getFileTotalFrame(int id, unsigned long &number);

/**
 * \brief		获得文件当前播放帧号
 * \param		[in] id				频道号
 * \param		[out] number		文件当前播放帧号
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		
 */		
	API_PLAYER int getFileCurrentFrame(int id, unsigned long &number);
	
/**
 * \brief		设置文件当前播放帧号
 * \param		[in] id			频道号
 * \param		[in] number			文件当前播放帧号
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		
 */		
	API_PLAYER int setFileCurrentFrame(int id, unsigned long number);

/**
 * \brief		获得当前播放时间
 * \param		[in] id				频道号
 * \param		[out] dwYear		年
 * \param		[out] dwMonth		月
 * \param		[out] dwDay			日
 * \param		[out] dwHour		时
 * \param		[out] dwMinute		分
 * \param		[out] dwSecond		秒
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		
 */	
	API_PLAYER int getCurrentPlayTime(int id, unsigned long &year, unsigned long &month, unsigned long &day, 
								unsigned long &hour, unsigned long &minute, unsigned long &second); 

/**
 * \brief		获取源缓冲区帧数量
 * \param		[in] id				频道号
 * \param		[out] number		源缓冲区帧数量
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		
 */		
	API_PLAYER int getSourceBufferRemain(int id, unsigned long &number);
		
/**
 * \brief		获取原始图像大小
 * \param		[in] id				频道号
 * \param		[out] width			宽
 * \param		[out] height		高
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		
 */	
	API_PLAYER int getPictureSize(int id, int &width, int &height);

/**
 * \brief		设置drawCallback回调函数
 * \param		[in] id				频道号
 * \param		[in] cb				回调函数指针
 * \param		[in] data	  		用户数据 
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note	    
 */
	API_PLAYER int setDrawCallback(int id, drawCallback cb, void *data);

/**
 * \brief		设置文件播放完的回调函数
 * \param		[in] id				频道号
 * \param		[in] cb				回调函数指针 
 * \param		[in] data	  		用户数据 
 * \return		错误码，同C接口函数
 * \date		2016-09-07
 * \note		
 */		
	API_PLAYER int setFileEndCallback(int id, fileEndCallback cb, void *data);

/**
 * \brief		查询信息
 * \param		[in] id				频道号
 * \param		[in] cmd			命令
 * \param		[out] buff  		查询所得的信息
 * \param		[in] len  			buff的长度
 * \param		[out] returnLen  	查询所得的信息的有效长度
 * \return		错误码，同C接口函数
 * \date		2016-08-31
 * \note		包含：当前时间、帧率信息、媒体信息
 */
	API_PLAYER int queryInfo(int id, queryCmd_t cmd, char *buff, int len, int &returnLen);

	/**
 * \brief		开启本地语音采集
 * \param		[in] id				频道号
 * \param		[in] cb				回调函数	 
 * \param		[in] sampleBit		采样位宽，如8位 	
 * \param		[in] sampleRate		每秒采样率 
 * \param		[in] len			长度
 * \return		错误码，同C接口函数	 
 * \date		2016-09-07
 * \note		
 */
	API_PLAYER int startAudioRecord(int id, audioRecordCallback cb, unsigned int sampleBit, unsigned int sampleRate, unsigned int len);

/**
 * \brief		关闭本地语音采集
 * \param		[in] id				频道号
 * \return		错误码，同C接口函数
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
 * \brief		创建播放频道
 * \param		[in] manufacturer	设备厂商，详见manufacturer_t
 * \param		[in] type			播放类型，详见channel_t	
 * \param		[out] id			创建所得的频道号	
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_LOAD_LIBRARY_FAILED
 * \return		错误码 PLAYER_ERR_GET_PROC_ADDR_FAILED
 * \return		错误码 PLAYER_ERR_CANNOT_CREATE_INVALID_CHANNEL
 * \return		错误码 PLAYER_ERR_CREATE_CHANNEL_FAILED
 * \return		错误码 PLAYER_ERR_NONE_FREE_CHANNEL
 * \date		2016-09-07
 * \note		
 */
API_PLAYER int Player_createChannel(manufacturer_t manufacturer, channel_t type, int *id);

/**
 * \brief		释放播放频道
 * \param		[in] id				待释放的频道号	 
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_RELEASE_FREE_CHANNEL
 * \date		2016-09-07
 * \note		
 */
API_PLAYER int Player_releaseChannel(int id);


/**
 * \brief		设置播放缓冲区大小（实时流/录像流）
 * \param		[in] id				频道号
 * \param		[in] size			播放缓冲区大小
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_SET_BUFF_POOL_SIZE_WHEN_NOT_STREAM_TYPE
 * \return		错误码 PLAYER_ERR_CANNOT_SET_BUFF_POOL_SIZE_WHEN_IS_PLAYING
 * \return		错误码 PLAYER_ERR_CANNOT_SIZE_IS_TOO_SMALL
 * \return		错误码 PLAYER_ERR_CANNOT_SIZE_IS_TOO_LARGE
 * \date		2017-06-02
 * \note		请在play之前设置播放缓冲区大小。若不设置，则play时将使用默认值
 */
API_PLAYER int Player_setBuffPoolSize(int id, unsigned long size);



/**
 * \brief		开始播放（实时流/录像流）
 * \param		[in] id				频道号
 * \param		[in] streamHeader	流首
 * \param		[in] len			流首长度
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_PLAY_WHEN_NOT_STREAM_TYPE
 * \return		错误码 PLAYER_ERR_CANNOT_PLAY_WHEN_IS_PLAYING
 * \return		错误码 PLAYER_ERR_CANNOT_PLAY_WHEN_NONE_WINDOW
 * \return		错误码 PLAYER_ERR_SET_STREAM_OPEN_MODE_FAILED
 * \return		错误码 PLAYER_ERR_OPEN_STREAM_FAILED
 * \return		错误码 PLAYER_ERR_SET_DISPLAY_BUF_FAILED
 * \return		错误码 PLAYER_ERR_PLAY_STREAM_FAILED
 * \date		2016-09-07
 * \note		
 */
API_PLAYER int Player_play_stream(int id, unsigned char *streamHeader, unsigned int len);

/**
 * \brief		开始播放（录像文件）
 * \param		[in] id				频道号
 * \param		[in] fileName		文件名
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_PLAY_WHEN_NOT_FILE_TYPE
 * \return		错误码 PLAYER_ERR_CANNOT_PLAY_WHEN_IS_PLAYING
 * \return		错误码 PLAYER_ERR_FILENAME_IS_NULL
 * \return		错误码 PLAYER_ERR_CANNOT_PLAY_WHEN_NONE_WINDOW
 * \return		错误码 PLAYER_ERR_OPEN_FILE_FAILED
 * \return		错误码 PLAYER_ERR_PLAY_FILE_FAILED
 * \date		2016-09-07
 * \note					
 */	
API_PLAYER int Player_play_file(int id, const char *fileName);

/**
 * \brief		停止播放
 * \param		[in] id				频道号
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_STOP_WHEN_IS_NOT_PLAYING
 * \date		2016-09-07
 * \note		
 */	
API_PLAYER int Player_stop(int id);

/**
 * \brief		送入待解码显示的视频数据
 * \param		[in] id				频道号
 * \param		[in] data			待解码显示的视频数据
 * \param		[in] len			视频数据长度
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_INPUT_WHEN_NOT_STREAM_TYPE
 * \return		错误码 PLAYER_ERR_CANNOT_INPUT_WHEN_IS_NOT_PLAYING
 * \return		错误码 PLAYER_ERR_INPUT_FAILED
 * \date		2016-09-07
 * \note		
 */	
API_PLAYER int Player_inputData(int id, unsigned char *data, unsigned int len); 

/**
 * \brief		设置解码类型
 * \param		[in] id				频道号
 * \param		[in] type			解码类型，见decode_t	 
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_SET_DECODE_WHEN_AUDIO_RECORDING
 * \return		错误码 PLAYER_ERR_CANNOT_SET_DECODE_WHEN_NOT_STREAM_TYPE
 * \return		错误码 PLAYER_ERR_CANNOT_SET_DECODE_WHEN_IS_NOT_PLAYING
 * \return		错误码 PLAYER_ERR_CANNOT_SET_DECODE_WHEN_IS_PLAYING
 * \return		错误码 PLAYER_ERR_SET_DECODE_FAILED
 * \return		错误码 PLAYER_ERR_DONOT_SUPPORT_HARD_DECODE
 * \date		2016-09-07
 * \note		采用硬解码模式时，有较多功能不兼容，故不建议采用。
 */
API_PLAYER int Player_setDecodeType(int id, decode_t type); 

/**
 * \brief		获取解码类型	
 * \param		[in] id				频道号
 * \param		[out] type			解码类型，见decode_t
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_GET_DECODE_WHEN_AUDIO_RECORDING
 * \return		错误码 PLAYER_ERR_CANNOT_GET_DECODE_WHEN_NOT_STREAM_TYPE
 * \date		2016-09-07
 * \note		
 */	
API_PLAYER int Player_getDecodeType(int id, decode_t *type); 

/**
 * \brief		设置显示范围 
 * \param		[in] id				频道号
 * \param		[in] hWnd			需设置显示范围的窗口句柄
 * \param		[in] left			显示范围左位置
 * \param		[in] top			显示范围顶位置
 * \param		[in] right			显示范围右位置
 * \param		[in] bottom			显示范围底位置
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_HWND_IS_NULL
 * \return		错误码 PLAYER_ERR_RECT_IS_NULL
 * \return		错误码 PLAYER_ERR_SET_DISPLAY_REGION_FAILED
 * \date		2016-12-07
 * \note		
 */	
API_PLAYER int Player_setDisplayRegion(int id, void *hWnd, long left, long top, long right, long bottom);

/**
 * \brief		添加播放窗口 
 * \param		[in] id				频道号
 * \param		[in] hWnd			需添加的显示窗口句柄
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_ADD_MORE_WINDOW
 * \return		错误码 PLAYER_ERR_CANNOT_ADD_EXISTENCE_WINDOW
 * \date		2016-09-07
 * \note		添加的第一个窗口为主窗口，后续添加的窗口为从窗口。
 */	
API_PLAYER int Player_addWindow(int id, void *hWnd);

/**
 * \brief		删除播放窗口
 * \param		[in] id				频道号
 * \param		[in] hWnd			待删除的显示窗口句柄	
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_REMOVE_FIRST_WINDOW_WHEN_PLAYING
 * \return		错误码 PLAYER_ERR_CANNOT_REMOVE_INEXISTENCE_WINDOW
 * \date		2016-09-07
 * \note		
 */	
API_PLAYER int Player_removeWindow(int id, void *hWnd);
	
/**
 * \brief		抓图接口
 * \param		[in] id				频道号
 * \param		[in] fileName		文件名
 * \param		[in] format			格式，详见format_t
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_SNAP_WHEN_NOT_PLAYING
 * \return		错误码 PLAYER_ERR_CANNOT_SNAP_WHEN_HARD_DECODE
 * \return		错误码 PLAYER_ERR_GET_PICTURE_SIZE_FAILED
 * \return		错误码 PLAYER_ERR_SNAP_FAILED
 * \date		2016-09-07
 * \note		
 */	
API_PLAYER int Player_snapPicture(int id, const char *fileName, format_t format = FORMAT_JPG);

/**
 * \brief		打开语音
 * \param		[in] id				频道号
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPEN_SOUND_WHEN_NOT_PLAYING
 * \return		错误码 PLAYER_ERR_OPEN_SOUND_FAILED
 * \date		2016-09-07
 * \note		语音控制接口		
 */	
API_PLAYER int Player_openSound(int id);

/**
 * \brief		关闭语音
 * \param		[in] id				频道号
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_CLOSE_SOUND_WHEN_NOT_PLAYING
 * \return		错误码 PLAYER_ERR_CLOSE_SOUND_FAILED
 * \date		2016-09-07
 * \note		语音控制接口	
 */	
API_PLAYER int Player_closeSound(int id);

/**
 * \brief		获取音量值
 * \param		[in] id				频道号
 * \param		[out] volume		音量值  
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_GET_VOLUME_WHEN_NOT_PLAYING
 * \date		2016-09-07
 * \note		语音控制接口		
 */	
API_PLAYER int Player_getVolume(int id, unsigned short *volume);

/**
 * \brief		设置音量值
 * \param		[in] id				频道号
 * \param		[in] volume			音量值  
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_SET_VOLUME_WHEN_NOT_PLAYING
 * \return		错误码 PLAYER_ERR_SET_VOLUME_FAILED
 * \date		2016-09-07
 * \note		语音控制接口		
 */		
API_PLAYER int Player_setVolume(int id, unsigned short volume);

/**
 * \brief		获取色彩值
 * \param		[in] id				频道号
 * \param		[out] brightness	亮度值 
 * \param		[out] contrast		色度值  
 * \param		[out] saturation   	对比度 
 * \param		[out] hue  			饱和度  
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_GET_COLOR_WHEN_NOT_PLAYING
 * \return		错误码 PLAYER_ERR_GET_COLOR_FAILED
 * \date		2016-09-07
 * \note		包含：亮度，色度，对比度，饱和度
 */
API_PLAYER int Player_getColor(int id, int *brightness, int *contrast, int *saturation, int *hue);
	
/**
 * \brief		设置色彩值
 * \param		[in] id				频道号
 * \param		[in] brightness		亮度值 
 * \param		[in] contrast		色度值  
 * \param		[in] saturation   	对比度 
 * \param		[in] hue  			饱和度  
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_SET_COLOR_WHEN_NOT_PLAYING
 * \return		错误码 PLAYER_ERR_SET_COLOR_FAILED	
 * \date		2016-09-07
 * \note		包含：亮度，色度，对比度，饱和度
 */	
API_PLAYER int Player_setColor(int id, int brightness, int contrast, int saturation, int hue);

/**
 * \brief		播放控制
 * \param		[in] id				频道号
 * \param		[in] option			播放命令，详见playControl_t
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_PLAY_CONTROL_WHEN_NOT_PLAYBACK
 * \return		错误码 PLAYER_ERR_CANNOT_PLAY_CONTROL_WHEN_NOT_PLAYING
 * \return		错误码 PLAYER_ERR_PLAY_CONTROL_FAILED
 * \date		2016-09-07
 * \note			
 */	
API_PLAYER int Player_playControl(int id, playControl_t option);

/**
 * \brief		设置播放进度
 * \param		[in] id				频道号
 * \param		[in] position		播放进度（范围：0>position>100）
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_SET_POSITION_WHEN_NOT_FILE_TYPE
 * \return		错误码 PLAYER_ERR_CANNOT_SET_POSITION_WHEN_NOT_PLAYING
 * \return		错误码 PLAYER_ERR_OUT_BOUND_POSITION		
 * \return		错误码 PLAYER_ERR_SET_POSITION_FAILED
 * \date		2016-09-07
 * \note		文件模式专用
 */	
API_PLAYER int Player_setPlayPosition(int id, int position);
	
/**
 * \brief		获取播放进度
 * \param		[in] id				频道号
 * \param		[out] position		播放进度
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_GET_POSITION_WHEN_NOT_FILE_TYPE
 * \return		错误码 PLAYER_ERR_CANNOT_GET_POSITION_WHEN_NOT_PLAYING
 * \return		错误码 PLAYER_ERR_SET_POSITION_FAILED
 * \date		2016-09-07
 * \note		文件模式专用
 * \note		
 */	
API_PLAYER int Player_getPlayPosition(int id, int *position);

/**
 * \brief		获得文件总帧数
 * \param		[in] id				频道号
 * \param		[out] number		文件总帧数
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_GET_TOTAL_FRAME_WHEN_NOT_FILE_TYPE
 * \return		错误码 PLAYER_ERR_CANNOT_GET_TOTAL_FRAME_WHEN_NOT_PLAYING
 * \date		2016-09-07
 * \note		
 */	
API_PLAYER int Player_getFileTotalFrame(int id, unsigned long *number);

/**
 * \brief		获得文件当前播放帧号
 * \param		[in] id				频道号
 * \param		[out] number		文件当前播放帧号
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_GET_CURRENT_FRAME_WHEN_NOT_FILE_TYPE
 * \return		错误码 PLAYER_ERR_CANNOT_GET_CURRENT_FRAME_WHEN_NOT_PLAYING
 * \date		2016-09-07
 * \note		
 */		
API_PLAYER int Player_getFileCurrentFrame(int id, unsigned long *number);
	
/**
 * \brief		设置文件当前播放帧号
 * \param		[in] id				频道号
 * \param		[in] number			文件当前播放帧号
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_SET_CURRENT_FRAME_WHEN_NOT_FILE_TYPE
 * \return		错误码 PLAYER_ERR_CANNOT_SET_CURRENT_FRAME_WHEN_NOT_PLAYING
 * \return		错误码 PLAYER_ERR_SET_CURRENT_FRAME_FAILED
 * \date		2016-09-07
 * \note		
 */		
API_PLAYER int Player_setFileCurrentFrame(int id, unsigned long number);

/**
 * \brief		获得当前播放时间
 * \param		[in] id				频道号
 * \param		[out] dwYear		年
 * \param		[out] dwMonth		月
 * \param		[out] dwDay			日
 * \param		[out] dwHour		时
 * \param		[out] dwMinute		分
 * \param		[out] dwSecond		秒
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_GET_CURRENT_TIME_WHEN_NOT_PLAYBACK
 * \return		错误码 PLAYER_ERR_CANNOT_GET_CURRENT_TIME_WHEN_NOT_PLAYING
 * \return		错误码 PLAYER_ERR_GET_CURRENT_TIME_FAILED
 * \date		2016-09-07
 * \note		
 */	
API_PLAYER int Player_getCurrentPlayTime(int id, unsigned long *year, unsigned long *month, unsigned long *day, 
								unsigned long *hour, unsigned long *minute, unsigned long *second); 

/**
 * \brief		获取源缓冲区帧数量
 * \param		[in] id				频道号
 * \param		[out] number		源缓冲区帧数量
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_GET_REMAIN_WHEN_NOT_PLAYBACK
 * \return		错误码 PLAYER_ERR_CANNOT_GET_REMAIN_WHEN_NOT_PLAYING
 * \date		2016-09-07
 * \note		
 */		
API_PLAYER int Player_getSourceBufferRemain(int id, unsigned long *number);
		
/**
 * \brief		获取原始图像大小
 * \param		[in] id				频道号
 * \param		[out] width			宽
 * \param		[out] height		高
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_GET_PICTURE_SIZE_WHEN_AUDIO_RECORDING
 * \return		错误码 PLAYER_ERR_CANNOT_GET_PICTURE_SIZE_WHEN_NOT_PLAYING
 * \return		错误码 PLAYER_ERR_GET_PICTURE_SIZE_FAILED
 * \date		2016-09-07
 * \note		
 */	
API_PLAYER int Player_getPictureSize(int id, int *width, int *height);

/**
 * \brief		设置drawCallback回调函数
 * \param		[in] id				频道号
 * \param		[in] cb				回调函数指针
 * \param		[in] data	  		用户数据 
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CB_IS_NULL
 * \return		错误码 PLAYER_ERR_SET_DRAW_CALLBACK_FAILED
 * \date		2016-09-07
 * \note	    
 */
API_PLAYER int Player_setDrawCallback(int id, drawCallback cb, void *data);

/**
 * \brief		设置文件播放完的回调函数
 * \param		[in] id				频道号
 * \param		[in] cb				回调函数指针 
 * \param		[in] data	  		用户数据 
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CB_IS_NULL
 * \return		错误码 PLAYER_ERR_SET_FILE_END_CALLBACK_FAILED
 * \date		2016-09-07
 * \note		
 */		
API_PLAYER int Player_setFileEndCallback(int id, fileEndCallback cb, void *data);

/**
 * \brief		查询信息
 * \param		[in] id				频道号
 * \param		[in] cmd			命令
 * \param		[out] buff  		查询所得的信息
 * \param		[in] len  			buff的长度
 * \param		[out] returnLen  	查询所得的信息的有效长度
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_BUFF_IS_NULL
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CMD
 * \return		错误码 PLAYER_ERR_DO_NOT_SUPPORT_QUERY_MEDIA
 * \return		错误码 PLAYER_ERR_QUERY_INFO_FAILED
 * \date		2016-09-07
 * \note		包含：当前时间、帧率信息、媒体信息
 */
API_PLAYER int Player_queryInfo(int id, queryCmd_t cmd, char *buff, int len, int *returnLen);

/**
 * \brief		开启本地语音采集
 * \param		[in] id				频道号
 * \param		[in] cb				回调函数	 
 * \param		[in] sampleBit		采样位宽，如8位 	
 * \param		[in] sampleRate		每秒采样率 
 * \param		[in] len			长度
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_START_RECORD_WHEN_NOT_AUDIO_RECORD
 * \return		错误码 PLAYER_ERR_CB_IS_NULL
 * \return		错误码 PLAYER_ERR_START_AUDIO_RECORD_FAILED
 * \date		2016-09-07
 * \note		
 */
API_PLAYER int Player_startAudioRecord(int id, audioRecordCallback cb, unsigned int sampleBit, unsigned int sampleRate, unsigned int len);

/**
 * \brief		关闭本地语音采集
 * \param		[in] id				频道号
 * \return		错误码 PLAYER_ERR_SUCCESS
 * \return		错误码 PLAYER_ERR_OUT_BOUND_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_OPERATE_FREE_CHANNEL
 * \return		错误码 PLAYER_ERR_CANNOT_STOP_RECORD_WHEN_NOT_AUDIO_RECORD
 * \return		错误码 PLAYER_ERR_STOP_AUDIO_RECORD_FAILED 
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
