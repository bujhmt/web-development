#!/bin/bash

echo "Building project...."
PUBLIC_URL="/~kp9223/lab4" npm run build

echo "Rsync Project files to server:"
rsync -rv -e "ssh -l kp9223 -p 6022" ./build/ sandbox.ee.kpi.ua:~/public_html/lab4
