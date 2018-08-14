@echo off

set header_file_0=raytracing_course_h.msbuild
set cpp_file_0=raytracing_course_cpp.msbuild


echo ^<?xml version="1.0" encoding="utf-8"?^> > %header_file_0%
echo ^<Project DefaultTargets="Build" ToolsVersion="15.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003"^> >> %header_file_0%
echo ^<ItemGroup^> >> %header_file_0%

ucdev_build_file_generator_r.exe --input ..\include\ --mode h >> %header_file_0%
ucdev_build_file_generator_r.exe --input ..\src\raytracing_course\ --mode h >> %header_file_0%


echo ^</ItemGroup^> >> %header_file_0%
echo ^</Project^> >> %header_file_0%

echo ^<?xml version="1.0" encoding="utf-8"?^> > %cpp_file_0%
echo ^<Project DefaultTargets="Build" ToolsVersion="15.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003"^> >> %cpp_file_0%
echo ^<ItemGroup^> >> %cpp_file_0%

ucdev_build_file_generator_r.exe --input ..\src\raytracing_course\ --mode cpp >> %cpp_file_0%

echo ^</ItemGroup^> >> %cpp_file_0%
echo ^</Project^> >> %cpp_file_0%





