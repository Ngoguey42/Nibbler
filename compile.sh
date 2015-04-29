rm -f a.out

echo "Compiling OpenGL.so"

clang++ -std=c++14 -Wall -Werror -Wextra -O2 -fPIC -shared\
		OpenGL/Window.cpp \
		-I ~/.brew/include/ \
		-I . \
		-L ~/.brew/lib/ -lglfw3 -framework OpenGL\
		        -o OpenGL.so

echo "Compiling a.out"

clang++ -std=c++14 -Wall -Werror -Wextra -O2\
		main.cpp\
		-I .

./a.out
