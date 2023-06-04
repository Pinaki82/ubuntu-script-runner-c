cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    installscriptrunner
    VERSION 0.1.0
    DESCRIPTION "Ubuntu Linux software Install Script using https://github.com/ryanmjacobs/c"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES C
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare executable ----

add_executable(installscriptrunner_exe source/main.c)
add_executable(installscriptrunner::exe ALIAS installscriptrunner_exe)

set_property(TARGET installscriptrunner_exe PROPERTY OUTPUT_NAME installscriptrunner)

target_compile_features(installscriptrunner_exe PRIVATE c_std_99)

target_link_libraries(installscriptrunner_exe PRIVATE)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT installscriptrunner_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of installscriptrunner"
  )
endif()

include(cmake/dev-mode.cmake)
