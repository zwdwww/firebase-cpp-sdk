# !/bin/bash
#
# Copyright 2020 Google LLC
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
# Builds and runs the tests, meant to be used on a Linux environment.

# Fail on any error.
set -e
# Display commands being run.
set -x

# Make a directory to work in
mkdir -p mac_ios_simulator_build
cd mac_ios_simulator_build

# Configure cmake with tests enabled
# and disable use of libsecret due to not working on kokoro builders
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/ios_simulator.cmake .. -DCLANG_ENABLE_MODULES=YES -DFIREBASE_CPP_BUILD_TESTS=ON -DFIREBASE_FORCE_FAKE_SECURE_STORAGE=ON

# Build the SDK and the tests
cmake --build .

