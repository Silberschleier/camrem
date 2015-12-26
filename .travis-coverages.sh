#!/bin/bash

./camrem_unit_tests
./camremd &
sleep 2
pyresttest http://localhost:8888 tests/integration_offline.yml
coveralls -e src/json -e src/easylogging -e tests