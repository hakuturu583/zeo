cmake_minimum_required(VERSION 2.8.12)
project(zeo)

find_package(zeda REQUIRED)
find_package(zm REQUIRED)

add_definitions("-Wall -g -O3")

include_directories(include)

# Build
add_library(${PROJECT_NAME} SHARED
    src/zeo_color.c
    src/zeo_optic.c
    src/zeo_misc.c
    src/zeo_vec2d.c
    src/zeo_mat2d.c
    src/zeo_vec3d.c
    src/zeo_vec6d.c
    src/zeo_mat3d.c
    src/zeo_mat6d.c
    src/zeo_vec3d_list.c
    src/zeo_vec3d_tree.c
    src/zeo_vec3d_pca.c
    src/zeo_ep.c
    src/zeo_frame.c
    src/zeo_pointcloud.c
    src/zeo_elem.c
    src/zeo_elem_list.c
    src/zeo_ph.c
    src/zeo_nurbs.c
    src/zeo_prim_box.c
    src/zeo_prim_sphere.c
    src/zeo_prim_ellips.c
    src/zeo_prim_cyl.c
    src/zeo_prim_ecyl.c 
    src/zeo_prim_cone.c 
    src/zeo_prim_ph.c
    src/zeo_prim_nurbs.c
    src/zeo_shape.c
    src/zeo_shape_list.c
    src/zeo_mshape.c
    src/zeo_brep.c
    src/zeo_brep_trunc.c
    src/zeo_brep_bool.c
    src/zeo_bv_ch2.c
    src/zeo_bv_aabb.c
    src/zeo_bv_obb.c
    src/zeo_bv_bball.c
    src/zeo_bv_qhull.c
    src/zeo_col.c
    src/zeo_col_box.c
    src/zeo_col_aabbtree.c
    src/zeo_col_minkowski.c 
    src/zeo_col_gjk.c
    src/zeo_col_mpr.c
    src/zeo_col_ph.c
    src/zeo_terra.c)
target_link_libraries(${PROJECT_NAME} zm zeda)

add_executable(zeo_gjk app/zeo_gjk.c)
target_link_libraries(zeo_gjk ${PROJECT_NAME})

add_executable(zeo_qhull app/zeo_qhull.c)
target_link_libraries(zeo_qhull ${PROJECT_NAME})

#add_executable(zeo_terra app/zeo_terra.c)
#target_link_libraries(zeo_terra ${PROJECT_NAME})

# Install
INSTALL (
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*")

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)

install (TARGETS 
    zeo_gjk
    zeo_qhull
    #zeo_terra
    RUNTIME DESTINATION bin)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-export
    LIBRARY        DESTINATION lib
    INCLUDES       DESTINATION include
    PUBLIC_HEADER  DESTINATION include/${PROJECT_NAME})

install(EXPORT ${PROJECT_NAME}-export
    FILE ${PROJECT_NAME}-config.cmake
    DESTINATION share/cmake/${PROJECT_NAME}
    EXPORT_LINK_INTERFACE_LIBRARIES)