mkdir build_win
cd build_win
cmake -D CMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" ..
cd ..

mkdir build_win_release
cd build_win_release
set QTDIR=c:\panter\qt\4.6.3
set PATH=c:\panter\qt\4.6.3\bin;%PATH%
cmake -D CMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" ..
cd ..

@pause