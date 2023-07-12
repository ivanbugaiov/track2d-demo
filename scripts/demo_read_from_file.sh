#!/bin/sh

SCRIPT_DIR="$(dirname $(readlink -f ${0}))"
PROJECT_ROOT="$(readlink -f ${SCRIPT_DIR}/..)"
BUILD_DIR="${PROJECT_ROOT}/build"
RUN_DIR="${PROJECT_ROOT}/build"
BIN_PATH="${BUILD_DIR}/track2d-demo"
ASSET_DIR="${PROJECT_ROOT}/assets"

update_version() {
  cd ${PROJECT_ROOT}
  git pull
  git submodule update --init --recursive
}

build() {
  mkdir -p ${BUILD_DIR}
  cd ${BUILD_DIR}
  cmake -DWITH_TRACK_DISPLAY=On ..
  
  local jN=$(cat /proc/cpuinfo | grep -o 'processor' | wc -l)
  make -j${jN}
}

run_demo() {
  local demo_name="${1}"
  test -f ${BIN_PATH} || { echo "error: demo binary not found"; exit 1; }

  mkdir "${RUN_DIR}/${demo_name}"
  cd "${RUN_DIR}/${demo_name}"
  
  PERIMETER_PATH="${ASSET_DIR}/${demo_name}/perimeter.txt"
  PLOT_PATH="${ASSET_DIR}/${demo_name}/plot.txt"
  ${BIN_PATH} "${PLOT_PATH}" "${PERIMETER_PATH}"
}

echo "##############################"
echo "### update project sources ###"
echo "##############################"
echo ""
#update_version
echo ""

echo "##############################"
echo "######## build project #######"
echo "##############################"
echo ""
build
echo ""

echo "##############################"
echo "########## run demo ##########"
echo "##############################"
echo ""

run_demo 'demo_straight_trajectory'
run_demo 'demo_curving_trajectory'
