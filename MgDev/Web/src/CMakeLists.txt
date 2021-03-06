add_subdirectory(ApacheAgent)
add_subdirectory(WebApp)
add_subdirectory(WebSupport)
add_subdirectory(HttpHandler)
#add_subdirectory(CgiAgent)
add_subdirectory(PhpApi)
if (WITH_JAVA)
    add_subdirectory(JavaApi)
    add_subdirectory(JavaApiEx)
endif (WITH_JAVA)

# Needed for api binding generation
file(COPY "MapGuideApi" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY "WEB-INF" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/localized DESTINATION ${MG_WWWROOT} COMPONENT ${MG_COMPONENT})
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mapadmin DESTINATION ${MG_WWWROOT} COMPONENT ${MG_COMPONENT})

# Stamp actual version to resizableadmin.php
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/mapadmin/resizableadmin.php DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/mapadmin)
execute_process(COMMAND sed -i "s#${MG_VERSION_MAJOR}.${MG_VERSION_MINOR}.0.0#${MG_VERSION_FULL}#g" ${CMAKE_CURRENT_BINARY_DIR}/mapadmin/resizableadmin.php)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/mapadmin/resizableadmin.php DESTINATION ${MG_WWWROOT}/mapadmin COMPONENT ${MG_COMPONENT})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mapagent DESTINATION ${MG_WWWROOT} COMPONENT ${MG_COMPONENT})
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mapviewerphp DESTINATION ${MG_WWWROOT} COMPONENT ${MG_COMPONENT})
if (WITH_JAVA)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mapviewerjava DESTINATION ${MG_WWWROOT} COMPONENT ${MG_COMPONENT})
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/WEB-INF DESTINATION ${MG_WWWROOT} COMPONENT ${MG_COMPONENT})
endif (WITH_JAVA)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/schemareport DESTINATION ${MG_WWWROOT} COMPONENT ${MG_COMPONENT})
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/stdicons DESTINATION ${MG_WWWROOT} COMPONENT ${MG_COMPONENT})
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/viewerfiles DESTINATION ${MG_WWWROOT} COMPONENT ${MG_COMPONENT})
#install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/webconfig.ini DESTINATION ${MG_WWWROOT} COMPONENT ${MG_COMPONENT})
configure_file(${CMAKE_MODULE_PATH}/../configs/webconfig.ini.in ${CMAKE_CURRENT_BINARY_DIR}/webconfig.ini)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/webconfig.ini DESTINATION ${MG_WWWROOT} COMPONENT ${MG_COMPONENT})
install_empty_directory("TempDir" ${MG_WWWROOT})