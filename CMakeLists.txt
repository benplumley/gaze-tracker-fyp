#find_library(MGL mgl PATHS /usr/local/lib)

ADD_EXECUTABLE( GazeTracker GazeTracker.cpp EyeInterface.cpp DataCollector.cpp GazeViewer.cpp helpers2.cpp )
TARGET_LINK_LIBRARIES( GazeTracker ${OpenCV_LIBS} )
#target_link_libraries( GazeTracker  ${MGL})