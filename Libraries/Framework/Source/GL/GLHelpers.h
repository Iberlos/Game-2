#ifndef __GLHelpers_H__
#define __GLHelpers_H__

void CheckForGLErrors();

GLuint LoadTexture(const char* filename, unsigned int* outWidth = nullptr, unsigned int* outHeight = nullptr);
GLuint LoadTextureCubemap(const char** filenames);
void Flip32BitImageVertically(unsigned char* buffer, unsigned int width, unsigned int height);

#endif //__GLHelpers_H__
