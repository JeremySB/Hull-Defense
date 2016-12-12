// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Game Engine constants.h v4.0
// Last modification: Mar-1-2015

#pragma once
#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//=============================================================================
//                  Constants
//=============================================================================

// window
const char CLASS_NAME[] = "HullDefense";
const char GAME_TITLE[] = "Hull Defense";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  1100;               // width of game in pixels
const UINT GAME_HEIGHT = 600;               // height of game in pixels
const int  MENU_RIGHT_HEIGHT = 8;
const int  MENU_RIGHT_WIDTH = 250;
	
// careful about changing these, the grid might not line up well
const UINT CELL_WIDTH = 25;               // width of grid cell in pixels
const UINT CELL_HEIGHT = 25;               // height of grid cell in pixels
const UINT GRID_WIDTH = GAME_WIDTH/CELL_WIDTH;
const UINT GRID_HEIGHT = GAME_HEIGHT/CELL_HEIGHT;
const UINT MAX_ENEMIES = 30;

enum StructureTypes {base = 1, wall = 15, turret = 3, tower = 4, photonCannon = 5, permWall = 10};
enum Targeting {weakestTarget, strongestTarget, baseTarget};

const UINT PATHFINDING_MODIFIER = 5;

// game
const bool VSYNC = false;                   // true locks display to vertical sync rate
const float FRAME_RATE = 240.0f;            // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const double PI = 3.14159265;
const int MAX_PARTICLES = 1000;


// graphic images
const char BACKGROUND_IMAGE[] = "pictures\\background1DAN.png";  // background
const char BASE_IMAGE[] = "pictures\\baseDANIEL.png";
const char WALL_IMAGE[] = "pictures\\wallJEREMY.png";
const char TURRET_BASE_IMAGE[] = "pictures\\turretBaseDANIEL.png";
const char TURRET_GUN_IMAGE[] = "pictures\\turretGunDANIEL.png";
const char TURRET_PROJECTILE_IMAGE[] = "pictures\\turretProjectileJEREMY2.png";
const char TOWER_BASE_IMAGE[] = "pictures\\towerBaseJEREMY.png";
const char TOWER_GUN_IMAGE[] = "pictures\\towerGunJEREMY.png";
const char TOWER_PROJECTILE_IMAGE[] = "pictures\\turretProjectileJEREMY2.png";
const char PHOTON_CANNON_BASE_IMAGE[] = "pictures\\photonCannonBaseJEREMY.png";
const char PHOTON_CANNON_GUN_IMAGE[] = "pictures\\photonCannonGunJEREMY.png";
const char PHOTON_CANNON_PROJECTILE_IMAGE[] = "pictures\\photonCannonProjectileJEREMY.png";
const char PHOTON_CANNON_PROJECTILE_EXPLOSION[] = "pictures\\photonCannonExplosionJEREMY.png";
const char GOOD_SELECTION_IMAGE[] = "pictures\\goodSelectionJEREMY.png";
const char ENEMY_IMAGE[] = "pictures\\EnemyAttack.png";//"pictures\\EnemyTemp.png";
const char HEALTHBAR_IMAGE[] = "pictures\\Healthbar.png";

// intro images
const char MAIN_MENU[] = "pictures\\mainScreenDANIEL.png";
const char INSTRUCTION0[] = "pictures\\instructionDANIEL.png";
const char INSTRUCTION1[] = "pictures\\instruction1DANIEL.png";
const char INSTRUCTION2[] = "pictures\\instruction2DANIEL.png";
const char WIN_SCREEN[] = "pictures\\winScreenDANIEL.png";
const char WAVE_COMPLETE[] = "pictures\\waveComplete.png";
const char LOSE_SCREEN[] = "pictures\\loseScreenDANIEL.png";

// menu images
const char TOWERMENU_IMAGE[] = "pictures\\buildmenuDANIEL.png";
const char TURRETMENU_IMAGE[] = "pictures\\repairmenuDANIEL.png";
const char WALLMENU_IMAGE[] = "pictures\\sellmenuDANIEL.png";
const char DEFMENU_IMAGE[] = "pictures\\menuDefaultDANIEL.png";
const char FONT_IMAGE[]	= "pictures\\CKfont.png";
const char LOADING_SCREEN[] = "pictures\\loadingScreen.png";

// menu
const int TABS_WIDTH = 140;
const int TABS_HEIGHT = 27;

//#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)

// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "audio\\Win\\project2.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\project2.xsb";

// audio cues
const char BACKGROUND[] = "backgroundmusic";
const char LASER[] = "laser";
const char ENERGY[] = "energy";
const char PLACEMENT[] = "placement";
const char SQUISH[] = "Squish";

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR CONSOLE_KEY  = '`';         // ` key
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key

const char LEVEL1WAVEFILE[] = "level1.txt";
const char LEVEL2WAVEFILE[] = "level2.txt";
const char LEVEL3WAVEFILE[] = "level3.txt";

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
    if (ptr)
    { 
        ptr->Release(); 
        ptr = NULL;
    }
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
    if (ptr)
    { 
        delete ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
    if (ptr)
    { 
        delete[] ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
    if (ptr)
        ptr->onLostDevice(); 
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
    if (ptr)
        ptr->onResetDevice(); 
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

#endif
