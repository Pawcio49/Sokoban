LIBS=-lGL -lglfw -lGLEW
HEADERS=allmodels.h  constants.h  cube.h  lodepng.h  model.h  shaderprogram.h  sphere.h  teapot.h logic/filehandling.h logic/movement.h enumeration/worldElements.h camera/camera.h ViewManaging.h
FILES=cube.cpp  lodepng.cpp  main_file.cpp  model.cpp  shaderprogram.cpp  sphere.cpp  teapot.cpp  torus.cpp logic/filehandling.cpp logic/movement.cpp camera/camera.cpp ViewManaging.cpp

main_file: $(FILES) $(HEADERS)
	g++ -o main_file $(FILES)  $(LIBS) -I.
