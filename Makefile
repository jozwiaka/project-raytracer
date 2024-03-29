download_stb:
	wget https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
	wget https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h
	mv stb_image.h external/stb
	mv stb_image_write.h external/stb
prepare:
	rm -rf build
	mkdir build
conan: prepare
	# pip install conan
	# conan profile detect --force # Let Conan try to guess the profile, based on the current operating system and installed tools
	# cat /root/.conan2/profiles/default || echo "Wrong profile path"
	# conan install ./ --output-folder=build --build=missing -c tools.system.package_manager:mode=install
configure: conan
	cd build && cmake ..
build: configure
	cd build && cmake --build . -j
test: build
	# cd build && make test
run_nogui:
	cd build && ./src/nogui/exe_nogui
run_gui:
	cd build && ./src/gui/exe_gui
callgrind:
	cd build && valgrind --tool=callgrind ./exe_nogui && kcachegrin callgrind.out.*
gui: prepare conan configure build test run_gui
nogui: prepare conan configure build test run_nogui

package: build
	cd build && cpack
install:
	dpkg -i build/raytracer-1.0.0-Linux.deb
run_installed:
	/usr/bin/exe_nogui
uninstall:
	dpkg -r raytracer
