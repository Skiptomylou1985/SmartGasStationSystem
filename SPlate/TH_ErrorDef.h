// ***************************************************************
//  TH_ErrorDef.h   version:  4.0     date: 2010.4.12
//  -------------------------------------------------------------
//  清华大学智能图文信息处理研究室。版权所有。
//  -------------------------------------------------------------
//  Center for Intelligent Image and Document Information Processing
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//   Author: Zhou Jian
// ***************************************************************
//		Revision history:
//			2010.4.12: v4.0, 定义SDK的出错信息
// ***************************************************************

#if !defined(__TH_ERRORDEF_INCLUDE_H__)
#define __TH_ERRORDEF_INCLUDE_H__

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

// The errors that may occur during the use of the SDK
#define		TH_ERR_NONE								0		//没有错误
#define		TH_ERR_GENERIC							1		//省份设置错误
#define		TH_ERR_MEMORYALLOC						2		//内存分配错误
#define		TH_ERR_INVALIDFORMAT					7		//不支持的图像格式
#define		TH_ERR_INVALIDWIDTH						8		//图像宽度必须是8的整数倍
#define     TH_ERR_THREADLIMIT						20		//调用线程数超过规定数量
#define		TH_ERR_NODOG							-1		//没有找到加密狗
#define		TH_ERR_CARTYPEERROR						-2		//车辆类型识别模块错误
#define		TH_ERR_READDOG							-3		//读取加密狗出错
#define		TH_ERR_INVALIDDOG						-4		//不是合法的加密狗
#define		TH_ERR_INVALIDUSER						-6		//不是合法的加密狗用户
#define		TH_ERR_MOUDLEERROR						-7		//车标识别模块错误
#define     TH_ERR_INVALIDMOUDLE					-8		//模块没有合法授权
#define     TH_ERR_BUFFULL							-9		//识别缓冲区已满
#define		TH_ERR_INITVEHDETECT					-10		//初始化车辆检测模块错误
#define		TH_ERR_VEHDETECT						-11		//车辆检测模块错误
#define     TH_ERR_INVALIDCALL						-99		//非法调用
#define     TH_ERR_EXCEPTION						-100	//异常
#define		TH_ERR_INITLIMIT						21		//初始化次数超过加密狗许可 
#define		TH_ERR_MULTIINSTANCE					22		//车牌识别实例超限制

//以下为车型识别算法返回错误
#define		TH_ERR_CARMODEL_PLATELOC_ERR			1001	//车牌坐标信息异常
#define     TH_ERR_READMODEL						1002	//读车型模型异常

#ifdef __cplusplus
}	// extern "C"
#endif

#endif // !defined(__TH_ERRORDEF_INCLUDE_H__)
