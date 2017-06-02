### ImageLoader,Resource,Texture关系

Resource负责根据文件路径或者文件名字找出图片，ImageLoader负责将图片读成bitmap，Texture负责把bitmap封装成Texture

### Shader的作用

OpenGL中渲染跟Shader息息相关，不同的Shader呈现出来不同的渲染管线，展示在屏幕上就是不同的形态。
比方说屏幕上可以有2D的物体，也可以有3D的物体同时存在，原因就是用了两套不同的Shader。
Shader控制整个渲染过程，包括MVP矩阵，还有光照，纹理映射等等。