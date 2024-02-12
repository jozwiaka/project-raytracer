add_library(HitRecord STATIC HitRecord.cpp )
target_link_libraries(HitRecord PUBLIC exe_flags Math Ray Material)
target_include_directories(
    HitRecord
    INTERFACE "./"
    )