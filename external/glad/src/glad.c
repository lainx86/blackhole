#include <glad/glad.h>

PFNGLACTIVETEXTUREPROC glad_glActiveTexture = NULL;
PFNGLATTACHSHADERPROC glad_glAttachShader = NULL;
PFNGLBINDBUFFERPROC glad_glBindBuffer = NULL;
PFNGLBINDFRAMEBUFFERPROC glad_glBindFramebuffer = NULL;
PFNGLBINDRENDERBUFFERPROC glad_glBindRenderbuffer = NULL;
PFNGLBINDTEXTUREPROC glad_glBindTexture = NULL;
PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray = NULL;
PFNGLBLENDFUNCPROC glad_glBlendFunc = NULL;
PFNGLBUFFERDATAPROC glad_glBufferData = NULL;
PFNGLBUFFERSUBDATAPROC glad_glBufferSubData = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glad_glCheckFramebufferStatus = NULL;
PFNGLCLEARPROC glad_glClear = NULL;
PFNGLCLEARCOLORPROC glad_glClearColor = NULL;
PFNGLCOMPILESHADERPROC glad_glCompileShader = NULL;
PFNGLCREATEPROGRAMPROC glad_glCreateProgram = NULL;
PFNGLCREATESHADERPROC glad_glCreateShader = NULL;
PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers = NULL;
PFNGLDELETEFRAMEBUFFERSPROC glad_glDeleteFramebuffers = NULL;
PFNGLDELETEPROGRAMPROC glad_glDeleteProgram = NULL;
PFNGLDELETERENDERBUFFERSPROC glad_glDeleteRenderbuffers = NULL;
PFNGLDELETESHADERPROC glad_glDeleteShader = NULL;
PFNGLDELETETEXTURESPROC glad_glDeleteTextures = NULL;
PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays = NULL;
PFNGLDEPTHMASKPROC glad_glDepthMask = NULL;
PFNGLDISABLEPROC glad_glDisable = NULL;
PFNGLDRAWARRAYSPROC glad_glDrawArrays = NULL;
PFNGLDRAWELEMENTSPROC glad_glDrawElements = NULL;
PFNGLENABLEPROC glad_glEnable = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray = NULL;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glad_glFramebufferRenderbuffer = NULL;
PFNGLFRAMEBUFFERTEXTURE2DPROC glad_glFramebufferTexture2D = NULL;
PFNGLGENBUFFERSPROC glad_glGenBuffers = NULL;
PFNGLGENFRAMEBUFFERSPROC glad_glGenFramebuffers = NULL;
PFNGLGENRENDERBUFFERSPROC glad_glGenRenderbuffers = NULL;
PFNGLGENTEXTURESPROC glad_glGenTextures = NULL;
PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays = NULL;
PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog = NULL;
PFNGLGETPROGRAMIVPROC glad_glGetProgramiv = NULL;
PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog = NULL;
PFNGLGETSHADERIVPROC glad_glGetShaderiv = NULL;
PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation = NULL;
PFNGLLINKPROGRAMPROC glad_glLinkProgram = NULL;
PFNGLRENDERBUFFERSTORAGEPROC glad_glRenderbufferStorage = NULL;
PFNGLSHADERSOURCEPROC glad_glShaderSource = NULL;
PFNGLTEXIMAGE2DPROC glad_glTexImage2D = NULL;
PFNGLTEXPARAMETERIPROC glad_glTexParameteri = NULL;
PFNGLUNIFORM1FPROC glad_glUniform1f = NULL;
PFNGLUNIFORM1IPROC glad_glUniform1i = NULL;
PFNGLUNIFORM2FPROC glad_glUniform2f = NULL;
PFNGLUNIFORM3FVPROC glad_glUniform3fv = NULL;
PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv = NULL;
PFNGLUSEPROGRAMPROC glad_glUseProgram = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer = NULL;
PFNGLVIEWPORTPROC glad_glViewport = NULL;

int gladLoadGLLoader(GLADloadproc load)
{
    if (!load) {
        return 0;
    }

    glad_glActiveTexture = (PFNGLACTIVETEXTUREPROC)load("glActiveTexture");
    glad_glAttachShader = (PFNGLATTACHSHADERPROC)load("glAttachShader");
    glad_glBindBuffer = (PFNGLBINDBUFFERPROC)load("glBindBuffer");
    glad_glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)load("glBindFramebuffer");
    glad_glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)load("glBindRenderbuffer");
    glad_glBindTexture = (PFNGLBINDTEXTUREPROC)load("glBindTexture");
    glad_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)load("glBindVertexArray");
    glad_glBlendFunc = (PFNGLBLENDFUNCPROC)load("glBlendFunc");
    glad_glBufferData = (PFNGLBUFFERDATAPROC)load("glBufferData");
    glad_glBufferSubData = (PFNGLBUFFERSUBDATAPROC)load("glBufferSubData");
    glad_glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)load("glCheckFramebufferStatus");
    glad_glClear = (PFNGLCLEARPROC)load("glClear");
    glad_glClearColor = (PFNGLCLEARCOLORPROC)load("glClearColor");
    glad_glCompileShader = (PFNGLCOMPILESHADERPROC)load("glCompileShader");
    glad_glCreateProgram = (PFNGLCREATEPROGRAMPROC)load("glCreateProgram");
    glad_glCreateShader = (PFNGLCREATESHADERPROC)load("glCreateShader");
    glad_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)load("glDeleteBuffers");
    glad_glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)load("glDeleteFramebuffers");
    glad_glDeleteProgram = (PFNGLDELETEPROGRAMPROC)load("glDeleteProgram");
    glad_glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)load("glDeleteRenderbuffers");
    glad_glDeleteShader = (PFNGLDELETESHADERPROC)load("glDeleteShader");
    glad_glDeleteTextures = (PFNGLDELETETEXTURESPROC)load("glDeleteTextures");
    glad_glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)load("glDeleteVertexArrays");
    glad_glDepthMask = (PFNGLDEPTHMASKPROC)load("glDepthMask");
    glad_glDisable = (PFNGLDISABLEPROC)load("glDisable");
    glad_glDrawArrays = (PFNGLDRAWARRAYSPROC)load("glDrawArrays");
    glad_glDrawElements = (PFNGLDRAWELEMENTSPROC)load("glDrawElements");
    glad_glEnable = (PFNGLENABLEPROC)load("glEnable");
    glad_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)load("glEnableVertexAttribArray");
    glad_glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)load("glFramebufferRenderbuffer");
    glad_glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)load("glFramebufferTexture2D");
    glad_glGenBuffers = (PFNGLGENBUFFERSPROC)load("glGenBuffers");
    glad_glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)load("glGenFramebuffers");
    glad_glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)load("glGenRenderbuffers");
    glad_glGenTextures = (PFNGLGENTEXTURESPROC)load("glGenTextures");
    glad_glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)load("glGenVertexArrays");
    glad_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)load("glGetProgramInfoLog");
    glad_glGetProgramiv = (PFNGLGETPROGRAMIVPROC)load("glGetProgramiv");
    glad_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)load("glGetShaderInfoLog");
    glad_glGetShaderiv = (PFNGLGETSHADERIVPROC)load("glGetShaderiv");
    glad_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)load("glGetUniformLocation");
    glad_glLinkProgram = (PFNGLLINKPROGRAMPROC)load("glLinkProgram");
    glad_glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)load("glRenderbufferStorage");
    glad_glShaderSource = (PFNGLSHADERSOURCEPROC)load("glShaderSource");
    glad_glTexImage2D = (PFNGLTEXIMAGE2DPROC)load("glTexImage2D");
    glad_glTexParameteri = (PFNGLTEXPARAMETERIPROC)load("glTexParameteri");
    glad_glUniform1f = (PFNGLUNIFORM1FPROC)load("glUniform1f");
    glad_glUniform1i = (PFNGLUNIFORM1IPROC)load("glUniform1i");
    glad_glUniform2f = (PFNGLUNIFORM2FPROC)load("glUniform2f");
    glad_glUniform3fv = (PFNGLUNIFORM3FVPROC)load("glUniform3fv");
    glad_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)load("glUniformMatrix4fv");
    glad_glUseProgram = (PFNGLUSEPROGRAMPROC)load("glUseProgram");
    glad_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)load("glVertexAttribPointer");
    glad_glViewport = (PFNGLVIEWPORTPROC)load("glViewport");

    return glad_glActiveTexture &&
        glad_glAttachShader &&
        glad_glBindBuffer &&
        glad_glBindFramebuffer &&
        glad_glBindRenderbuffer &&
        glad_glBindTexture &&
        glad_glBindVertexArray &&
        glad_glBlendFunc &&
        glad_glBufferData &&
        glad_glBufferSubData &&
        glad_glCheckFramebufferStatus &&
        glad_glClear &&
        glad_glClearColor &&
        glad_glCompileShader &&
        glad_glCreateProgram &&
        glad_glCreateShader &&
        glad_glDeleteBuffers &&
        glad_glDeleteFramebuffers &&
        glad_glDeleteProgram &&
        glad_glDeleteRenderbuffers &&
        glad_glDeleteShader &&
        glad_glDeleteTextures &&
        glad_glDeleteVertexArrays &&
        glad_glDepthMask &&
        glad_glDisable &&
        glad_glDrawArrays &&
        glad_glDrawElements &&
        glad_glEnable &&
        glad_glEnableVertexAttribArray &&
        glad_glFramebufferRenderbuffer &&
        glad_glFramebufferTexture2D &&
        glad_glGenBuffers &&
        glad_glGenFramebuffers &&
        glad_glGenRenderbuffers &&
        glad_glGenTextures &&
        glad_glGenVertexArrays &&
        glad_glGetProgramInfoLog &&
        glad_glGetProgramiv &&
        glad_glGetShaderInfoLog &&
        glad_glGetShaderiv &&
        glad_glGetUniformLocation &&
        glad_glLinkProgram &&
        glad_glRenderbufferStorage &&
        glad_glShaderSource &&
        glad_glTexImage2D &&
        glad_glTexParameteri &&
        glad_glUniform1f &&
        glad_glUniform1i &&
        glad_glUniform2f &&
        glad_glUniform3fv &&
        glad_glUniformMatrix4fv &&
        glad_glUseProgram &&
        glad_glVertexAttribPointer &&
        glad_glViewport;
}
