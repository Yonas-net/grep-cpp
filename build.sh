#!/bin/bash
set -exo pipefail
export PATH="/usr/lib/ccache:$PATH"
rm -rf debug
mkdir debug
cd debug
cmake -GNinja -DCMAKE_BUILD_TYPE=Debug ..
ninja
#ninja install
