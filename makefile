LIBS=-LSFML-2.2/lib -lsfml-window-s -lsfml-system-s -lsfml-graphics-s -lfreetype -lglew -lopenal32 -lopengl32 -lwinmm -lgdi32 -lglew 
DLIBS=-LSFML-2.2/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
INCLUDE=-ISFML-2.2/include
DEF=-DSFML_STATIC
CPPFLAGS=-std=c++11
static:
	g++ $(CPPFLAGS) -c main.cpp $(INCLUDE)
	g++ $(CPPFLAGS) -DSFML_STATIC -o letterfrenzy.exe  $(INCLUDE) main.cpp $(LIBS) 
	
dynamic:
	mingw32-g++ $(CPPFLAGS) -c main.cpp $(INCLUDE)
	mingw32-g++ $(CPPFLAGS) -o letterfrenzy.exe $(INCLUDE) main.o $(DLIBS) 