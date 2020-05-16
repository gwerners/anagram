#!/bin/bash
#https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/
#para sair ao acontecer algum erro no script:
set -euo pipefail

#mostrar comandos a medida que executa (apenas para debug)
#set -x

#move para o diretorio do script caso seja executado de outro diretorio:
cd "$(dirname "${0}")"

#salva dir base
ROOT=$(pwd)

function CheckNeeded {
  NEEDED=$(which ${1})
  if [ ! -f "${NEEDED}" ]; then
    echo "You need ${1} to run this script!"
    exit 0
  fi
}
function formatCode {
  set +euo pipefail
  DIFF_COUNT=0
  CLANG_FORMAT_CMD=clang-format-6.0
  FILES=$(find . -path ./build -prune -o -path ./old -prune -o -path ./cpp-taskflow -prune -o -iname "*.c" -o -iname "*.h" -o -iname "*.cpp" -o -iname "*.hpp" -o -iname "*.cc" -o -iname "*.hh" -o -iname "*.c++" -o -iname "*.h++" -iname "*.cxx" -o -iname "*.hxx")

  for f in ${FILES}
  do
    if [ ! -d "${f}" ]; then
      DIFF_FILE="$(${CLANG_FORMAT_CMD} -style=Chromium ${f} | diff -u ${f} -)"
      DIFF_WORDCOUNT="$(echo "${DIFF_FILE}" | wc -w)"
      if [ ${DIFF_WORDCOUNT} -gt 0 ]; then
        echo "FORMAT FIXED:${f}"
        DIFF_COUNT=$((${DIFF_COUNT}+1))
        $(${CLANG_FORMAT_CMD} -style=file -i ${f})
      fi
    fi
  done
  set -euo pipefail
  echo "Code format is ok - count $DIFF_COUNT"
  #exit $DIFF_COUNT
}
CheckNeeded clang-format-6.0 || exit 1
formatCode
