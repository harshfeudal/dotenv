# 
# Copyright 2025 harshfeudal
# 
# Licensed under MIT License.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# 

cmake_minimum_required(VERSION 3.15)
project(Dotenv VERSION 2.0.0 DESCRIPTION "A simple C++ dotenv file reader for reading .env file in simplest way")

aux_source_directory(test mainsrc)
add_executable(${PROJECT_NAME} ${mainsrc})

target_include_directories(${PROJECT_NAME} PRIVATE "include")

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Copy .env file
# Verify .env exists before copying
if(EXISTS "${CMAKE_SOURCE_DIR}/.env")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/.env" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/.env"
        COMMENT "Copying .env file to output directory"
    )
else()
    message(WARNING ".env file not found in source directory")
endif()
