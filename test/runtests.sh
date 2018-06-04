#!/bin/bash

# Due to the nature of this test, we have to run this
# twice -- once for the promise interface, and once for
# the stub interface.
#
# In each case, the proxy must be restarted.

DIR=$(cd $(dirname "$0"); pwd)

function gdbus_stub() {
    echo "=== STUB ==="
    pushd stub
    mkdir -p build
    cd build
    cd .. ; rm -rf build ; mkdir build; cd build; cmake .. -DCODEGEN="$DIR/../gdbus-codegen-glibmm.py" -DCMAKE_BUILD_TYPE=Debug
    make
    ./stubtest &
    TEST_PID=$!
    popd
}

function gdbus_promise() {
    echo "=== PROMISE ==="
    pushd promise
    mkdir -p build
    cd build
    cd .. ; rm -rf build ; mkdir build; cd build; cmake .. -DCODEGEN="$DIR/../gdbus-codegen-glibmm.py" -DCMAKE_BUILD_TYPE=Debug
    make
    ./promisetest &
    TEST_PID=$!
    popd
}

function gdbus_proxy() {
    echo "=== PROXY ==="
    pushd proxy
    mkdir -p build
    cd build
    cd .. ; rm -rf build ; mkdir build; cd build; cmake .. -DCODEGEN="$DIR/../gdbus-codegen-glibmm.py" -DCMAKE_BUILD_TYPE=Debug

    make
    ./proxytest&
    PROXY_PID=$!
    popd
}

function test_promise() {
    echo "===*** TESTING PROMISE INTERFACE ***==="
    gdbus_stub
    gdbus_proxy
    sleep 1
    kill $TEST_PID
    kill $PROXY_PID    
}

function test_stub() {
    echo "===*** TESTING STUB INTERFACE ***==="
    gdbus_stub
    gdbus_proxy
    sleep 1
    kill $TEST_PID
    kill $PROXY_PID    
}

test_promise
echo
echo "!!! Please ignore the 'Terminated' messages, as is normal for bash to print when a process is killed."
sleep 2
echo
echo
test_stub
echo
echo "Tests have now concluded."
