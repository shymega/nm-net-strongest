# Copyright 2019-2024 Dom Rodriguez (shymega)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#
# See the License for the specific language governing permissions and
# limitations under the License.

project('nm-conn-strongest',
        'c',
        version: '0.1.0',
        default_options: [
          'c_std=c89'])

project_source_files = [
  'src/main.c',
]

project_dependencies = [
  dependency('glib-2.0'),
  dependency('libnm'),
]

include_dirs = [
  'include/'
]

build_args = [
  '-DPROJECT_NAME=' + meson.project_name(),
  '-DPROJECT_VERSION=' + meson.project_version(),
  '-Wall',
  '-Wextra',
  '-Wunused',
  '-Wconversion',
]

project_target = executable(
  meson.project_name(),
  project_source_files,
  dependencies: project_dependencies,
  include_directories: include_dirs,
  install: true,
  c_args: build_args,
)

test('basic', project_target)
