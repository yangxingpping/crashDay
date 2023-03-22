



set(GIT_WORK_COPY 0)
set(SVN_WORK_COPY 0)
set(_test_ver "NOK")

execute_process(
    COMMAND git ls-remote --get-url
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    OUTPUT_VARIABLE _test_ver
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
if("${_test_ver}" MATCHES ".git")
    set(GIT_WORK_COPY 1)
endif()

execute_process(
    COMMAND svn info
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    OUTPUT_VARIABLE _test_ver
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
if("${_test_ver}" MATCHES "URL")
    set(SVN_WORK_COPY 1)
endif()

if(GIT_WORK_COPY)
    set(BUILD_REVISION_CONTROLLER "GIT")

    execute_process(
        COMMAND git rev-parse --short HEAD
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        OUTPUT_VARIABLE PROJECT_VERSION_PATCH
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
elseif(SVN_WORK_COPY)
    set(BUILD_REVISION_CONTROLLER "SVN")

    execute_process(
        COMMAND svn info -r 'HEAD' | grep Revision | egrep -o "[0-9]+"
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        OUTPUT_VARIABLE PROJECT_VERSION_PATCH
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()

string(TIMESTAMP BUILD_TIMESTAMP)




add_definitions(-DBUILD_REVISION=${BUILD_REVISION})
add_definitions(-DBUILD_REVISION_CONTROLLER=${BUILD_REVISION_CONTROLLER})
add_definitions(-DBUILD_REVISION_BRANCH=${BUILD_REVISION_BRANCH})
add_definitions(-DBUILD_TIMESTAMP=${BUILD_TIMESTAMP})

add_definitions(-DVERSION_MAJOR=${VERSION_MAJOR})
add_definitions(-DVERSION_MINIOR=${VERSION_MINIOR})
add_definitions(-DVERSION_BUGFIX=${VERSION_BUGFIX})
add_definitions(-DVERSION_FULL="${VERSION_MAJOR}.${VERSION_MINIOR}.${VERSION_BUGFIX}")
add_definitions(-DAPP_NAME="${APP_NAME}")
add_definitions(-DFULL_APP_NAME="${APP_NAME} ${VERSION_FULL} r${BUILD_REVISION}")

