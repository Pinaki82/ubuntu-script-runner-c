# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(installscriptrunnerTests LANGUAGES C)

# ---- Tests ----

add_executable(installscriptrunner_test source/installscriptrunner_test.c)
target_link_libraries(installscriptrunner_test PRIVATE installscriptrunner_lib)
target_compile_features(installscriptrunner_test PRIVATE c_std_99)

add_test(NAME installscriptrunner_test COMMAND installscriptrunner_test)

# ---- End-of-file commands ----

add_folders(Test)
