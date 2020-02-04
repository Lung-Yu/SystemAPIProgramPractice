#ifndef _SERVICE_OPERATE_H_
#define _SERVICE_OPERATE_H_


#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

enum OperateType
{
	CREATE_SERVICE,
	START_SERVICE,
	STOP_SERVICE,
	DELETE_SERVICE
};

BOOL SystemServiceOperate(char *lpszDriverPath, OperateType iOperateType);
#endif