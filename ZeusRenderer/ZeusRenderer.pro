QT += widgets

TARGET = ZeusRenderer

HEADERS += \
    mainwindow.h \
    Renderer/Render/RenderState.h \
    Renderer/Mesh/Mesh.h \
    Renderer/Mesh/Cube.h \
    Renderer/Render/RenderBuffer.h \
    Renderer/Shader/ShaderProgram.h \
    Renderer/Shader/ShaderManager.h \
    Renderer/Render/DrawCall.h \
    Renderer/Mesh/Batch.h \
    Renderer/Material/MaterialManager.h \
    Renderer/Render/StaticDrawcall.h \
    Renderer/Texture/TextureManager.h \
    Renderer/Context.h \
    Renderer/Mesh/Sphere.h \
    Renderer/Mesh/Quad.h \
    Renderer/Render/Render.h \
    Renderer/Texture/FrameTexture2D.h \
    Renderer/Postprocess/FrameBuffer.h \
    Renderer/Shape/AABB.h \
    Renderer/Shape/BoundingBox.h \
    Renderer/Shape/Frustum.h \
    Renderer/Debug/DebugDraw.h \
    Renderer/Debug/DCommon.h \
    Renderer/Debug/Macros.h \
    Renderer/Interactive/Transform3D.h \
    Renderer/Debug/DUpdateEvent.h \
    Renderer/Debug/DVertex.h \
    window.h \
    Renderer/Debug/OpenGLBuffer.h \
    Renderer/Debug/OpenGLCommon.h \
    Renderer/Debug/OpenGLError.h \
    Renderer/Debug/OpenGLFrameResults.h \
    Renderer/Debug/OpenGLFrameTimer.h \
    Renderer/Debug/OpenGLFunctions.h \
    Renderer/Debug/OpenGLFunctions_3_3_core.h \
    Renderer/Debug/OpenGLMarkerResult.h \
    Renderer/Debug/OpenGLMarkerScoped.h \
    Renderer/Debug/OpenGLProfiler.h \
    Renderer/Debug/OpenGLProfilerVisualizer.h \
    Renderer/Debug/OpenGLShaderProgram.h \
    Renderer/Debug/OpenGLVertexArrayObject.h \
    Renderer/Interactive/Camera3D.h \
    Renderer/Interactive/InputManager.h \
    Renderer/OpenGLWidget.h \
    Renderer/Entity/Entity.h \
    Renderer/Entity/StaticEntity.h \
    Renderer/SceneNode/EntityNode.h \
    Renderer/SceneNode/StaticEntityNode.h \
    Renderer/Scene/Scene.h \
    Renderer/Scene/AssetManager.h \
    Renderer/Render/RenderQueue.h \
    Renderer/Mesh/Board.h \
    Renderer/Mesh/Terrain.h \
    Renderer/Interactive/ThirdPersonCamera.h \
    Renderer/Interactive/Player.h \
    Renderer/Loader/mtlloader.h \
    Renderer/Loader/ObjLoader.h \
    Renderer/Mesh/Model.h \
    Renderer/Render/InstanceDrawcall.h \
    Renderer/Mesh/InstanceBatch.h \
    Renderer/Loader/AnimationLoader.h \
    Renderer/Mesh/AnimationBatch.h \
    Renderer/Render/AnimationDrawcall.h \
    Renderer/Entity/AnimationEntity.h \
    Renderer/Entity/BillboardEntity.h \
    Renderer/SceneNode/InstanceEntityNode.h \
    Renderer/SceneNode/AnimationEntityNode.h \
    Renderer/Mesh/Triangle.h \
    Renderer/SceneNode/TerrainEntityNode.h \
    Renderer/Controller/EngineController.h \
    Renderer/Render/RenderManager.h \
    Renderer/Postprocess/Shadow.h \
    Renderer/Postprocess/Filter.h \
    Renderer/Scene/Sky.h \
    Renderer/Lighting/Lighting.h \
    Renderer/Lighting/DirLight.h \
    Renderer/Lighting/PointLight.h \
    Renderer/Postprocess/GaussianBlur.h \
    Renderer/Postprocess/BloomEffect.h

SOURCES += \
    mainwindow.cpp \
    Renderer/Mesh/Mesh.cpp \
    Renderer/Mesh/Cube.cpp \
    Renderer/Render/RenderBuffer.cpp \
    Renderer/Shader/ShaderProgram.cpp \
    Renderer/Shader/ShaderManager.cpp \
    Renderer/Render/DrawCall.cpp \
    Renderer/Mesh/Batch.cpp \
    Renderer/Material/MaterialManager.cpp \
    Renderer/Render/StaticDrawcall.cpp \
    Renderer/Texture/TextureManager.cpp \
    Renderer/Context.cpp \
    Renderer/Mesh/Sphere.cpp \
    Renderer/Mesh/Quad.cpp \
    Renderer/Render/Render.cpp \
    Renderer/Texture/FrameTexture2d.cpp \
    Renderer/Postprocess/FrameBuffer.cpp \
    Renderer/Shape/AABB.cpp \
    Renderer/Shape/BoundingBox.cpp \
    Renderer/Shape/Frustum.cpp \
    Renderer/Interactive/Camera3D.cpp \
    Renderer/Debug/DebugDraw.cpp \
    Renderer/Interactive/Transform3D.cpp \
    Renderer/Debug/DUpdateEvent.cpp \
    main.cpp \
    window.cpp \
    Renderer/Debug/OpenGLError.cpp \
    Renderer/Debug/OpenGLFrameResults.cpp \
    Renderer/Debug/OpenGLFrameTimer.cpp \
    Renderer/Debug/OpenGLMarkerResult.cpp \
    Renderer/Debug/OpenGLProfiler.cpp \
    Renderer/Debug/OpenGLProfilerVisualizer.cpp \
    Renderer/Debug/OpenGLShaderProgram.cpp \
    Renderer/Interactive/InputManager.cpp \
    Renderer/OpenGLWidget.cpp \
    Renderer/Entity/Entity.cpp \
    Renderer/Entity/StaticEntity.cpp \
    Renderer/SceneNode/EntityNode.cpp \
    Renderer/SceneNode/StaticEntityNode.cpp \
    Renderer/Scene/Scene.cpp \
    Renderer/Scene/AssetManager.cpp \
    Renderer/Render/RenderQueue.cpp \
    Renderer/Mesh/Board.cpp \
    Renderer/Mesh/Terrain.cpp \
    Renderer/Interactive/ThirdPersonCamera.cpp \
    Renderer/Interactive/Player.cpp \
    Renderer/Loader/mtlloader.cpp \
    Renderer/Loader/ObjLoader.cpp \
    Renderer/Mesh/Model.cpp \
    Renderer/Render/InstanceDrawcall.cpp \
    Renderer/Mesh/InstanceBatch.cpp \
    Renderer/Loader/AnimationLoader.cpp \
    Renderer/Mesh/AnimationBatch.cpp \
    Renderer/Render/AnimationDrawcall.cpp \
    Renderer/Entity/AnimationEntity.cpp \
    Renderer/Entity/BillboardEntity.cpp \
    Renderer/SceneNode/InstanceEntityNode.cpp \
    Renderer/SceneNode/AnimationEntityNode.cpp \
    Renderer/Mesh/Triangle.cpp \
    Renderer/SceneNode/TerrainEntityNode.cpp \
    Renderer/Controller/EngineController.cpp \
    Renderer/Render/RenderManager.cpp \
    Renderer/Postprocess/Shadow.cpp \
    Renderer/Postprocess/Filter.cpp \
    Renderer/Scene/Sky.cpp \
    Renderer/Lighting/Lighting.cpp \
    Renderer/Lighting/DirLight.cpp \
    Renderer/Lighting/PointLight.cpp \
    Renderer/Postprocess/GaussianBlur.cpp \
    Renderer/Postprocess/BloomEffect.cpp

RESOURCES += \
    resource.qrc

CONFIG += gl_debug
CONFIG += mobility
CONFIG(debug,debug|release) {
  CONFIG(gl_debug) {
      DEFINES += GL_DEBUG
  }
}

FORMS += \
    mainwindow.ui

LIBS += -L$$PWD/Renderer/Dependency/lib/ -llibassimp.dll -llibzlibstatic

INCLUDEPATH += $$PWD/Renderer/Dependency/include
DEPENDPATH += $$PWD/Renderer/Dependency/include
