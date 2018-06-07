#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H
#include "../Shader/ShaderProgram.h"
#include "../Texture/FrameTexture2D.h"
/*
 * GaussianBlur.h
 *
 * Describe: GaussianBlur post-processing
 *
 * Created on: 2018-6-2
 *      Author: Zeus
 */
class GaussianBlur
{
public:
    GaussianBlur(ShaderProgram *shader);
    ~GaussianBlur();
    void blurProcess(FrameTexture2D *input,FrameTexture2D *output);

private:
    ShaderProgram *blurShader;

};

#endif // GAUSSIANBLUR_H
