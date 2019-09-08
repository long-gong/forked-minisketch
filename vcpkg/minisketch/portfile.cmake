include(vcpkg_common_functions)

vcpkg_check_linkage(ONLY_STATIC_LIBRARY)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO long-gong/forked-minisketch
    REF 578883fec63e0fe4d04cdac53b98e1c414bb62d2
    SHA512 02b5d08847999932e84abe9a9a6683e6804a3b55dc51c84d5d37e2d4f1f2e2e2e003d423ddbb2645c8ab010f7ab3b57821fde83c37e0978a0c8478bef8be39e2
    HEAD_REF master
)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
)

vcpkg_install_cmake()

file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/minisketch RENAME copyright)