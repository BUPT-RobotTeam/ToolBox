cmake_minimum_required(VERSION 3.16)
project(tool_box VERSION 1.10 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
add_definitions ( -Wall )
#message(DEBUG "1111${PWD}")
set(VT_VERSION  ${PROJECT_VERSION})
set(VT_INTRO_VERSION  1)
add_definitions(
        -DVT_VERSION=${VT_VERSION}
        -DVT_INTRO_VERSION=${VT_INTRO_VERSION}
        -DVER_ORIGINAL
)


#set(CMAKE_PREFIX_PATH ${QTDIR})
set( CMAKE_INCLUDE_CURRENT_DIR ON )

set( CMAKE_AUTOMOC  ON)
set( CMAKE_AUTOUIC  ON)
set( CMAKE_AUTORCC  ON)
include(GNUInstallDirs)
list(APPEND CMAKE_AUTOMOC_MACRO_NAMES "Q_GADGET" "CUSTOM_MACRO")

set( CMAKE_CXX_STANDARD 14 )

set( CMAKE_BUILD_TYPE Debug )

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Charts Gui Network PrintSupport Quick QuickControls2 Widgets LinguistTools)

include_directories(../eigen-3.4.0)

set(
        HEADERS
        bezier.h
        commands.h
        datatypes.h
        digitalfiltering.h
        mainwindow.h
        tcpserversimple.h
        utility.h
        vbytearray.h
        vescinterface.h
        # pages pri
        pages/pageconnection.h
        pages/pagedebugprint.h
        pages/pagewelcome.h
        pages/pagedataanalysis.h
        pages/pagesettings.h
        pages/pageimu.h
        pages/pageserialanalysis.h
        pages/pagepath.h
        pages/pagenone.h
        pages/txtdialog.h
        #widgets.pri
        widgets/displaybar.h
        widgets/displaypercentage.h
        widgets/helpdialog.h
        widgets/pagelistitem.h
        widgets/paramtable.h
        widgets/qcustomplot.h
        widgets/rtdatatext.h
        widgets/nrfpair.h
        widgets/vtextbrowser.h
        widgets/imagewidget.h
        widgets/parameditstring.h
        widgets/aspectimglabel.h
        widgets/historylineedit.h
        widgets/vesc3dview.h
        widgets/superslider.h
        time_optimizer/mosek.h
        time_optimizer/time_optimizer.h
        time_optimizer/timeAllocator.h
        time_optimizer/traj_poly_mono.h
        time_optimizer/trajectory_base.h
        time_optimizer/trajectory_generator.h
        time_optimizer/trajectory_generator_waypoint.h
)

set(
        FORMS
        mainwindow.ui
        #pages.pri
        pages/pageconnection.ui
        pages/pagedebugprint.ui
        pages/pagewelcome.ui
        pages/pagedataanalysis.ui
        pages/pagesettings.ui
        pages/pageimu.ui
        pages/pageserialanalysis.ui
        pages/pagenone.ui
        pages/pagepath.ui
        pages/txtdialog.ui
        #widgets
        widgets/helpdialog.ui
        widgets/nrfpair.ui
        widgets/parameditstring.ui
)

set(
        SOURCES
        main.cpp
        mainwindow.cpp
        packet.cpp
        vbytearray.cpp
        commands.cpp
        vescinterface.cpp
        digitalfiltering.cpp
        utility.cpp
        tcpserversimple.cpp
        bezier.cpp
        #pages.pri
        pages/pageconnection.cpp
        pages/pagedebugprint.cpp
        pages/pagewelcome.cpp
        pages/pagedataanalysis.cpp
        pages/pagesettings.cpp
        pages/pageimu.cpp
        pages/pageserialanalysis.cpp
        pages/pagepath.cpp
        pages/pagenone.cpp
        pages/txtdialog.cpp
        #widgets.pri
        widgets/displaybar.cpp
        widgets/displaypercentage.cpp
        widgets/helpdialog.cpp
        widgets/pagelistitem.cpp
        widgets/qcustomplot.cpp
        widgets/rtdatatext.cpp
        widgets/nrfpair.cpp
        widgets/vtextbrowser.cpp
        widgets/imagewidget.cpp
        widgets/parameditstring.cpp
        widgets/aspectimglabel.cpp
        widgets/historylineedit.cpp
        widgets/vesc3dview.cpp 
        widgets/superslider.cpp

        time_optimizer/time_optimizer.cpp time_optimizer/trajectory_generator.cpp time_optimizer/trajectory_generator_waypoint.cpp
)
option(HAS_SERIALPORT "use serial port" on)

if(HAS_SERIALPORT)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS  serialport)
    add_definitions(-DHAS_SERIALPORT)
endif()




#QT5_WRAP_UI(UIS ${FORMS})

include_directories(./ pages res time_optimizer v-rep widgets)
link_directories( ${PROJECT_SOURCE_DIR}/time_optimizer/mosek8_1 )

set(
        RESOURCES
        res.qrc
)

#QT5_ADD_RESOURCES(RSCS ${RESOURCES})

QT5_ADD_TRANSLATION(TRS res/language/lang_Chinese.ts res/language/lang_English.ts)

add_executable(tool_box_${PROJECT_VERSION}
        ${SOURCES} ${FORMS}  ${RESOURCES} ${TRS} ${HEADERS}
        )
target_link_libraries(${PROJECT_NAME}_${PROJECT_VERSION}
    Qt5::Widgets
    Qt5::Gui
    Qt5::Core
    Qt5::PrintSupport
    Qt5::Charts
    Qt5::Network
    Qt5::Quick
    Qt5::QuickControls2
    Qt5::SerialPort
    mosek64_8_1.lib
        #    Qt5::LinguistTools
)
