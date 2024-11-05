# ---------------------------------------------------------------------------------------------------------------------------- #
# 1) check for too many arguments passed to script
if ($args.Count -gt 0)
{
    Write-Output "Error: Too many parameters"
    exit 1
}
# ---------------------------------------------------------------------------------------------------------------------------- #
# 2) search for "CMakeLists.txt" in workspace directory
if (-not(Test-Path -Path "$PSScriptRoot/../CMakeLists.txt"))
{
    Write-Output "Error: Failed to find CMakeLists.txt"
    exit 1
}
# ---------------------------------------------------------------------------------------------------------------------------- #
# 3) configure CMake if "build" folder has not been generated
Set-Location -Path "$PSScriptRoot/.."
if (-not(Test-Path "$PSScriptRoot/../build" -PathType Container))
{
    cmake -S . -B ./build -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
}
# ---------------------------------------------------------------------------------------------------------------------------- #
# 4) finally, build all CMake projects in this workspace directory
cmake --build ./build
# ---------------------------------------------------------------------------------------------------------------------------- #