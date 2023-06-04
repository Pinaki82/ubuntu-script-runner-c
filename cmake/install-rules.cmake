install(
    TARGETS installscriptrunner_exe
    RUNTIME COMPONENT installscriptrunner_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
