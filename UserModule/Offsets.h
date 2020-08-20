#pragma once
#include <vector>
/*
#include <string>
#include "math.hpp"
#include <list>
#include "visuals.h"
#include <d3dx9math.h>
#pragma comment (lib, "d3dx9.lib")
*/

//UPDATE OFFSETS FROM FIRST LAGGY PROJECT

struct Offsets {
	// GOM offset
	static constexpr uint64_t gameObjectManager = 0x15181E8;
	// setters
	uint64_t gameObjectManager = 0x0;
	uint64_t gameWorld = 0x0;
	uint64_t localGameWorld = 0x0;
	uint64_t fpsCamera = 0x0;
	uint64_t OpticCamera = 0x0;

	// below structs of data with offsets
	struct localGameWorld_offsets
	{
		static constexpr uint64_t itemList = 0x48;
		static constexpr uint64_t registeredPlayers = 0x68;
		static constexpr uint64_t m_LocalPlayerID = 0x30;
	};

	struct unicodeString
	{
		static constexpr uint64_t length = 0x10;
		static constexpr uint64_t stringBase = 0x14;
	};

	struct profile
	{
		static constexpr uint64_t information = 0x28;
		static constexpr uint64_t id = 0x10;
	};

	struct information
	{
		static constexpr uint64_t playerName = 0x10;
	};

	struct movementContext
	{
		static constexpr uint64_t angles_0 = 0x1D0;
		static constexpr uint64_t angles_1 = 0x1D8;
		static constexpr uint64_t position = 0x1E0;
	};

	struct Player
	{
		static constexpr uint64_t m_pPlayerProfile = 0x03A0;
		static constexpr uint64_t movementContext = 0x38;
		static constexpr uint64_t proceduralWeaponAnimation = 0x70; //updayed 1/11/2020
		static constexpr uint64_t playerBody = 0x88; //updated 1/11/2020
		static constexpr uint64_t m_pHealthController = 0x3D0; //updated 1/11/2020
		static constexpr uint64_t profile = 0x3A0; //updayed 1/11/2020

	};
};