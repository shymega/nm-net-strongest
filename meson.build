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
#  '-Werror',
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
