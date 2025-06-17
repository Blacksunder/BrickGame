Requirements for installation and playing:
	For qt projects you need to install two main packages:
		Qt framework:
		- for Ubuntu: sudo apt install qt6-base-dev
		- for MacOS: brew install qt
		CMake utility:
		- for Ubuntu: sudo apt install cmake
		- for MacOS: brew install cmake
	For console projects you need to install ncurses library.
	Also you will need a g++ compiler for all projects.

Requirements for test:
	There's a "test" target in the Makefile,
	to run it successfully your PC must have an installed Gtest library.
	Also for a target "coverage" in the same project you need to have "gcov" and "lcov" utilities

Requirements for dist and dvi:
	The Makefile has targets "dvi" and "dist". To use them you are to have "textlive" and "doxygen" utilities (for "dvi")
	and "tar" (for "dist")

Common information:
	Every game has their own control buttons, game states and rules.
	All of them are discribed in the info folder, which you can open mannualy or by using the "dvi" target.
	Imaginations of State Machines for each game you can also find in the info folder.

	If the installation failed due to lack of required utilities on you device, the best way to fix it: 
	1) Install necessary packages.
	2) Run Makefile again.
	3) If all requirements are fulfilled the installation must go successfully.
