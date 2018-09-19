INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(include)

SET(CML_MAIN_HEADERS
		include/scic/vector.h
)

add_subdirectory(src)

INSTALL(FILES ${CML_MAIN_HEADERS} DESTINATION include/scic)
INSTALL(DIRECTORY include/scic/vector DESTINATION include/scic)
