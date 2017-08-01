// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 SPLATE_HKCN_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// SPLATE_HKCN_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef SPLATE_HKCN_EXPORTS
#define SPLATE_HKCN_API __declspec(dllexport)
#else
#define SPLATE_HKCN_API __declspec(dllimport)
#endif

#include "Markup.h"
#include "HCNetSDK.h"
#include "log.h"
#include "plaympeg4.h"
#include "DataType.h"
#include "DecodeCardSdk.h"

// 此类是从 SPlate_hkcn.dll 导出的
class SPLATE_HKCN_API CSPlate_hkcn {
public:
	CSPlate_hkcn(void);
	// TODO:  在此添加您的方法。
};

extern SPLATE_HKCN_API int nSPlate_hkcn;

SPLATE_HKCN_API int fnSPlate_hkcn(void);
