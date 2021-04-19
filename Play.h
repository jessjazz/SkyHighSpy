//********************************************************************************************************************************
//				           ___                         ___                   .-.       .-.                          
//				          (   )                       (   )                 /    \    /    \                        
//				   .-..    | |    .---.   ___  ___     | |.-.    ___  ___   | .`. ;   | .`. ;    .--.    ___ .-.    
//				  /    \   | |   / .-, \ (   )(   )    | /   \  (   )(   )  | |(___)  | |(___)  /    \  (   )   \   
//				 ' .-,  ;  | |  (__) ; |  | |  | |     |  .-. |  | |  | |   | |_      | |_     |  .-. ;  | ' .-. ;  
//				 | |  . |  | |    .'`  |  | |  | |     | |  | |  | |  | |  (   __)   (   __)   |  | | |  |  / (___) 
//				 | |  | |  | |   / .'| |  | '  | |     | |  | |  | |  | |   | |       | |      |  |/  |  | |        
//				 | |  | |  | |  | /  | |  '  `-' |     | |  | |  | |  | |   | |       | |      |  ' _.'  | |        
//				 | |  ' |  | |  ; |  ; |   `.__. |     | '  | |  | |  ; '   | |       | |      |  .'.-.  | |        
//				 | `-'  '  | |  ' `-'  |   ___ | |     ' `-' ;   ' `-'  /   | |       | |      '  `-' /  | |        
//				 | \__.'  (___) `.__.'_.  (   )' |      `.__.     '.__.'   (___)     (___)      `.__.'  (___)       
//				 | |                       ; `-' '                                                                  
//				(___)                       .__.'                                                                  
//
//********************************************************************************************************************************
//                                A simple C++ framework for learning how to make 2D games
//											Copyright 2020 Sumo-Digital Limited
//********************************************************************************************************************************

#ifndef PLAYPCH_H
#define PLAYPCH_H
#define PLAY_VERSION	"0.9.21.02.16"

#include <cstdint>
#include <cstdlib>
#include <cmath> 

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <future>


#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#define NOMINMAX // Stop windows macros defining min and max macros which can be problematic.
// Windows Header Files
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>

// Includes the GDI plus headers.
// These are only needed by internal parts of the library.

#include "dwmapi.h"
#include <Shlobj.h>
#pragma warning(push)
#pragma warning(disable:4458) // declaration of 'xyz' hides class member

 // This is used to avoid issues with NOMINMAX
namespace Gdiplus
{
	using std::min;
	using std::max;
}
#include <GdiPlus.h>
#pragma warning(pop)


// Macros for Assertion and Tracing
void TracePrintf(const char* file, int line, const char* fmt, ...);
void AssertFailMessage(const char* message, const char* file, long line );
void DebugOutput( const char* s );
void DebugOutput( std::string s );


#ifdef _DEBUG
#define PB_TRACE(fmt, ...) TracePrintf(__FILE__, __LINE__, fmt, __VA_ARGS__);
#define PB_ASSERT(x) if(!(x)){ PB_TRACE(" *** ASSERT FAIL *** !("#x")\n\n"); AssertFailMessage(#x, __FILE__, __LINE__), __debugbreak(); }
#define PB_ASSERT_MSG(x,y) if(!(x)){ PB_TRACE(" *** ASSERT FAIL *** !("#x")\n\n"); AssertFailMessage(y, __FILE__, __LINE__), __debugbreak(); }
#else
#define PB_TRACE(fmt, ...)
#define PB_ASSERT(x) if(!(x)){ AssertFailMessage(#x, __FILE__, __LINE__);  }
#define PB_ASSERT_MSG(x,y) if(!(x)){ AssertFailMessage(y, __FILE__, __LINE__); }
#endif // _DEBUG

// Global constants such as PI
constexpr float PLAY_PI	= 3.14159265358979323846f;   // pi



//*******************************************************************
// PLAY BEGIN: PlayMemory.h
//*******************************************************************

#ifndef PLAY_PLAYMEMORY_H
#define PLAY_PLAYMEMORY_H
//********************************************************************************************************************************
//* Copyright 2020 Sumo-Digital Limited
//********************************************************************************************************************************
// File:		PlayMemory.h
// Created:		August 2020 - Sumo Academy
// Platform:	Independent
// Description:	Declaration for a simple memory tracker to prevent leaks
//********************************************************************************************************************************

// Prints out all the currently allocated memory to the debug output
void PrintAllocations( const char* tagText );

// Allocate some memory with a known origin
void* operator new(size_t size, const char* file, int line);
// Allocate some memory with a known origin
void* operator new[](size_t size, const char* file, int line); 
// Allocate some memory without a known origin
void* operator new[](size_t size);

// Free some memory 
void operator delete[](void* p);
// Free some memory (matching allocator for exceptions )
void operator delete(void* p, const char* file, int line);
// Free some memory (matching allocator for exceptions )
void operator delete[](void* p, const char* file, int line); 

//#ifdef PLAY_IMPLEMENTATION
#define new new( __FILE__ , __LINE__ )
//#endif

#endif
//*******************************************************************
// PLAY END: PlayMemory.h
//*******************************************************************


//*******************************************************************
// PLAY BEGIN: PlayMaths.h
//*******************************************************************

#ifndef PLAY_PLAYMATHS_H
#define PLAY_PLAYMATHS_H
//********************************************************************************************************************************
// Copyright 2020 Sumo-Digital Limited
//********************************************************************************************************************************
// File:		PlayMaths.h
// Created:		October 2020 - Sumo Academy
// Description:	A very simple set of 2D maths structures and operations
// Platform:	Independent
//********************************************************************************************************************************

#pragma warning (push)
#pragma warning (disable : 4201) // nonstandard extension used: nameless struct/union

// The main 2D structure used in the library
struct Vector2f
{
	Vector2f() {}
	// We're encouraging implicity type conversions between float and int with the same number of parameters
	Vector2f( float x, float y ) : x( x ), y( y ) {}
	Vector2f( int x, int y ) : x( static_cast<float>( x ) ), y( static_cast<float>( y ) ) {}
	Vector2f( float x, int y ) : x( x ), y( static_cast<float>( y ) ) {}
	Vector2f( int x, float y ) : x( static_cast<float>( x ) ), y( y ) {}

	// Different ways of accessing member data
	union
	{
		float v[2];
		struct { float x; float y; };
		struct { float width; float height; };
	};

};

#pragma warning(pop)

// A point is conceptually different to a vector, but maps to Vector2f for ease of use
using Point2f = Vector2f;

//**************************************************************************************************
// Vector component operations
//**************************************************************************************************

// Vector component addition
inline Vector2f operator + ( const Vector2f& lhs, const Vector2f& rhs )
{
	Vector2f ret;
	for( int i = 0; i < 2; ++i )
	{
		ret.v[i] = lhs.v[i] + rhs.v[i];
	}
	return ret;
}

// Vector component assignment addition
inline Vector2f& operator += ( Vector2f& lhs, const Vector2f& rhs )
{
	for( int i = 0; i < 2; ++i )
	{
		lhs.v[i] += rhs.v[i];
	}
	return lhs;
}

// Vector component subtraction
inline Vector2f operator - ( const Vector2f& lhs, const Vector2f& rhs )
{
	Vector2f ret;
	for( int i = 0; i < 2; ++i )
	{
		ret.v[i] = lhs.v[i] - rhs.v[i];
	}
	return ret;
}

// Vector component assignment subtraction
inline Vector2f& operator -= ( Vector2f& lhs, const Vector2f& rhs )
{
	for( int i = 0; i < 2; ++i )
	{
		lhs.v[i] -= rhs.v[i];
	}
	return lhs;
}

// Vector component unary negation
inline Vector2f operator - ( const Vector2f& op )
{
	Vector2f ret;
	for( int i = 0; i < 2; ++i )
	{
		ret.v[i] = -op.v[i];
	}
	return ret;
}

// Vector component multiplication
inline Vector2f operator * ( const Vector2f& lhs, const Vector2f& rhs )
{
	Vector2f ret;
	for( int i = 0; i < 2; ++i )
	{
		ret.v[i] = lhs.v[i] * rhs.v[i];
	}
	return ret;
}

// Vector component assignment multiplication
inline Vector2f operator *= ( Vector2f& lhs, const Vector2f& rhs )
{
	Vector2f ret;
	for( int i = 0; i < 2; ++i )
	{
		lhs.v[i] *= rhs.v[i];
	}
	return lhs;
}

// Vector component division
inline Vector2f operator / ( const Vector2f& lhs, const Vector2f& rhs )
{
	Vector2f ret;
	for( int i = 0; i < 2; ++i )
	{
		ret.v[i] = lhs.v[i] / rhs.v[i];
	}
	return ret;
}

// Vector component assignment division
inline Vector2f operator /= ( Vector2f& lhs, const Vector2f& rhs )
{
	Vector2f ret;
	for( int i = 0; i < 2; ++i )
	{
		lhs.v[i] /= rhs.v[i];
	}
	return lhs;
}

//**************************************************************************************************
// Vector scalar operations
//**************************************************************************************************

// Vector scalar multiplication
inline Vector2f operator * ( const Vector2f& lhs, const float rhs )
{
	Vector2f ret;
	for( int i = 0; i < 2; ++i )
	{
		ret.v[i] = lhs.v[i] * rhs;
	}
	return ret;
}

// Vector scalar multiplication (reverse operands)
inline Vector2f operator * ( const float lhs, const Vector2f& rhs )
{
	return rhs * lhs;
}

// Vector scalar assignment multiplication
inline Vector2f operator *= ( Vector2f& lhs, const float& rhs )
{
	Vector2f ret;
	for( int i = 0; i < 2; ++i )
	{
		lhs.v[i] *= rhs;
	}
	return lhs;
}

// Vector scalar division
inline Vector2f operator / ( const Vector2f& lhs, const float rhs )
{
	return lhs * ( float( 1 ) / rhs );
}

// Vector scalar division (reverse operands)
inline Vector2f operator / ( const float lhs, const Vector2f& rhs )
{
	Vector2f ret;
	for( int i = 0; i < 2; ++i )
	{
		ret.v[i] = lhs / rhs.v[i];
	}
	return ret;
}

// Vector scalar assignment multiplication
inline Vector2f operator /= ( Vector2f& lhs, const float& rhs )
{
	Vector2f ret;
	for( int i = 0; i < 2; ++i )
	{
		lhs.v[i] /= rhs;
	}
	return lhs;
}

//**************************************************************************************************
// Vector component comparisons
//**************************************************************************************************

// Vector components exactly equal
inline bool operator == ( const Vector2f& lhs, const Vector2f& rhs )
{
	Vector2f ret;
	for( int i = 0; i < 2; ++i )
	{
		if( lhs.v[i] != rhs.v[i] )
			return false;
	}
	return true;
}

// Vector components not equal
inline bool operator != ( const Vector2f& lhs, const Vector2f& rhs )
{
	return !( lhs == rhs );
}

// Vector components equal to within specified tolerance.
inline bool EqualTol( const Vector2f& lhs, const Vector2f& rhs, const float tolerance )
{
	Vector2f ret;
	for( int i = 0; i < 2; ++i )
	{
		if( std::abs( lhs.v[i] - rhs.v[i] ) > tolerance )
		{
			return false;
		}
	}
	return true;
}

//**************************************************************************************************
// Common maths functions
//**************************************************************************************************

// Dot product
inline float dot( const Vector2f& lhs, const Vector2f& rhs )
{
	float ret = 0.f;
	for( int i = 0; i < 2; ++i )
	{
		ret += lhs.v[i] * rhs.v[i];
	}
	return ret;
}

// Orthagonal vector
inline Vector2f normal( const Vector2f& lhs )
{
	Vector2f ret;
	ret.v[0] = -lhs.v[1];
	ret.v[1] = lhs.v[0];
	return ret;
}

// Vector length squared
inline float lengthSqr( const Vector2f& v )
{
	return dot( v, v );
}

// Vector length
inline float length( const Vector2f& v )
{
	return sqrt( dot( v, v ) );
}

// Vector normalize
inline Vector2f normalize( const Vector2f& v )
{
	return v / length( v );
}


#endif


//*******************************************************************
// PLAY END: PlayMaths.h
//*******************************************************************


//*******************************************************************
// PLAY BEGIN: PlayBuffer.h
//*******************************************************************

#ifndef PLAY_PLAYBUFFER_H
#define PLAY_PLAYBUFFER_H
//********************************************************************************************************************************
//* Copyright 2020 Sumo-Digital Limited
//********************************************************************************************************************************
// File:		PlayBuffer.h
// Created:		March 2020 - Sumo Academy
// Description:	A software drawing buffer which provides the basis for creating 2D games  
// Platform:	Windows
// Notes:		Provides a 32-bit ARGB display buffer
//********************************************************************************************************************************

// The target frame rate
constexpr int FRAMES_PER_SECOND = 60;

// Some defines to hide the complexity of WinMain arguments 
#define PLAY_WINARGS_IN		_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd
#define PLAY_WINARGS_OUT	hInstance, hPrevInstance, lpCmdLine, nShowCmd

// Encapsulates the functionality of a 2D display buffer 
// > Singleton class accessed using PlayBuffer::Instance()
class PlayBuffer
{
public:

	// A pixel structure to represent an ARBG format pixel
	struct Pixel
	{
		Pixel() {}
		Pixel( uint32_t bits ) : bits( bits ) {}
		Pixel( float r, float g, float b ) :
			a( 0xFF ), r( static_cast<uint8_t>( r ) ), g( static_cast<uint8_t>( g ) ), b( static_cast<uint8_t>( b ) ) {}
		Pixel( int r, int g, int b ) :
			a( 0xFF ), r( static_cast<uint8_t>( r ) ), g( static_cast<uint8_t>( g ) ), b( static_cast<uint8_t>( b ) ) {}
		Pixel( int a, int r, int g, int b ) : 
			a( static_cast<uint8_t>( a ) ), r( static_cast<uint8_t>( r ) ), g( static_cast<uint8_t>( g ) ),	b( static_cast<uint8_t>( b ) ) {}

		union
		{
			uint32_t bits{ 0xFF000000 }; // Alpha set to opaque by default
			struct { uint8_t b, g, r, a; }; // This order corresponds to ( a<<24 | r<<16 | g<<8 | b )
		};
	};

	// Defaul pixel colours for ease of use
	static PlayBuffer::Pixel pixBlack, pixWhite, pixRed, pixGreen, pixBlue, pixMagenta, pixCyan, pixYellow, pixOrange, pixGrey;

	//********************************************************************************************************************************
	// Instance functions
	//********************************************************************************************************************************

	// Creates the PlayBuffer instance and initialise the display buffer
	static PlayBuffer& Instance( int nWidth, int nHeight, int nScale, Pixel bgColour = { 0, 0, 0 } );
	// Returns the PlayBuffer instance
	static PlayBuffer& Instance();
	// Destroys the PlayBuffer instance
	static void Destroy();
	
	//********************************************************************************************************************************
	// Windows functions
	//********************************************************************************************************************************

	// Passes control of Windows functionality over to the PlayBuffer 
	int HandleWindows( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow, LPCWSTR windowName );
	// Handles Windows messages for the PlayBuffer  
	static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	// Copies the display buffer pixels to the window
	int Present();

	//********************************************************************************************************************************
	// Getter functions
	//********************************************************************************************************************************

	// Get a pointer to the display buffer's pixel data. 
	uint32_t* GetDisplayBuffer() { return m_pDisplayBuffer; } // Bad abstraction, but good for modularity
	// Gets the width of the display buffer in pixels
	int GetWidth() const { return m_width; }
	// Gets the height of the display buffer in pixels 
	int GetHeight() const { return m_height; }
	// Gets the scale of the display buffer in pixels
	int GetScale() const { return m_scale; }

	//********************************************************************************************************************************
	// Mouse and keyboard functions
	//********************************************************************************************************************************

	// Returns the status of the supplied mouse button (0=left, 1=right)
	bool GetMouseDown( int button ) const;
	// Get the screen position of the mouse cursor
	Point2f GetMousePos() const { return m_mousePos; }
	// Returns true if the key has been pressed since it was last released
	// > https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	bool KeyPressed( int vKey );
	// Returns true if the key is currently being held down
	// > https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	bool KeyDown( int vKey );

	//********************************************************************************************************************************
	// Basic buffer drawing functions
	//********************************************************************************************************************************

	// Clears the display buffer using the given pixel colour
	void ClearBuffer( Pixel colour );
	// Sets the colour of an individual pixel in the display buffer
	void DrawPixel( int posX, int posY, Pixel pix );
	// Sets the colour of an individual pixel in the display buffer
	void DrawPixel( Point2f pos, Pixel pix ); 
	// Sets the colour of an individual pixel in the display buffer
	void DrawLine( Point2f startPos, Point2f endPos, Pixel pix );
	// Draws a pixel line into the display buffer
	void DrawLine( int startX, int startY, int endX, int endY, Pixel pix );
	// Draws a rectangle into the display buffer
	void DrawRect( Point2f topLeft, Point2f bottomRight, Pixel pix, bool fill = false );
	// Draws a circle into the display buffer
	void DrawCircle( Point2f centrePos, int radius, Pixel pix );

	//********************************************************************************************************************************
	// Debug font functions
	//********************************************************************************************************************************

	// Draws a single character using the in-built debug font
	// > Returns the character width in pixels
	int DrawDebugCharacter( Point2f pos, char c, Pixel pix );
	// Draws text using the in-built debug font
	// > Returns the x position at the end of the text
	int DrawDebugString( Point2f pos, const std::string& s, Pixel pix, bool centred = true );
	
	//********************************************************************************************************************************
	// Timing bar functions
	//********************************************************************************************************************************

	// Sets the current timing bar segment to a specific colour
	// > Returns the index of the new timing segment
	int SetTimingBarColour( PlayBuffer::Pixel pix );
	// Draws the timing bar at the given position and size
	void DrawTimingBar( Point2f pos, Point2f size );
	// Gets the duration (in milliseconds) of a specific timing segment
	float GetTimingSegmentDuration( int id ) const;

	//********************************************************************************************************************************
	// Loading functions
	//********************************************************************************************************************************

	// Reads the width and height of a png image
	static int ReadPNGImage( std::string& fileAndPath, int& width, int& height );
	// Loads a png image and puts the image data into the destination image provided
	static int LoadPNGImage( std::string& fileAndPath, int& width, int& height, uint32_t*& destImage );

private:

	//********************************************************************************************************************************
	// Constructor / destructor
	//********************************************************************************************************************************

	// Creates a window of the required size and scale and allocates the display buffer
	PlayBuffer( int nWidth, int nHeight, int nScale, Pixel bgColour ); 
	// Frees up memory from all the different buffers
	~PlayBuffer();
	// The assignment operator is removed to prevent copying of a singleton class
	PlayBuffer& operator=( const PlayBuffer& ) = delete;
	// The copy constructor is removed to prevent copying of a singleton class
	PlayBuffer( const PlayBuffer& ) = delete;

	//********************************************************************************************************************************
	// Miscellaneous internal functions
	//********************************************************************************************************************************

	// Allocates a buffer for the debug font and copies the font pixel data to it
	void DecompressDubugFont( void );
	// Returns the pixel width of a string using the debig font
	int GetDebugStringWidth( const std::string& s );
	// Draws the offset points from the origin in all octants
	void DrawCircleOctants( int posX, int posY, int offX, int offY, Pixel pix );
	// Ends the current timing segment and calculates the duration
	LARGE_INTEGER EndTimingSegment();

	struct TimingSegment
	{
		PlayBuffer::Pixel pix;
		long long begin{ 0 };
		long long end{ 0 };
		float millisecs{ 0 };
	};

	// Vector of timing data segments
	std::vector<TimingSegment> m_vTimings;

	// Display buffer dimensions
	int m_width{ 0 }, m_height{ 0 }, m_scale{ 0 };

	// Buffer pointers
	uint32_t* m_pDisplayBuffer{ nullptr };
	uint8_t* m_pDebugFontBuffer{ nullptr };

	//Position of the mouse in the display buffer
	Point2f m_mousePos{ 0, 0 };
	//left right.
	bool m_bMouseDown[2]{ false, false };
	// Pointer to the isntance.
	static PlayBuffer* s_pInstance;
	// The handle to the PLayBuffer Window 
	HWND m_hWindow{ nullptr };
	// A GDI+ token
	unsigned long long m_gpToken{ 0 };
};



#endif



//*******************************************************************
// PLAY END: PlayBuffer.h
//*******************************************************************


//*******************************************************************
// PLAY BEGIN: PlayBlitter.h
//*******************************************************************

#ifndef PLAY_PLAYBLITTER_H
#define PLAY_PLAYBLITTER_H
//********************************************************************************************************************************
//* Copyright 2020 Sumo-Digital Limited
//********************************************************************************************************************************
// File:		PlayBlitter.h
// Created:		March 2020 - Sumo Academy
// Description:	A simple image manager for handling spites/backgrounds with PlayBuffer
// Platform:	Independent
// Notes:		Uses PNG format. The end of the filename indicates the number of frames e.g. "bat_4.png" or "tiles_10x10.png"
//********************************************************************************************************************************

// A 2D sprite manager class, named in honour of the Amiga Blitter
// > Singleton class accessed using PlayBlitter::Instance()
class PlayBlitter
{
public:
	//********************************************************************************************************************************
	// Instance functions
	//********************************************************************************************************************************

	// Creates the PlayBlitter instance and creates sprites from all the PNGs in the directory indicated
	static PlayBlitter& Instance( const char* path );
	// Returns the PlayBlitter instance
	static PlayBlitter& Instance();
	// Destroys the PlayBlitter instance
	static void Destroy();
	// Set the display buffer for all subsequent drawing operations
	void SetDisplayBuffer( uint32_t* pDisplayBuffer, int bufferWidth, int bufferHeight ) { m_displayBuffer = pDisplayBuffer; m_displayBufferWidth = bufferWidth; m_displayBufferHeight = bufferHeight; }

	//********************************************************************************************************************************
	// Loading functions
	//********************************************************************************************************************************

	// Loads a spritesheet and creates a sprite from it (custom asset pipelines)
	// > All sprites are normally created by the PlayBlitter constructor
	int LoadSpriteSheet( const std::string& path, const std::string& filename );
	// Loads a background image which is assumed to be the same size as the display buffer
	// > Returns the index of the loaded background
	int LoadBackground( const char* fileAndPath );

	//********************************************************************************************************************************
	// Sprite Getters and Setters
	//********************************************************************************************************************************

	// Gets the sprite id of the first matching sprite whose filename contains the given text
	// > Returns -1 if not found
	int GetSpriteId( const char* spriteName ) const;
	// Gets the root filename of a specific sprite
	const std::string& GetSpriteName( int spriteId );
	// Gets the size of the sprite with the given id
	Vector2f GetSpriteSize( int spriteId ) const;
	// Gets the number of frames in the sprite with the given id
	int GetSpriteFrames( int spriteId ) const;
	// Gets the origin of the sprite with the given id (offset from top left)
	Vector2f GetSpriteOrigin( int spriteId ) const;
	// Sets the origin of the sprite with the given id (offset from top left)
	void SetSpriteOrigin( int spriteId, Vector2f newOrigin, bool relative = false );
	// Centres the origin of the sprite with the given id
	void CentreSpriteOrigin( int spriteId );
	// Centres the origins of all the sprites
	void CentreAllSpriteOrigins();
	// Sets the origin of all sprites found matching the given name (offset from top left)
	void SetSpriteOrigins( const char* rootName, Vector2f newOrigin, bool relative = false );
	// Gets the number of sprites which have been loaded and created by PlayBlitter
	int GetTotalLoadedSprites() const { return m_nTotalSprites; }

	//********************************************************************************************************************************
	// Drawing functions
	//********************************************************************************************************************************

	// Draw the sprite without rotation or transparency (fastest draw)
	inline void Draw( int spriteId, Point2f pos, int frameIndex ) const { BlitSprite( spriteId, static_cast<int>( pos.x + 0.5f ), static_cast<int>( pos.y + 0.5f ), frameIndex ); }
	// Draw the sprite with transparency (slower than without transparency)
	inline void DrawTransparent( int spriteId, Point2f pos, int frameIndex, float alphaMultiply ) const { BlitSprite( spriteId, static_cast<int>( pos.x + 0.5f ), static_cast<int>( pos.y + 0.5f ), frameIndex, alphaMultiply ); }; // This just to force people to consider when they use an explicit alpha multiply
	// Draw the sprite rotated with transprency (slowest draw)
	inline void DrawRotated( int spriteId, Point2f pos, int frameIndex, float angle, float scale = 1.0f, float alphaMultiply = 1.0f ) const { RotateScaleSprite( spriteId, static_cast<int>( pos.x + 0.5f ), static_cast<int>( pos.y + 0.5f ), frameIndex, angle, scale, alphaMultiply ); }
	// Draws a previously loaded background image
	void DrawBackground( int backgroundIndex = 0 );
	// Multiplies the sprite image buffer by the colour values
	// > Applies to all subseqent drawing calls for this sprite, but can be reset by calling agin with rgb set to white
	void ColourSprite( int spriteId, int r, int g, int b );

	// Draws a string using a sprite-based font exported from PlayFontTool
	int DrawString( int fontId, Point2f pos, std::string text ) const;
	// Draws a centred string using a sprite-based font exported from PlayFontTool
	int DrawStringCentred( int fontId, Point2f pos, std::string text ) const;
	// Draws an individual text character using a sprite-based font 
	int DrawChar( int fontId, Point2f pos, char c ) const;
	// Draws a rotated text character using a sprite-based font 
	int DrawCharRotated( int fontId, Point2f pos, float angle, float scale, char c ) const;
	// Gets the width of an individual text character from a sprite-based font
	int GetFontCharWidth( int fontId, char c ) const;

	// A pixel-based sprite collision test based on drawing
	bool SpriteCollide( int s1Id, Point2f s1Pos, int s1FrameIndex, float s1Angle, int s1PixelColl[4], int s2Id, Point2f s2pos, int s2FrameIndex, float s2Angle, int s2PixelColl[4] ) const;

	// Internal sprite structure for storing individual sprite data
	struct Sprite
	{
		int id{ -1 }; // Fast way of finding the right sprite
		std::string name; // Slow way of finding the right sprite
		int width{ -1 }, height{ -1 }; // The width and height of a single image in the sprite
		int canvasWidth{ -1 }, canvasHeight{ -1 }; // The width and height of the entire sprite canvas
		int hCount{ -1 }, vCount{ -1 }, totalCount{ -1 };  // The number of sprite images in the canvas horizontally and verticaally
		int originX{ 0 }, originY{ 0 }; // The origin and centre of rotation for the sprite (whole pixels only)
		uint32_t* pCanvasBuffer{ nullptr }; // The sprite data
		uint32_t* pPreMultAlpha{ nullptr }; // The sprite data premultiplied with its own alpha
		Sprite() = default;
	};

private:

	//********************************************************************************************************************************
	// Constructors / destructors
	//********************************************************************************************************************************

	// Loads all the PNGs from the directory provided and sets them up as Sprites
	PlayBlitter( const char* path );
	// Frees up all the sprites and shuts down the manager
	~PlayBlitter(); 
	// The assignment operator is removed to prevent copying of a singleton class
	PlayBlitter& operator=( const PlayBlitter& ) = delete;
	// The copy constructor is removed to prevent copying of a singleton class
	PlayBlitter( const PlayBlitter& ) = delete; 

	//********************************************************************************************************************************
	// Internal functions relating to drawing
	//********************************************************************************************************************************

	// Draws a sprite using a direct copy of the sprite image to the display buffer
	// > Setting AlphaMultiply < 1 forces a less optimal rendering approach in BlitSprite
	void BlitSprite( int spriteId, int xpos, int ypos, int frameIndex, float alphaMultiply = 1.0f ) const;
	// Draws a sprite rotated and sclaed to the display buffer (much slower than Blit
	// > AlphaMultiply isn't a signfiicant additional slow down on RotateScaleSprite
	void RotateScaleSprite( int spriteId, int xpos, int ypos, int frameIndex, float angle, float scale, float alphaMultiply = 1.0f ) const;
	// Multiplies the sprite image by its own alpha transparency values to save repeating this calculation on every draw
	// > A colour multiplication can also be applied at this stage, which affects all subseqent drawing operations on the sprite
	void PreMultiplyAlpha( uint32_t* source, uint32_t* dest, int width, int height, int maxSkipWidth, float alphaMultiply, uint32_t colourMultiply );

	// Count of the total number of sprites loaded
	int m_nTotalSprites{ 0 };
	// Whether the singleton has been initialised yet
	bool m_bInitialised{ false };

	// Data about the current display buffer
	uint32_t* m_displayBuffer{ nullptr };
	// Width of the assigned display buffer
	int m_displayBufferWidth{ 0 };
	// height of the assigned display buffer
	int m_displayBufferHeight{ 0 };

	// A vector of all the loaded sprites
	std::vector< Sprite > vSpriteData;
	// A vector of all the loaded backgrounds
	std::vector< uint32_t* > vBackgroundData;

	// A pointer to the static instance
	static PlayBlitter* s_pInstance;

};

#endif
//*******************************************************************
// PLAY END: PlayBlitter.h
//*******************************************************************


//*******************************************************************
// PLAY BEGIN: PlaySpeaker.h
//*******************************************************************

#ifndef PLAY_PLAYSPEAKER_H
#define PLAY_PLAYSPEAKER_H
//********************************************************************************************************************************
//* Copyright 2020 Sumo-Digital Limited
//********************************************************************************************************************************
//* File:			PlaySpeaker.h
//* Created:		July 2020 - Sumo Academy
//* Description:	Declaration for a simple audio manager 
//*					
//********************************************************************************************************************************

// Encapsulates the functionality of a sound manager 
// > Singleton class accessed using PlaySpeaker::Instance()
class PlaySpeaker
{
public:
	//********************************************************************************************************************************
	// Instance access functions
	//********************************************************************************************************************************

	// Instantiates class and loads all the.MP3 sounds from the directory provided
	static PlaySpeaker& Instance();
	// Returns the PlaySpeaker instance
	static PlaySpeaker& Instance( const char* path );
	// Destroys the PlaySpeaker instance
	static void Destroy();

	//********************************************************************************************************************************
	// Sound playing and stopping
	//********************************************************************************************************************************

	// Play a sound using part of all of its name
	void StartSound( const char* name, bool bLoop );
	//  Stop the currently playing sound using part of all of its name
	void StopSound( const char* name ); 

private:
	//********************************************************************************************************************************
	// Constructor and destructor
	//********************************************************************************************************************************

	// Creates manager object and loads all the.MP3 sounds in the specified directory
	PlaySpeaker( const char* path ); 
	// Closes all loaded sounds
	~PlaySpeaker(); 
	// The assignment operator is removed to prevent copying of a singleton class
	PlaySpeaker& operator=( const PlaySpeaker& ) = delete;
	// The copy operator is removed to prevent copying of a singleton class
	PlaySpeaker( const PlaySpeaker& ) = delete;

	// Vector of mp3 strings
	std::vector< std::string > vSoundStrings;
	// Pointer to the singleton
	static PlaySpeaker* s_pInstance;
};

#endif

//*******************************************************************
// PLAY END: PlaySpeaker.h
//*******************************************************************


//*******************************************************************
// PLAY BEGIN: PlayManager.h
//*******************************************************************

#ifndef PLAY_PLAYMANAGER_H
#define PLAY_PLAYMANAGER_H
//********************************************************************************************************************************
// Copyright 2020 Sumo-Digital Limited
//********************************************************************************************************************************
// File:		PlayManager.h
// Created:		October 2020 - Sumo Academy
// Description:	A manager for providing simplified access to the PlayBuffer framework
// Platform:	Independent
// Notes:		The PlayManager is "opt in" as many will want to create their own GameObject
//********************************************************************************************************************************

#ifdef PLAY_USING_GAMEOBJECT_MANAGER

#ifndef PLAY_ADD_GAMEOBJECT_MEMBERS
#define PLAY_ADD_GAMEOBJECT_MEMBERS 
#endif

// Slightly more friendly-looking Vector and Point aliases 
using Vector2D = Vector2f;
using Point2D = Vector2f;

#ifdef PLAY_IMPLEMENTATION

// PlayManager manges a map of GameObject structures
// > Additional member variables can be added with PLAY_ADD_GAMEOBJECT_MEMBERS 
struct GameObject
{
	GameObject( int type, Point2D pos, int collisionRadius, int spriteId );

	// Default member variables: don't change these!
	int type{ -1 };
	int spriteId{ -1 };
	Point2D pos{ 0.0f, 0.0f };
	Point2D oldPos{ 0.0f, 0.0f };
	Vector2D velocity{ 0.0f, 0.0f };
	Vector2D acceleration{ 0.0f, 0.0f };
	float rotation{ 0.0f };
	float rotSpeed{ 0.0f };
	float oldRot{ 0.0f };
	int frame{ 0 };
	float framePos{ 0.0f };
	float animSpeed{ 0.0f };
	int radius{ 0 };
	float scale{ 1 };
	PLAY_ADD_GAMEOBJECT_MEMBERS

	int GetId() { return m_id; }

private:
	// The GameObject's id should never be changed manually so we make it private!
	int m_id{ -1 };

	// Preventing assignment and copying reduces the potential for bugs
	GameObject& operator=( const GameObject& ) = delete;
	GameObject( const GameObject& ) = delete;
};

#else

struct GameObject;

#endif

namespace Play
{
	// Alignment for font drawing operations
	enum Align
	{
		LEFT = 0,
		RIGHT,
		CENTRE,
	};

	enum Direction
	{
		HORIZONTAL = 0,
		VERTICAL,
		ALL,
	};

	// PlayManager uses colour values from 0-100 for red, green, blue and alpha
	struct Colour
	{
		Colour( float r, float g, float b ) : red( r ), green( g ), blue( b ) {}
		Colour( int r, int g, int b ) : red( static_cast<float>( r ) ), green( static_cast<float>( g ) ), blue( static_cast<float>( b ) ) {}
		float red, green, blue;
	};

	extern Colour cBlack, cRed, cGreen, cBlue, cMagenta, cCyan, cYellow, cOrange, cWhite, cGrey;

	//**************************************************************************************************
	// Manager creation and deletion
	//**************************************************************************************************

	// Initialises the managers and creates a window of the required dimensions
	void CreateManager( int width, int height, int scale );
	// Shuts down the managers and closes the window
	void DestroyManager();

	//**************************************************************************************************
	// PlayBuffer functions
	//**************************************************************************************************

	// Clears the display buffer using the colour provided
	void ClearDrawingBuffer( Colour col );
	// Loads a PNG file as the background image for the window
	int LoadBackground( const char* pngFilename );
	// Draws the background image previously loaded with Play::LoadBackground() into the drawing buffer
	void DrawBackground( int background = 0 );
	// Draws text to the screen using the built-in debug font
	void DrawDebugText( Point2D pos, const char* text, Colour col = cWhite, bool centred = true );
	// Copies the contents of the drawing buffer to the window
	void PresentDrawingBuffer();
	// Handles the compliations of windows programming so you don't have to!
	int HandleWindows( PLAY_WINARGS_IN, const char* windowName );
	// Gets the co-ordinates of the mouse cursor within the display buffer
	Point2D GetMousePos();

	//**************************************************************************************************
	// PlaySpeaker functions
	//**************************************************************************************************

	// Plays an mp3 audio file from the "Data\Sounds" directory
	void PlayAudio( const char* mp3Filename );
	// Loops an mp3 audio file from the "Data\Sounds" directory
	void StartAudioLoop( const char* mp3Filename );
	// Stops a looping mp3 audio file started with Play::StartSoundLoop()
	void StopAudioLoop( const char* mp3Filename );

	//**************************************************************************************************
	// PlayBlitter functions
	//**************************************************************************************************

	// Gets the sprite id of the first matching sprite whose filename contains the given text
	int GetSpriteId( const char* spriteName );
	// Gets the pixel height of a sprite
	int GetSpriteHeight( const char* spriteName );
	// Gets the pixel width of a sprite
	int GetSpriteWidth( const char* spriteName );
	// Gets the stem filename for the sprite (without path or extension)
	const char* GetSpriteName( int spriteId );
	// Blends the sprite with the given colour (works best on white sprites)
	// > Note that colouring affects subsequent DrawSprite calls using the same sprite!!
	void ColourSprite( const char* spriteName, Colour col );

	// Centres the origin of the first sprite found matching the given name
	void CentreSpriteOrigin( const char* spriteName );
	// Centres the origin of all sprites found matching the given name
	void CentreMatchingSpriteOrigins( const char* partName );
	// Centres the origins of all loaded sprites
	void CentreAllSpriteOrigins();
	// Moves the origin of the first sprite found matching the given name
	void MoveSpriteOrigin( const char* spriteName, int xoffset, int yoffset );
	// Moves the origin of all sprites found matching the given name
	void MoveMatchingSpriteOrigins( const char* partName, int xoffset, int yoffset );
	// Moves the origin of all loaded sprites
	void MoveAllSpriteOrigins( int xoffset, int yoffset );

	// Draws the first matching sprite whose filename contains the given text
	void DrawSprite( const char* spriteName, Point2D pos, int frameIndex );
	// Draws the sprite using its unique sprite ID
	void DrawSprite( int spriteID, Point2D pos, int frame );
	// Draws the sprite with transparency (slower than DrawSprite)
	void DrawSpriteTransparent( const char* spriteName, Point2D pos, int frame, float opacity );
	// Draws the sprite with transparency (slower than DrawSprite)
	void DrawSpriteTransparent( int spriteID, Point2D pos, int frame, float opacity );
	// Draws the sprite with rotation and transparancy (slowest DrawSprite)
	void DrawSpriteRotated( const char* spriteName, Point2D pos, int frame, float angle, float scale, float opacity = 1.0f );
	// Draws the sprite with rotation and transparancy (slowest DrawSprite)
	void DrawSpriteRotated( int spriteID, Point2D pos, int frame, float angle, float scale, float opacity = 1.0f );
	// Draws a single-pixel wide line between two points in the given colour
	void DrawLine( Point2D start, Point2D end, Colour col );
	// Draws a single-pixel wide circle in the given colour
	void DrawCircle( Point2D pos, int radius, Colour col );
	// Draws a line between two points using a sprite
	// > Note that colouring affects subsequent DrawSprite calls using the same sprite!!
	void DrawSpriteLine( Point2D startPos, Point2D endPos, const char* penSprite, Colour c = cWhite );
	// Draws a circle using a sprite
	// > Note that colouring affects subsequent DrawSprite calls using the same sprite!!
	void DrawSpriteCircle( int x, int y, int radius, const char* penSprite, Colour c = cWhite );
	// Draws text using a sprite-based font exported from PlayFontTool
	void DrawFontText( const char* fontId, std::string text, Point2D pos, Align justify = LEFT );


	//**************************************************************************************************
	// GameObject functions
	//**************************************************************************************************

	// Creates a new GameObject and adds it to the managed list.
	// > Returns the new object's unique id
	int CreateGameObject( int type, Point2D pos, int collisionRadius, const char* spriteName );
	// Retrieves a GameObject based on its id
	// > Returns an object with a type of -1 if no object can be found
	GameObject& GetGameObject( int id );
	// Retrieves the first GameObject matching the given type
	// > Returns an object with a type of -1 if no object can be found
	GameObject& GetGameObjectByType( int type );
	// Collects the IDs of all of the GameObjects with the matching type
	std::vector<int> CollectGameObjectIDsByType( int type );
	// Collects the IDs of all of the GameObjects
	std::vector<int> CollectAllGameObjectIDs();
	// Performs a typical update of the object's position and animation
	void UpdateGameObject( GameObject& object );
	// Deletes the GameObject with the corresponding id
	//> Use GameObject.GetId() to find out its unique id
	void DestroyGameObject( int id );
	// Deletes all GameObjects with the corresponding type
	void DestroyGameObjectsByType( int type );
	
	// Checks whether the two objects are within each other's collision radii
	bool IsColliding( GameObject& obj1, GameObject& obj2 );
	// Checks whether any part of the object is visible within the DisplayBuffer
	bool IsVisible( GameObject& obj );
	// Checks whether the object is overlapping the edge of the screen and moving outwards 
	bool IsLeavingDisplayArea( GameObject& obj, Direction dirn = ALL );
	// Checks whether the animation has completed playing
	bool IsAnimationComplete( GameObject& obj );

	// Sets the velocity of the object based on a target rotation angle
	void SetGameObjectDirection( GameObject& obj, int speed, float rotation );
	// Set the velocity of the object based on a target point
	void PointGameObject( GameObject& obj, int speed, int targetX, int targetY );

	// Changes the object's current spite and resets its animation frame to the start
	void SetSprite( GameObject& obj, const char* spriteName, float animSpeed );
	// Draws the object's sprite without rotation or transparancy (fastest)
	void DrawObject( GameObject& obj );
	// Draws the object's sprite with transparancy (slower than DrawObject)
	void DrawObjectTransparent( GameObject& obj, float opacity );
	// Draws the object's sprite with rotation and transparancy (slower than DrawObject)
	void DrawObjectRotated( GameObject& obj, float opacity = 1.0f );

	//**************************************************************************************************
	// Miscellaneous functions
	//**************************************************************************************************

	// Returns true if the key has been pressed since it was last released
	// > https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	bool KeyPressed( int vKey );
	// Returns true if the key is currently being held down
	// > https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	bool KeyDown( int vKey );

	// Returns a random number as if you rolled a die with this many sides
	int RandomRoll( int sides );
	// Returns a random number from min to max inclusive
	int RandomRollRange( int min, int max );

	// Converts radians to degrees
	constexpr float RadToDeg( float radians )
	{
		return ( radians / PLAY_PI ) * 180.0f;
	}

	// Converts radians to degrees
	constexpr float DegToRad( float degrees )
	{
		return ( degrees / 180.0f ) * PLAY_PI;
	}

}
#endif

#endif


//*******************************************************************
// PLAY END: PlayManager.h
//*******************************************************************


#endif // PLAYPCH_H





//*******************************************************************
//*******************************************************************
//*******************************************************************
#ifdef PLAY_IMPLEMENTATION
//*******************************************************************
//*******************************************************************
//*******************************************************************

//*******************************************************************
// PLAY BEGIN: PlayMemory.cpp
//*******************************************************************

//********************************************************************************************************************************
//* Copyright 2020 Sumo-Digital Limited
//********************************************************************************************************************************
//* File:			PlayMemory.cpp
//* Created:		August 2020 - Sumo Academy
//* Platform:		Independent
//* Description:	Implementation of a simple memory tracker to prevent leaks. Uses #define new which looks neat and tidy
//*                 (especially for new C++ programmers), but doesn't work for placement new, so you are likely to get compile 
//*                 errors if you start including it in your own header files.  
//*                 Avoids use of STL or anything else which allocates memory as this could create infinite loops!
//* Notes:          This is a simple approach to support your understanding of overriding the new operator.
//*                 See below for more advanced approaches:
//*                 1) The CRT Debug Heap Library (a more advanced version of this approach)
//*                 https://docs.microsoft.com/en-us/visualstudio/debugger/crt-debug-heap-details?view=vs-2019
//*                 2) Heap Profiling in the debugger 
//*                 https://docs.microsoft.com/en-us/visualstudio/profiling/memory-usage?view=vs-2019
//********************************************************************************************************************************


// Undefine 'new' in this compilation unit only.
// #TODO : Review the use of the 'new' macro it could be asking for trouble.
#undef new

constexpr int MAX_ALLOCATIONS = 8192 * 4;
constexpr int MAX_FILENAME = 1024;

// A structure to store data on each memory allocation
struct ALLOC
{
    void* address = 0;
    char file[MAX_FILENAME] = { 0 };
    int line = 0;
    size_t size = 0;

    ALLOC(void* a, const char* fn, int l, size_t s) { address = a; line = l; size = s; strcpy_s(file, fn); };
    ALLOC(void) { };
};

ALLOC g_vAllocations[MAX_ALLOCATIONS];
unsigned int g_vAllocCount = 0;


void CreateStaticObject( void );

//********************************************************************************************************************************
// Overrides for new operator (x4)
//********************************************************************************************************************************

// The file and line are passed through using the macro defined in PlayMemory.h which redefines new. This will only happen if 
// PlayMemory.h has been parsed in advace of the use of new in the relevant code. This approach is problematic for classes 
// the safest appproach. The two definitions of new without the file and line pick up any other memory allocations for completeness.
void* operator new( size_t size, const char *file, int line )
{
    PB_ASSERT(g_vAllocCount < MAX_ALLOCATIONS);
    CreateStaticObject();
    void* p = malloc(size);
    g_vAllocations[g_vAllocCount++] = ALLOC{ p, file, line, size };
    return p;
}

void* operator new[](size_t size, const char* file, int line)
{
    PB_ASSERT(g_vAllocCount < MAX_ALLOCATIONS);
    CreateStaticObject();
    void* p = malloc(size);
    g_vAllocations[g_vAllocCount++] = ALLOC{ p, file, line, size };
    return p;
}

void* operator new(size_t size)
{
    PB_ASSERT(g_vAllocCount < MAX_ALLOCATIONS);
    CreateStaticObject();
    void* p = malloc(size);
    g_vAllocations[g_vAllocCount++] = ALLOC{ p, "Unknown", 0, size };
    return p;
}

void* operator new[](size_t size)
{
    PB_ASSERT(g_vAllocCount < MAX_ALLOCATIONS);
    CreateStaticObject();
    void* p = malloc(size);
    g_vAllocations[g_vAllocCount++] = ALLOC{ p, "Unknown", 0, size };
    return p;
}

//********************************************************************************************************************************
// Overrides for delete operator (x4)
//********************************************************************************************************************************

// The definitions with file and line are only included for exception handling, where it looks for a form of delete that matches 
// the new that was used to allocate it.
void operator delete(void* p, const char* file, int line)
{
    UNREFERENCED_PARAMETER( line );
    UNREFERENCED_PARAMETER( file );
    operator delete(p);
}

void operator delete(void* p)
{
    for (unsigned int a=0; a<g_vAllocCount; a++ )
    {
        if (g_vAllocations[a].address == p)
        {
            g_vAllocations[a] = g_vAllocations[g_vAllocCount-1];
            g_vAllocations[g_vAllocCount-1].address = nullptr;
            g_vAllocCount--;
        }
    }
    free(p);
}

void operator delete[](void* p, const char* file, int line)
{
    UNREFERENCED_PARAMETER( line );
    UNREFERENCED_PARAMETER( file );
    operator delete[](p);
}

void operator delete[](void* p)
{
    for (unsigned int a = 0; a < g_vAllocCount; a++)
    {
        if (g_vAllocations[a].address == p)
        {
            g_vAllocations[a] = g_vAllocations[g_vAllocCount - 1];
            g_vAllocations[g_vAllocCount - 1].address = nullptr;
            g_vAllocCount--;
        }
    }
    free(p);
}


//********************************************************************************************************************************
// Printing allocations
//********************************************************************************************************************************

// A method for printing out all the memory allocation immediately before program exit (or as close as you can get)
// This is achieved by creating a class as a static object before the first memory allocation, which stays in scope until
// after everything else is destroyed. When it is cleaned up its destructor prints the allocations to show us any leaks!
class DestroyedLast
{
public:
    DestroyedLast()
    {
        PrintAllocations( "<STARTUP>");
    }
    ~DestroyedLast()
    {
        PrintAllocations( "<MEMORY LEAK>" );
    }
};

void CreateStaticObject( void )
{
    static DestroyedLast last;
}

void PrintAllocations( const char* tagText )
{
    int bytes = 0;
    char buffer[MAX_FILENAME * 2] = { 0 };
    DebugOutput("**************************************************\n");
    DebugOutput("MEMORY ALLOCATED\n");
    DebugOutput("**************************************************\n");
    for (ALLOC a : g_vAllocations)
    {
        if (a.address != nullptr)
        {
            char* lastSlash = strrchr(a.file, '\\' );
            if (lastSlash)
            {
                strcpy_s(buffer, lastSlash+1);
                strcpy_s(a.file, buffer);
            }
            // Format in such a way that VS can double click to jump to the allocation.
            sprintf_s( buffer, "%s %s(%d): 0x%02X %d bytes\n", tagText, a.file, a.line, static_cast<int>( reinterpret_cast<long long>( a.address ) ), static_cast<int>( a.size ) );
            DebugOutput(buffer);
            bytes += static_cast<int>(a.size);
       }
    }
    sprintf_s( buffer, "%s Total = %d bytes\n", tagText, bytes );
    DebugOutput(buffer);
    DebugOutput("**************************************************\n");

}



//*******************************************************************
// PLAY END: PlayMemory.cpp
//*******************************************************************


//*******************************************************************
// PLAY BEGIN: PlayBuffer.cpp
//*******************************************************************

//********************************************************************************************************************************
//* Copyright 2020 Sumo-Digital Limited
//********************************************************************************************************************************
// File:		PlayBuffer.cpp
// Created:		March 2020 - Sumo Academy
// Description:	A software drawing buffer which provides the basis for creating 2D games  
// Platform:	Windows
// Notes:		Provides a 32-bit ARGB display buffer
//********************************************************************************************************************************

// Instruct Visual Studio to add these to the list of libraries to link
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "dwmapi.lib")


PlayBuffer* PlayBuffer::s_pInstance = nullptr;

// External functions which must be implemented by the user 
extern bool MainGameUpdate( float ); // Called every frame
extern void MainGameExit( void ); // Called on quit

PlayBuffer::Pixel PlayBuffer::pixBlack{ 0x00, 0x00, 0x00 };
PlayBuffer::Pixel PlayBuffer::pixWhite{ 0xFF, 0xFF, 0xFF };
PlayBuffer::Pixel PlayBuffer::pixRed{ 0xFF, 0x00, 0x00 };
PlayBuffer::Pixel PlayBuffer::pixGreen{ 0x00, 0xFF, 0x00 };
PlayBuffer::Pixel PlayBuffer::pixBlue{ 0x00, 0x00, 0xFF };
PlayBuffer::Pixel PlayBuffer::pixMagenta{ 0xFF, 0x00, 0xFF };
PlayBuffer::Pixel PlayBuffer::pixCyan{ 0x00, 0xFF, 0xFF };
PlayBuffer::Pixel PlayBuffer::pixYellow{ 0xFF, 0xFF, 0x00 };
PlayBuffer::Pixel PlayBuffer::pixOrange{ 0xFF, 0x8F, 0x00 };
PlayBuffer::Pixel PlayBuffer::pixGrey{ 0x80, 0x80, 0x80 };



//********************************************************************************************************************************
// Constructor / Destructor (Private)
//********************************************************************************************************************************

PlayBuffer::PlayBuffer( int nWidth, int nHeight, int nScale, Pixel bgColour )
{
	m_width = nWidth;
	m_width = nWidth;
	m_height = nHeight;
	m_scale = nScale;

	// A working buffer for our display. Each pixel is stored as an unsigned 32-bit integer: alpha<<24 | red<<16 | green<<8 | blue
	m_pDisplayBuffer = new uint32_t[static_cast<size_t>( m_width ) * m_height];
	PB_ASSERT( m_pDisplayBuffer );

	memset( m_pDisplayBuffer, 0, sizeof( uint32_t ) * m_width * m_height );

	uint32_t* p = m_pDisplayBuffer;

	for( int i = 0; i < m_width * m_height; i++ )
		*p++ = bgColour.bits;

	m_pDebugFontBuffer = nullptr; // Created on first use

	// Initialize GDI+
	Gdiplus::GdiplusStartupInput startupInput;
	ULONG_PTR token;
	Gdiplus::Status gdiStatus = Gdiplus::GdiplusStartup( &token, &startupInput, NULL );
	PB_ASSERT( Gdiplus::Ok == gdiStatus );
	m_gpToken = token;
}

PlayBuffer::~PlayBuffer( void )
{
	delete[] m_pDisplayBuffer;

	if( m_pDebugFontBuffer )
		delete[] m_pDebugFontBuffer;

	PB_ASSERT( s_pInstance->m_gpToken );
	Gdiplus::GdiplusShutdown( static_cast<ULONG_PTR>(s_pInstance->m_gpToken) );

	s_pInstance = nullptr;
}

//********************************************************************************************************************************
// Instance functions
//********************************************************************************************************************************

PlayBuffer& PlayBuffer::Instance()
{
	if( !s_pInstance )
		PB_ASSERT_MSG( false, "Trying to use PlayBuffer without initialising it!" );

	return *s_pInstance;
}

PlayBuffer& PlayBuffer::Instance( int nWidth, int nHeight, int nScale, Pixel bgColour )
{
	PB_ASSERT_MSG( !s_pInstance, "Trying to create multiple instances of singleton class!" );

	s_pInstance = new PlayBuffer( nWidth, nHeight, nScale, bgColour );

	return *s_pInstance;
}

void PlayBuffer::Destroy()
{
	PB_ASSERT_MSG( s_pInstance, "Trying to use destroy PlayBuffer which hasn't been instanced!" );

	delete s_pInstance;

	s_pInstance = nullptr;
}

//********************************************************************************************************************************
// Windows functions
//********************************************************************************************************************************

int PlayBuffer::HandleWindows( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, LPCWSTR windowName )
{
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof( WNDCLASSEX );

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = PlayBuffer::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon( hInstance, IDI_APPLICATION );
	wcex.hCursor = LoadCursor( nullptr, IDC_ARROW );
	wcex.hbrBackground = (HBRUSH)( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = windowName;
	wcex.hIconSm = LoadIcon( wcex.hInstance, IDI_APPLICATION );

	RegisterClassExW( &wcex );

	int	w = m_width * m_scale;
	int h = m_height * m_scale;

	UINT dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	RECT rect = { 0, 0, w, h }; 
	AdjustWindowRect( &rect, dwStyle, FALSE );
	HWND hWnd = CreateWindowW( windowName, windowName, dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr );

	if( !hWnd )
		return FALSE;

	m_hWindow = hWnd;

	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );

	HACCEL hAccelTable = LoadAccelerators( hInstance, windowName );

	LARGE_INTEGER frequency;        
	double elapsedTime = 0.0;
	static LARGE_INTEGER lastDrawTime;
	LARGE_INTEGER now;

	MSG msg{};
	bool quit = false;

	// Set up counters for timing the frame
	QueryPerformanceCounter( &lastDrawTime );
	QueryPerformanceFrequency( &frequency );

	// Standard windows message loop
	while( !quit )
	{
		// Hangle windows messages
		if( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
		{
			if( msg.message == WM_QUIT )
				break;

			if( !TranslateAccelerator( msg.hwnd, hAccelTable, &msg ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}

		do
		{
			QueryPerformanceCounter( &now );
			elapsedTime = ( now.QuadPart - lastDrawTime.QuadPart ) * 1000.0 / frequency.QuadPart;

		} while( elapsedTime < 1000.0f / FRAMES_PER_SECOND );

		// Call the main game update function
		quit = MainGameUpdate( static_cast<float>( elapsedTime ) / 1000.0f );
		lastDrawTime = now;

		DwmFlush(); // Waits for DWM compositor to finish
	}

	// Call the main game cleanup function
	MainGameExit();

	return static_cast<int>( msg.wParam );
}


LRESULT CALLBACK PlayBuffer::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
		case WM_PAINT:
			PAINTSTRUCT ps;
			BeginPaint( hWnd, &ps );
			EndPaint( hWnd, &ps );
			break;

		case WM_DESTROY:
			PostQuitMessage( 0 );
			break;
		case WM_LBUTTONDOWN:
			s_pInstance->m_bMouseDown[0] = true;
			break;
		case WM_LBUTTONUP:
			s_pInstance->m_bMouseDown[0] = false;
			break;
		case WM_RBUTTONDOWN:
			s_pInstance->m_bMouseDown[1] = true;
			break;
		case WM_RBUTTONUP:
			s_pInstance->m_bMouseDown[1] = false;
			break;
		case WM_MOUSEMOVE:
			s_pInstance->m_mousePos.x = static_cast<float>( GET_X_LPARAM( lParam ) / s_pInstance->m_scale );
			s_pInstance->m_mousePos.y = static_cast<float>( GET_Y_LPARAM( lParam ) / s_pInstance->m_scale );
			break;
		case WM_MOUSELEAVE:
			s_pInstance->m_mousePos.x = -1;
			s_pInstance->m_mousePos.y = -1;
			break;
		default:
			return DefWindowProc( hWnd, message, wParam, lParam );
	}
	return 0;
}


int PlayBuffer::Present( void )
{
	// Set up a BitmapInfo structure to represent the pixel format of the display buffer
	BITMAPINFOHEADER bitmap_info_header
	{
			sizeof( BITMAPINFOHEADER ), // size of its own data,
			m_width, m_height,			// width and height
			1, 32, BI_RGB,				// planes must always be set to 1 (docs), 32-bit pixel data, uncompressed 
			0, 0, 0, 0, 0				// rest can be set to 0 as this is uncompressed and has no palette
	};

	BITMAPINFO bitmap_info{ bitmap_info_header, { 0,0,0,0 } };	// No palette data required for this bitmap

	HDC hDC = GetDC( m_hWindow );

	// Copy the display buffer to the window: GDI only implements up scaling using simple pixel duplication, but that's what we want
	// Note that GDI+ DrawImage would do the same thing, but it's much slower! 
	StretchDIBits( hDC, 0, 0, m_width * m_scale, m_height * m_scale, 0, m_height + 1, m_width, -m_height, m_pDisplayBuffer, &bitmap_info, DIB_RGB_COLORS, SRCCOPY ); // We flip h because Bitmaps store pixel data upside down.
	
	ReleaseDC( m_hWindow, hDC );

	return 1;
}

//********************************************************************************************************************************
// Mouse functions
//********************************************************************************************************************************

bool PlayBuffer::GetMouseDown( int button ) const
{
	PB_ASSERT_MSG( button == 1 || button == 0, "Invalid mouse button selected." );
	return m_bMouseDown[button];
};

bool PlayBuffer::KeyPressed( int vKey )
{
	static std::map< int, bool > keyMap;

	bool& held = keyMap[vKey];

	if( KeyDown( vKey ) && !held )
	{
		held = true;
		return true;
	}

	if( !KeyDown( vKey ) )
		held = false;

	return false;
}

bool PlayBuffer::KeyDown( int vKey )
{
	return GetAsyncKeyState( vKey ) & 0x8000;
}

//********************************************************************************************************************************
// Basic buffer drawing functions
//********************************************************************************************************************************

void PlayBuffer::ClearBuffer( Pixel colour )
{
	uint32_t* pBuffEnd = m_pDisplayBuffer + ( m_width * m_height );
	for( uint32_t* pBuff = m_pDisplayBuffer; pBuff < pBuffEnd; *pBuff++ = colour.bits );
}

void PlayBuffer::DrawPixel( Point2f pos, Pixel srcPix )
{
	// Convert floating point co-ordinates to pixels
	DrawPixel( static_cast<int>( pos.x + 0.5f ), static_cast<int>( pos.y + 0.5f ), srcPix );
}

void PlayBuffer::DrawPixel( int posX, int posY, Pixel srcPix )
{
	if( srcPix.a == 0x00 || posX < 0 || posX >= m_width || posY < 0 || posY >= m_height )
		return;

	uint32_t* dest = &m_pDisplayBuffer[ ( posY * m_width ) + posX ];

	if( srcPix.a == 0xFF ) // Completely opaque pixel - no need to blend
	{
		*dest = srcPix.bits;
	}
	else
	{
		Pixel blendPix( *dest );
		float srcAlpha = srcPix.a / 255.0f;
		float oneMinusSrcAlpha = 1.0f - srcAlpha;

		blendPix.a = 0xFF;
		blendPix.r = static_cast<uint8_t>( ( srcAlpha * srcPix.r ) + ( oneMinusSrcAlpha * blendPix.r ) );
		blendPix.g = static_cast<uint8_t>( ( srcAlpha * srcPix.g ) + ( oneMinusSrcAlpha * blendPix.g ) );
		blendPix.b = static_cast<uint8_t>( ( srcAlpha * srcPix.b ) + ( oneMinusSrcAlpha * blendPix.b ) );

		*dest = blendPix.bits;
	}

	return;
}

void PlayBuffer::DrawLine( Point2f startPos, Point2f endPos, Pixel pix )
{
	// Convert floating point co-ordinates to pixels
	int x1 = static_cast<int>( startPos.x + 0.5f );
	int y1 = static_cast<int>( startPos.y + 0.5f );
	int x2 = static_cast<int>( endPos.x + 0.5f );
	int y2 = static_cast<int>( endPos.y + 0.5f );

	DrawLine( x1, y1, x2, y2, pix );
}


void PlayBuffer::DrawLine( int startX, int startY, int endX, int endY, Pixel pix )
{
	//Implementation of Bresenham's Line Drawing Algorithm
	int dx = abs( endX - startX );
	int sx = 1;
	if( endX < startX ) { sx = -1; }

	int dy = -abs( endY - startY );
	int sy = 1;
	if( endY < startY ) { sy = -1; }

	int err = dx + dy;

	if( err == 0 ) return;

	int x = startX;
	int y = startY;

	while( true )
	{
		DrawPixel( x, y, pix );

		if( x == endX && y == endY )
			break;

		int e2 = 2 * err;
		if( e2 >= dy )
		{
			err += dy;
			x += sx;
		}
		if( e2 <= dx )
		{
			err += dx;
			y += sy;
		}
	}
}

void PlayBuffer::DrawRect( Point2f topLeft, Point2f bottomRight, Pixel pix, bool fill )
{
	// Convert floating point co-ordinates to pixels
	int x1 = static_cast<int>( topLeft.x + 0.5f );
	int x2 = static_cast<int>( bottomRight.x + 0.5f );
	int y1 = static_cast<int>( topLeft.y + 0.5f );
	int y2 = static_cast<int>( bottomRight.y + 0.5f );

	if( fill )
	{
		for( int x = x1; x < x2; x++ )
		{
			for( int y = y1; y < y2; y++ )
				DrawPixel( x, y , pix );
		}
	}
	else
	{
		DrawLine( x1, y1, x2, y1, pix );
		DrawLine( x2, y1, x2, y2, pix );
		DrawLine( x2, y2, x1, y2, pix );
		DrawLine( x1, y2, x1, y1, pix );
	}
}

// Private function called by DrawCircle
void PlayBuffer::DrawCircleOctants( int posX, int posY, int offX, int offY, Pixel pix )
{
	DrawPixel( { posX + offX , posY + offY }, pix );
	DrawPixel( { posX - offX , posY + offY }, pix );
	DrawPixel( { posX + offX , posY - offY }, pix );
	DrawPixel( { posX - offX , posY - offY }, pix );
	DrawPixel( { posX - offY , posY + offX }, pix );
	DrawPixel( { posX + offY , posY - offX }, pix );
	DrawPixel( { posX - offY , posY - offX }, pix );
	DrawPixel( { posX + offY , posY + offX }, pix );
}

void PlayBuffer::DrawCircle( Point2f pos, int radius, Pixel pix )
{
	// Convert floating point co-ordinates to pixels
	int x = static_cast<int>( pos.x + 0.5f );
	int y = static_cast<int>( pos.y + 0.5f );

	int dx = 0;
	int dy = radius;

	int d = 3 - 2 * radius;
	DrawCircleOctants( x, y, dx, dy, pix );

	while( dy >= dx )
	{
		dx++;
		if( d > 0 )
		{
			dy--;
			d = static_cast<int>( d + 4 * ( dx - dy ) + 10 );
		}
		else
		{
			d = static_cast<int>( d + 4 * dx + 6 );
		}
		DrawCircleOctants( x, y, dx, dy, pix );
	}
};


//********************************************************************************************************************************
// Debug font functions
//********************************************************************************************************************************

// Settings for the embedded debug font
#define FONT_IMAGE_WIDTH	96
#define FONT_IMAGE_HEIGHT	36
#define FONT_CHAR_WIDTH		6
#define FONT_CHAR_HEIGHT	12

// A 96x36 font image @ 1bpp containing basic ASCII characters from 0x30 (0) to 0x5F (underscore) at 6x12 pixels each
static const uint32_t debugFontData[] =
{
	0x87304178, 0x0800861F, 0xFFFFFFE1, 0x7BBFBE79, 0xF7FE79EF, 0xFFFFFFFE, 0x7BBFBE79, 0xF7FE79EC, 0xFFFFFFFE, 0x7BBFBE79, 0xF7FE79EC, 0xFFFFFFFE, 0x7BBFBE79, 0xF7FE79EF, 0xFFEE3DFE, 0x6BB86080,
	0x1078860F, 0xE3DFFEFE, 0x5BB7FEFB, 0xE7BE7BEF, 0xFFBFFF41, 0x7BB7FEFB, 0xE7BE7BEC, 0xFFDFFEDF, 0x7BB7FEFB, 0xE7BE7BEC, 0xFFEE3DDF, 0x7BB7FEFB, 0xE7BE7BEF, 0xFFFFFFFF, 0x7BB7BEF9, 0xE7BE7BEF,
	0xFFFFFFDF, 0x87B001F8, 0x187E87EF, 0xFFFFFFDF, 0x86106104, 0x00007A30, 0x1E7C5061, 0x79E79E79, 0xF7DF7B7F, 0x5E7DA79E, 0x79E79F79, 0xF7DF7B7F, 0x5E7DA79E, 0x79E79F79, 0xF7DF7B7F, 0x5E7DA79E,
	0x59E79F79, 0xF7DF7B7F, 0x597DA79E, 0x58005F78, 0x30D0037F, 0x477DA79E, 0x59E79F79, 0xF7DE7B7F, 0x597DA79E, 0x59E79F79, 0xF7DE7B7F, 0x5E7DA79E, 0x41E79F79, 0xF7DE7B7F, 0x5E7DA79E, 0x7DE79F79,
	0xF7DE7B7F, 0x5E7DA79E, 0x7DE79E79, 0xF7DE7B7F, 0x5E7DA79E, 0x81E06104, 0x07C17A38, 0xDE01A7A1, 0x06106101, 0xE79E79E0, 0x337F3FFF, 0x79E79EED, 0xE79E79EF, 0xB77FBFFF, 0x79E79FED, 0xE79E79EF,
	0xB7BFBFFF, 0x79E79FED, 0xE79A79EF, 0xB7BFBFFF, 0x79E75FED, 0xE79AB5EF, 0x77DFBFFF, 0x05E0E1ED, 0xE79ACC0E, 0xF7DFBFFF, 0x7DE77EED, 0xE79AB7ED, 0xF7EFBFFF, 0x7DE7BEED, 0xE79A7BEB, 0xF7EFBFFF,
	0x7DE7BEED, 0xE79A7BE7, 0xF7F7BFFF, 0x7DA7BEED, 0xE79A7BE7, 0xF7F7BCFF, 0x7DD79EED, 0xEB5A7BE7, 0xF7FBBCFF, 0x7C27A1EE, 0x1CE57810, 0x33FB3EC0
};

void PlayBuffer::DecompressDubugFont( void )
{
	m_pDebugFontBuffer = new uint8_t[FONT_IMAGE_WIDTH * FONT_IMAGE_HEIGHT];

	for( int y = 0; y < FONT_IMAGE_HEIGHT; y++ )
	{
		for( int x = 0; x < FONT_IMAGE_WIDTH; x++ )
		{
			int bufferIndex = ( y * FONT_IMAGE_WIDTH ) + x;
			int dataIndex = bufferIndex / 32;
			int dataShift = 31 - ( bufferIndex % 32 );

			// Convert 1bpp to an 8-bit array for easy data access
			if( ( debugFontData[dataIndex] >> dataShift ) & 0x01 )
				m_pDebugFontBuffer[( y * FONT_IMAGE_WIDTH ) + x] = 0; // not ARGB just 0 (no pixel)
			else
				m_pDebugFontBuffer[( y * FONT_IMAGE_WIDTH ) + x] = 1; // not ARGB just 1 (a pixel)
		}
	}
}

int PlayBuffer::DrawDebugCharacter( Point2f pos, char c, Pixel pix )
{
	// Limited character set in the font (0x30-0x5F) so includes translation of useful chars outside that range
	switch( c )
	{
		case 0x2C: c = 0x5E; break; // Map full stop to comma (nearly the same!)
		case 0x2D: c = 0x3B; break; // Map minus to semi-colon (rarely used)
		case 0x28: c = 0x5B; break; // Map brackets to square brackets
		case 0x29: c = 0x5D; break; // Map brackets to square brackets
		case 0x2E: c = 0x5E; break; // Map full stop to carot (never used)
	}

	if( c < 0x30 || c > 0x5F )
		return FONT_CHAR_WIDTH;

	int sourceX = ( ( c - 0x30 ) % 16 ) * FONT_CHAR_WIDTH;
	int sourceY = ( ( c - 0x30 ) / 16 ) * FONT_CHAR_HEIGHT;

	// Loop over the bounding box of the glyph
	for( int x = 0; x < FONT_CHAR_WIDTH; x++ )
	{
		for( int y = 0; y < FONT_CHAR_HEIGHT; y++ )
		{
			if( m_pDebugFontBuffer[( ( sourceY + y ) * FONT_IMAGE_WIDTH ) + ( sourceX + x )] > 0 )
				DrawPixel( { pos.x + x, pos.y + y }, pix );
		}
	}

	return FONT_CHAR_WIDTH;
}

int PlayBuffer::DrawDebugString( Point2f pos, const std::string& s, Pixel pix, bool centred )
{
	if( m_pDebugFontBuffer == nullptr )
		DecompressDubugFont();

	if( centred )
		pos.x -= GetDebugStringWidth( s ) / 2;

	pos.y -= 6; // half the height of the debug font

	for( char c : s )
		pos.x += DrawDebugCharacter( pos, static_cast<char>( toupper( c ) ), pix ) + 1;

	// Return horizontal position at the end of the string so strings can be concatenated easily
	return static_cast<int>( pos.x );
}

int PlayBuffer::GetDebugStringWidth( const std::string& s )
{
	return static_cast<int>( s.length() ) * ( FONT_CHAR_WIDTH + 1 );
}

//********************************************************************************************************************************
// Timing bar functions
//********************************************************************************************************************************

LARGE_INTEGER PlayBuffer::EndTimingSegment()
{
	int size = static_cast<int>( m_vTimings.size() );

	LARGE_INTEGER now, freq;
	QueryPerformanceCounter( &now );
	QueryPerformanceFrequency( &freq );

	if( size > 0 )
	{
		m_vTimings[size - 1].end = now.QuadPart;
		m_vTimings[size - 1].millisecs = static_cast<float>( m_vTimings[size - 1].end - m_vTimings[size - 1].begin );
		m_vTimings[size - 1].millisecs = static_cast<float>( ( m_vTimings[size - 1].millisecs * 1000.0f ) / freq.QuadPart );
	}

	return now;
}

int PlayBuffer::SetTimingBarColour( PlayBuffer::Pixel pix )
{
	TimingSegment newData;
	newData.pix = pix;
	newData.begin = EndTimingSegment().QuadPart;

	m_vTimings.push_back( newData );

	return static_cast<int>( m_vTimings.size() );
};

void PlayBuffer::DrawTimingBar( Point2f pos, Point2f size )
{
	EndTimingSegment();

	int startPixel{ 0 };
	int endPixel{ 0 };
	for( const TimingSegment& t : m_vTimings )
	{
		endPixel += static_cast<int>( ( size.width * t.millisecs ) / 16.667f );
		DrawRect( { pos.x + startPixel, pos.y }, { pos.x + endPixel, pos.y + size.height }, t.pix, true );
		startPixel = endPixel;
	}

	DrawRect( { pos.x, pos.y }, { pos.x + size.width, pos.y + size.height }, PlayBuffer::pixBlack, false );
	DrawRect( { pos.x - 1, pos.y - 1 }, { pos.x + size.width + 1 , pos.y + size.height +1  }, PlayBuffer::pixWhite, false );

	// Reset the timer - shouldn't reduce the allocated vector size
	m_vTimings.clear();
}

float PlayBuffer::GetTimingSegmentDuration( int id ) const
{
	PB_ASSERT_MSG( id < static_cast<int>(m_vTimings.size()), "Invalid id for timing data." );
	return m_vTimings[id].millisecs;
}

//********************************************************************************************************************************
// Loading functions
//********************************************************************************************************************************

int PlayBuffer::ReadPNGImage( std::string& fileAndPath, int& width, int& height )
{
	// Convert filename from single to wide string for GDI+ compatibility
	size_t newsize = strlen( fileAndPath.c_str() ) + 1;
	wchar_t* wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s( &convertedChars, wcstring, newsize, fileAndPath.c_str(), _TRUNCATE );

	HBITMAP hBitmap = NULL;

	// Use GDI+ to load file into Bitmap structure
	Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromFile( wcstring, false );
	int status = bitmap->GetLastStatus();

	if( status != Gdiplus::Ok )
		return -status;

	bitmap->GetHBITMAP( Gdiplus::Color( 255, 255, 255 ), &hBitmap );

	width = bitmap->GetWidth();
	height = bitmap->GetHeight();

	delete bitmap;
	delete[] wcstring;

	return 1;
}


int PlayBuffer::LoadPNGImage( std::string& fileAndPath, int& width, int& height, uint32_t*& destImage )
{
	// Convert filename from single to wide string for GDI+ compatibility
	size_t newsize = strlen( fileAndPath.c_str() ) + 1;
	wchar_t* wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s( &convertedChars, wcstring, newsize, fileAndPath.c_str(), _TRUNCATE );

	HBITMAP hBitmap = NULL;

	// Use GDI+ to load file into Bitmap structure
	Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromFile( wcstring, false );
	int status = bitmap->GetLastStatus();

	if( status != Gdiplus::Ok )
		return -status;

	bitmap->GetHBITMAP( Gdiplus::Color( 255, 255, 255 ), &hBitmap );

	// Create BitmapData structure to pull the data into
	Gdiplus::BitmapData* bitmapData = new Gdiplus::BitmapData;

	width = bitmap->GetWidth();
	height = bitmap->GetHeight();

	// Lock the bitmap in advance of reading its data
	Gdiplus::Rect rect( 0, 0, width, height );
	bitmap->LockBits( &rect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, bitmapData );

	// Get a pointer to the actual bit data
	uint32_t* sourcePixels = static_cast<uint32_t*>( bitmapData->Scan0 );

	destImage = new uint32_t[width * height];
	memset( destImage, 0, sizeof( uint32_t ) * width * height );

	uint32_t* destPixels = destImage;

	// Copy the data across
	for( int b = 0; b < width * height; b++ )
		*destPixels++ = *sourcePixels++;

	//Unlock the bitmap
	bitmap->UnlockBits( bitmapData );

	delete bitmap;
	delete bitmapData;
	delete[] wcstring;

	return 1;
}

//********************************************************************************************************************************
// Miscellaneous functions
//********************************************************************************************************************************


void AssertFailMessage( const char* message, const char* file, long line )
{
	// file - the file in which the assertion failed ( __FILE__ )
	// line - the line of code where the assertion failed ( __LINE__ )
	std::filesystem::path p = file;
	std::string s = p.filename().string() + " : LINE " + std::to_string( line );
	s += "\n" + std::string( message );
	int wide_count = MultiByteToWideChar( CP_UTF8, 0, s.c_str(), -1, NULL, 0 );
	wchar_t* wide = new wchar_t[wide_count];
	MultiByteToWideChar( CP_UTF8, 0, s.c_str(), -1, wide, wide_count );
	MessageBox( NULL, wide, (LPCWSTR)L"Assertion Failure", MB_ICONWARNING );
	delete[] wide;
}

void DebugOutput( const char* s )
{
	OutputDebugStringA( s );
}

void DebugOutput( std::string s )
{
	OutputDebugStringA( s.c_str() );
}

void TracePrintf( const char* file, int line, const char* fmt, ... )
{
	constexpr size_t kMaxBufferSize = 512u;
	char buffer[kMaxBufferSize];

	va_list args;
	va_start( args, fmt );
	// format should be double click-able in VS 
	int len = sprintf_s( buffer, kMaxBufferSize, "%s(%d): ", file, line );
	vsprintf_s( buffer + len, kMaxBufferSize - len, fmt, args );
	DebugOutput( buffer );
	va_end( args );
}





//*******************************************************************
// PLAY END: PlayBuffer.cpp
//*******************************************************************


//*******************************************************************
// PLAY BEGIN: PlayBlitter.cpp
//*******************************************************************

//********************************************************************************************************************************
//* Copyright 2020 Sumo-Digital Limited
//********************************************************************************************************************************
// File:		PlayBlitter.cpp
// Created:		March 2020 - Sumo Academy
// Description:	A simple image manager for handling spites/backgrounds with PlayBuffer
// Platform:	Independent
// Notes:		Uses PNG format. The end of the filename indicates the number of frames e.g. "bat_4.png" or "tiles_10x10.png"
//********************************************************************************************************************************




PlayBlitter* PlayBlitter::s_pInstance = nullptr;

//********************************************************************************************************************************
// Constructor / Destructor (Private)
//********************************************************************************************************************************

PlayBlitter::PlayBlitter( const char* path )
{
	// Iterate through the directory
	PB_ASSERT_MSG( std::filesystem::exists( path ), "PlayBlitter: Drectory provided does not exist." );

	for( const auto& p : std::filesystem::directory_iterator( path ) )
	{
		// Switch everything to uppercase to avoid need to check case each time
		std::string filename = p.path().string();
		for( char& c : filename ) c = static_cast<char>( toupper( c ) );

		// Only attempt to load PNG files
		if( filename.find( ".PNG" ) != std::string::npos )
		{
			std::ifstream png_infile;
			png_infile.open( filename, std::ios::binary ); // Don't do this as part of the constructor or we lose 16 bytes!

			// If the PNG was opened okay
			if( png_infile )
			{
				int spriteId = LoadSpriteSheet( p.path().parent_path().string() + "\\", p.path().stem().string() );

				// Now we check for .inf file for each sprite and load origins
				int originX = 0, originY = 0;

				std::string info_filename = filename.replace( filename.find( ".PNG" ), 4, ".INF" );

				if( std::filesystem::exists( info_filename ) )
				{
					std::ifstream info_infile;
					info_infile.open( info_filename, std::ios::in );

					PB_ASSERT_MSG( info_infile.is_open(), std::string( "Unable to load existing .inf file: " + info_filename ).c_str() );
					if( info_infile.is_open() )
					{
						std::string type;
						info_infile >> type;
						info_infile >> originX;
						info_infile >> originY;
					}

					info_infile.close();
				}

				SetSpriteOrigin( spriteId, { originX, originY } );
			}

			png_infile.close();
		}
	}
}

PlayBlitter::~PlayBlitter()
{
	for( Sprite& s : vSpriteData )
	{
		if( s.pCanvasBuffer )
			delete[] s.pCanvasBuffer;

		if( s.pPreMultAlpha )
			delete[] s.pPreMultAlpha;
	}

	for( uint32_t*& pBgBuffer : vBackgroundData )
	{
		delete[] pBgBuffer;
	}
}



//********************************************************************************************************************************
// Instance functions
//********************************************************************************************************************************

PlayBlitter& PlayBlitter::Instance()
{
	PB_ASSERT_MSG( s_pInstance, "Trying to use PlayCollider without initialising it!" );
	return *s_pInstance;
}

PlayBlitter& PlayBlitter::Instance( const char* path )
{
	PB_ASSERT_MSG( !s_pInstance, "Trying to create multiple instances of singleton class!" );
	s_pInstance = new PlayBlitter( path );
	return *s_pInstance;
}

void PlayBlitter::Destroy()
{
	PB_ASSERT_MSG( s_pInstance, "Trying to use destroy PlayBuffer which hasn't been instanced!" );
	delete s_pInstance;
	s_pInstance = nullptr;
}

//********************************************************************************************************************************
// Loading functions
//********************************************************************************************************************************

int PlayBlitter::LoadSpriteSheet( const std::string& path, const std::string& filename )
{
	Sprite s;
	s.id = m_nTotalSprites++;
	s.name = filename;
	s.originX = s.originY = 0;
	s.hCount = s.vCount = 1; // default to a single-framed sprite

	// Switch everything to uppercase to avoid need to check case each time
	for( char& c : s.name ) c = static_cast<char>( toupper( c ) );

	// Look for the final number in the filename to pull out the number of frames across the width
	size_t frameWidthEnd = s.name.find_last_of( "0123456789" );
	size_t frameWidthStart = s.name.find_last_not_of( "0123456789" );

	if( frameWidthEnd == s.name.length() - 1 )
	{
		// Grab the number of frames
		std::string widthString = s.name.substr( frameWidthStart + 1, frameWidthEnd - frameWidthStart );

		// Make sure the number is valid 
		size_t num = widthString.find_first_of( "0123456789" );
		PB_ASSERT_MSG( num == 0, std::string( "Incorrectly named sprite: " + filename ).c_str() );

		s.hCount = stoi( widthString );

		if( s.name[frameWidthStart] == 'X' )
		{
			//Two dimensional sprite sheet so the width was actually the height: copy it over and work out the real width
			s.vCount = s.hCount;

			// Cut off the last number we just found plus an "x", then check for another number indicating a frame height (optional)
			std::string truncated = s.name.substr( 0, frameWidthStart );
			frameWidthEnd = truncated.find_last_of( "0123456789" );
			frameWidthStart = truncated.find_last_not_of( "0123456789" );

			if( frameWidthEnd == truncated.length() - 1 && frameWidthStart != std::string::npos )
			{
				// Grab the number of images in the height
				widthString = truncated.substr( frameWidthStart + 1, frameWidthEnd - frameWidthStart );

				// Make sure the number is valid
				num = widthString.find_first_of( "0123456789" );
				PB_ASSERT_MSG( num == 0, std::string( "Incorrectly named sprite: " + filename ).c_str() );

				s.hCount = stoi( widthString );
			}
			else
			{
				PB_ASSERT_MSG( false, std::string( "Incorrectly named sprite: " + filename ).c_str() );
			}
		}
		else
		{
			s.vCount = 1;
		}
	}

	s.totalCount = s.hCount * s.vCount;

	std::string fileAndPath( path + s.name + ".PNG" );
	PlayBuffer::LoadPNGImage( fileAndPath, s.canvasWidth, s.canvasHeight, s.pCanvasBuffer ); // Allocates memory as we don't know the size
	s.width = s.canvasWidth / s.hCount;
	s.height = s.canvasHeight / s.vCount;

	// Create a separate buffer with the pre-multiplyied alpha
	s.pPreMultAlpha = new uint32_t[static_cast<size_t>( s.canvasWidth ) * s.canvasHeight];
	memset( s.pPreMultAlpha, 0, sizeof( uint32_t ) * s.canvasWidth * s.canvasHeight );
	PreMultiplyAlpha( s.pCanvasBuffer, s.pPreMultAlpha, s.canvasWidth, s.canvasHeight, s.width, 1.0f, 0x00FFFFFF );

	// Add the sprite to our vector
	vSpriteData.push_back( s );

	return s.id;
}

int PlayBlitter::LoadBackground( const char* fileAndPath )
{
	int imageWidth, imageHeight;
	uint32_t* pLoadBuffer, * pLoadBufferIt, * pBackgroundBufferIt;

	uint32_t* pBackgroundBuffer = new uint32_t[static_cast<size_t>( m_displayBufferWidth ) * m_displayBufferHeight];
	PB_ASSERT( pBackgroundBuffer );

	std::string pngFile( fileAndPath );
	PB_ASSERT_MSG( std::filesystem::exists( fileAndPath ), "The background png does not exist at the given location." );
	PlayBuffer::LoadPNGImage( pngFile, imageWidth, imageHeight, pLoadBuffer ); // Allocates memory in function as we don't know the size

	pLoadBufferIt = pLoadBuffer;
	pBackgroundBufferIt = pBackgroundBuffer;

	//Copy the image to our background buffer clipping where necessary
	for( int h = 0; h < std::min( imageHeight, m_displayBufferHeight ); h++ )
	{
		for( int w = 0; w < std::min( imageWidth, m_displayBufferWidth ); w++ )
		{
			*pBackgroundBufferIt++ = *pLoadBufferIt++;
		}

		// Skip pixels if we're clipping
		pBackgroundBufferIt += std::max( m_displayBufferWidth - imageWidth, 0 );
		pLoadBufferIt += std::max( imageWidth - m_displayBufferWidth, 0 );
	}

	// Free up the loading buffer
	delete pLoadBuffer;

	vBackgroundData.push_back( pBackgroundBuffer );

	return static_cast<int>(vBackgroundData.size()) - 1;
}


//********************************************************************************************************************************
// Sprite Getters and Setters
//********************************************************************************************************************************
int PlayBlitter::GetSpriteId( const char* name ) const
{
	std::string tofind( name );
	for( char& c : tofind ) c = static_cast<char>( toupper( c ) );

	for( const Sprite& s : vSpriteData )
	{
		if( s.name.find( tofind ) != std::string::npos )
			return s.id;
	}
	return -1;
}

const std::string& PlayBlitter::GetSpriteName( int spriteId )
{
	PB_ASSERT_MSG( spriteId >= 0 && spriteId < m_nTotalSprites, "Trying to get name of invalid sprite id" );
	return vSpriteData[spriteId].name;
}

Vector2f PlayBlitter::GetSpriteSize( int spriteId ) const
{
	PB_ASSERT_MSG( spriteId >= 0 && spriteId < m_nTotalSprites, "Trying to get width of invalid sprite id" );
	return { vSpriteData[spriteId].width, vSpriteData[spriteId].height };
}

int PlayBlitter::GetSpriteFrames( int spriteId ) const
{
	PB_ASSERT_MSG( spriteId >= 0 && spriteId < m_nTotalSprites, "Trying to get frames of invalid sprite id" );
	return vSpriteData[spriteId].totalCount;
}

Vector2f PlayBlitter::GetSpriteOrigin( int spriteId ) const
{
	PB_ASSERT_MSG( spriteId >= 0 && spriteId < m_nTotalSprites, "Trying to get origin with invalid sprite id" );
	return { vSpriteData[spriteId].originX, vSpriteData[spriteId].originY };
}

void PlayBlitter::SetSpriteOrigin( int spriteId, Vector2f newOrigin, bool relative )
{
	PB_ASSERT_MSG( spriteId >= 0 && spriteId < m_nTotalSprites, "Trying to set origin with invalid sprite id" );
	if( relative )
	{
		vSpriteData[spriteId].originX += static_cast<int>( newOrigin.x );
		vSpriteData[spriteId].originY += static_cast<int>( newOrigin.y );
	}
	else
	{
		vSpriteData[spriteId].originX = static_cast<int>( newOrigin.x );
		vSpriteData[spriteId].originY = static_cast<int>( newOrigin.y );
	}
}

void PlayBlitter::CentreSpriteOrigin( int spriteId )
{
	SetSpriteOrigin( spriteId, GetSpriteSize( spriteId ) / 2 );
}

void PlayBlitter::CentreAllSpriteOrigins( void )
{
	for( Sprite& s : vSpriteData )
		CentreSpriteOrigin( s.id );
}

void PlayBlitter::SetSpriteOrigins( const char* rootName, Vector2f newOrigin, bool relative )
{
	std::string tofind( rootName );
	for( char& c : tofind ) c = static_cast<char>( toupper( c ) );

	for( Sprite& s : vSpriteData )
	{
		if( s.name.find( tofind ) != std::string::npos )
		{
			if( relative )
			{
				s.originX += static_cast<int>( newOrigin.x );
				s.originY += static_cast<int>( newOrigin.y );
			}
			else
			{
				s.originX = static_cast<int>( newOrigin.x );
				s.originY = static_cast<int>( newOrigin.y );
			}
		}
	}
}

//********************************************************************************************************************************
// Drawing functions
//********************************************************************************************************************************

void PlayBlitter::DrawBackground( int backgroundId )
{
	PB_ASSERT_MSG( m_displayBuffer, "Trying to draw background without initialising display!" );
	PB_ASSERT_MSG( static_cast<int>(vBackgroundData.size()) > backgroundId, "Background image out of range!" );
	// Takes about 1ms for 720p screen on i7-8550U
	memcpy( m_displayBuffer, vBackgroundData[backgroundId], sizeof( uint32_t ) * m_displayBufferWidth * m_displayBufferHeight );
}

void PlayBlitter::ColourSprite( int spriteId, int r, int g, int b )
{
	PB_ASSERT_MSG( spriteId >= 0 && spriteId < m_nTotalSprites, "Trying to colour invalid sprite id" );

	Sprite& s = vSpriteData[spriteId];
	uint32_t col = ( ( r & 0xFF ) << 16 ) | ( ( g & 0xFF ) << 8 ) | ( b & 0xFF );

	PreMultiplyAlpha( s.pCanvasBuffer, s.pPreMultAlpha, s.canvasWidth, s.canvasHeight, s.width, 1.0f, col );
}

int PlayBlitter::DrawString( int fontId, Point2f pos, std::string text ) const
{
	PB_ASSERT_MSG( fontId >= 0 && fontId < m_nTotalSprites, "Trying to use invalid sprite id for font" );

	int width = 0;

	for( char c : text )
	{
		Draw( fontId, { pos.x + width, pos.y }, c - 32 );
		width += GetFontCharWidth( fontId, c );
	}
	return width;
}

int PlayBlitter::DrawStringCentred( int fontId, Point2f pos, std::string text ) const
{
	int totalWidth = 0;

	for( char c : text )
		totalWidth += PlayBlitter::Instance().GetFontCharWidth( fontId, c );

	pos.x -= totalWidth / 2;

	DrawString( fontId, pos, text );
	return totalWidth;
}

int PlayBlitter::DrawChar( int fontId, Point2f pos, char c ) const
{
	PB_ASSERT_MSG( fontId >= 0 && fontId < m_nTotalSprites, "Trying to use invalid sprite id for font" );
	BlitSprite( fontId, static_cast<int>( pos.x ), static_cast<int>( pos.y ), c - 32 );
	return GetFontCharWidth( fontId, c );
}

int PlayBlitter::DrawCharRotated( int fontId, Point2f pos, float angle, float scale, char c ) const
{
	PB_ASSERT_MSG( fontId >= 0 && fontId < m_nTotalSprites, "Trying to use invalid sprite id for font" );
	RotateScaleSprite( fontId, static_cast<int>( pos.x ), static_cast<int>( pos.y ), c - 32, angle, scale );
	return GetFontCharWidth( fontId, c );
}

int PlayBlitter::GetFontCharWidth( int fontId, char c ) const
{
	PB_ASSERT_MSG( fontId >= 0 && fontId < m_nTotalSprites, "Trying to use invalid sprite id for font" );
	return *( vSpriteData[fontId].pCanvasBuffer + ( c - 32 ) ) & 0xFF;
}

//********************************************************************************************************************************
// Function:	SpriteCollide: function that checks by pixel if two sprites collide
// Parameters:	s1Xpos, s1Ypos, s2Xpos, s2Ypos = the origin of rotation for both sprites.
//				s1Id, s2Id = the ids of both sprites
//				s1angle, s2angle = the angle of rotation for both sprites, clockwise. 0 = unrotated.
//				s1Pixelcoll, s2Pixelcoll = the top left and bottom right co-ordinates defining the collision rectangle of both sprites
//				
// Returns: true if a single pixel or more overlap between the two sprites and false if not.
// Notes:	rounding errors may cause it not to be pixel perfect.	
//********************************************************************************************************************************
bool PlayBlitter::SpriteCollide( int id_1, Point2f pos_1, int frame_1, float angle_1, int s1PixelColl[4], int id_2, Point2f pos_2, int frame_2, float angle_2, int s2PixelColl[4] ) const
{
	//transform all co-ordinates of sprite2 into the frame of sprite 1.

	//To do this we'll set up three co-ordinate systems.
	//X,Y are screen, u,v are sprite 1 and a,b are sprite 2.
	//The input is position of centre of rotation in screen and position of centre of rotation in sprite1 and sprite2.

	//We define the origin of the sprite1 as the beginning of its buffer.
	//First I calculate the offset vector for sprite one in the screen.
	//in sprite offsetu = rotOffX, offsetv = rotOffY.
	//When I refer to origin of the sprite I mean the 0,0 pixel.


	//Next define corners of sprite
	const Sprite& s1 = vSpriteData[id_1];
	const Sprite& s2 = vSpriteData[id_2];

	//Convert collision box locations from relative to sprite origin to relative to sprite top left. Hence TL.
	int s1PixelCollTL[4]{ 0 };
	int s2PixelCollTL[4]{ 0 };

	for( int i{ 0 }; i < 2; i++ )
	{
		s1PixelCollTL[2 * i] = s1PixelColl[2 * i] + s1.originX;
		s1PixelCollTL[2 * i + 1] = s1PixelColl[2 * i + 1] + s1.originY;
		s2PixelCollTL[2 * i] = s2PixelColl[2 * i] + s2.originX;
		s2PixelCollTL[2 * i + 1] = s2PixelColl[2 * i + 1] + s2.originY;
	}

	//in screen
	float cosAngle1 = cos( angle_1 );
	float sinAngle1 = sin( angle_1 );
	float offsetSprite1X = cosAngle1 * s1.originX - sinAngle1 * s1.originY;
	float offsetSprite1Y = cosAngle1 * s1.originY + sinAngle1 * s1.originX;

	//Next I calculate the sprite origin in the screen.
	float originSprite1X = pos_1.x - offsetSprite1X;
	float originSprite1Y = pos_1.y - offsetSprite1Y;

	//Repeat for other sprite.
	float cosAngle2 = cos( angle_2 );
	float sinAngle2 = sin( angle_2 );
	float offsetSprite2X = cosAngle2 * s2.originX - sinAngle2 * s2.originY;
	float offsetSprite2Y = cosAngle2 * s2.originY + sinAngle2 * s2.originX;

	//Next I calculate the sprite origin in the screen.
	float originSprite2X = pos_2.x - offsetSprite2X;
	float originSprite2Y = pos_2.y - offsetSprite2Y;

	//calculate the difference between two sprite origins in screen
	float originDiffX = originSprite2X - originSprite1X;
	float originDiffY = originSprite2Y - originSprite1Y;

	//calculation of the difference between two sprite origins in frame of sprite 1.
	float originDiffu = originDiffX * cosAngle1 + originDiffY * sinAngle1;
	float originDiffv = originDiffY * cosAngle1 - originDiffX * sinAngle1;

	int s2Width = s2.width;
	int s2Height = s2.height;
	int s1Width = s1.width;

	float cosAngleDiff = cos( angle_2 - angle_1 );
	float sinAngleDiff = sin( angle_2 - angle_1 );
	//top left, top right, bottom right, bottom left.
	float s2Cu[4]
	{
		0,
		s2Width * cosAngleDiff,
		s2Width * cosAngleDiff - s2Height * sinAngleDiff,
		-s2Height * sinAngleDiff
	};

	float s2Cv[4]
	{
		0,
		s2Width * sinAngleDiff,
		s2Width * sinAngleDiff + s2Height * cosAngleDiff,
		s2Height * cosAngleDiff
	};


	float minCu{ std::numeric_limits<float>::infinity() };
	float minCv{ std::numeric_limits<float>::infinity() };
	float maxCu{ -std::numeric_limits<float>::infinity() };
	float maxCv{ -std::numeric_limits<float>::infinity() };

	//calculate the extremes of the rotated sprite2.
	for( int i = 0; i < 4; i++ )
	{
		minCu = std::min( s2Cu[i], minCu );
		minCv = std::min( s2Cv[i], minCv );
		maxCu = std::max( s2Cu[i], maxCu );
		maxCv = std::max( s2Cv[i], maxCv );
	}

	//calculate the maximum and minimum positions in the sprite1 frame of the sprite2 corners.
	float maxu = (originDiffu)+( maxCu );
	float maxv = (originDiffv)+( maxCv );
	float minu = (originDiffu)+( minCu );
	float minv = (originDiffv)+( minCv );

	if( minu > s1PixelCollTL[2] || minv > s1PixelCollTL[3] || maxu < s1PixelCollTL[0] || maxv < s1PixelCollTL[1] )
	{
		return false;
	}
	else
	{
		//wrap both frame indexes just in case.
		frame_1 = frame_1 % s1.totalCount;
		frame_2 = frame_2 % s2.totalCount;


		//clip so we loop through sprite 1.
		//Restrict the range we look in for pixel based collisions.
		minv = ( minv < s1PixelCollTL[1] ) ? static_cast<float>( s1PixelCollTL[1] ) : minv;
		maxv = ( maxv > s1PixelCollTL[3] ) ? static_cast<float>( s1PixelCollTL[3] ) : maxv;
		minu = ( minu < s1PixelCollTL[0] ) ? static_cast<float>( s1PixelCollTL[0] ) : minu;
		maxu = ( maxu > s1PixelCollTL[2] ) ? static_cast<float>( s1PixelCollTL[2] ) : maxu;


		//Set up the starting position in sprite 2 frame. We know the box corners in u, v relative to the sprite 2 origin but we need to get them in a,b.
		float minCa = ( minu - originDiffu ) * cosAngleDiff + ( minv - originDiffv ) * sinAngleDiff;
		float minCb = -( minu - originDiffu ) * sinAngleDiff + ( minv - originDiffv ) * cosAngleDiff;

		//rounding at this point
		int iminu = static_cast<int>( minu );
		int iminv = static_cast<int>( minv );
		int imaxu = static_cast<int>( maxu );
		int imaxv = static_cast<int>( maxv );

		float startinga = minCa;
		float startingb = minCb;

		float rowstarta = startinga;
		float rowstartb = startingb;

		//Set up starting and finishing pointers for both the sprite 1 buffer and sprite 2 buffer 
		//starting pointer for the sprite 1 buffer is the minu and minv.
		int sprite1Offset = s1Width * frame_1 + iminu + iminv * s1.canvasWidth;
		uint32_t* sprite1Src = s1.pCanvasBuffer + sprite1Offset;

		//The base pointer for the sprite2 will just be start of the correct frame in the canvas buffer.
		int sprite2Offset = s2Width * frame_2;
		uint32_t* sprite2Base = s2.pCanvasBuffer + sprite2Offset;
		//Define the number which we need to add to get down a row in sprite1.
		int sprite1ChangeRow = s1.canvasWidth - ( imaxu - iminu );


		//Start of double for loop.
		//Go through the overlapping region (warning may go out of the buffer of sprite 2.)
		for( int v{ iminv }; v < imaxv; v++ )
		{

			//store a and b to be the start of the row.
			float a = rowstarta;
			float b = rowstartb;

			for( int u{ iminu }; u < imaxu; u++ )
			{

				//Edit this part to add a collision box.
				//If we are in sprite 2 then extract the look at the pixels.
				if( a >= s2PixelCollTL[0] && b >= s2PixelCollTL[1] && a < s2PixelCollTL[2] && b < s2PixelCollTL[3] )
				{
					int sprite2Pixel = static_cast<int>( a ) + static_cast<int>( b ) * s2.canvasWidth;
					uint32_t sprite2Src = *( sprite2Base + sprite2Pixel );

					//If both pixels at that position are opaque then there is a collision. 
					if( sprite2Src > 0x00FFFFFF && *sprite1Src > 0x00FFFFFF )
					{
						return true;
					}

				}
				//add change in for going along u. go along a row.
				a += cosAngleDiff;
				b += -sinAngleDiff;

				sprite1Src++;

			}
			//increment for row of sprite 1.
			sprite1Src += sprite1ChangeRow;

			//work out start of next row based on start of previous row. 
			rowstarta += sinAngleDiff;
			rowstartb += cosAngleDiff;
		}
	}
	return false;
}


//********************************************************************************************************************************
// Function:	BlitSprite - draws a sprite with and withough a global alpha multiply
// Parameters:	spriteId = the id of the sprite to draw
//				xpos, ypos = the position you want to draw the sprite
//				frameIndex = which frame of the animation to draw (wrapped)
// Notes:		Alpha multiply approach is relatively unoptimized
//********************************************************************************************************************************
void PlayBlitter::BlitSprite( int spriteId, int xpos, int ypos, int frameIndex, float alphaMultiply ) const
{
	PB_ASSERT_MSG( m_displayBuffer, "DisplayBuffer not initialised" );
	PB_ASSERT_MSG( spriteId >= 0 && spriteId < m_nTotalSprites, "Trying to draw invalid sprite id" );

	const Sprite& spr = vSpriteData[spriteId];

	// Nothing within the display buffer to draw
	if( ( xpos - spr.originX ) > m_displayBufferWidth || ( xpos - spr.originX ) + spr.width < 0 || ( ypos - spr.originY ) > m_displayBufferHeight || ( ypos - spr.originY ) + spr.width < 0 )
		return;

	// Work out if we need to clip to the display buffer (and by how much)
	int xClipStart = -( xpos - spr.originX );
	if( xClipStart < 0 ) { xClipStart = 0; }

	int xClipEnd = ( ( xpos - spr.originX ) + spr.width ) - m_displayBufferWidth;
	if( xClipEnd < 0 ) { xClipEnd = 0; }

	int yClipStart = -( ypos - spr.originY );
	if( yClipStart < 0 ) { yClipStart = 0; }

	int yClipEnd = ( ( ypos - spr.originY ) + spr.height ) - m_displayBufferHeight;
	if( yClipEnd < 0 ) { yClipEnd = 0; }

	// Set up the source and destination pointers based on clipping
	int destOffset = ( m_displayBufferWidth * ( ( ypos - spr.originY ) + yClipStart ) ) + ( ( xpos - spr.originX ) + xClipStart );
	uint32_t* destPixels = m_displayBuffer + destOffset;

	frameIndex = frameIndex % spr.totalCount;
	int imageX = frameIndex % spr.hCount;
	int imageY = frameIndex / spr.hCount;
	int pixelX = imageX * spr.width;
	int pixelY = imageY * spr.height;
	int frameOffset = pixelX + ( spr.canvasWidth * pixelY );

	int srcOffset = ( spr.canvasWidth * yClipStart ) + xClipStart;
	uint32_t* srcPixels = spr.pPreMultAlpha + frameOffset + srcOffset;

	// Work out in advance how much we need to add to src and dest to reach the next row 
	int destInc = m_displayBufferWidth - spr.width + xClipEnd + xClipStart;
	int srcInc = spr.canvasWidth - spr.width + xClipEnd + xClipStart;

	//Work out final pixel in destination.
	int destColOffset = ( m_displayBufferWidth * ( spr.height - yClipEnd - yClipStart - 1 ) ) + ( spr.width - xClipEnd - xClipStart );
	uint32_t* destColEnd = destPixels + destColOffset;

	//How many pixels per row in sprite.
	int endRow = spr.width - xClipEnd - xClipStart;

	if( alphaMultiply < 1.0f )
	{
		// *******************************************************************************************************************************************************
		// A basic (unoptimized) approach which separates the channels and performs a 'typical' alpha blending operation: (src * srcAlpha)+(dest * (1-srcAlpha))
		// Has the advantage that a global alpha multiplication can be easily added over the top, so we use this method when a global multiply is required
		// *******************************************************************************************************************************************************

		// Slightly more optimised iterations without the additions in the loop
		while( destPixels < destColEnd )
		{
			uint32_t* destRowEnd = destPixels + endRow;

			while( destPixels < destRowEnd )
			{
				uint32_t src = *srcPixels++;
				uint32_t dest = *destPixels;

				// If this isn't a fully transparent pixel 
				if( src < 0xFF000000 )
				{
					int srcAlpha = static_cast<int>( ( 0xFF - ( src >> 24 ) ) * alphaMultiply );
					int constAlpha = static_cast<int>( 255 * alphaMultiply );

					// Source pixels are already multiplied by srcAlpha so we just apply the constant alpha multiplier
					int destRed = constAlpha * ( ( src >> 16 ) & 0xFF );
					int destGreen = constAlpha * ( ( src >> 8 ) & 0xFF );
					int destBlue = constAlpha * ( src & 0xFF );

					int invSrcAlpha = 0xFF - srcAlpha;

					// Apply a standard Alpha blend [ src*srcAlpha + dest*(1-SrcAlpha) ]
					destRed += invSrcAlpha * ( ( dest >> 16 ) & 0xFF );
					destGreen += invSrcAlpha * ( ( dest >> 8 ) & 0xFF );
					destBlue += invSrcAlpha * ( dest & 0xFF );

					// Bring back to the range 0-255
					destRed >>= 8;
					destGreen >>= 8;
					destBlue >>= 8;

					// Put ARGB components back together again
					*destPixels++ = 0xFF000000 | ( destRed << 16 ) | ( destGreen << 8 ) | destBlue;
				}
				else
				{
					// If this is a fully transparent pixel then the low bits store how many there are in a row
					// This means we can skip to the next pixel which isn't fully transparent
					uint32_t skip = std::min( src & 0x00FFFFFF, (uint32_t)( destRowEnd - destPixels - 1 ) );
					srcPixels += skip;
					++destPixels += skip;
				}
			}
			// Increase buffers by pre-calculated amounts
			destPixels += destInc;
			srcPixels += srcInc;
		}

	}
	else
	{
		// *******************************************************************************************************************************************************
		// An optimized approach which uses pre-multiplied alpha, parallel channel multiplication and pixel skipping to achieve the same 'typical' alpha 
		// blending operation (src * srcAlpha)+(dest * (1-srcAlpha)). Not easy to apply a global alpha multiplication over the top, but used everywhere else.
		// *******************************************************************************************************************************************************

		// Slightly more optimised iterations without the additions in the loop
		while( destPixels < destColEnd )
		{
			uint32_t* destRowEnd = destPixels + endRow;

			while( destPixels < destRowEnd )
			{
				uint32_t src = *srcPixels++;
				uint32_t dest = *destPixels;

				// If this isn't a fully transparent pixel 
				if( src < 0xFF000000 )
				{
					// This performes the dest*(1-srcAlpha) calculation for all channels in parallel with minor accuracy loss in dest colour.
					// It does this by shifting all the destination channels down by 4 bits in order to "make room" for the later multiplication.
					// After shifting down, it masks out the bits which have shifted into the adjacent channel data.
					// This casues the RGB data to be rounded down to their nearest 16 producing a reduction in colour accuracy.
					// This is then multiplied by the inverse alpha (inversed in PreMultiplyAlpha), also divided by 16 (hence >> 8+8+8+4).
					// The multiplication brings our RGB values back up to their original bit ranges (albeit rounded to the nearest 16).
					// As the colour accuracy only affects the desination pixels behind semi-transparent source pixels and so isn't very obvious.
					dest = ( ( ( dest >> 4 ) & 0x000F0F0F ) * ( src >> 28 ) );
					// Add the (pre-multiplied Alpha) source to the destination and force alpha to opaque
					*destPixels++ = ( src + dest ) | 0xFF000000;
				}
				else
				{
					// If this is a fully transparent pixel then the low bits store how many there are in a row
					// This means we can skip to the next pixel which isn't fully transparent
					uint32_t skip = std::min( src & 0x00FFFFFF, (uint32_t)( destRowEnd - destPixels - 1 ) );
					srcPixels += skip;
					++destPixels += skip;
				}
			}
			// Increase buffers by pre-calculated amounts
			destPixels += destInc;
			srcPixels += srcInc;
		}

	}

	return;
}



//********************************************************************************************************************************
// Function:	RotateScaleSprite - draws a rotated and scaled sprite with global alpha multiply
// Parameters:	s = the sprite to draw
//				xpos, ypos = the position of the center of rotation.
//				frameIndex = which frame of the animation to draw (wrapped)
//				angle = rotation angle
//				scale = parameter to magnify the sprite.
//				rotOffX, rotOffY = offset of centre of rotation to the top left of the sprite
//				alpha = the fraction defining the amount of sprite and background that is draw. 255 = all sprite, 0 = all background.
// Notes:		Pre-calculates roughly where the sprite will be in the display buffer and only processes those pixels. 
//				Approx 15 times slower than not rotating.
//********************************************************************************************************************************
void PlayBlitter::RotateScaleSprite( int spriteId, int xpos, int ypos, int frameIndex, float angle, float scale, float alphaMultiply ) const
{
	PB_ASSERT_MSG( m_displayBuffer, "DisplayBuffer not initialised" );
	PB_ASSERT_MSG( spriteId >= 0 && spriteId < m_nTotalSprites, "Trying to draw invalid sprite id" );

	const Sprite& spr = vSpriteData[spriteId];

	frameIndex = frameIndex % spr.totalCount;
	int imageX = frameIndex % spr.hCount;
	int imageY = frameIndex / spr.hCount;
	int pixelX = imageX * spr.width;
	int pixelY = imageY * spr.height;
	int frameOffset = pixelX + ( spr.canvasWidth * pixelY );

	//pointers to start of source and destination buffers
	uint32_t* pSrcBase = spr.pPreMultAlpha + frameOffset;
	uint32_t* pDstBase = m_displayBuffer;

	//the centre of rotation in the sprite frame relative to the top corner
	float fRotCentreU = static_cast<float>( spr.originX );
	float fRotCentreV = static_cast<float>( spr.originY );

	//u/v are co-ordinates in the rotated sprite frame. x/y are screen buffer co-ordinates.
	//change in u/v for a unit change in x/y.
	float dUdX = static_cast<float>( cos( -angle ) ) * ( 1.0f / scale );
	float dVdX = static_cast<float>( sin( -angle ) ) * ( 1.0f / scale );
	float dUdY = -dVdX;
	float dVdY = dUdX;

	//Position in the sprite rotated frame with origin at the center of rotation of the sprite corners.
	float leftU = -fRotCentreU * scale;
	float rightU = ( spr.width + -fRotCentreU ) * scale;
	float topV = ( -fRotCentreV ) * scale;
	float bottomV = ( spr.height - fRotCentreV ) * scale;

	//Scale added in to cancel out the scale in dUdX.
	float boundingBoxCorners[4][2]
	{
		{ ( dUdX * leftU + dVdX * topV ) * scale,			( dUdY * leftU + dVdY * topV ) * scale		},	// Top left
		{ ( dUdX * leftU + dVdX * bottomV ) * scale,		( dUdY * leftU + dVdY * bottomV ) * scale		},	// Bottom left
		{ ( dUdX * rightU + dVdX * bottomV ) * scale,		( dUdY * rightU + dVdY * bottomV ) * scale	},	// Bottom right
		{ ( dUdX * rightU + dVdX * topV ) * scale,			( dUdY * rightU + dVdY * topV ) * scale,		},	// Top right
	};

	float minX = std::numeric_limits<float>::infinity();
	float minY = std::numeric_limits<float>::infinity();
	float maxX = -std::numeric_limits<float>::infinity();
	float maxY = -std::numeric_limits<float>::infinity();

	//calculate the extremes of the rotated corners.
	for( int i = 0; i < 4; i++ )
	{
		minX = std::min( minX, boundingBoxCorners[i][0] );
		maxX = std::max( maxX, boundingBoxCorners[i][0] );
		minY = std::min( minY, boundingBoxCorners[i][1] );
		maxY = std::max( maxY, boundingBoxCorners[i][1] );
	}

	//clip the starting and finishing positions.
	int startY = ypos + static_cast<int>( minY );
	if( startY < 0 ) { startY = 0; minY = static_cast<float>( -ypos ); }

	int endY = ypos + static_cast<int>( maxY );
	if( endY > m_displayBufferHeight ) { endY = m_displayBufferHeight; }

	int startX = xpos + static_cast<int>( minX );
	if( startX < 0 ) { startX = 0; minX = static_cast<float>( -xpos ); }

	int endX = xpos + static_cast<int>( maxX );
	if( endX > m_displayBufferWidth ) { endX = m_displayBufferWidth; }

	//rotate the basis so we get the edge of the bounding box in the sprite frame.
	float startingU = dUdX * minX + dUdY * minY + fRotCentreU;
	float startingV = dVdY * minY + dVdX * minX + fRotCentreV;

	float rowU = startingU;
	float rowV = startingV;

	uint32_t* destPixels = pDstBase + ( static_cast<size_t>( m_displayBufferWidth ) * startY ) + startX;
	int nextRow = m_displayBufferWidth - ( endX - startX );

	uint32_t* srcPixels = pSrcBase;

	//Start of double for loop. 
	for( int y = startY; y < endY; y++ )
	{
		float u = rowU;
		float v = rowV;

		for( int x = startX; x < endX; x++ )
		{
			//Check to see if u and v correspond to a valid pixel in sprite.
			if( u > 0 && v > 0 && u < spr.width && v < spr.height )
			{
				srcPixels = pSrcBase + static_cast<size_t>( u ) + ( static_cast<size_t>( v ) * spr.canvasWidth );
				uint32_t src = *srcPixels;

				if( src < 0xFF000000 )
				{
					int srcAlpha = static_cast<int>( ( 0xFF - ( src >> 24 ) ) * alphaMultiply );
					int constAlpha = static_cast<int>( 255 * alphaMultiply );

					// Source pixels are already multiplied by srcAlpha so we just apply the constant alpha multiplier
					int destRed = constAlpha * ( ( src >> 16 ) & 0xFF );
					int destGreen = constAlpha * ( ( src >> 8 ) & 0xFF );
					int destBlue = constAlpha * ( src & 0xFF );

					uint32_t dest = *destPixels;
					int invSrcAlpha = 0xFF - srcAlpha;

					// Apply a standard Alpha blend [ src*srcAlpha + dest*(1-SrcAlpha) ]
					destRed += invSrcAlpha * ( ( dest >> 16 ) & 0xFF );
					destGreen += invSrcAlpha * ( ( dest >> 8 ) & 0xFF );
					destBlue += invSrcAlpha * ( dest & 0xFF );

					// Bring back to the range 0-255
					destRed >>= 8;
					destGreen >>= 8;
					destBlue >>= 8;

					// Put ARGB components back together again
					*destPixels = 0xFF000000 | ( destRed << 16 ) | ( destGreen << 8 ) | destBlue;
				}
			}

			destPixels++;

			//change the position in the sprite frame for changing X in the display
			u += dUdX;
			v += dVdX;
		}

		//work out the change in the sprite frame for changing Y in the display
		rowU += dUdY;
		rowV += dVdY;
		//next row
		destPixels += nextRow;
	}
}

//********************************************************************************************************************************
// Function:	PreMultiplyAlpha - calculates the (src*srcAlpha) alpha blending calculation in advance as it doesn't change
// Parameters:	s = the sprite to precalculate data for
// Notes:		Also inverts the alpha ready for the (dest*(1-srcAlpha)) calculation and stores information in the new
//				buffer which provides the number of fully-transparent pixels in a row (so they can be skipped)
//********************************************************************************************************************************
void PlayBlitter::PreMultiplyAlpha( uint32_t* source, uint32_t* dest, int width, int height, int maxSkipWidth, float alphaMultiply = 1.0f, uint32_t colourMultiply = 0x00FFFFFF )
{
	uint32_t* pSourcePixels = source;
	uint32_t* pDestPixels = dest;

	// Iterate through all the pixels in the entire canvas
	for( int bh = 0; bh < height; bh++ )
	{
		for( int bw = 0; bw < width; bw++ )
		{
			uint32_t src = *pSourcePixels;

			// Separate the channels and calculate src*srcAlpha
			int srcAlpha = static_cast<int>( ( src >> 24 ) * alphaMultiply );

			int destRed = ( srcAlpha * ( ( src >> 16 ) & 0xFF ) ) >> 8;
			int destGreen = ( srcAlpha * ( ( src >> 8 ) & 0xFF ) ) >> 8;
			int destBlue = ( srcAlpha * ( src & 0xFF ) ) >> 8;

			destRed = ( destRed * ( ( colourMultiply >> 16 ) & 0xFF ) ) >> 8;
			destGreen = ( destGreen * ( ( colourMultiply >> 8 ) & 0xFF ) ) >> 8;
			destBlue = ( destBlue * ( colourMultiply & 0xFF ) ) >> 8;

			srcAlpha = 0xFF - srcAlpha; // invert the alpha ready to multiply with the destination pixels
			*pDestPixels = ( srcAlpha << 24 ) | ( destRed << 16 ) | ( destGreen << 8 ) | destBlue;

			if( srcAlpha == 0xFF ) // Completely transparent pixel
			{
				int repeats = 0;

				// We can only skip to the end of the row because the sprite frames are arranged on a continuous canvas
				int maxSkip = maxSkipWidth - ( bw % maxSkipWidth );

				for( int zw = 1; zw < maxSkip; zw++ )
				{
					if( *( pSourcePixels + zw ) >> 24 == 0x00 ) // Another transparent pixel
						repeats++;
					else
						break;
				}

				*pDestPixels = 0xFF000000 | repeats; // Doesn't matter what the colour was so we use it to store the skip value
			}

			pDestPixels++;
			pSourcePixels++;
		}
	}
}









//*******************************************************************
// PLAY END: PlayBlitter.cpp
//*******************************************************************


//*******************************************************************
// PLAY BEGIN: PlaySpeaker.cpp
//*******************************************************************

//********************************************************************************************************************************
//* Copyright 2020 Sumo-Digital Limited
//********************************************************************************************************************************
// File:		PlaySpeaker.cpp
// Created:		March 2020 - Sumo Academy
// Description:	Implementation of a very simple audio manager using the MCI
// Platform:	Windows
// Notes:		Uses MP3 format. Playback isn't always instentaneous and can 
//				trigger small frame glitches when StartSound is called
//********************************************************************************************************************************



// Instruct Visual Studio to link the multimedia library  
#pragma comment(lib, "winmm.lib")

PlaySpeaker* PlaySpeaker::s_pInstance = nullptr;

//********************************************************************************************************************************
// Constructor and destrutor (private)
//********************************************************************************************************************************
PlaySpeaker::PlaySpeaker( const char* path )
{
	PB_ASSERT_MSG( !s_pInstance, "PlaySpeaker is a singleton class: multiple instances not allowed!" );

	// Iterate through the directory
	for( auto& p : std::filesystem::directory_iterator( path ) )
	{
		// Switch everything to uppercase to avoid need to check case each time
		std::string filename = p.path().string();
		for( char& c : filename ) c = static_cast<char>( toupper( c ) );

		// Only load .mp3 files
		if( filename.find( ".MP3" ) != std::string::npos )
		{
			vSoundStrings.push_back( filename );
			std::string command = "open \"" + filename + "\" type mpegvideo alias " + filename;
			mciSendStringA( command.c_str(), NULL, 0, 0 );
		}
	}

	s_pInstance = this;
}

PlaySpeaker::~PlaySpeaker( void )
{
	for( std::string& s : vSoundStrings )
	{
		std::string command = "close " + s;
		mciSendStringA( command.c_str(), NULL, 0, 0 );
	}
}

//********************************************************************************************************************************
// Instance access functions
//********************************************************************************************************************************

PlaySpeaker& PlaySpeaker::Instance()
{
	PB_ASSERT_MSG( s_pInstance, "Trying to use PlaySpeaker without initialising it!" );

	return *s_pInstance;
}

PlaySpeaker& PlaySpeaker::Instance( const char* path )
{
	PB_ASSERT_MSG( !s_pInstance, "Trying to create multiple instances of singleton class!" );

	s_pInstance = new PlaySpeaker( path );

	return *s_pInstance;
}

void PlaySpeaker::Destroy()
{
	PB_ASSERT_MSG( s_pInstance, "Trying to use destroy PlaySpeaker which hasn't been instanced!" );

	delete s_pInstance;

	s_pInstance = nullptr;
}

//********************************************************************************************************************************
// Sound playing functions
//********************************************************************************************************************************
void PlaySpeaker::StartSound( const char* name, bool bLoop )
{
	std::string filename( name );
	for( char& c : filename ) c = static_cast<char>( toupper( c ) );

	// Iterate through the sound data 
	for( std::string& s : vSoundStrings )
	{
		if( s.find( filename ) != std::string::npos )
		{
			std::string command = "play " + s + " from 0";
			if( bLoop ) command += " repeat";
			mciSendStringA( command.c_str(), NULL, 0, 0 );
			return;
		}
	}
	PB_ASSERT_MSG( false, std::string( "Trying to play unknown sound effect: " + std::string( name ) ).c_str() );
}

void PlaySpeaker::StopSound( const char* name )
{
	std::string filename( name );
	for( char& c : filename ) c = static_cast<char>( toupper( c ) );

	// Iterate through the sound data 
	for( std::string& s : vSoundStrings )
	{
		if( s.find( filename ) != std::string::npos )
		{
			std::string command = "stop " + s;
			mciSendStringA( command.c_str(), NULL, 0, 0 );
			return;
		}
	}
	PB_ASSERT_MSG( false, std::string( "Trying to stop unknown sound effect: " + std::string( name ) ).c_str() );
}
//*******************************************************************
// PLAY END: PlaySpeaker.cpp
//*******************************************************************


//*******************************************************************
// PLAY BEGIN: PlayManager.cpp
//*******************************************************************

//********************************************************************************************************************************
// Copyright 2020 Sumo-Digital Limited
//********************************************************************************************************************************
// File:		PlayManager.cpp
// Created:		October 2020 - Sumo Academy
// Description:	A manager for providing simplified access to the PlayBuffer framework
// Platform:	Independent
// Notes:		The PlayManager is "opt in" as many will want to create their own GameObject
//********************************************************************************************************************************

//**************************************************************************************************
// GameObject Class Definition
//**************************************************************************************************

// Define this to opt in to the PlayManager
#ifdef PLAY_USING_GAMEOBJECT_MANAGER

// Constructor for the GameObject struct - kept as simple as possible
GameObject::GameObject( int type, Point2f newPos, int collisionRadius, int spriteId = 0 )
	: type( type ), pos( newPos ), radius( collisionRadius ), spriteId( spriteId )
{
	// Member variables are assigned default values in the class header
	static int uniqueId = 0;
	m_id = uniqueId++;
}

// The PlayManager is namespace rather than a class
namespace Play
{
	// A map is used internally to store all the GameObjects and their unique ids
	static std::map<int, GameObject&> objectMap;

	// Used instead of Null return values, PlayMangager operations performed on this GameObject should fail transparently
	static GameObject noObject{ -1,{ 0, 0 }, 0, -1 };

	// A set of default colour definitions
	Colour cBlack{ 0.0f, 0.0f, 0.0f };
	Colour cRed{ 100.0f, 0.0f, 0.0f };
	Colour cGreen{ 0.0f, 100.0f, 0.0f };
	Colour cBlue{ 0.0f, 0.0f, 100.0f };
	Colour cMagenta{ 100.0f, 0.0f, 100.0f };
	Colour cCyan{ 0.0f, 100.0f, 100.0f };
	Colour cYellow{ 100.0f, 100.0f, 0.0f };
	Colour cOrange{ 100.0f, 50.0f, 0.0f };
	Colour cWhite{ 100.0f, 100.0f, 100.0f };
	Colour cGrey{ 50.0f, 50.0f, 50.0f };

	//**************************************************************************************************
	// Manager creation and deletion
	//**************************************************************************************************

	void CreateManager( int displayWidth, int displayHeight, int displayScale )
	{
		PlayBuffer::Instance( displayWidth, displayHeight, displayScale );
		PlayBlitter::Instance( "Data\\Sprites\\" );
		PlayBlitter::Instance().SetDisplayBuffer( PlayBuffer::Instance().GetDisplayBuffer(), displayWidth, displayHeight );
		PlaySpeaker::Instance( "Data\\Audio\\" );
		// Seed the game's random number generator based on the time
		srand( (int)time( NULL ) );
	}

	// Destroys the managers closes the window
	void DestroyManager()
	{
		PlaySpeaker::Destroy();
		PlayBlitter::Destroy();
		PlayBuffer::Destroy();
		for( std::pair<const int, GameObject&>& p : objectMap )
			delete& p.second;
		objectMap.clear();
	}

	//**************************************************************************************************
	// PlayBuffer functions
	//**************************************************************************************************

	void ClearDrawingBuffer( Colour c )
	{
		int r = static_cast<int>( c.red * 2.55f );
		int g = static_cast<int>( c.green * 2.55f );
		int b = static_cast<int>( c.blue * 2.55f );
		PlayBuffer::Instance().ClearBuffer( { r, g, b } );
	}

	int LoadBackground( const char* pngFilename )
	{
		return PlayBlitter::Instance().LoadBackground( pngFilename );
	}

	void DrawBackground( int background )
	{
		PlayBlitter::Instance().DrawBackground( background );
	}

	void DrawDebugText( Point2D pos, const char* text, Colour c, bool centred )
	{
		PlayBuffer::Instance().DrawDebugString( pos, text, { c.red * 2.55f, c.green * 2.55f, c.blue * 2.55f }, centred );
	}

	void PresentDrawingBuffer()
	{
		PlayBuffer& pbuf = PlayBuffer::Instance();
		PlayBlitter& pblt = PlayBlitter::Instance();
		static bool debugInfo = false;

		if( KeyPressed( VK_F1 ) )
			debugInfo = !debugInfo;

		if( debugInfo )
		{
			int textX = 10;
			int textY = 10;
			std::string s = "PlayBuffer Version:" + std::string( PLAY_VERSION );
			pbuf.DrawDebugString( { textX - 1, textY - 1 }, s, PlayBuffer::pixBlack, false );
			pbuf.DrawDebugString( { textX + 1, textY + 1 }, s, PlayBuffer::pixBlack, false );
			pbuf.DrawDebugString( { textX + 1, textY - 1 }, s, PlayBuffer::pixBlack, false );
			pbuf.DrawDebugString( { textX - 1, textY + 1 }, s, PlayBuffer::pixBlack, false );
			pbuf.DrawDebugString( { textX, textY }, s, PlayBuffer::pixYellow, false );

			for( std::pair<const int, GameObject&>& i : objectMap )
			{
				GameObject& obj = i.second;
				int id = obj.spriteId;
				Vector2D size = pblt.GetSpriteSize( obj.spriteId );
				Vector2D origin = pblt.GetSpriteOrigin( id );

				// Corners of sprite drawing area
				Point2D p0 = obj.pos - origin;
				Point2D p2 = { obj.pos.x + size.width - origin.x, obj.pos.y + size.height - origin.y };
				Point2D p1 = { p2.x, p0.y };
				Point2D p3 = { p0.x, p2.y };

				DrawLine( p0, p1, cRed );
				DrawLine( p1, p2, cRed );
				DrawLine( p2, p3, cRed );
				DrawLine( p3, p0, cRed );

				DrawCircle( obj.pos, obj.radius, cBlue );

				DrawLine( { obj.pos.x - 20,  obj.pos.y - 20 }, { obj.pos.x + 20, obj.pos.y + 20 }, cWhite );
				DrawLine( { obj.pos.x + 20, obj.pos.y - 20 }, { obj.pos.x - 20, obj.pos.y + 20 }, cWhite );

				s = pblt.GetSpriteName( obj.spriteId ) + " f[" + std::to_string( obj.frame ) + "]";
				pbuf.DrawDebugString( { ( p0.x + p1.x ) / 2.0f, p0.y - 20 }, s, PlayBuffer::pixWhite, true );
			}
		}

		PlayBuffer::Instance().Present();
	}

	int HandleWindows( PLAY_WINARGS_IN, const char* windowName )
	{
		int wide_count = MultiByteToWideChar( CP_UTF8, 0, windowName, -1, NULL, 0 );
		wchar_t* wideWindowName = new wchar_t[wide_count];
		MultiByteToWideChar( CP_UTF8, 0, windowName, -1, wideWindowName, wide_count );
		int r = PlayBuffer::Instance().HandleWindows( PLAY_WINARGS_OUT, wideWindowName );
		delete wideWindowName;
		return r;
	}

	Point2D GetMousePos()
	{
		PlayBuffer& pbuf = PlayBuffer::Instance();
		return pbuf.GetMousePos();
	}

	//**************************************************************************************************
	// PlaySpeaker functions
	//**************************************************************************************************

	void PlayAudio( const char* fileName )
	{
		PlaySpeaker::Instance().StartSound( fileName, false );
	}

	void StartAudioLoop( const char* fileName )
	{
		PlaySpeaker::Instance().StartSound( fileName, true );
	}

	void StopAudioLoop( const char* fileName )
	{
		PlaySpeaker::Instance().StopSound( fileName );
	}

	//**************************************************************************************************
	// PlayBlitter functions
	//**************************************************************************************************


	int GetSpriteId( const char* spriteName )
	{
		return PlayBlitter::Instance().GetSpriteId( spriteName );
	}

	int GetSpriteHeight( const char* spriteName )
	{
		return static_cast<int>(PlayBlitter::Instance().GetSpriteSize( GetSpriteId( spriteName ) ).height);
	}

	int GetSpriteWidth( const char* spriteName )
	{
		return static_cast<int>( PlayBlitter::Instance().GetSpriteSize( GetSpriteId( spriteName ) ).width );
	}

	const char* GetSpriteName( int spriteId )
	{
		return PlayBlitter::Instance().GetSpriteName( spriteId ).c_str();
	}

	void ColourSprite( const char* spriteName, Colour c )
	{
		int spriteId = PlayBlitter::Instance().GetSpriteId( spriteName );
		PlayBlitter::Instance().ColourSprite( spriteId, static_cast<int>( c.red * 2.55f ), static_cast<int>( c.green * 2.55f), static_cast<int>( c.blue * 2.55f ) );
	}

	void CentreSpriteOrigin( const char* spriteName )
	{
		PlayBlitter& pblt = PlayBlitter::Instance();
		int spriteId = pblt.GetSpriteId( spriteName );
		pblt.SetSpriteOrigin( spriteId, pblt.GetSpriteSize( spriteId ) / 2, false );
	}

	void CentreMatchingSpriteOrigins( const char* rootName )
	{
		PlayBlitter& pblt = PlayBlitter::Instance();
		int spriteId = pblt.GetSpriteId( rootName ); // Finds the first matching sprite and assumes same dimensions
		pblt.SetSpriteOrigins( rootName, pblt.GetSpriteSize( spriteId ) / 2, false );
	}

	void CentreAllSpriteOrigins()
	{
		PlayBlitter& pblt = PlayBlitter::Instance();

		for( int i = 0; i < pblt.GetTotalLoadedSprites(); i++ )
			pblt.SetSpriteOrigin( i, pblt.GetSpriteSize( i ) / 2, false );
	}

	void MoveSpriteOrigin( const char* spriteName, int xoffset, int yoffset )
	{
		PlayBlitter& pblt = PlayBlitter::Instance();
		int spriteId = pblt.GetSpriteId( spriteName );
		pblt.SetSpriteOrigin( spriteId, { xoffset, yoffset }, true ); // relative option set
	}

	void MoveMatchingSpriteOrigins( const char* rootName, int xoffset, int yoffset )
	{
		PlayBlitter& pblt = PlayBlitter::Instance();
		pblt.SetSpriteOrigins( rootName, { xoffset, yoffset }, true ); // relative option set
	}

	void MoveAllSpriteOrigins()
	{
		PlayBlitter& pblt = PlayBlitter::Instance();

		for( int i = 0; i < pblt.GetTotalLoadedSprites(); i++ )
			pblt.SetSpriteOrigin( i, pblt.GetSpriteSize( i ) / 2, true );
	}

	void DrawSprite( const char* spriteName, Point2D pos, int frameIndex )
	{
		PlayBlitter::Instance().Draw( PlayBlitter::Instance().GetSpriteId( spriteName ), pos, frameIndex );
	}

	void DrawSprite( int spriteID, Point2D pos, int frameIndex )
	{
		PlayBlitter::Instance().Draw( spriteID, pos, frameIndex );
	}

	void DrawSpriteTransparent( const char* spriteName, Point2D pos, int frameIndex, float opacity )
	{
		PlayBlitter::Instance().DrawTransparent( PlayBlitter::Instance().GetSpriteId( spriteName ), pos, frameIndex, opacity );
	}

	void DrawSpriteTransparent( int spriteID, Point2D pos, int frameIndex, float opacity )
	{
		PlayBlitter::Instance().DrawTransparent( spriteID, pos, frameIndex, opacity );
	}

	void DrawSpriteRotated( const char* spriteName, Point2D pos, int frameIndex, float angle, float scale, float opacity )
	{
		PlayBlitter::Instance().DrawRotated( PlayBlitter::Instance().GetSpriteId( spriteName ), pos, frameIndex, angle, scale, opacity );
	}

	void DrawSpriteRotated( int spriteID, Point2D pos, int frameIndex, float angle, float scale, float opacity )
	{
		PlayBlitter::Instance().DrawRotated( spriteID, pos, frameIndex, angle, scale, opacity );
	}

	void DrawLine( Point2f start, Point2f end, Colour c )
	{
		return PlayBuffer::Instance().DrawLine( start, end, { c.red * 2.55f, c.green * 2.55f, c.blue * 2.55f }  );
	}

	void DrawCircle( Point2D pos, int radius, Colour c )
	{
		PlayBuffer::Instance().DrawCircle( pos, radius, { c.red * 2.55f, c.green * 2.55f, c.blue * 2.55f } );
	}

	void DrawSpriteLine( Point2f startPos, Point2f endPos, const char* penSprite, Colour c )
	{
		int spriteId = PlayBlitter::Instance().GetSpriteId( penSprite );
		ColourSprite( penSprite, c );

		//Draws a line in any angle
		int x1 = static_cast<int>( startPos.x );
		int y1 = static_cast<int>( startPos.y );
		int x2 = static_cast<int>( endPos.x );
		int y2 = static_cast<int>( endPos.y );

		//Implementation of Bresenham's Line Drawing Algorithm
		int dx = abs( x2 - x1 );
		int sx = 1;
		if( x2 < x1 ) { sx = -1; }

		int dy = -abs( y2 - y1 );
		int sy = 1;
		if( y2 < y1 ) { sy = -1; }
		
		int err = dx + dy;

		if( err == 0 ) return;

		while( true )
		{
			Play::DrawSprite( spriteId, { x1, y1 }, 0 );
			
			if( x1 == x2 && y1 == y2 )
				break;

			int e2 = 2 * err;
			if( e2 >= dy )
			{
				err += dy;
				x1 += sx;
			}
			if( e2 <= dx )
			{
				err += dx;
				y1 += sy;
			}
		}
	}

	void DrawCircleOctants( int spriteId, int x, int y, int ox, int oy )
	{
		//displaying all 8 coordinates of(x,y) residing in 8-octants
		Play::DrawSprite( spriteId, { x + ox, y + oy }, 0 );
		Play::DrawSprite( spriteId, { x - ox, y + oy }, 0 );
		Play::DrawSprite( spriteId, { x + ox, y - oy }, 0 );
		Play::DrawSprite( spriteId, { x - ox, y - oy }, 0 );
		Play::DrawSprite( spriteId, { x + oy, y + ox }, 0 );
		Play::DrawSprite( spriteId, { x - oy, y + ox }, 0 );
		Play::DrawSprite( spriteId, { x + oy, y - ox }, 0 );
		Play::DrawSprite( spriteId, { x - oy, y - ox }, 0 );
	}

	void DrawSpriteCircle( int x, int y, int radius, const char* penSprite, Colour c )
	{
		int spriteId = PlayBlitter::Instance().GetSpriteId( penSprite );
		ColourSprite( penSprite, c );

		int ox = 0, oy = radius;
		int d = 3 - 2 * radius;
		DrawCircleOctants( spriteId, x, y, ox, oy );

		while( oy >= ox )
		{
			ox++;
			if( d > 0 )
			{
				oy--;
				d = d + 4 * ( ox - oy ) + 10;
			}
			else
			{
				d = d + 4 * ox + 6;
			}
			DrawCircleOctants( spriteId, x, y, ox, oy );
		}
	};

	void DrawFontText( const char* fontId, std::string text, Point2D pos, Align justify )
	{
		int font = PlayBlitter::Instance().GetSpriteId( fontId );

		int totalWidth{ 0 };
		for( char c : text )
			totalWidth += PlayBlitter::Instance().GetFontCharWidth( font, c );

		switch( justify )
		{
			case CENTRE:
				pos.x -= totalWidth / 2;
				break;
			case RIGHT:
				pos.x -= totalWidth;
				break;
			default:
				break;
		}

		PlayBlitter::Instance().DrawString( font, pos, text );
	}

	//**************************************************************************************************
	// GameObject functions
	//**************************************************************************************************

	int CreateGameObject( int type, Point2f newPos, int collisionRadius, const char* spriteName )
	{
		int spriteId = PlayBlitter::Instance().GetSpriteId( spriteName );
		// Deletion is handled in DestroyGameObject()
		GameObject* pObj = new GameObject( type, newPos, collisionRadius, spriteId );
		int id = pObj->GetId();
		objectMap.insert( std::map<int, GameObject&>::value_type( id, *pObj ) );
		return id;
	}

	GameObject& GetGameObject( int ID )
	{
		if( objectMap.find( ID ) == objectMap.end() )
			return noObject;

		return objectMap.find( ID )->second;
	}

	GameObject& GetGameObjectByType( int type )
	{
		for( std::pair<const int, GameObject&>& i : objectMap )
		{
			if( i.second.type == type )
				return i.second;
		}

		return noObject;
	}

	std::vector<int> CollectGameObjectIDsByType( int type )
	{
		std::vector<int> vec;
		for( std::pair<const int, GameObject&>& i : objectMap )
		{
			if( i.second.type == type )
				vec.push_back( i.first );
		}
		return vec; // Returning a copy of the vector
	}

	std::vector<int> CollectAllGameObjectIDs()
	{
		std::vector<int> vec;

		for( std::pair<const int, GameObject&>& i : objectMap )
			vec.push_back( i.first );

		return vec; // Returning a copy of the vector
	}

	void UpdateGameObject( GameObject& obj )
	{
		if( obj.type == -1 ) return; // Don't update noObject

		// Save the current position in case we need to go back
		obj.oldPos = obj.pos;
		obj.oldRot = obj.rotation;

		// Move the object according to a very simple physical model
		obj.velocity += obj.acceleration;
		obj.pos += obj.velocity;
		obj.rotation += obj.rotSpeed;

		// Handle the animation frame update
		obj.framePos += obj.animSpeed;
		if( obj.framePos > 1.0f )
		{
			obj.frame++;
			obj.framePos -= 1.0f;
		}
	}

	void DestroyGameObject( int ID )
	{
		if( objectMap.find( ID ) == objectMap.end() )
		{
			PB_ASSERT_MSG( false, "Unable to find object with given ID" );
		}
		else
		{
			GameObject* go = &objectMap.find( ID )->second;
			delete go;
			objectMap.erase( ID );
		}
	}

	void DestroyGameObjectsByType( int objType )
	{
		std::vector<int> typeVec = CollectGameObjectIDsByType( objType );
		for( int i = 1; i < typeVec.size(); i++ )
			DestroyGameObject( typeVec[i] );
	}

	bool IsColliding( GameObject& object1, GameObject& object2 )
	{
		//Don't collide with noObject
		if( object1.type == -1 || object2.type == -1 )
			return false;

		int xDiff = int( object1.pos.x ) - int( object2.pos.x );
		int yDiff = int( object1.pos.y ) - int( object2.pos.y );
		int radii = object2.radius + object1.radius;

		// Game progammers don't do square root!
		return( ( xDiff * xDiff ) + ( yDiff * yDiff ) < radii * radii );
	}

	bool IsVisible( GameObject& obj )
	{
		if( obj.type == -1 ) return false; // Not for noObject

		PlayBlitter& pblt = PlayBlitter::Instance();
		PlayBuffer& pbuf = PlayBuffer::Instance();

		int spriteID = obj.spriteId;
		Vector2f spriteSize = pblt.GetSpriteSize( obj.spriteId );
		Vector2f spriteOrigin = pblt.GetSpriteOrigin( spriteID );

		return( obj.pos.x + spriteSize.width - spriteOrigin.x > 0 && obj.pos.x - spriteOrigin.x < pbuf.GetWidth() &&
			obj.pos.y + spriteSize.height - spriteOrigin.y > 0 && obj.pos.y - spriteOrigin.y < pbuf.GetHeight() );
	}

	bool IsLeavingDisplayArea( GameObject& obj, Direction dirn )
	{
		if( obj.type == -1 ) return false; // Not for noObject

		PlayBuffer& pbuf = PlayBuffer::Instance();
		PlayBlitter& pblt = PlayBlitter::Instance();

		int spriteID = obj.spriteId;
		Vector2f spriteSize = pblt.GetSpriteSize( obj.spriteId );
		Vector2f spriteOrigin = pblt.GetSpriteOrigin( spriteID );

		if( dirn != VERTICAL )
		{
			if( obj.pos.x - spriteOrigin.x < 0 && obj.velocity.x < 0 )
				return true;

			if( obj.pos.x + spriteSize.width - spriteOrigin.x > pbuf.GetWidth() && obj.velocity.x > 0 )
				return true;
		}

		if( dirn != HORIZONTAL )
		{
			if( obj.pos.y - spriteOrigin.y < 0 && obj.velocity.y < 0 )
				return true;

			if( obj.pos.y + spriteSize.height - spriteOrigin.y > pbuf.GetHeight() && obj.velocity.y > 0 )
				return true;
		}

		return false;
	}

	bool IsAnimationComplete( GameObject& obj )
	{
		if( obj.type == -1 ) return false; // Not for noObject
		return obj.frame >= PlayBlitter::Instance().GetSpriteFrames( obj.spriteId ) - 1;
	}

	void SetGameObjectDirection( GameObject& obj, int speed, float angle )
	{
		if( obj.type == -1 ) return; // Not for noObject

		obj.velocity.x = speed * cos( angle );
		obj.velocity.y = speed * sin( angle );
	}

	void PointGameObject( GameObject& obj, int speed, int targetX, int targetY )
	{
		if( obj.type == -1 ) return; // Not for noObject

		float xdiff = obj.pos.x - targetX;
		float ydiff = obj.pos.y - targetY;

		float angle = atan2( ydiff, xdiff ) + 3.14f;

		obj.velocity.x = speed * cos( angle );
		obj.velocity.y = speed * sin( angle );
	}

	void SetSprite( GameObject& obj, const char* spriteName, float animSpeed )
	{
		int newSprite = PlayBlitter::Instance().GetSpriteId( spriteName );
		// Only reset the animation back to the start when it is new
		if( newSprite != obj.spriteId )
			obj.frame = 0;
		obj.spriteId = newSprite;
		obj.animSpeed = animSpeed;
	}

	void DrawObject( GameObject& obj )
	{
		if( obj.type == -1 ) return; // Don't draw noObject
		PlayBlitter::Instance().Draw( obj.spriteId, obj.pos, obj.frame );
	}

	void DrawObjectTransparent( GameObject& obj, float opacity )
	{
		if( obj.type == -1 ) return; // Don't draw noObject
		PlayBlitter::Instance().DrawTransparent( obj.spriteId, obj.pos, obj.frame, opacity );
	}

	void DrawObjectRotated( GameObject& obj, float opacity )
	{
		if( obj.type == -1 ) return; // Don't draw noObject
		PlayBlitter::Instance().DrawRotated( obj.spriteId, obj.pos, obj.frame, obj.rotation, obj.scale, opacity );
	}


	//**************************************************************************************************
	// Miscellaneous functions
	//**************************************************************************************************

	bool KeyPressed( int vKey )
	{
		static std::map< int, bool > keyMap;

		bool& held = keyMap[vKey];

		if( KeyDown( vKey ) && !held )
		{
			held = true;
			return true;
		}

		if( !KeyDown( vKey ) )
			held = false;

		return false;
	}

	bool KeyDown( int vKey )
	{
		return GetAsyncKeyState( vKey ) & 0x8000;
	}

	int RandomRoll( int sides )
	{
		return ( rand() % sides ) + 1;
	}

	int RandomRollRange( int begin, int end )
	{
		int range = abs( end - begin );
		int rnd = ( rand() % ( range + 1 ) );
		if( end > begin )
			return begin + rnd;
		else
			return end + rnd;
	}
}

#endif

//*******************************************************************
// PLAY END: PlayManager.cpp
//*******************************************************************

#endif // PLAY_IMPLEMENTATION
