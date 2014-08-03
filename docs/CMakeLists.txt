if(DOXYGEN_DOT_FOUND)
	set(HAVE_DOT "YES")
else()
	set(HAVE_DOT "NO")
endif(DOXYGEN_DOT_FOUND)

configure_file(
"${PROJECT_SOURCE_DIR}/docs/Doxyfile.in"
"${PROJECT_BINARY_DIR}/docs/Doxyfile" @ONLY)
add_custom_target(docs ALL ${DOXYGEN_EXECUTABLE}
                  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/docs
                  COMMENT "Generating HTML documentation" VERBATIM)