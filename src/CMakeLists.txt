PROJECT(app)

ADD_LIBRARY(start start.cpp start.hpp)
ADD_EXECUTABLE(app app.cpp)
ADD_EXECUTABLE(welcome welcome.cpp)
TARGET_LINK_LIBRARIES(app start ${wxWidgets_LIBRARIES})
