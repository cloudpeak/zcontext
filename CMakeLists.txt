# PROJECT: zcontext
cmake_minimum_required(VERSION 2.6)
project(zcontext)

if (MSVC)
    enable_language(CXX ASM_MASM)
else()
    enable_language(CXX ASM)
endif()

set(CMAKE_ASM_MASM_CREATE_STATIC_LIBRARY "<CMAKE_AR> /OUT:<TARGET> <LINK_FLAGS> <OBJECTS>")

if(MSVC AND CMAKE_CL_64 EQUAL 0)
    set(CMAKE_ASM_MASM_FLAGS "${CMAKE_ASM_MASM_FLAGS} /safeseh")
endif()

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_definitions(-DZCONTEXT_EXPORT=)

message("System processor: " ${CMAKE_SYSTEM_PROCESSOR})

if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    set(CPU_ARCH "arm")
elseif (${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64")
    set(CPU_ARCH "arm64")
elseif (${CMAKE_SYSTEM_PROCESSOR} MATCHES "i686")
    set(CPU_ARCH "i386")
elseif (${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64")
    set(CPU_ARCH "x86_64")
elseif (${CMAKE_SYSTEM_PROCESSOR} MATCHES "powerpc" AND CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(CPU_ARCH "powerpc64")
elseif (${CMAKE_SYSTEM_PROCESSOR} MATCHES "powerpc" AND CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(CPU_ARCH "powerpc")
endif()

if(WIN32)
  if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(CPU_ARCH "i386")
  else()
    set(CPU_ARCH "x86_64")
  endif()
endif()

message("Cpu arch: " ${CPU_ARCH})
message("sizeof void p: " ${CMAKE_SIZEOF_VOID_P})

if(WIN32)
  set(ABI ms)
elseif(${CPU_ARCH} STREQUAL "arm")
  set(ABI aapcs)
elseif(${CPU_ARCH} STREQUAL "mips")
  set(ABI o32)
else()
  set(ABI sysv)
endif()
message("ABI: " ${ABI})

if(APPLE)
  set(BINARY_FORMAT "macho")
elseif(WIN32)
  set(BINARY_FORMAT "pe")
else()
  set(BINARY_FORMAT "elf")
endif()
message("Binary format: " ${BINARY_FORMAT})

if(WIN32)
    if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "arm")
        set(ASM "armasm")
        set(EXT_NAME "asm")
    elseif(GNU)
        set(ASM "gas")
        set(EXT_NAME "asm")
    else()
        set(ASM "masm")
        set(EXT_NAME "asm")
    endif()
else()
    set(ASM "gas")
    set(EXT_NAME "S")
endif()
message("asm name: " ${ASM})
message("ext name: " ${EXT_NAME})

message("asm file: make_${CPU_ARCH}_${ABI}_${BINARY_FORMAT}_${ASM}.${EXT_NAME}")
message("asm file: jump_${CPU_ARCH}_${ABI}_${BINARY_FORMAT}_${ASM}.${EXT_NAME}")

set(SOURCES src/asm/make_${CPU_ARCH}_${ABI}_${BINARY_FORMAT}_${ASM}.${EXT_NAME}
            src/asm/jump_${CPU_ARCH}_${ABI}_${BINARY_FORMAT}_${ASM}.${EXT_NAME})


add_library(zcontext STATIC ${SOURCES})


