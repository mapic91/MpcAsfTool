#ifndef JXQYPICTURE_H_INCLUDED
#define JXQYPICTURE_H_INCLUDED

#ifdef BUILDING_DLL
#define JXQYPICTURE_DLL __declspec(dllexport)
#else
#define JXQYPICTURE_DLL __declspec(dllimport)
#endif
#define DLL_CALLCONV __stdcall

typedef unsigned char BYTE,*PBYTE;

#ifdef __cplusplus
extern "C" {
#endif

//读取文件，读取成功返回true
JXQYPICTURE_DLL bool DLL_CALLCONV ReadFile(const char* filePath);
//读取文件后，获得帧数量
JXQYPICTURE_DLL int DLL_CALLCONV GetFrameCount();
//获得文件的画布大小
JXQYPICTURE_DLL int DLL_CALLCONV GetCanvasWidth();
JXQYPICTURE_DLL int DLL_CALLCONV GetCanvasHeight();
//获得帧图像数据，每帧图片得长宽都是画布大小，失败返回NULL
//RGBA,BGRA,RGB为颜色循序
//数据的循序是从左到右，从上到下。
//即：0 1 2 3
//    4 5 6 7
//    . . .
//返回的data不需要时要free()
JXQYPICTURE_DLL PBYTE DLL_CALLCONV GetFrameDataRGBA(int index);
JXQYPICTURE_DLL PBYTE DLL_CALLCONV GetFrameDataBGRA(int index);
JXQYPICTURE_DLL PBYTE DLL_CALLCONV GetFrameDataRGB(int index);
//释放资源，最后不再需要此dll时使用
JXQYPICTURE_DLL void DLL_CALLCONV FreeResource();

#ifdef __cplusplus
}
#endif

#endif // JXQYPICTURE_H_INCLUDED
