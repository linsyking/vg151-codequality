#!/bin/bash

ssh ta@111.186.58.48 << EOF
  cd /home/ta/22FA/vg151-codequality
  git pull
  echo "pull done"
  su - root -c "cd /home/ta/22FA/vg151-codequality && cmake --build build --config Release --target codequality && cmake --install build --config Release --target codequality" < ~ta/.p
EOF
