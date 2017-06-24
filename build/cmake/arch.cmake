function(raptor_add_arch ARCH SRC_DIR)
  option(BUILD_ARCH_${ARCH} "Build the ${ARCH} architecture" NO)
  if(BUILD_ARCH_${ARCH})
    file(GLOB_RECURSE ARCH_SRC
      "${RAPTOR_DIR}/${SRC_DIR}/*.c"
      "${RAPTOR_DIR}/${SRC_DIR}/*.h"
      "${RAPTOR_DIR}/${SRC_DIR}/*.s"
      "${RAPTOR_DIR}/${SRC_DIR}/*.cpp"
      "${RAPTOR_DIR}/${SRC_DIR}/*.hpp"
    )

    set(KERNEL_NAME "raptor-${ARCH}.bin")
    add_executable(${KERNEL_NAME} ${ARCH_SRC})
    raptor_add_libfuel(${ARCH})
    target_link_libraries(${KERNEL_NAME} fuel-${ARCH})
  endif()
endfunction()

function(raptor_set_arch_cflags ARCH CFLAGS_TO_ADD)
  if(NOT BUILD_ARCH_${ARCH})
    return()
  endif()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CFLAGS_TO_ADD}")
  set(KERNEL_NAME "raptor-${ARCH}.bin")
  set_target_properties(${KERNEL_NAME} PROPERTIES COMPILE_FLAGS ${CFLAGS_TO_ADD})
  set_target_properties(fuel-${ARCH} PROPERTIES COMPILE_FLAGS ${CFLAGS_TO_ADD})
endfunction()

function(raptor_set_arch_ldflags ARCH LDFLAGS_TO_ADD)
  if(NOT BUILD_ARCH_${ARCH})
    return()
  endif()
  set(KERNEL_NAME "raptor-${ARCH}.bin")
  set_target_properties(${KERNEL_NAME} PROPERTIES LINK_FLAGS ${LDFLAGS_TO_ADD})
  set_target_properties(fuel-${ARCH} PROPERTIES LINK_FLAGS ${LDFLAGS_TO_ADD})
endfunction()
