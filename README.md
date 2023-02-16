This is a GUI written using the Qt toolkit to make the test more easier.



## Prerequisites：

1. [Eigen3](eigen.tuxfamily.org/index.php?title=Main_Page#Download): download Eigen 3.4.0 from this URL: https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.zip. 

2. [Mosek](https://www.mosek.com/) : We use **mosek** for solving second-order cone program(SOCP). To use mosek, you should approve an academic license in [here](https://www.mosek.com/products/academic-licenses/). The academic license is free and is easy to approve. The license file should be placed inside a folder called "mosek"  under the user's home directory (``$HOME/mosek/mosek.lic`` or  ``%USERPROFILE%\mosek\mosek.lic``). In most typical cases that will be:

   1. ``/home/YOUR_USER_NAME/mosek/mosek.lic``      (Linux)        

   2. ``/Users/YOUR_USER_NAME/mosek/mosek.lic``     (OSX)        

   3. ``C:\Users\YOUR_USER_NAME\mosek\mosek.lic``   (Windows)

   All header and library files are already included in the ``time_optimizer/mosek8_1``  folder under this repo, so you don't need to download mosek again.

# Build

before you build this project, unzip the eigen archive you have downloaded and place it inside the parent directory of this project 

## build in QT Creator

open the ToolBox.pro. Configure project with QT5, then build.

## build with CMake 

If you use CLion, configure the QT toolchain first.

Then configure cmake with the cmake option below:

```bash
-DCMAKE_PREFIX_PATH=E:\YOUR_QT_LOCATION\qt\5.15.2\mingw81_64 
-DCMAKE_PROJECT_INCLUDE_BEFORE=E:\YOUR_QT_LOCATION\qt\qt\Tools\QtCreator\share\qtcreator\package-manager\auto-setup.cmake
```

before run add QT to your path.