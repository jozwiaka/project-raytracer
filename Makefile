download_stb:
	wget https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
	wget https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h
	mv stb_image.h external/stb
	mv stb_image_write.h external/stb

prepare:
	rm -rf build
	mkdir build
conan: prepare
	pip install conan
	conan profile detect --force # Let Conan try to guess the profile, based on the current operating system and installed tools
	cat /root/.conan2/profiles/default || echo "Wrong profile path"
	conan install ./ --output-folder=build --build=missing -c tools.system.package_manager:mode=install
configure: conan
	cd build && cmake ..
build: configure
	# cd build && cmake --build . -v
	cd build && cmake --build .
test: build
	# cd build && make test
run:
	cd build && ./src/exe
callgrind:
	cd build && valgrind --tool=callgrind ./exe && kcachegrin callgrind.out.*
all: prepare conan configure build test run