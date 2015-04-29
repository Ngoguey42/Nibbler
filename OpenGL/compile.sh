rm -f a.out
clang++ -std=c++14\
	main.cpp Window.cpp \
		-I ~/.brew/include/ \
		-L ~/.brew/lib/ -lglfw3 -framework OpenGL
./a.out
