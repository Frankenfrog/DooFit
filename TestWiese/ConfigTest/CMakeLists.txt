
#root_generate_dictionaries(ConfigTestDict ConfigTest.h)
#${ConfigTestDict}
add_library(ConfigTest ConfigTest.cpp ConfigTest.h)

add_executable(TestConfig ConfigTestMain.cpp)

target_link_libraries(TestConfig ConfigTest Config Pdf2WsStd ${ALL_LIBRARIES}) 

