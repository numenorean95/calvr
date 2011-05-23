MACRO(SETUP_CORE_LIBRARY LIB_NAME)
    ADD_LIBRARY(${LIB_NAME}
        ${CALVR_DYNAMIC_OR_STATIC}
        ${LIB_PUBLIC_HEADERS}
        ${LIB_SRC_FILES}
    )
    IF(LIB_INTERNAL_LIBRARIES)
        LINK_INTERNAL(${LIB_NAME} ${LIB_INTERNAL_LIBRARIES})
    ENDIF(LIB_INTERNAL_LIBRARIES)

    IF(LIB_EXTERNAL_INCLUDES)
        INCLUDE_DIRECTORIES(${LIB_EXTERNAL_INCLUDES})
    ENDIF(LIB_EXTERNAL_INCLUDES)

    IF(LIB_EXTERNAL_LIBRARIES)
        TARGET_LINK_LIBRARIES(${LIB_NAME} ${LIB_EXTERNAL_LIBRARIES})
    ENDIF(LIB_EXTERNAL_LIBRARIES)

    IF(MSVC)
        SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES PREFIX "/")
        FOREACH(CONF ${CMAKE_CONFIGURATION_TYPES})        # For each configuration (Debug, Release, MinSizeRel... and/or anything the user chooses)
            STRING(TOUPPER "${CONF}" CONF)                # Go uppercase (DEBUG, RELEASE...)
            # We use "FILE(TO_CMAKE_PATH", to create nice looking paths
            FILE(TO_CMAKE_PATH "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/" TMPVAR)
            SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES "ARCHIVE_OUTPUT_DIRECTORY_${CONF}" "${TMPVAR}")
            FILE(TO_CMAKE_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/" TMPVAR)
            SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES "RUNTIME_OUTPUT_DIRECTORY_${CONF}" "${TMPVAR}")
            FILE(TO_CMAKE_PATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/" TMPVAR)
            SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES "LIBRARY_OUTPUT_DIRECTORY_${CONF}" "${TMPVAR}")
        ENDFOREACH(CONF ${CMAKE_CONFIGURATION_TYPES})
    ENDIF(MSVC)
    
    INSTALL(TARGETS ${LIB_NAME} DESTINATION lib)

ENDMACRO(SETUP_CORE_LIBRARY LIB_NAME)

MACRO(LINK_INTERNAL TRGTNAME)
    FOREACH(LINKLIB ${ARGN})
        IF(MSVC AND MSVC_VERSIONED_DLL)
            #ADD_DEPENDENCIES(${TRGTNAME} ${LINKLIB})
            #TARGET_LINK_LIBRARIES(${TRGTNAME} ${LINKLIB})
        ELSE(MSVC AND MSVC_VERSIONED_DLL)
        ENDIF(MSVC AND MSVC_VERSIONED_DLL)
    ENDFOREACH(LINKLIB)
ENDMACRO(LINK_INTERNAL TRGTNAME)