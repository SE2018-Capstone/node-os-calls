{
  "targets": [
    {
      "target_name": "node_os_calls",
      "sources": [ "example.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
