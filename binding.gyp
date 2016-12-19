{
  'targets': [
    {
      'target_name': 'node_os_calls',
      'sources': [
        'src/node_module.cc',
        'src/volume.cc',
      ],
      'include_dirs': [
        '<!(node -e "require(\'nan\')")'
      ],
      'conditions': [
        ['OS=="linux"', {
          'defines': [
            'OS_LINUX',
          ],
        }],
        ['OS=="win"', {
          'defines': [
            'OS_WIN',
          ],
        }],
        ['OS=="mac"', {
          'defines': [
            'OS_MAC',
          ],
        }],
      ],
    }
  ]
}
