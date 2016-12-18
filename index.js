const path = require('path');
// Need path to look like ./build/Release/node_os_calls and work on all systems
module.exports = require("." + path.sep + path.join('build', 'Release', 'node_os_calls'));
