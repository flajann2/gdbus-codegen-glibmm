#!/bin/bash

# Due to the nature of this test, we have to run this
# twice -- once for the promise interface, and once for
# the stub interface.
#
# In each case, the proxy must be restarted.

DIR=$(cd $(dirname "$0"); pwd)

function build_it() {
    rm -rf build
    mkdir -p build
    cd build
    cmake .. -DCODEGEN="$DIR/../gdbus-codegen-glibmm.py" -DCMAKE_BUILD_TYPE=Debug
    make
}

function gdbus_stub() {
    echo "=== STUB ==="
    pushd stub
    build_it
    ./stubtest &
    TEST_PID=$!
    popd
}

function gdbus_promise() {
    echo "=== PROMISE ==="
    pushd promise
    build_it
    ./promisetest &
    TEST_PID=$!
    popd
}

function gdbus_proxy() {
    echo "=== PROXY ==="
    pushd proxy
    build_it
    ./proxytest&
    PROXY_PID=$!
    popd
}

function test_luxpromise() {
    echo "===*** TESTING LuxPromise CLASS ***==="
    pushd luxpromise
    build_it
    ./test_luxpromise
    popd
}

function test_promise() {
    echo "===*** TESTING PROMISE INTERFACE ***==="
    gdbus_promise
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

test_luxpromise

test_promise
echo
echo "!!! Please ignore the 'Terminated' messages, as is normal for bash to print when a process is killed."
sleep 2
echo
echo

test_stub
echo
echo "Tests have now concluded."
echo "!!! Please ignore the 'Terminated' messages, as is normal for bash to print when a process is killed."
