#ifndef GLAD_GLAD_H_
#define GLAD_GLAD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

#ifndef GLAPI
#define GLAPI extern
#endif

#ifndef APIENTRY
#define APIENTRY
#endif

#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

#ifndef __gl_h_
#define __gl_h_
#endif

typedef void (*GLADapiproc)(void);
typedef GLADapiproc (*GLADloadproc)(const char *name);

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef int8_t GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef uint8_t GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef char GLchar;
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;

#define GL_FALSE 0
#define GL_TRUE 1
#define GL_POINTS 0x0000
#define GL_LINES 0x0001
#define GL_TRIANGLES 0x0004
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_UNSIGNED_BYTE 0x1401
#define GL_UNSIGNED_INT 0x1405
#define GL_FLOAT 0x1406
#define GL_DEPTH_TEST 0x0B71
#define GL_BLEND 0x0BE2
#define GL_CULL_FACE 0x0B44
#define GL_SRC_ALPHA 0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_ONE 1
#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_STATIC_DRAW 0x88E4
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_LINEAR 0x2601
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_RGB 0x1907
#define GL_RGBA 0x1908
#define GL_FRAMEBUFFER 0x8D40
#define GL_RENDERBUFFER 0x8D41
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_DEPTH_STENCIL_ATTACHMENT 0x821A
#define GL_DEPTH24_STENCIL8 0x88F0
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#define GL_PROGRAM_POINT_SIZE 0x8642

typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC)(GLenum texture);
typedef void (APIENTRYP PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
typedef void (APIENTRYP PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
typedef void (APIENTRYP PFNGLBINDFRAMEBUFFERPROC)(GLenum target, GLuint framebuffer);
typedef void (APIENTRYP PFNGLBINDRENDERBUFFERPROC)(GLenum target, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLBINDTEXTUREPROC)(GLenum target, GLuint texture);
typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC)(GLuint array);
typedef void (APIENTRYP PFNGLBLENDFUNCPROC)(GLenum sfactor, GLenum dfactor);
typedef void (APIENTRYP PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
typedef GLenum (APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC)(GLenum target);
typedef void (APIENTRYP PFNGLCLEARPROC)(GLbitfield mask);
typedef void (APIENTRYP PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRYP PFNGLCOMPILESHADERPROC)(GLuint shader);
typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC)(void);
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC)(GLenum type);
typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint *buffers);
typedef void (APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC)(GLsizei n, const GLuint *framebuffers);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC)(GLuint program);
typedef void (APIENTRYP PFNGLDELETERENDERBUFFERSPROC)(GLsizei n, const GLuint *renderbuffers);
typedef void (APIENTRYP PFNGLDELETESHADERPROC)(GLuint shader);
typedef void (APIENTRYP PFNGLDELETETEXTURESPROC)(GLsizei n, const GLuint *textures);
typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint *arrays);
typedef void (APIENTRYP PFNGLDEPTHMASKPROC)(GLboolean flag);
typedef void (APIENTRYP PFNGLDISABLEPROC)(GLenum cap);
typedef void (APIENTRYP PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);
typedef void (APIENTRYP PFNGLDRAWELEMENTSPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices);
typedef void (APIENTRYP PFNGLENABLEPROC)(GLenum cap);
typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef void (APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLGENBUFFERSPROC)(GLsizei n, GLuint *buffers);
typedef void (APIENTRYP PFNGLGENFRAMEBUFFERSPROC)(GLsizei n, GLuint *framebuffers);
typedef void (APIENTRYP PFNGLGENRENDERBUFFERSPROC)(GLsizei n, GLuint *renderbuffers);
typedef void (APIENTRYP PFNGLGENTEXTURESPROC)(GLsizei n, GLuint *textures);
typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint *arrays);
typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRYP PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint *params);
typedef GLint (APIENTRYP PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLLINKPROGRAMPROC)(GLuint program);
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length);
typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLUNIFORM1FPROC)(GLint location, GLfloat v0);
typedef void (APIENTRYP PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
typedef void (APIENTRYP PFNGLUNIFORM2FPROC)(GLint location, GLfloat v0, GLfloat v1);
typedef void (APIENTRYP PFNGLUNIFORM3FVPROC)(GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUSEPROGRAMPROC)(GLuint program);
typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
typedef void (APIENTRYP PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);

GLAPI PFNGLACTIVETEXTUREPROC glad_glActiveTexture;
GLAPI PFNGLATTACHSHADERPROC glad_glAttachShader;
GLAPI PFNGLBINDBUFFERPROC glad_glBindBuffer;
GLAPI PFNGLBINDFRAMEBUFFERPROC glad_glBindFramebuffer;
GLAPI PFNGLBINDRENDERBUFFERPROC glad_glBindRenderbuffer;
GLAPI PFNGLBINDTEXTUREPROC glad_glBindTexture;
GLAPI PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray;
GLAPI PFNGLBLENDFUNCPROC glad_glBlendFunc;
GLAPI PFNGLBUFFERDATAPROC glad_glBufferData;
GLAPI PFNGLBUFFERSUBDATAPROC glad_glBufferSubData;
GLAPI PFNGLCHECKFRAMEBUFFERSTATUSPROC glad_glCheckFramebufferStatus;
GLAPI PFNGLCLEARPROC glad_glClear;
GLAPI PFNGLCLEARCOLORPROC glad_glClearColor;
GLAPI PFNGLCOMPILESHADERPROC glad_glCompileShader;
GLAPI PFNGLCREATEPROGRAMPROC glad_glCreateProgram;
GLAPI PFNGLCREATESHADERPROC glad_glCreateShader;
GLAPI PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers;
GLAPI PFNGLDELETEFRAMEBUFFERSPROC glad_glDeleteFramebuffers;
GLAPI PFNGLDELETEPROGRAMPROC glad_glDeleteProgram;
GLAPI PFNGLDELETERENDERBUFFERSPROC glad_glDeleteRenderbuffers;
GLAPI PFNGLDELETESHADERPROC glad_glDeleteShader;
GLAPI PFNGLDELETETEXTURESPROC glad_glDeleteTextures;
GLAPI PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays;
GLAPI PFNGLDEPTHMASKPROC glad_glDepthMask;
GLAPI PFNGLDISABLEPROC glad_glDisable;
GLAPI PFNGLDRAWARRAYSPROC glad_glDrawArrays;
GLAPI PFNGLDRAWELEMENTSPROC glad_glDrawElements;
GLAPI PFNGLENABLEPROC glad_glEnable;
GLAPI PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray;
GLAPI PFNGLFRAMEBUFFERRENDERBUFFERPROC glad_glFramebufferRenderbuffer;
GLAPI PFNGLFRAMEBUFFERTEXTURE2DPROC glad_glFramebufferTexture2D;
GLAPI PFNGLGENBUFFERSPROC glad_glGenBuffers;
GLAPI PFNGLGENFRAMEBUFFERSPROC glad_glGenFramebuffers;
GLAPI PFNGLGENRENDERBUFFERSPROC glad_glGenRenderbuffers;
GLAPI PFNGLGENTEXTURESPROC glad_glGenTextures;
GLAPI PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays;
GLAPI PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog;
GLAPI PFNGLGETPROGRAMIVPROC glad_glGetProgramiv;
GLAPI PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog;
GLAPI PFNGLGETSHADERIVPROC glad_glGetShaderiv;
GLAPI PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation;
GLAPI PFNGLLINKPROGRAMPROC glad_glLinkProgram;
GLAPI PFNGLRENDERBUFFERSTORAGEPROC glad_glRenderbufferStorage;
GLAPI PFNGLSHADERSOURCEPROC glad_glShaderSource;
GLAPI PFNGLTEXIMAGE2DPROC glad_glTexImage2D;
GLAPI PFNGLTEXPARAMETERIPROC glad_glTexParameteri;
GLAPI PFNGLUNIFORM1FPROC glad_glUniform1f;
GLAPI PFNGLUNIFORM1IPROC glad_glUniform1i;
GLAPI PFNGLUNIFORM2FPROC glad_glUniform2f;
GLAPI PFNGLUNIFORM3FVPROC glad_glUniform3fv;
GLAPI PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv;
GLAPI PFNGLUSEPROGRAMPROC glad_glUseProgram;
GLAPI PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer;
GLAPI PFNGLVIEWPORTPROC glad_glViewport;

#define glActiveTexture glad_glActiveTexture
#define glAttachShader glad_glAttachShader
#define glBindBuffer glad_glBindBuffer
#define glBindFramebuffer glad_glBindFramebuffer
#define glBindRenderbuffer glad_glBindRenderbuffer
#define glBindTexture glad_glBindTexture
#define glBindVertexArray glad_glBindVertexArray
#define glBlendFunc glad_glBlendFunc
#define glBufferData glad_glBufferData
#define glBufferSubData glad_glBufferSubData
#define glCheckFramebufferStatus glad_glCheckFramebufferStatus
#define glClear glad_glClear
#define glClearColor glad_glClearColor
#define glCompileShader glad_glCompileShader
#define glCreateProgram glad_glCreateProgram
#define glCreateShader glad_glCreateShader
#define glDeleteBuffers glad_glDeleteBuffers
#define glDeleteFramebuffers glad_glDeleteFramebuffers
#define glDeleteProgram glad_glDeleteProgram
#define glDeleteRenderbuffers glad_glDeleteRenderbuffers
#define glDeleteShader glad_glDeleteShader
#define glDeleteTextures glad_glDeleteTextures
#define glDeleteVertexArrays glad_glDeleteVertexArrays
#define glDepthMask glad_glDepthMask
#define glDisable glad_glDisable
#define glDrawArrays glad_glDrawArrays
#define glDrawElements glad_glDrawElements
#define glEnable glad_glEnable
#define glEnableVertexAttribArray glad_glEnableVertexAttribArray
#define glFramebufferRenderbuffer glad_glFramebufferRenderbuffer
#define glFramebufferTexture2D glad_glFramebufferTexture2D
#define glGenBuffers glad_glGenBuffers
#define glGenFramebuffers glad_glGenFramebuffers
#define glGenRenderbuffers glad_glGenRenderbuffers
#define glGenTextures glad_glGenTextures
#define glGenVertexArrays glad_glGenVertexArrays
#define glGetProgramInfoLog glad_glGetProgramInfoLog
#define glGetProgramiv glad_glGetProgramiv
#define glGetShaderInfoLog glad_glGetShaderInfoLog
#define glGetShaderiv glad_glGetShaderiv
#define glGetUniformLocation glad_glGetUniformLocation
#define glLinkProgram glad_glLinkProgram
#define glRenderbufferStorage glad_glRenderbufferStorage
#define glShaderSource glad_glShaderSource
#define glTexImage2D glad_glTexImage2D
#define glTexParameteri glad_glTexParameteri
#define glUniform1f glad_glUniform1f
#define glUniform1i glad_glUniform1i
#define glUniform2f glad_glUniform2f
#define glUniform3fv glad_glUniform3fv
#define glUniformMatrix4fv glad_glUniformMatrix4fv
#define glUseProgram glad_glUseProgram
#define glVertexAttribPointer glad_glVertexAttribPointer
#define glViewport glad_glViewport

int gladLoadGLLoader(GLADloadproc load);

#ifdef __cplusplus
}
#endif

#endif
