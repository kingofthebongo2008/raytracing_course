docker run --rm -v %~dp0:C:\tmp -w C:\tmp buildtools2017 msbuild .\build\raytracing_course.sln /p:Configuration=release /p:Platform=x64 /p:_IsNativeEnvironment=true




