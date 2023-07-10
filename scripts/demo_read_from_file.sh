#!/bin/sh

SCRIPT_DIR="$(dirname $(readlink -f ${0}))"
PROJECT_ROOT="$(readlink -f ${SCRIPT_DIR}/..)"

BUILD_DIR="${PROJECT_ROOT}/build"

update_version() {
  cd ${PROJECT_ROOT}
  git pull
  git submodule update --init --recursive
}

build() {
  mkdir -p ${BUILD_DIR}
  cd ${BUILD_DIR}
  cmake ..
  
  local jN=$(cat /proc/cpuinfo | grep -o 'processor' | wc -l)
  make -j${jN}
}

echo "##############################"
echo "### update project sources ###"
echo "##############################"
echo ""
update_version
echo ""

echo "##############################"
echo "######## build project #######"
echo "##############################"
echo ""
build
echo ""

BIN_PATH="${BUILD_DIR}/track2d-demo"

test -f ${BIN_PATH} || { echo "error: demo binary not found"; exit 1; }

ASSET_DIR="${PROJECT_ROOT}/assets"

PERIMETER_PATH="${ASSET_DIR}/demo_read_from_file/perimeter.txt"
PLOT_PATH="${ASSET_DIR}/demo_read_from_file/plot.txt"

echo "##############################"
echo "########## run demo ##########"
echo "##############################"
echo ""

${BIN_PATH} "${PLOT_PATH}" "${PERIMETER_PATH}"

