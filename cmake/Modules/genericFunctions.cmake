################# private functions ##############################################
function (get_os_distro_vendor os_vendor)
    find_program(lsb_release lsb_release)
        execute_process(COMMAND ${lsb_release} -is
                    OUTPUT_VARIABLE lsb_vendor_name
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
                    
    set(${os_vendor} ${lsb_vendor_name} PARENT_SCOPE)
endfunction()

function (convert_version_string_to_list version_string version_list)
    string(REPLACE "." ";" tmp ${${version_string}})
    set(${version_list} ${tmp} PARENT_SCOPE)
endfunction()
################# private functions end #########################################

function (get_boost_python_component_name pythonlib_version component_name)
    get_os_distro_vendor(os_vendor)
    convert_version_string_to_list(${pythonlib_version} version_list)
    list(GET version_list 0 major_version)
    list(GET version_list 1 minor_version)
    string(COMPARE EQUAL "${major_version}" "3" result)
    
    if("${os_vendor}" STREQUAL "Ubuntu")
        if(result)
            set(${component_name} "python-py${major_version}${minor_version}" PARENT_SCOPE)
        else()
            set(${component_name} "python" PARENT_SCOPE)
        endif()
    elseif("${os_vendor}" STREQUAL "openSUSE Tumbleweed")
        set(${component_name} "python${major_version}${minor_version}" PARENT_SCOPE)
    # This is the default on other distros than ubuntu for now. Fix this later as
    # required.
    else()
        if(result)
            set(${component_name} "python${major_version}" PARENT_SCOPE)
        else()
            set(${component_name} "python" PARENT_SCOPE)
        endif()
    endif()
endfunction()

function(get_python_module_install_path python_version_string install_path)
    get_os_distro_vendor(os_vendor)
    convert_version_string_to_list(${python_version_string} version_list)
    list(GET version_list 0 major_version)
    list(GET version_list 1 minor_version)
    
    if(("${os_vendor}" STREQUAL "Ubuntu") AND 
    (("${CMAKE_INSTALL_PREFIX}" STREQUAL "/usr") OR
     ("${CMAKE_INSTALL_PREFIX}" STREQUAL "/usr/local")))
        string(COMPARE EQUAL "${major_version}" "3" result)
        if(result)
            set(${install_path} 
                "lib/python${major_version}/dist-packages" PARENT_SCOPE)
        else()
            set(${install_path} 
                "lib/python${major_version}.${minor_version}/dist-packages" 
                PARENT_SCOPE)
        endif()

    else()
        set(${install_path} 
            "lib/python${major_version}.${minor_version}/site-packages"
            PARENT_SCOPE)
    endif()
    
endfunction()

