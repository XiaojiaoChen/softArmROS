cmake_minimum_required(VERSION 2.8.3)
project(origarm_ros)

## Compile as C++11, supported in ROS Kinetic and newer
 add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED
rospy
roscpp
std_msgs
std_srvs
geometry_msgs
message_generation
urdf
)

find_package(cmake_modules REQUIRED)

find_package(xacro REQUIRED)

find_package(Eigen3 REQUIRED)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a exec_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a exec_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to

##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
add_message_files(FILES
  Command_Position.msg
  Command_ABL.msg
  Command_Pre_Open.msg

  Seg_ABL.msg
  Seg_Pre.msg
  Valve.msg
  SegOpening.msg

  States.msg
  Sensor.msg
  Sensor_Seg.msg
  Sensor_Act.msg
    	
  keynumber.msg
  modenumber.msg
  segnumber.msg
)

## Generate services in the 'srv' folder
add_service_files(FILES
  ik.srv
  feature.srv
)
## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   #   # )

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  geometry_msgs
  std_msgs 
  std_srvs # Or other packages containing msgs
)

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a exec_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
    CATKIN_DEPENDS
  message_runtime
  moveit_core
  moveit_ros_planning_interface
#  INCLUDE_DIRS include
#  LIBRARIES origarm_ros
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

###########
## Build ##
###########

file(GLOB xacro_files model/urdf/origarmRigidKE.urdf.xacro)
xacro_add_files(${xacro_files} TARGET media_files)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include ${catkin_INCLUDE_DIRS}
)

include_directories($EIGEN3_INCLUDE_DIR)
add_definitions(${EIGEN_DEFINITIONS})


## Declare a C++ library
add_library(myPID
  src/myPID.cpp
 )
add_dependencies(myPID ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(myPID
  ${catkin_LIBRARIES}
)

add_library(myFunction
  src/myFunction.cpp
)
add_dependencies(myFunction ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(myFunction
 ${catkin_LIBRARIES}
)
## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
# add_executable(${PROJECT_NAME}_node src/origarm_ros_node.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against


#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
 catkin_install_python(PROGRAMS
   scripts/pythonnodetest.py
   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
 )

## Mark executables for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_executables.html
# install(TARGETS ${PROJECT_NAME}_node
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark libraries for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_libraries.html
 install(TARGETS myFunction
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
 )


## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
 install(FILES
   DIRECTORY include/${PROJECT_NAME}/
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
 )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_origarm_ros.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)


add_executable(State_Estimator
  src/State_Estimator.cpp
)
add_dependencies(State_Estimator ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(State_Estimator
  ${catkin_LIBRARIES} myFunction
)

add_executable(Camera
  src/Camera.cpp
)
add_dependencies(Camera ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(Camera
  ${catkin_LIBRARIES}
)

add_executable(COMMUNICATION_STM
  src/COMMUNICATION_STM.cpp
)
add_dependencies(COMMUNICATION_STM ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(COMMUNICATION_STM
  ${catkin_LIBRARIES}
)

add_executable(Position_controller
  src/Position_controller.cpp
)
add_dependencies(Position_controller ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(Position_controller
  ${catkin_LIBRARIES}
)

add_executable(ABL_controller
  src/ABL_controller.cpp
)
add_dependencies(ABL_controller ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(ABL_controller
  ${catkin_LIBRARIES}
)

#Jing
add_executable(spi_node src/spi_node.cpp)       
add_dependencies(spi_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(spi_node                        
   ${catkin_LIBRARIES}
 )

add_executable(joy_teleopt src/joy_teleopt.cpp) 
add_dependencies(joy_teleopt ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(joy_teleopt             
   ${catkin_LIBRARIES}
 )

add_executable(keyboard src/keyboard.cpp) 
add_dependencies(keyboard ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(keyboard             
   ${catkin_LIBRARIES}
 )

add_executable(demo_abl src/demo_abl.cpp) 
add_dependencies(demo_abl ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(demo_abl             
   ${catkin_LIBRARIES}
 )

add_executable(demo_picknplace src/demo_picknplace.cpp) 
add_dependencies(demo_picknplace ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(demo_picknplace             
   ${catkin_LIBRARIES}
 )

add_executable(demo_xyz src/demo_xyz.cpp) 
add_dependencies(demo_xyz ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(demo_xyz             
   ${catkin_LIBRARIES}
 ) 

add_executable(demo_payload src/demo_payload.cpp) 
add_dependencies(demo_payload ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(demo_payload             
   ${catkin_LIBRARIES}
 )

add_executable(kinematicsEquivalence
  src/kinematicsEquivalence.cpp
)
add_dependencies(kinematicsEquivalence ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(kinematicsEquivalence
  ${catkin_LIBRARIES}
)

add_executable(demo_kinematic_2seg src/demo_kinematic_2seg.cpp) 
add_dependencies(demo_kinematic_2seg ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(demo_kinematic_2seg            
   ${catkin_LIBRARIES}
 )

add_executable(demo_kinematic_3seg src/demo_kinematic_3seg.cpp) 
add_dependencies(demo_kinematic_3seg ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(demo_kinematic_3seg             
   ${catkin_LIBRARIES}
 )

add_executable(demo_trajectory src/demo_trajectory.cpp) 
add_dependencies(demo_trajectory ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(demo_trajectory            
   ${catkin_LIBRARIES}
 )

add_executable(demo_trajectory_regenerate src/demo_trajectory_regenerate.cpp) 
add_dependencies(demo_trajectory_regenerate ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(demo_trajectory_regenerate           
   ${catkin_LIBRARIES}
 )

add_executable(demo_abl_datacollection src/demo_abl_datacollection.cpp) 
add_dependencies(demo_abl_datacollection ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(demo_abl_datacollection           
   ${catkin_LIBRARIES}
 )

add_executable(Kinematics_grids src/Kinematics_grids.cpp) 
add_dependencies(Kinematics_grids ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(Kinematics_grids           
   ${catkin_LIBRARIES}
 )

add_executable(demo_repeatability src/demo_repeatability.cpp) 
add_dependencies(demo_repeatability ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(demo_repeatability           
   ${catkin_LIBRARIES}
 )