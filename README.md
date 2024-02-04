
# amgl
**Software (may be CUDA later) OpenGL-like API**

# todo list
#### *Rendering:*
- [ ] *amglClear*
- [ ] amglClearBuffer
  - [ ] *amglClearBufferiv*
  - [ ] *amglClearBufferuiv*
  - [ ] *amglClearBufferfv*
  - [ ] *amglClearBufferfi*
  - [ ] *amglClearNamedFramebufferiv*
  - [ ] *amglClearNamedFramebufferuiv*
  - [ ] *amglClearNamedFramebufferfi*
- [ ] *amglClearColor*
- [ ] *amglClearDepth*
- [ ] *amglClearStencil*
- [ ] amglDrawBuffer
  - [ ] *amglDrawBuffer*
  - [ ] *amglNamedFramebufferDrawBuffer*
- [ ] amglReadBuffer
  - [ ] *amglReadBuffer*
  - [ ] *amglNamedFramebufferReadBuffer*
- [ ] amglReadPixels
  - [ ] *amglReadPixels*
  - [ ] *amglReadnPixels*
  
#### *Buffer Objects:*
- [x] *amglBindBuffer*
- [x] amglBindBufferBase
  - [x] *amglBindBufferBase*
  - [x] *amglBindBuffersBase*
- [x] amglBindBufferRange
  - [x] *amglBindBufferRange*
  - [x] *amglBindBuffersRange*
- [x] amglBufferData
  - [x] *amglBufferData*
  - [x] *amglNamedBufferData*
- [x] amglBufferSubData
  - [x] *amglBufferSubData*
  - [x] *amglNamedBufferSubData*
- [x] amglCopyBufferSubData
  - [x] *amglCopyBufferSubData*
  - [x] *amglCopyNamedBufferSubData*
- [x] *amglDeleteBuffers*
- [x] amglEnableVertexAttrib
  - [x] *amglEnableVertexAttribArray*
  - [x] *amglEnableVertexArrayAttrib*
- [x] amglDisableVertexAttrib
  - [x] *amglDisableVertexAttribArray*
  - [x] *amglDisableVertexArrayAttrib*
- [ ] *amglDrawArrays*
- [ ] *amglDrawArraysIndirect*
- [ ] *amglDrawArraysInstanced*
- [ ] *amglDrawArraysInstancedBaseInstance*
- [ ] *amglDrawElements*
- [ ] *amglDrawElementsBaseVertex*
- [ ] *amglDrawElementsIndirect*
- [ ] *amglDrawElementsInstanced*
- [ ] *amglDrawElementsInstancedBaseInstance*
- [ ] *amglDrawElementsInstancedBaseVertex*
- [ ] *amglDrawElementsInstancedBaseVertexBaseInstance*
- [ ] *amglDrawRangeElements*
- [ ] *amglDrawRangeElementsBaseVertex*
- [x] *amglGenBuffers*
- [ ] amglGetBufferParameter
  - [ ] *amglGetBufferParameteriv*
  - [ ] *amglGetBufferParameteri64v*
  - [ ] *amglGetNamedBufferParameteriv*
  - [ ] *amglGetNamedBufferParameteri64v*
- [x] amglGetBufferSubData
  - [x] *amglGetBufferSubData*
  - [x] *amglGetNamedBufferSubData*
- [ ] amglGetVertexAttrib
  - [ ] *amglGetVertexAttribdv*
  - [ ] *amglGetVertexAttribfv*
  - [ ] *amglGetVertexAttribiv*
  - [ ] *amglGetVertexAttribIiv*
  - [ ] *amglGetVertexAttribIuiv*
  - [ ] *amglGetVertexAttribLdv*
- [x] *amglInvalidateBufferData*
- [x] *amglIsBuffer*
- [x] amglMapBuffer
  - [x] *amglMapBuffer*
  - [x] *amglMapNamedBuffer*
- [ ] amglMapBufferRange
  - [ ] *amglMapBufferRange*
  - [ ] *amglMapNamedBufferRange*
- [ ] *amglMultiDrawArrays*
- [ ] *amglMultiDrawArraysIndirect*
- [ ] *amglMultiDrawElements*
- [ ] *amglMultiDrawElementsBaseVertex*
- [ ] *amglMultiDrawElementsIndirect*
- [ ] *amglProvokingVertex*
- [x] amglUnmapBuffer
  - [x] *amglUnmapBuffer*
  - [x] *amglUnmapNamedBuffer*
- [ ] *amglVertexAttribDivisor*
- [x] amglVertexAttribPointer
  - [x] *amglVertexAttribPointer*
  - [x] *amglVertexAttribIPointer*
  - [x] *amglVertexAttribLPointer*
- [ ] *amglVertexBindingDivisor*

#### *Vertex Array Objects:*
- [x] *amglBindVertexArray*
- [x] *amglDeleteVertexArray*
- [x] *amglGenVertexArray*
- [x] *amglIsVertexArray*

#### *State Management:*
- [ ] *amglBlendColor*
- [ ] *amglBlendEquation*
- [ ] *amglBlendEquation*
- [ ] *amglBlendFunc*
- [ ] *amglBlendFuncSeparate*
- [ ] *amglClampColor*
- [ ] *amglColorMask*
- [ ] *amglCullFace*
- [ ] *amglDepthFunc*
- [ ] *amglDepthMask*
- [ ] *amglDepthRange*
- [ ] *amglEnable*
- [ ] *amglEnablei*
- [ ] *amglDisable*
- [ ] *amglDisablei*
- [ ] *amglFrontFace*
- [ ] amglGet
  - [ ] *amglGetBooleanv*
  - [ ] *amglGetDoublev*
  - [ ] *amglGetFloatv*
  - [ ] *amglGetIntegerv*
  - [ ] *amglGetInteger64v*
  - [ ] *amglGetBooleani_v*
  - [ ] *amglGetIntegeri_v*
  - [ ] *amglGetFloati_v*
  - [ ] *amglGetDoublei_v*
  - [ ] *amglGetInteger64i_v*
- [x] *amglGetError*
- [ ] *amglIsEnabled*
- [ ] *amglLineWidth*
- [ ] *amglLogicOp*
- [ ] *amglPointSize*
- [ ] *amglPolygonMode*
- [ ] *amglPolygonOffset*
- [ ] *amglSampleCoverage*
- [ ] *amglScissor*
- [ ] *amglStencilFunc*
- [ ] *amglStencilFuncSeparate*
- [ ] *amglStencilMask*
- [ ] *amglStencilMaskSeparate*
- [ ] *amglStencilOp*
- [ ] *amglStencilOpSeparate*
- [ ] *amglViewport*

#### *Frame Buffers:*
- [ ] *amglBindFramebuffer*
- [ ] *amglBindRenderbuffer*
- [ ] amglBlitFramebuffer
  - [ ] *amglBlitFramebuffer*
  - [ ] *amglBlitNamedFramebuffer*
- [ ] amglCheckFramebufferStatus
  - [ ] *amglCheckFramebufferStatus*
  - [ ] *amglCheckNamedFramebufferStatus*
- [ ] *amglDeleteFramebuffers*
- [ ] *amglDeleteRenderbuffers*
- [ ] amglDrawBuffers
  - [ ] *amglDrawBuffers*
  - [ ] *amglDrawNamedBuffers*
- [ ] amglFramebufferParameteri
  - [ ] *amglFramebufferParameteri*
  - [ ] *amglNamedFramebufferParameteri*
- [ ] amglFramebufferRenderbuffer
  - [ ] *amglFramebufferRenderbuffer*
  - [ ] *amglNamedFramebufferRenderbuffer*
- [ ] amglFramebufferTexture
  - [ ] *amglFramebufferTexture*
  - [ ] *amglFramebufferTexture1D*
  - [ ] *amglFramebufferTexture2D*
  - [ ] *amglFramebufferTexture3D*
  - [ ] *amglNamedFramebufferTexture*
- [ ] amglFramebufferTextureLayer
  - [ ] *amglFramebufferTextureLayer*
  - [ ] *amglNamedFramebufferTextureLayer*
- [ ] *amglGenFramebuffers*
- [ ] *amglGenRenderbuffers*
- [ ] amglGenerateMipmap
  - [ ] *amglGenerateMipmap*
  - [ ] *amglGenerateTextureMipmap*
- [ ] amglGetFramebufferAttachmentParameter
  - [ ] *amglGetFramebufferAttachmentParameteriv*
  - [ ] *amglGetNamedFramebufferAttachmentParameteriv*
- [ ] amglGetFramebufferParameter
  - [ ] *amglGetFramebufferParameteriv*
  - [ ] *amglGetNamedFramebufferParameteriv*
- [ ] amglGetRenderbufferParameter
  - [ ] *amglGetRenderbufferParameteriv*
  - [ ] *amglGetNamedRenderbufferParameteriv*
- [ ] amglInvalidateFramebuffer
  - [ ] *amglInvalidateFramebuffer*
  - [ ] *amglInvalidateNamedFramebufferData*
- [ ] amglInvalidateSubFramebuffer
  - [ ] *amglInvalidateSubFramebuffer*
  - [ ] *amglInvalidateNamedFramebufferSubData*
- [ ] *amglIsFramebuffer*
- [ ] *amglIsRenderbuffer*
- [ ] amglRenderbufferStorage
  - [ ] *amglRenderbufferStorage*
  - [ ] *amglNamedRenderbufferStorage*
- [ ] amglRenderbufferStorageMultisample
  - [ ] *amglRenderbufferStorageMultisample*
  - [ ] *amglNamedRenderbufferStorageMultisample*
- [ ] *amglSampleMaski*

#### *Textures:*
- [ ] *amglActiveTexture*
- [ ] *amglBindImageTexture*
- [ ] *amglBindImageTextures*
- [ ] *amglBindTexture*
- [ ] *amglBindTextures*
- [ ] *amglClearTexImage*
- [ ] *amglClearTexSubImage*
- [ ] *amglCopyImageSubData*
- [ ] *amglCopyTexImage1D*
- [ ] *amglCopyTexImage2D*
- [ ] amglCopyTexSubImage1D
  - [ ] *amglCopyTexSubImage1D*
  - [ ] *amglCopyTextureSubImage1D*
- [ ] amglCopyTexSubImage2D
  - [ ] *amglCopyTexSubImage2D*
  - [ ] *amglCopyTextureSubImage2D*
- [ ] amglCopyTexSubImage3D
  - [ ] *amglCopyTexSubImage3D*
  - [ ] *amglCopyTextureSubImage3D*
- [ ] *amglDeleteTextures*
- [ ] *amglGenTextures*
- [ ] *amglGenerateMipmap*
- [ ] *amglGenerateTextureMipmap*
- [ ] amglGetTexImage
  - [ ] *amglGetTexImage*
  - [ ] *amglGetnTexImage*
  - [ ] *amglGetTextureImage*
- [ ] amglGetTexLevelParameter
  - [ ] *amglGetTexLevelParameterfv*
  - [ ] *amglGetTexLevelParameteriv*
  - [ ] *amglGetTextureLevelParameterfv*
  - [ ] *amglGetTextureLevelParameteriv*
- [ ] amglGetTexParameter
  - [ ] *amglGetTexParameterfv*
  - [ ] *amglGetTexParameteriv*
  - [ ] *amglGetTexParameterIiv*
  - [ ] *amglGetTexParameterIuiv*
  - [ ] *amglGetTextureParameterfv*
  - [ ] *amglGetTextureParameteriv*
  - [ ] *amglGetTextureParameterIiv*
  - [ ] *amglGetTextureParameterIuiv*
- [ ] *amglGetTextureSubImage*
- [ ] *amglInvalidateTexImage*
- [ ] *amglInvalidateTexSubImage*
- [ ] *amglIsTexture*
- [ ] amglTexBuffer
  - [ ] *amglTexBuffer*
  - [ ] *amglTextureBuffer*
- [ ] amglTexBufferRange
  - [ ] *amglTexBufferRange*
  - [ ] *amglTextureBufferRange*
- [ ] *amglTexImage1D*
- [ ] *amglTexImage2D*
- [ ] *amglTexImage2DMultisample*
- [ ] *amglTexImage3D*
- [ ] *amglTexImage3DMultisample*
- [ ] amglTexParameter
  - [ ] *amglTexParameterf*
  - [ ] *amglTexParameteri*
  - [ ] *amglTextureParameterf*
  - [ ] *amglTextureParameteri*
  - [ ] *amglTexParameterfv*
  - [ ] *amglTexParameteriv*
  - [ ] *amglTexParameterIiv*
  - [ ] *amglTexParameterIuiv*
  - [ ] *amglTextureParameterfv*
  - [ ] *amglTextureParameteriv*
  - [ ] *amglTextureParameterIiv*
  - [ ] *amglTextureParameterIuiv*
- [ ] amglTexStorage1D
  - [ ] *amglTexStorage1D*
  - [ ] *amglTextureStorage1D*
- [ ] amglTexStorage2D
  - [ ] *amglTexStorage2D*
  - [ ] *amglTextureStorage2D*
- [ ] amglTexStorage2DMultisample
  - [ ] *amglTexStorage2DMultisample*
  - [ ] *amglTextureStorage2DMultisample*
- [ ] amglTexStorage3D
  - [ ] *amglTexStorage3D*
  - [ ] *amglTextureStorage3D*
- [ ] amglTexStorage3DMultisample
  - [ ] *amglTexStorage3DMultisample*
  - [ ] *amglTextureStorage3DMultisample*
- [ ] amglTexSubImage1D
  - [ ] *amglTexSubImage1D*
  - [ ] *amglTextureSubImage1D*
- [ ] amglTexSubImage2D
  - [ ] *amglTexSubImage2D*
  - [ ] *amglTextureSubImage2D*
- [ ] amglTexSubImage3D
  - [ ] *amglTexSubImage3D*
  - [ ] *amglTextureSubImage3D*
- [ ] *amglTextureView*

#### *Shaders:*
- [ ] *amglAttachShader*
- [ ] *amglBindAttribLocation*
- [ ] *amglBindFragDataLocation*
- [ ] *amglBindFragDataLocationIndexed*
- [ ] *amglCompileShader*
- [ ] *amglCreateProgram*
- [ ] *amglCreateShader*
- [ ] *amglCreateShaderProgramv*
- [ ] *amglDeleteProgram*
- [ ] *amglDeleteShader*
- [ ] *amglDetachShader*
- [ ] *amglGetActiveAttrib*
- [ ] *amglGetActiveSubroutineName*
- [ ] *amglGetActiveSubroutineUniformiv*
- [ ] *amglGetActiveSubroutineUniformName*
- [ ] *amglGetActiveUniform*
- [ ] *amglGetActiveUniformBlockiv*
- [ ] *amglGetActiveUniformBlockName*
- [ ] *amglGetActiveUniformsiv*
- [ ] *amglGetAttachedShaders*
- [ ] *amglGetAttribLocation*
- [ ] *amglGetFragDataIndexed*
- [ ] *amglGetFragDataLocation*
- [ ] *amglGetProgramiv*
- [ ] *amglGetProgramBinary*
- [ ] *amglGetProgramInfoLog*
- [ ] *amglGetProgramResourceiv*
- [ ] *amglGetProgramResourceIndex*
- [ ] *amglGetProgramResourceLocation*
- [ ] *amglGetProgramResourceLocationIndex*
- [ ] *amglGetProgramResourceName*
- [ ] *amglGetProgramStage*
- [ ] *amglGetShaderiv*
- [ ] *amglGetShaderInfoLog*
- [ ] *amglGetShaderSource*
- [ ] *amglGetSubroutineIndex*
- [ ] *amglGetSubroutineUniformLocation*
- [ ] amglGetUniform
  - [ ] *amglGetUniformfv*
  - [ ] *amglGetUniformiv*
  - [ ] *amglGetUniformuiv*
  - [ ] *amglGetUniformdv*
  - [ ] *amglGetUniformfv*
  - [ ] *amglGetUniformiv*
  - [ ] *amglGetUniformuiv*
  - [ ] *amglGetUniformdv*
- [ ] *amglGetUniformBlockIndex*
- [ ] *amglGetUniformIndices*
- [ ] *amglGetUniformLocation*
- [ ] *amglGetUniformSubroutine*
- [ ] *amglIsProgram*
- [ ] *amglIsShader*
- [ ] *amglLinkProgram*
- [ ] *amglMinSampleShading*
- [ ] *amglProgramBinary*
- [ ] *amglProgramParameteri*
- [ ] amglProgramUniform
  - [ ] *amglProgramUniform1f*
  - [ ] *amglProgramUniform2f*
  - [ ] *amglProgramUniform3f*
  - [ ] *amglProgramUniform4f*
  - [ ] *amglProgramUniform1i*
  - [ ] *amglProgramUniform2i*
  - [ ] *amglProgramUniform3i*
  - [ ] *amglProgramUniform4i*
  - [ ] *amglProgramUniform1ui*
  - [ ] *amglProgramUniform2ui*
  - [ ] *amglProgramUniform3ui*
  - [ ] *amglProgramUniform4ui*
  - [ ] *amglProgramUniform1fv*
  - [ ] *amglProgramUniform2fv*
  - [ ] *amglProgramUniform3fv*
  - [ ] *amglProgramUniform4fv*
  - [ ] *amglProgramUniform1iv*
  - [ ] *amglProgramUniform2iv*
  - [ ] *amglProgramUniform3iv*
  - [ ] *amglProgramUniform3iv*
  - [ ] *amglProgramUniform1uiv*
  - [ ] *amglProgramUniform2uiv*
  - [ ] *amglProgramUniform3uiv*
  - [ ] *amglProgramUniform4uiv*
  - [ ] *amglProgramUniformMatrix2fv*
  - [ ] *amglProgramUniformMatrix3fv*
  - [ ] *amglProgramUniformMatrix4fv*
  - [ ] *amglProgramUniformMatrix2x3fv*
  - [ ] *amglProgramUniformMatrix3x2fv*
  - [ ] *amglProgramUniformMatrix2x4fv*
  - [ ] *amglProgramUniformMatrix4x2fv*
  - [ ] *amglProgramUniformMatrix3x4fv*
  - [ ] *amglProgramUniformMatrix4x3fv*
- [ ] *amglReleaseShaderCompiler*
- [ ] *amglShaderBinary*
- [ ] *amglShaderSource*
- [ ] *amglShaderStorageBlockBinding*
- [ ] amglUniform
  - [ ] *amglUniform1f*
  - [ ] *amglUniform2f*
  - [ ] *amglUniform3f*
  - [ ] *amglUniform4f*
  - [ ] *amglUniform1i*
  - [ ] *amglUniform2i*
  - [ ] *amglUniform3i*
  - [ ] *amglUniform4i*
  - [ ] *amglUniform1ui*
  - [ ] *amglUniform2ui*
  - [ ] *amglUniform3ui*
  - [ ] *amglUniform4ui*
  - [ ] *amglUniform1fv*
  - [ ] *amglUniform2fv*
  - [ ] *amglUniform3fv*
  - [ ] *amglUniform4fv*
  - [ ] *amglUniform1iv*
  - [ ] *amglUniform2iv*
  - [ ] *amglUniform3iv*
  - [ ] *amglUniform3iv*
  - [ ] *amglUniform1uiv*
  - [ ] *amglUniform2uiv*
  - [ ] *amglUniform3uiv*
  - [ ] *amglUniform4uiv*
  - [ ] *amglUniformMatrix2fv*
  - [ ] *amglUniformMatrix3fv*
  - [ ] *amglUniformMatrix4fv*
  - [ ] *amglUniformMatrix2x3fv*
  - [ ] *amglUniformMatrix3x2fv*
  - [ ] *amglUniformMatrix2x4fv*
  - [ ] *amglUniformMatrix4x2fv*
  - [ ] *amglUniformMatrix3x4fv*
  - [ ] *amglUniformMatrix4x3fv*
- [ ] *amglUniformBlockBinding*
- [ ] *amglUniformSubroutines*
- [ ] *amglUseProgram*
- [ ] *amglValidateProgram*

#### *Debug:*
- [ ] *amglDebugMessageCallback*
- [ ] *amglDebugMessageControl*
- [ ] *amglDebugMessageInsert*
- [ ] *amglGetDebugMessageLog*
- [ ] *amglGetObjectLabel*
- [ ] *amglGetObjectPtrLabel*
- [ ] *amglGetPointerv*
- [ ] *amglGetProgramInterfaceiv*
- [ ] *amglObjectLabel*
- [ ] *amglObjectPtrLabel*