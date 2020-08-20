#pragma once
#include <windows.h>
#include "vector.h"

typedef struct _KM_READ_REQUEST
{
	ULONG ProcessId;
	UINT_PTR SourceAddress;
	ULONGLONG Size;
	void* Output;

} KM_READ_REQUEST;


typedef struct _KM_WRITE_REQUEST
{
	ULONG ProcessId;
	ULONG ProcessidOfSource;
	UINT_PTR SourceAddress;
	UINT_PTR TargetAddress;
	ULONGLONG Size;
} KM_WRITE_REQUEST;


typedef struct _GET_USERMODULE_IN_PROCESS
{
	ULONG pid;            
	ULONG64 BaseAddress;
} GET_USERMODULE_IN_PROCESS;


typedef struct _EFT_Player
{
	uintptr_t	 instance;
	FVector		 headPos;
	FVector		 location;
};

typedef struct _EFT_Extract
{
	uintptr_t	 instance;
	std::string  name;
	FVector		 location;
};

namespace _EFT_ 
{
	struct 
		BaseObject
		{
			uint64_t previousObjectLink;	//0x0000
			uint64_t nextObjectLink;		//0x0008
			uint64_t object;				//0x0010
		};

	struct 
		GameObjectManager
		{
			uint64_t lastTaggedObject;	//0x0000
			uint64_t taggedObjects;		//0x0008
			uint64_t lastActiveObject;	//0x0010
			uint64_t activeObjects;		//0x0018
		}; //Size: 0x0010

	class 
		ListInternal
		{
			public:
			char pad_0x0000[0x20]; //0x0000
			uintptr_t* firstEntry; //0x0020 
		}; //Size=0x0028

	class 
		List
		{
			public:
			char pad_0x0000[0x10];	//0x0000
			ListInternal* listBase; //0x0010 
			__int32 itemCount;		//0x0018 
		}; //Size=0x001C
}

