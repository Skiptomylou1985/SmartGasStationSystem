// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� SPLATE_HKCN_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// SPLATE_HKCN_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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

// �����Ǵ� SPlate_hkcn.dll ������
class SPLATE_HKCN_API CSPlate_hkcn {
public:
	CSPlate_hkcn(void);
	// TODO:  �ڴ�������ķ�����
};

extern SPLATE_HKCN_API int nSPlate_hkcn;

SPLATE_HKCN_API int fnSPlate_hkcn(void);
