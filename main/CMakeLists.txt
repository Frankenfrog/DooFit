# Executables
add_executable(FitterStd FitterStd.cpp)

# Aliases for module libs
set(CONFIG_LIBS Config)
set(PDF2WS_STD_LIBS Pdf2WsStd)
set(BUILDER_STD_LIBS BuilderStd BuilderStdConfig)



# Linker information
target_link_libraries(FitterStd ${PDF2WS_STD_LIBS} ${CONFIG_LIBS} ${ALL_LIBRARIES})
