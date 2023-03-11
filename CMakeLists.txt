# 
# Copyright 2023 harshfeudal
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License. 
# 

cmake_minimum_required(VERSION 3.15)
project(Dotenv VERSION 1.2.0 DESCRIPTION "A simple C++ dotenv file reader for reading .env file in simplest way")

# Define an INTERFACE library for the header-only library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set properties for the target
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Add test executable target and link against the header-only library
add_executable(test_dotenv test/test.cpp)
target_link_libraries(test_dotenv PRIVATE ${PROJECT_NAME})
