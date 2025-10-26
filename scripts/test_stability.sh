#!/bin/sh
set -e

# Stability test for HCC compiler
# Runs multiple compilation attempts to detect race conditions and crashes

ITERATIONS=${1:-50}
WORKING_DIR="$(cd "$(dirname "$0")/.." && pwd)"
cd "$WORKING_DIR"

# Ensure build exists
if [ ! -f "build/hcc" ]; then
    echo "Error: build/hcc not found. Run ./scripts/build.sh first."
    exit 1
fi

echo "Starting HCC stability test ($ITERATIONS iterations)..."
echo "Working directory: $WORKING_DIR"
echo

success=0
fail=0
failed_attempts=""

for i in $(seq 1 "$ITERATIONS"); do
    timeout 30 ./build/hcc -O -g \
        -fi samples/shaders.c \
        -fo /tmp/hcc_test_$i.spirv \
        -fomc /tmp/hcc_test_$i.h \
        --enable-unordered-swizzling >/dev/null 2>&1
    
    exit_code=$?
    if [ $exit_code -eq 0 ]; then
        success=$((success + 1))
        status="✓"
    else
        fail=$((fail + 1))
        failed_attempts="$failed_attempts $i"
        status="✗"
    fi
    
    # Calculate success rate
    if [ $i -gt 0 ]; then
        rate=$(echo "scale=1; $success * 100 / $i" | bc)
    else
        rate="0.0"
    fi
    
    # Progress indicator
    printf "\r[%3d/%d] %s Success: %3d | Fail: %3d | Rate: %5.1f%%" \
        "$i" "$ITERATIONS" "$status" "$success" "$fail" "$rate"
done

echo
echo

# Cleanup test artifacts
rm -f /tmp/hcc_test_*.spirv /tmp/hcc_test_*.h

# Print results
echo "========================================="
echo "HCC Stability Test Results"
echo "========================================="
echo "Iterations:  $ITERATIONS"
echo "Successes:   $success ($(echo "scale=1; $success * 100 / $ITERATIONS" | bc)%)"
echo "Failures:    $fail ($(echo "scale=1; $fail * 100 / $ITERATIONS" | bc)%)"

if [ $fail -gt 0 ]; then
    echo
    echo "Failed on attempts:$failed_attempts"
    echo "========================================="
    echo "❌ STABILITY TEST FAILED"
    exit 1
else
    echo "========================================="
    echo "✅ STABILITY TEST PASSED"
    exit 0
fi
