cmake_minimum_required(VERSION 3.11)
cmake_policy(SET CMP0074 NEW)

project(Minibook VERSION 0.0 LANGUAGES C CXX)

# TODO: Don't link with libpng if the options is OFF.
option(MINIBOOK_USE_LIBPNG "Use libpng to write PNG files." ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/bin)

# TODO: copy dll's to output dir

aux_source_directory(src/ SOURCES)
aux_source_directory(src/Exceptions/ SOURCES)
aux_source_directory(src/Implementations/ SOURCES)
aux_source_directory(src/Streams/ SOURCES)
aux_source_directory(src/Structures/ SOURCES)
add_executable(${PROJECT_NAME} ${SOURCES})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

find_package(Agg REQUIRED)
find_package(Freetype REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(PNG REQUIRED)
find_package(Stb REQUIRED)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE      
        MINIBOOK_USE_LIBPNG=$<BOOL:${MINIBOOK_USE_LIBPNG}>
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        src/
        ${AGG_INCLUDE_DIRS}
        ${FREETYPE_INCLUDE_DIRS}
        ${PNG_INCLUDE_DIR}
        ${Stb_INCLUDE_DIR}
)

target_link_directories(${PROJECT_NAME}
    PRIVATE
        ${AGG_LIBRARY_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${AGG_LIBRARIES}
        ${FREETYPE_LIBRARY}
        ${PNG_LIBRARY}
        nlohmann_json::nlohmann_json
)

if(MSVC)
    target_compile_options(${PROJECT_NAME}
        PRIVATE
            /FAcs
            /GR-
            /MP
            /MT
            /Wall
            /WX
            /wd4003 # not enough actual parameters for macro 'identifier'
            /wd4061 # enumerator 'identifier' in switch of enum 'enumeration' is not explicitly handled by a case label
            /wd4100 # 'identifier' : unreferenced formal parameter
            /wd4242 # 'identifier' : conversion from 'type1' to 'type2', possible loss of data
            /wd4244 # 'conversion' conversion from 'type1' to 'type2', possible loss of data
            /wd4267 # 'var' : conversion from 'size_t' to 'type', possible loss of data
            /wd4365 # 'action' : conversion from 'type_1' to 'type_2', signed/unsigned mismatch
            /wd4514 # 'function' : unreferenced inline function has been removed
            /wd4611 # interaction between '_setjmp' and C++ object destruction is non-portable
            /wd4623 # 'derived class' : default constructor was implicitly defined as deleted because a base class default constructor is inaccessible or deleted
            /wd4625 # 'derived class' : copy constructor was implicitly defined as deleted because a base class copy constructor is inaccessible or deleted
            /wd4626 # 'derived class' : assignment operator was implicitly defined as deleted because a base class assignment operator is inaccessible or deleted
            /wd4668 # 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
            /wd4710 # 'function' : function not inlined
            /wd4711 # function 'function' selected for inline expansion
            /wd4820 # 'bytes' bytes padding added after construct 'member_name'
            /wd4996 # Your code uses a function, class member, variable, or typedef that's marked deprecated
            /wd5026 # 'type': move constructor was implicitly defined as deleted
            /wd5027 # 'type': move assignment operator was implicitly defined as deleted
            /wd5039 # pointer or reference to potentially throwing function passed to extern C function under -EHc. Undefined behavior may occur if this function throws an exception.
            /wd5045 # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified        
            /wd5054 # operator 'operator-name': deprecated between enumerations of different types
            /wd5055 # operator 'operator-name': deprecated between enumerations and floating-point types
    )
endif(MSVC)
