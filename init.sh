mkdir -p src/core/{Camera,Image,Materials,Lights,Objects,Renderer,Scene} \
             src/utils/{Math,Utilities} \
             tests
touch src/core/{Camera/Camera.h,Camera/Camera.cpp,Image/Image.h,Image/Image.cpp,Materials/Material.h,Materials/Material.cpp,Lights/Light.h,Lights/Light.cpp,Objects/Object.h,Objects/Object.cpp,Renderer/Renderer.h,Renderer/Renderer.cpp,Scene/Scene.h,Scene/Scene.cpp} \
      src/utils/{Math/Vector.h,Math/Matrix.h,Math/MathUtils.h,Utilities/FileIO.h,Utilities/Random.h} \
      src/main.cpp
touch tests/{test_camera.cpp,test_image.cpp,test_materials.cpp,test_lights.cpp,test_objects.cpp,test_renderer.cpp,test_scene.cpp,test_utils.cpp} \
      CMakeLists.txt README.md
