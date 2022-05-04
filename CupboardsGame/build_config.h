#pragma once

//#define SFML_STATIC

#ifdef _DEBUG
#ifdef SFML_STATIC
#pragma comment(lib, "sfml-network-s-d.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "sfml-audio-s-d.lib")
#pragma comment(lib, "ogg.lib")
#pragma comment(lib, "vorbis.lib")
#pragma comment(lib, "vorbisfile.lib")
#pragma comment(lib, "vorbisenc.lib")
#pragma comment(lib, "flac.lib")
#pragma comment(lib, "openal32.lib")
#pragma comment(lib, "sfml-graphics-s-d.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "sfml-window-s-d.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "sfml-system-s-d.lib")
#pragma comment(lib, "winmm.lib")
#else // SFML_DYNAMIC
#pragma comment(lib, "sfml-network-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#pragma comment(lib, "openal32.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#endif // SFML_STATIC
#else
#ifdef SFML_STATIC
#pragma comment(lib, "sfml-network-s.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "sfml-audio-s.lib")
#pragma comment(lib, "ogg.lib")
#pragma comment(lib, "vorbis.lib")
#pragma comment(lib, "vorbisfile.lib")
#pragma comment(lib, "vorbisenc.lib")
#pragma comment(lib, "flac.lib")
#pragma comment(lib, "openal32.lib")
#pragma comment(lib, "sfml-graphics-s.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "sfml-window-s.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "sfml-system-s.lib")
#pragma comment(lib, "winmm.lib")
#else // SFML_DYNAMIC
#pragma comment(lib, "sfml-network.lib")
#pragma comment(lib, "sfml-audio.lib")
#pragma comment(lib, "openal32.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-system.lib")
#endif // SFML_STATIC
#endif // SFML_STATIC

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winspool.lib")
#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "odbc32.lib")
#pragma comment(lib, "odbccp32.lib")