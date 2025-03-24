#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <d3d11.h>

struct ImageData
{
    ID3D11ShaderResourceView *texture;
    int width;
    int height;
};

#endif // IMAGEDATA_H