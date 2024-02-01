cmake_minimum_required(VERSION 3.10)

#--------------------------------------------------------------------------------------------------
# variables
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROJECT_NAME MetaprogrammingSFINAE)


#--------------------------------------------------------------------------------------------------
# project
project(${PROJECT_NAME})

if (MSVC)
	# enable VS-Solution filters support
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif (MSVC)


#--------------------------------------------------------------------------------------------------
# builds
add_executable(${PROJECT_NAME}
	${SRC_DIR}/main.cpp
)

# properties
set_target_properties(${PROJECT_NAME}
	PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
)


#--------------------------------------------------------------------------------------------------
# compiler settings
if (MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

	add_compile_options("/std:c++latest")
	
	target_compile_options(${PROJECT_NAME} PRIVATE
		/W4
	)
else ()
	target_compile_options(${PROJECT_NAME} PRIVATE
		-std=c++20 -Wall -Wextra -pedantic -Werror
	)
endif (MSVC)


#--------------------------------------------------------------------------------------------------
# deb pkg
if (UNIX)
	install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

	set(CPACK_GENERATOR DEB)

	set(CPACK_PACKAGE_VERSION_MAJOR "1")
	set(CPACK_PACKAGE_VERSION_MINOR "0")
	set(CPACK_PACKAGE_VERSION_PATCH "0")

	set(CPACK_PACKAGE_CONTACT 155024765+ProphetRu@users.noreply.github.com)

	include(CPack)
endif (UNIX)
